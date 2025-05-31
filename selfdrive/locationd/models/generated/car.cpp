#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5856560380568843237) {
   out_5856560380568843237[0] = delta_x[0] + nom_x[0];
   out_5856560380568843237[1] = delta_x[1] + nom_x[1];
   out_5856560380568843237[2] = delta_x[2] + nom_x[2];
   out_5856560380568843237[3] = delta_x[3] + nom_x[3];
   out_5856560380568843237[4] = delta_x[4] + nom_x[4];
   out_5856560380568843237[5] = delta_x[5] + nom_x[5];
   out_5856560380568843237[6] = delta_x[6] + nom_x[6];
   out_5856560380568843237[7] = delta_x[7] + nom_x[7];
   out_5856560380568843237[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8687539781302616993) {
   out_8687539781302616993[0] = -nom_x[0] + true_x[0];
   out_8687539781302616993[1] = -nom_x[1] + true_x[1];
   out_8687539781302616993[2] = -nom_x[2] + true_x[2];
   out_8687539781302616993[3] = -nom_x[3] + true_x[3];
   out_8687539781302616993[4] = -nom_x[4] + true_x[4];
   out_8687539781302616993[5] = -nom_x[5] + true_x[5];
   out_8687539781302616993[6] = -nom_x[6] + true_x[6];
   out_8687539781302616993[7] = -nom_x[7] + true_x[7];
   out_8687539781302616993[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7030563345690224317) {
   out_7030563345690224317[0] = 1.0;
   out_7030563345690224317[1] = 0.0;
   out_7030563345690224317[2] = 0.0;
   out_7030563345690224317[3] = 0.0;
   out_7030563345690224317[4] = 0.0;
   out_7030563345690224317[5] = 0.0;
   out_7030563345690224317[6] = 0.0;
   out_7030563345690224317[7] = 0.0;
   out_7030563345690224317[8] = 0.0;
   out_7030563345690224317[9] = 0.0;
   out_7030563345690224317[10] = 1.0;
   out_7030563345690224317[11] = 0.0;
   out_7030563345690224317[12] = 0.0;
   out_7030563345690224317[13] = 0.0;
   out_7030563345690224317[14] = 0.0;
   out_7030563345690224317[15] = 0.0;
   out_7030563345690224317[16] = 0.0;
   out_7030563345690224317[17] = 0.0;
   out_7030563345690224317[18] = 0.0;
   out_7030563345690224317[19] = 0.0;
   out_7030563345690224317[20] = 1.0;
   out_7030563345690224317[21] = 0.0;
   out_7030563345690224317[22] = 0.0;
   out_7030563345690224317[23] = 0.0;
   out_7030563345690224317[24] = 0.0;
   out_7030563345690224317[25] = 0.0;
   out_7030563345690224317[26] = 0.0;
   out_7030563345690224317[27] = 0.0;
   out_7030563345690224317[28] = 0.0;
   out_7030563345690224317[29] = 0.0;
   out_7030563345690224317[30] = 1.0;
   out_7030563345690224317[31] = 0.0;
   out_7030563345690224317[32] = 0.0;
   out_7030563345690224317[33] = 0.0;
   out_7030563345690224317[34] = 0.0;
   out_7030563345690224317[35] = 0.0;
   out_7030563345690224317[36] = 0.0;
   out_7030563345690224317[37] = 0.0;
   out_7030563345690224317[38] = 0.0;
   out_7030563345690224317[39] = 0.0;
   out_7030563345690224317[40] = 1.0;
   out_7030563345690224317[41] = 0.0;
   out_7030563345690224317[42] = 0.0;
   out_7030563345690224317[43] = 0.0;
   out_7030563345690224317[44] = 0.0;
   out_7030563345690224317[45] = 0.0;
   out_7030563345690224317[46] = 0.0;
   out_7030563345690224317[47] = 0.0;
   out_7030563345690224317[48] = 0.0;
   out_7030563345690224317[49] = 0.0;
   out_7030563345690224317[50] = 1.0;
   out_7030563345690224317[51] = 0.0;
   out_7030563345690224317[52] = 0.0;
   out_7030563345690224317[53] = 0.0;
   out_7030563345690224317[54] = 0.0;
   out_7030563345690224317[55] = 0.0;
   out_7030563345690224317[56] = 0.0;
   out_7030563345690224317[57] = 0.0;
   out_7030563345690224317[58] = 0.0;
   out_7030563345690224317[59] = 0.0;
   out_7030563345690224317[60] = 1.0;
   out_7030563345690224317[61] = 0.0;
   out_7030563345690224317[62] = 0.0;
   out_7030563345690224317[63] = 0.0;
   out_7030563345690224317[64] = 0.0;
   out_7030563345690224317[65] = 0.0;
   out_7030563345690224317[66] = 0.0;
   out_7030563345690224317[67] = 0.0;
   out_7030563345690224317[68] = 0.0;
   out_7030563345690224317[69] = 0.0;
   out_7030563345690224317[70] = 1.0;
   out_7030563345690224317[71] = 0.0;
   out_7030563345690224317[72] = 0.0;
   out_7030563345690224317[73] = 0.0;
   out_7030563345690224317[74] = 0.0;
   out_7030563345690224317[75] = 0.0;
   out_7030563345690224317[76] = 0.0;
   out_7030563345690224317[77] = 0.0;
   out_7030563345690224317[78] = 0.0;
   out_7030563345690224317[79] = 0.0;
   out_7030563345690224317[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_537505539097362410) {
   out_537505539097362410[0] = state[0];
   out_537505539097362410[1] = state[1];
   out_537505539097362410[2] = state[2];
   out_537505539097362410[3] = state[3];
   out_537505539097362410[4] = state[4];
   out_537505539097362410[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_537505539097362410[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_537505539097362410[7] = state[7];
   out_537505539097362410[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2136100049303891178) {
   out_2136100049303891178[0] = 1;
   out_2136100049303891178[1] = 0;
   out_2136100049303891178[2] = 0;
   out_2136100049303891178[3] = 0;
   out_2136100049303891178[4] = 0;
   out_2136100049303891178[5] = 0;
   out_2136100049303891178[6] = 0;
   out_2136100049303891178[7] = 0;
   out_2136100049303891178[8] = 0;
   out_2136100049303891178[9] = 0;
   out_2136100049303891178[10] = 1;
   out_2136100049303891178[11] = 0;
   out_2136100049303891178[12] = 0;
   out_2136100049303891178[13] = 0;
   out_2136100049303891178[14] = 0;
   out_2136100049303891178[15] = 0;
   out_2136100049303891178[16] = 0;
   out_2136100049303891178[17] = 0;
   out_2136100049303891178[18] = 0;
   out_2136100049303891178[19] = 0;
   out_2136100049303891178[20] = 1;
   out_2136100049303891178[21] = 0;
   out_2136100049303891178[22] = 0;
   out_2136100049303891178[23] = 0;
   out_2136100049303891178[24] = 0;
   out_2136100049303891178[25] = 0;
   out_2136100049303891178[26] = 0;
   out_2136100049303891178[27] = 0;
   out_2136100049303891178[28] = 0;
   out_2136100049303891178[29] = 0;
   out_2136100049303891178[30] = 1;
   out_2136100049303891178[31] = 0;
   out_2136100049303891178[32] = 0;
   out_2136100049303891178[33] = 0;
   out_2136100049303891178[34] = 0;
   out_2136100049303891178[35] = 0;
   out_2136100049303891178[36] = 0;
   out_2136100049303891178[37] = 0;
   out_2136100049303891178[38] = 0;
   out_2136100049303891178[39] = 0;
   out_2136100049303891178[40] = 1;
   out_2136100049303891178[41] = 0;
   out_2136100049303891178[42] = 0;
   out_2136100049303891178[43] = 0;
   out_2136100049303891178[44] = 0;
   out_2136100049303891178[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2136100049303891178[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2136100049303891178[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2136100049303891178[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2136100049303891178[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2136100049303891178[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2136100049303891178[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2136100049303891178[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2136100049303891178[53] = -9.8000000000000007*dt;
   out_2136100049303891178[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2136100049303891178[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2136100049303891178[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2136100049303891178[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2136100049303891178[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2136100049303891178[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2136100049303891178[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2136100049303891178[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2136100049303891178[62] = 0;
   out_2136100049303891178[63] = 0;
   out_2136100049303891178[64] = 0;
   out_2136100049303891178[65] = 0;
   out_2136100049303891178[66] = 0;
   out_2136100049303891178[67] = 0;
   out_2136100049303891178[68] = 0;
   out_2136100049303891178[69] = 0;
   out_2136100049303891178[70] = 1;
   out_2136100049303891178[71] = 0;
   out_2136100049303891178[72] = 0;
   out_2136100049303891178[73] = 0;
   out_2136100049303891178[74] = 0;
   out_2136100049303891178[75] = 0;
   out_2136100049303891178[76] = 0;
   out_2136100049303891178[77] = 0;
   out_2136100049303891178[78] = 0;
   out_2136100049303891178[79] = 0;
   out_2136100049303891178[80] = 1;
}
void h_25(double *state, double *unused, double *out_7674468405216828503) {
   out_7674468405216828503[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6512488902834662459) {
   out_6512488902834662459[0] = 0;
   out_6512488902834662459[1] = 0;
   out_6512488902834662459[2] = 0;
   out_6512488902834662459[3] = 0;
   out_6512488902834662459[4] = 0;
   out_6512488902834662459[5] = 0;
   out_6512488902834662459[6] = 1;
   out_6512488902834662459[7] = 0;
   out_6512488902834662459[8] = 0;
}
void h_24(double *state, double *unused, double *out_4091148193101694413) {
   out_4091148193101694413[0] = state[4];
   out_4091148193101694413[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7951932019477121259) {
   out_7951932019477121259[0] = 0;
   out_7951932019477121259[1] = 0;
   out_7951932019477121259[2] = 0;
   out_7951932019477121259[3] = 0;
   out_7951932019477121259[4] = 1;
   out_7951932019477121259[5] = 0;
   out_7951932019477121259[6] = 0;
   out_7951932019477121259[7] = 0;
   out_7951932019477121259[8] = 0;
   out_7951932019477121259[9] = 0;
   out_7951932019477121259[10] = 0;
   out_7951932019477121259[11] = 0;
   out_7951932019477121259[12] = 0;
   out_7951932019477121259[13] = 0;
   out_7951932019477121259[14] = 1;
   out_7951932019477121259[15] = 0;
   out_7951932019477121259[16] = 0;
   out_7951932019477121259[17] = 0;
}
void h_30(double *state, double *unused, double *out_158137311058794483) {
   out_158137311058794483[0] = state[4];
}
void H_30(double *state, double *unused, double *out_404201438656954296) {
   out_404201438656954296[0] = 0;
   out_404201438656954296[1] = 0;
   out_404201438656954296[2] = 0;
   out_404201438656954296[3] = 0;
   out_404201438656954296[4] = 1;
   out_404201438656954296[5] = 0;
   out_404201438656954296[6] = 0;
   out_404201438656954296[7] = 0;
   out_404201438656954296[8] = 0;
}
void h_26(double *state, double *unused, double *out_5484592560022162352) {
   out_5484592560022162352[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8192751852000832933) {
   out_8192751852000832933[0] = 0;
   out_8192751852000832933[1] = 0;
   out_8192751852000832933[2] = 0;
   out_8192751852000832933[3] = 0;
   out_8192751852000832933[4] = 0;
   out_8192751852000832933[5] = 0;
   out_8192751852000832933[6] = 0;
   out_8192751852000832933[7] = 1;
   out_8192751852000832933[8] = 0;
}
void h_27(double *state, double *unused, double *out_8617978258118490938) {
   out_8617978258118490938[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1770561873143470615) {
   out_1770561873143470615[0] = 0;
   out_1770561873143470615[1] = 0;
   out_1770561873143470615[2] = 0;
   out_1770561873143470615[3] = 1;
   out_1770561873143470615[4] = 0;
   out_1770561873143470615[5] = 0;
   out_1770561873143470615[6] = 0;
   out_1770561873143470615[7] = 0;
   out_1770561873143470615[8] = 0;
}
void h_29(double *state, double *unused, double *out_8234917627507375619) {
   out_8234917627507375619[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3483924600013021648) {
   out_3483924600013021648[0] = 0;
   out_3483924600013021648[1] = 1;
   out_3483924600013021648[2] = 0;
   out_3483924600013021648[3] = 0;
   out_3483924600013021648[4] = 0;
   out_3483924600013021648[5] = 0;
   out_3483924600013021648[6] = 0;
   out_3483924600013021648[7] = 0;
   out_3483924600013021648[8] = 0;
}
void h_28(double *state, double *unused, double *out_4070780901597322722) {
   out_4070780901597322722[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8566323617082552222) {
   out_8566323617082552222[0] = 1;
   out_8566323617082552222[1] = 0;
   out_8566323617082552222[2] = 0;
   out_8566323617082552222[3] = 0;
   out_8566323617082552222[4] = 0;
   out_8566323617082552222[5] = 0;
   out_8566323617082552222[6] = 0;
   out_8566323617082552222[7] = 0;
   out_8566323617082552222[8] = 0;
}
void h_31(double *state, double *unused, double *out_1189643019676192683) {
   out_1189643019676192683[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6481842940957702031) {
   out_6481842940957702031[0] = 0;
   out_6481842940957702031[1] = 0;
   out_6481842940957702031[2] = 0;
   out_6481842940957702031[3] = 0;
   out_6481842940957702031[4] = 0;
   out_6481842940957702031[5] = 0;
   out_6481842940957702031[6] = 0;
   out_6481842940957702031[7] = 0;
   out_6481842940957702031[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_5856560380568843237) {
  err_fun(nom_x, delta_x, out_5856560380568843237);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8687539781302616993) {
  inv_err_fun(nom_x, true_x, out_8687539781302616993);
}
void car_H_mod_fun(double *state, double *out_7030563345690224317) {
  H_mod_fun(state, out_7030563345690224317);
}
void car_f_fun(double *state, double dt, double *out_537505539097362410) {
  f_fun(state,  dt, out_537505539097362410);
}
void car_F_fun(double *state, double dt, double *out_2136100049303891178) {
  F_fun(state,  dt, out_2136100049303891178);
}
void car_h_25(double *state, double *unused, double *out_7674468405216828503) {
  h_25(state, unused, out_7674468405216828503);
}
void car_H_25(double *state, double *unused, double *out_6512488902834662459) {
  H_25(state, unused, out_6512488902834662459);
}
void car_h_24(double *state, double *unused, double *out_4091148193101694413) {
  h_24(state, unused, out_4091148193101694413);
}
void car_H_24(double *state, double *unused, double *out_7951932019477121259) {
  H_24(state, unused, out_7951932019477121259);
}
void car_h_30(double *state, double *unused, double *out_158137311058794483) {
  h_30(state, unused, out_158137311058794483);
}
void car_H_30(double *state, double *unused, double *out_404201438656954296) {
  H_30(state, unused, out_404201438656954296);
}
void car_h_26(double *state, double *unused, double *out_5484592560022162352) {
  h_26(state, unused, out_5484592560022162352);
}
void car_H_26(double *state, double *unused, double *out_8192751852000832933) {
  H_26(state, unused, out_8192751852000832933);
}
void car_h_27(double *state, double *unused, double *out_8617978258118490938) {
  h_27(state, unused, out_8617978258118490938);
}
void car_H_27(double *state, double *unused, double *out_1770561873143470615) {
  H_27(state, unused, out_1770561873143470615);
}
void car_h_29(double *state, double *unused, double *out_8234917627507375619) {
  h_29(state, unused, out_8234917627507375619);
}
void car_H_29(double *state, double *unused, double *out_3483924600013021648) {
  H_29(state, unused, out_3483924600013021648);
}
void car_h_28(double *state, double *unused, double *out_4070780901597322722) {
  h_28(state, unused, out_4070780901597322722);
}
void car_H_28(double *state, double *unused, double *out_8566323617082552222) {
  H_28(state, unused, out_8566323617082552222);
}
void car_h_31(double *state, double *unused, double *out_1189643019676192683) {
  h_31(state, unused, out_1189643019676192683);
}
void car_H_31(double *state, double *unused, double *out_6481842940957702031) {
  H_31(state, unused, out_6481842940957702031);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
