from cereal import car
from panda import Panda
from math import exp
from openpilot.common.params import Params
#from openpilot.selfdrive.car import get_safety_config, get_friction
from opendbc.car import get_friction,get_safety_config, structs
from opendbc.car.interfaces import TorqueFromLateralAccelCallbackType, FRICTION_THRESHOLD, LatControlInputs,CarInterfaceBase
from opendbc.car.volkswagen.carcontroller import CarController
from opendbc.car.volkswagen.carstate import CarState
from opendbc.car.volkswagen.values import CAR, NetworkLocation, TransmissionType, VolkswagenFlags, VolkswagenSafetyFlags

NON_LINEAR_TORQUE_PARAMS = {
   CAR.VOLKSWAGEN_SHARAN_MK2: [119.999999999518543, 0.013752973175158755, 0.29000000000000004, -0.007255929913027823, \
                              15.000000000038696, 1.1156542774105294, 0.10000000000000002, 0.9999999999999999]  #khonsu's JSW + back in my day...
 }
NON_LINEAR_TORQUE_PARAMS = {
  CAR.VOLKSWAGEN_SHARAN_MK2: [19.999999999518543, 0.013752973175158755, 0.29000000000000004, -0.007255929913027823, \
                             15.000000000038696, 1.1156542774105294, 0.10000000000000002, 0.9999999999999999]  #khonsu's JSW + back in my day...
}
class CarInterface(CarInterfaceBase):
  def torque_from_lateral_accel_siglin(self, latcontrol_inputs: LatControlInputs, torque_params: car.CarParams.LateralTorqueTuning, lateral_accel_error: float,
                                       lateral_accel_deadzone: float, friction_compensation: bool, gravity_adjusted: bool) -> float:
    friction = get_friction(lateral_accel_error, lateral_accel_deadzone, FRICTION_THRESHOLD, torque_params, friction_compensation)

    def sig(val):
      # https://timvieira.github.io/blog/post/2014/02/11/exp-normalize-trick
      if val >= 0:
        return 1 / (1 + exp(-val)) - 0.5
      else:
        z = exp(val)
        return z / (1 + z) - 0.5

    # The "lat_accel vs torque" relationship is assumed to be the sum of "sigmoid + linear" curves
    # An important thing to consider is that the slope at 0 should be > 0 (ideally >1)
    # This has big effect on the stability about 0 (noise when going straight)
    # ToDo: To generalize to other VWs, explore tanh function as the nonlinear
    non_linear_torque_params = NON_LINEAR_TORQUE_PARAMS.get(self.CP.carFingerprint)
    assert non_linear_torque_params, "The params are not defined"
    a, b, c, _, e, f, g, h = non_linear_torque_params

    speed_factor = (40.23 / (max(1.0, latcontrol_inputs.vego + e))**f)
    speed_factor2 = max(0.2, 40.23 / (max(1.0, latcontrol_inputs.vego + g))**h)
    steer_torque = (sig(latcontrol_inputs.lateral_acceleration * a * speed_factor) * b * speed_factor2) + (latcontrol_inputs.lateral_acceleration * c)

    return float(steer_torque) + friction

  CarState = CarState
  CarController = CarController

  def torque_from_lateral_accel(self) -> TorqueFromLateralAccelCallbackType:
     if self.CP.carFingerprint in NON_LINEAR_TORQUE_PARAMS:
       return self.torque_from_lateral_accel_siglin
     else:
       return self.torque_from_lateral_accel_linear

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate: CAR, fingerprint, car_fw, alpha_long, docs) -> structs.CarParams:
    ret.brand = "volkswagen"
    ret.radarUnavailable = True

    if ret.flags & VolkswagenFlags.PQ:
      # Set global PQ35/PQ46/NMS parameters
      ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.volkswagenPq)]
      ret.enableBsm = 0x3BA in fingerprint[0]  # SWA_1

      if 0x440 in fingerprint[0] or docs:  # Getriebe_1
        ret.transmissionType = TransmissionType.automatic
      else:
        ret.transmissionType = TransmissionType.manual

      if any(msg in fingerprint[1] for msg in (0x1A0, 0xC2)):  # Bremse_1, Lenkwinkel_1
        ret.networkLocation = NetworkLocation.gateway
      else:
        ret.networkLocation = NetworkLocation.fwdCamera

      # The PQ port is in dashcam-only mode due to a fixed six-minute maximum timer on HCA steering. An unsupported
      # EPS flash update to work around this timer, and enable steering down to zero, is available from:
      #   https://github.com/pd0wm/pq-flasher
      # It is documented in a four-part blog series:
      #   https://blog.willemmelching.nl/carhacking/2022/01/02/vw-part1/
      # Panda ALLOW_DEBUG firmware required.
      #ret.dashcamOnly = True

    else:
      # Set global MQB parameters
      ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.volkswagen)]
      ret.enableBsm = 0x30F in fingerprint[0]  # SWA_01

      if 0xAD in fingerprint[0] or docs:  # Getriebe_11
        ret.transmissionType = TransmissionType.automatic
      elif 0x187 in fingerprint[0]:  # Motor_EV_01
        ret.transmissionType = TransmissionType.direct
      else:
        ret.transmissionType = TransmissionType.manual

      if any(msg in fingerprint[1] for msg in (0x40, 0x86, 0xB2, 0xFD)):  # Airbag_01, LWI_01, ESP_19, ESP_21
        ret.networkLocation = NetworkLocation.gateway
      else:
        ret.networkLocation = NetworkLocation.fwdCamera

      if 0x126 in fingerprint[2]:  # HCA_01
        ret.flags |= VolkswagenFlags.STOCK_HCA_PRESENT.value

    # Global lateral tuning defaults, can be overridden per-vehicle

    ret.steerLimitTimer = 0.4
    if ret.flags & VolkswagenFlags.PQ:
      ret.steerActuatorDelay = 0.11
      ret.longitudinalTuning.kf = 1.2
      ret.longitudinalTuning.kpBP = [0.]
      ret.longitudinalTuning.kpV =  [.45]
      ret.longitudinalTuning.kiBP = [0.]
      ret.longitudinalTuning.kiV =  [.69]
      ret.longitudinalActuatorDelay = 0.6
      CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)
    else:
      ret.steerActuatorDelay = 0.1
      ret.lateralTuning.pid.kpBP = [0.]
      ret.lateralTuning.pid.kiBP = [0.]
      ret.lateralTuning.pid.kf = 0.00006
      ret.lateralTuning.pid.kpV = [0.6]
      ret.lateralTuning.pid.kiV = [0.2]

    # Global longitudinal tuning defaults, can be overridden per-vehicle

    ret.alphaLongitudinalAvailable = ret.networkLocation == NetworkLocation.gateway or docs
    if alpha_long:
      # Proof-of-concept, prep for E2E only. No radar points available. Panda ALLOW_DEBUG firmware required.
      ret.openpilotLongitudinalControl = True
      ret.safetyConfigs[0].safetyParam |= VolkswagenSafetyFlags.LONG_CONTROL.value
      if ret.transmissionType == TransmissionType.manual:
        ret.minEnableSpeed = 4.5

    ret.pcmCruise = not ret.openpilotLongitudinalControl
    ret.stopAccel = -0.55
    ret.vEgoStarting = 0.1
    ret.vEgoStopping = 0.5
    ret.autoResumeSng = ret.minEnableSpeed == -1

    return ret
