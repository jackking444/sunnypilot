"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

import numpy as np
from dataclasses import dataclass

from opendbc.car import structs, DT_CTRL
from opendbc.car.common.filter_simple import FirstOrderFilter

from opendbc.car.hyundai.values import CarControllerParams
from opendbc.sunnypilot.car.hyundai.longitudinal.helpers import get_car_config
from opendbc.sunnypilot.car.hyundai.values import HyundaiFlagsSP

LongCtrlState = structs.CarControl.Actuators.LongControlState


@dataclass
class LongitudinalTuningState:
  accel_last: float = 0.0
  jerk: float = 0.0


class LongitudinalTuningController:
  """Longitudinal tuning methodology for HKG"""

  def __init__(self, CP: structs.CarParams, CP_SP: structs.CarParamsSP) -> None:
    self.CP = CP
    self.CP_SP = CP_SP

    self.state = LongitudinalTuningState()
    self.car_config = get_car_config(CP)
    self.accel_filter = FirstOrderFilter(0.0, 0.25, DT_CTRL * 2)
    self.desired_accel = 0.0
    self.actual_accel = 0.0
    self.jerk_upper = 0.0
    self.jerk_lower = 0.0

  def make_jerk(self, CC: structs.CarControl, CS: structs.CarState, long_control_state: LongCtrlState) -> None:
    if not self.CP_SP.flags & HyundaiFlagsSP.LONG_TUNING_BRAKING:
      jerk_limit = 3.0 if long_control_state == LongCtrlState.pid else 1.0

      self.jerk_upper = jerk_limit
      self.jerk_lower = jerk_limit
      return

    if not CC.enabled:
      self.jerk_upper = 0.0
      self.jerk_lower = 0.0
      return

    # Blend planned acceleration with current acceleration
    planned_accel = CC.actuators.accel
    current_accel = CS.out.aEgo
    blended_accel = 0.8 * planned_accel + 0.2 * current_accel

    # Apply acceleration filter
    prev_filtered_accel = self.accel_filter.x
    self.accel_filter.update(blended_accel)
    filtered_accel = self.accel_filter.x

    # Calculate jerk
    self.state.jerk = (filtered_accel - prev_filtered_accel) / (DT_CTRL * 2)

    # Jerk is limited by the following conditions imposed by ISO 15622:2018
    velocity = CS.out.vEgo
    if velocity < 5.0:
      decel_jerk_max = self.car_config.jerk_limits[1]
      accel_jerk_max = 1.0
    elif velocity > 20.0:
      decel_jerk_max = 2.5
      accel_jerk_max = 1.65
    else:   # Between 5 m/s and 20 m/s
      decel_jerk_max = 5.83 - (velocity/6)
      accel_jerk_max = self.car_config.jerk_limits[2]

    accel_jerk = accel_jerk_max if long_control_state == LongCtrlState.pid else 1.0
    min_upper_jerk = self.car_config.jerk_limits[0] if (velocity > 3.611) else 0.725
    min_lower_jerk = self.car_config.jerk_limits[0] if (velocity < 12.0) else 0.625
    multiplier = 3.0 if self.CP.radarUnavailable else 1.0

    self.jerk_upper = min(max(min_upper_jerk, self.state.jerk), accel_jerk)
    self.jerk_lower = min(max(min_lower_jerk, -self.state.jerk * multiplier), decel_jerk_max)

  def calculate_a_value(self, CC: structs.CarControl) -> None:
    def jerk_limited_integrator():
      if self.desired_accel >= self.actual_accel:
        val = self.jerk_upper * DT_CTRL * 2
      else:
        val = self.jerk_lower * DT_CTRL * 2

      return self.state.accel_last + np.clip(self.desired_accel - self.state.accel_last, -val, val)

    if not self.CP_SP.flags & HyundaiFlagsSP.LONG_TUNING:
      self.desired_accel = CC.actuators.accel
      self.actual_accel = CC.actuators.accel
      return

    if not CC.longActive:
      self.desired_accel = 0.0
      self.actual_accel = 0.0
      self.state.accel_last = 0.0
      return

    # Force zero aReqRaw during StopReq
    if CC.actuators.longControlState == LongCtrlState.stopping:
      self.desired_accel = 0.0
    else:
      self.desired_accel = float(np.clip(CC.actuators.accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))

    self.actual_accel = jerk_limited_integrator()
    self.state.accel_last = self.actual_accel
