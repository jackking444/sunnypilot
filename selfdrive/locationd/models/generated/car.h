#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5856560380568843237);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8687539781302616993);
void car_H_mod_fun(double *state, double *out_7030563345690224317);
void car_f_fun(double *state, double dt, double *out_537505539097362410);
void car_F_fun(double *state, double dt, double *out_2136100049303891178);
void car_h_25(double *state, double *unused, double *out_7674468405216828503);
void car_H_25(double *state, double *unused, double *out_6512488902834662459);
void car_h_24(double *state, double *unused, double *out_4091148193101694413);
void car_H_24(double *state, double *unused, double *out_7951932019477121259);
void car_h_30(double *state, double *unused, double *out_158137311058794483);
void car_H_30(double *state, double *unused, double *out_404201438656954296);
void car_h_26(double *state, double *unused, double *out_5484592560022162352);
void car_H_26(double *state, double *unused, double *out_8192751852000832933);
void car_h_27(double *state, double *unused, double *out_8617978258118490938);
void car_H_27(double *state, double *unused, double *out_1770561873143470615);
void car_h_29(double *state, double *unused, double *out_8234917627507375619);
void car_H_29(double *state, double *unused, double *out_3483924600013021648);
void car_h_28(double *state, double *unused, double *out_4070780901597322722);
void car_H_28(double *state, double *unused, double *out_8566323617082552222);
void car_h_31(double *state, double *unused, double *out_1189643019676192683);
void car_H_31(double *state, double *unused, double *out_6481842940957702031);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}