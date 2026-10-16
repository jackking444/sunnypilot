# Palisade HDA2 steering features design

## Goal

Port the missing Palisade-relevant steering features from
`yufeng66/openpilot:pal23sp-hda2-testing` onto this branch, which is based on
sunnypilot `v2026.10.06-4920`. Preserve the working Palisade 2023 HDA2 port,
its CAN behavior, and Panda safety integration.

## Existing and missing features

The target branch already contains the Lateral Jerk Torque Controller and Road
Edge Lane Change Controller. Keep those implementations and settings as they
are; verify compatibility with the new learner where they interact.

The target branch does not contain the source branch's speed-dependent torque
learner or lane-line centering controller. These are the features to port.

## Speed-dependent torque learning

- Add per-speed-bin learning for lateral acceleration factor and steering
  friction, adapting the source implementation to this branch's
  `TorqueEstimatorExt` and current car-parameter interfaces.
- Include both the regular point-based learner and the experimental
  moment-matrix mode. Keep the latter behind its own explicit setting.
- Require torque lateral control and the speed-dependent setting before
  applying learned speed bins. Keep manual overrides and existing global
  learning behavior intact.
- For unlearned speed ranges, use the nearest learned values with edge-clamped
  interpolation. Keep existing configured per-car speed bins authoritative.
- Add the friction-reduction setting for learned bins only. Do not scale manual
  overrides, configured seeds, or global fallback values.
- Seed the Palisade HDA2 configuration with the source branch's learner-informed
  defaults: lateral acceleration factor 2.61, friction 0.107, and steering
  delay 0.32 seconds. Scope these values to the Palisade configuration; do not
  change other Hyundai platforms.

## Lane-line centering

Add a separate optional controller that applies a small curvature correction
toward the lane center. Default it off. It may act only while lateral control
is active, vehicle speed is at least 5 m/s, lane-change state is inactive, and
both lane boundaries pass confidence, uncertainty, geometry, and width checks.
Bound the correction and smooth its changes. Support an adjustable target
offset, configurable model authority, and gradual release while a blinker is
active. Invalid inputs or disengagement clear or release the correction safely.

## Settings and compatibility

Expose persistent, backed-up parameters in the on-device settings and Sunnylink
schema following the target branch's existing patterns. New features default
off. Prevent conflicting controller modes using the existing Sunnypilot
compatibility behavior; do not enable or reset user settings implicitly.

No Panda firmware, safety-hook, CAN message layout, vehicle fingerprint, or
longitudinal-control changes are in scope. The vehicle continues using its
current longitudinal configuration.

## Verification

- Unit tests cover learner bin selection, learning/validity gates, fallback,
  friction reduction scope, and cache save/restore compatibility.
- Controller tests cover lane-boundary validity, offset bounds, model
  authority, blinker release, lane-change suppression, speed/disengagement
  gates, and finite output.
- Run relevant Palisade Hyundai interface/safety tests and Sunnylink settings
  schema tests to confirm no regression in the existing port.
- Keep local diagnostic scripts out of commits.
