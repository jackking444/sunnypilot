class WMACConstants:
  LEAD_WINDOW_SIZE = 5
  LEAD_PROB = 0.5

  SLOW_DOWN_WINDOW_SIZE = 5
  SLOW_DOWN_PROB = 0.6

  SLOW_DOWN_BP = [0., 10., 20., 30., 40., 50., 55., 60.]
  SLOW_DOWN_DIST = [25., 38., 55., 75., 95., 115., 130., 150.]

  SLOWNESS_WINDOW_SIZE = 12
  SLOWNESS_PROB = 0.5
  SLOWNESS_CRUISE_OFFSET = 1.05

  DANGEROUS_TTC_WINDOW_SIZE = 3
  DANGEROUS_TTC = 2.3

  MPC_FCW_WINDOW_SIZE = 10
  MPC_FCW_PROB = 0.5


class SNG_State:
  off = 0
  stopped = 1
  going = 2
