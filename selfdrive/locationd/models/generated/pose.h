#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7503614556887712841);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2650454973869903341);
void pose_H_mod_fun(double *state, double *out_140121567557128365);
void pose_f_fun(double *state, double dt, double *out_246987440794206982);
void pose_F_fun(double *state, double dt, double *out_7435016886215278560);
void pose_h_4(double *state, double *unused, double *out_4331234714176828190);
void pose_H_4(double *state, double *unused, double *out_1057825914325769739);
void pose_h_10(double *state, double *unused, double *out_6474328160559022177);
void pose_H_10(double *state, double *unused, double *out_32748343774837024);
void pose_h_13(double *state, double *unused, double *out_2854439485558780128);
void pose_H_13(double *state, double *unused, double *out_2775929548976754285);
void pose_h_14(double *state, double *unused, double *out_5002123430540527349);
void pose_H_14(double *state, double *unused, double *out_2024962517969602557);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}