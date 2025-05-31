#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7503614556887712841) {
   out_7503614556887712841[0] = delta_x[0] + nom_x[0];
   out_7503614556887712841[1] = delta_x[1] + nom_x[1];
   out_7503614556887712841[2] = delta_x[2] + nom_x[2];
   out_7503614556887712841[3] = delta_x[3] + nom_x[3];
   out_7503614556887712841[4] = delta_x[4] + nom_x[4];
   out_7503614556887712841[5] = delta_x[5] + nom_x[5];
   out_7503614556887712841[6] = delta_x[6] + nom_x[6];
   out_7503614556887712841[7] = delta_x[7] + nom_x[7];
   out_7503614556887712841[8] = delta_x[8] + nom_x[8];
   out_7503614556887712841[9] = delta_x[9] + nom_x[9];
   out_7503614556887712841[10] = delta_x[10] + nom_x[10];
   out_7503614556887712841[11] = delta_x[11] + nom_x[11];
   out_7503614556887712841[12] = delta_x[12] + nom_x[12];
   out_7503614556887712841[13] = delta_x[13] + nom_x[13];
   out_7503614556887712841[14] = delta_x[14] + nom_x[14];
   out_7503614556887712841[15] = delta_x[15] + nom_x[15];
   out_7503614556887712841[16] = delta_x[16] + nom_x[16];
   out_7503614556887712841[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2650454973869903341) {
   out_2650454973869903341[0] = -nom_x[0] + true_x[0];
   out_2650454973869903341[1] = -nom_x[1] + true_x[1];
   out_2650454973869903341[2] = -nom_x[2] + true_x[2];
   out_2650454973869903341[3] = -nom_x[3] + true_x[3];
   out_2650454973869903341[4] = -nom_x[4] + true_x[4];
   out_2650454973869903341[5] = -nom_x[5] + true_x[5];
   out_2650454973869903341[6] = -nom_x[6] + true_x[6];
   out_2650454973869903341[7] = -nom_x[7] + true_x[7];
   out_2650454973869903341[8] = -nom_x[8] + true_x[8];
   out_2650454973869903341[9] = -nom_x[9] + true_x[9];
   out_2650454973869903341[10] = -nom_x[10] + true_x[10];
   out_2650454973869903341[11] = -nom_x[11] + true_x[11];
   out_2650454973869903341[12] = -nom_x[12] + true_x[12];
   out_2650454973869903341[13] = -nom_x[13] + true_x[13];
   out_2650454973869903341[14] = -nom_x[14] + true_x[14];
   out_2650454973869903341[15] = -nom_x[15] + true_x[15];
   out_2650454973869903341[16] = -nom_x[16] + true_x[16];
   out_2650454973869903341[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_140121567557128365) {
   out_140121567557128365[0] = 1.0;
   out_140121567557128365[1] = 0.0;
   out_140121567557128365[2] = 0.0;
   out_140121567557128365[3] = 0.0;
   out_140121567557128365[4] = 0.0;
   out_140121567557128365[5] = 0.0;
   out_140121567557128365[6] = 0.0;
   out_140121567557128365[7] = 0.0;
   out_140121567557128365[8] = 0.0;
   out_140121567557128365[9] = 0.0;
   out_140121567557128365[10] = 0.0;
   out_140121567557128365[11] = 0.0;
   out_140121567557128365[12] = 0.0;
   out_140121567557128365[13] = 0.0;
   out_140121567557128365[14] = 0.0;
   out_140121567557128365[15] = 0.0;
   out_140121567557128365[16] = 0.0;
   out_140121567557128365[17] = 0.0;
   out_140121567557128365[18] = 0.0;
   out_140121567557128365[19] = 1.0;
   out_140121567557128365[20] = 0.0;
   out_140121567557128365[21] = 0.0;
   out_140121567557128365[22] = 0.0;
   out_140121567557128365[23] = 0.0;
   out_140121567557128365[24] = 0.0;
   out_140121567557128365[25] = 0.0;
   out_140121567557128365[26] = 0.0;
   out_140121567557128365[27] = 0.0;
   out_140121567557128365[28] = 0.0;
   out_140121567557128365[29] = 0.0;
   out_140121567557128365[30] = 0.0;
   out_140121567557128365[31] = 0.0;
   out_140121567557128365[32] = 0.0;
   out_140121567557128365[33] = 0.0;
   out_140121567557128365[34] = 0.0;
   out_140121567557128365[35] = 0.0;
   out_140121567557128365[36] = 0.0;
   out_140121567557128365[37] = 0.0;
   out_140121567557128365[38] = 1.0;
   out_140121567557128365[39] = 0.0;
   out_140121567557128365[40] = 0.0;
   out_140121567557128365[41] = 0.0;
   out_140121567557128365[42] = 0.0;
   out_140121567557128365[43] = 0.0;
   out_140121567557128365[44] = 0.0;
   out_140121567557128365[45] = 0.0;
   out_140121567557128365[46] = 0.0;
   out_140121567557128365[47] = 0.0;
   out_140121567557128365[48] = 0.0;
   out_140121567557128365[49] = 0.0;
   out_140121567557128365[50] = 0.0;
   out_140121567557128365[51] = 0.0;
   out_140121567557128365[52] = 0.0;
   out_140121567557128365[53] = 0.0;
   out_140121567557128365[54] = 0.0;
   out_140121567557128365[55] = 0.0;
   out_140121567557128365[56] = 0.0;
   out_140121567557128365[57] = 1.0;
   out_140121567557128365[58] = 0.0;
   out_140121567557128365[59] = 0.0;
   out_140121567557128365[60] = 0.0;
   out_140121567557128365[61] = 0.0;
   out_140121567557128365[62] = 0.0;
   out_140121567557128365[63] = 0.0;
   out_140121567557128365[64] = 0.0;
   out_140121567557128365[65] = 0.0;
   out_140121567557128365[66] = 0.0;
   out_140121567557128365[67] = 0.0;
   out_140121567557128365[68] = 0.0;
   out_140121567557128365[69] = 0.0;
   out_140121567557128365[70] = 0.0;
   out_140121567557128365[71] = 0.0;
   out_140121567557128365[72] = 0.0;
   out_140121567557128365[73] = 0.0;
   out_140121567557128365[74] = 0.0;
   out_140121567557128365[75] = 0.0;
   out_140121567557128365[76] = 1.0;
   out_140121567557128365[77] = 0.0;
   out_140121567557128365[78] = 0.0;
   out_140121567557128365[79] = 0.0;
   out_140121567557128365[80] = 0.0;
   out_140121567557128365[81] = 0.0;
   out_140121567557128365[82] = 0.0;
   out_140121567557128365[83] = 0.0;
   out_140121567557128365[84] = 0.0;
   out_140121567557128365[85] = 0.0;
   out_140121567557128365[86] = 0.0;
   out_140121567557128365[87] = 0.0;
   out_140121567557128365[88] = 0.0;
   out_140121567557128365[89] = 0.0;
   out_140121567557128365[90] = 0.0;
   out_140121567557128365[91] = 0.0;
   out_140121567557128365[92] = 0.0;
   out_140121567557128365[93] = 0.0;
   out_140121567557128365[94] = 0.0;
   out_140121567557128365[95] = 1.0;
   out_140121567557128365[96] = 0.0;
   out_140121567557128365[97] = 0.0;
   out_140121567557128365[98] = 0.0;
   out_140121567557128365[99] = 0.0;
   out_140121567557128365[100] = 0.0;
   out_140121567557128365[101] = 0.0;
   out_140121567557128365[102] = 0.0;
   out_140121567557128365[103] = 0.0;
   out_140121567557128365[104] = 0.0;
   out_140121567557128365[105] = 0.0;
   out_140121567557128365[106] = 0.0;
   out_140121567557128365[107] = 0.0;
   out_140121567557128365[108] = 0.0;
   out_140121567557128365[109] = 0.0;
   out_140121567557128365[110] = 0.0;
   out_140121567557128365[111] = 0.0;
   out_140121567557128365[112] = 0.0;
   out_140121567557128365[113] = 0.0;
   out_140121567557128365[114] = 1.0;
   out_140121567557128365[115] = 0.0;
   out_140121567557128365[116] = 0.0;
   out_140121567557128365[117] = 0.0;
   out_140121567557128365[118] = 0.0;
   out_140121567557128365[119] = 0.0;
   out_140121567557128365[120] = 0.0;
   out_140121567557128365[121] = 0.0;
   out_140121567557128365[122] = 0.0;
   out_140121567557128365[123] = 0.0;
   out_140121567557128365[124] = 0.0;
   out_140121567557128365[125] = 0.0;
   out_140121567557128365[126] = 0.0;
   out_140121567557128365[127] = 0.0;
   out_140121567557128365[128] = 0.0;
   out_140121567557128365[129] = 0.0;
   out_140121567557128365[130] = 0.0;
   out_140121567557128365[131] = 0.0;
   out_140121567557128365[132] = 0.0;
   out_140121567557128365[133] = 1.0;
   out_140121567557128365[134] = 0.0;
   out_140121567557128365[135] = 0.0;
   out_140121567557128365[136] = 0.0;
   out_140121567557128365[137] = 0.0;
   out_140121567557128365[138] = 0.0;
   out_140121567557128365[139] = 0.0;
   out_140121567557128365[140] = 0.0;
   out_140121567557128365[141] = 0.0;
   out_140121567557128365[142] = 0.0;
   out_140121567557128365[143] = 0.0;
   out_140121567557128365[144] = 0.0;
   out_140121567557128365[145] = 0.0;
   out_140121567557128365[146] = 0.0;
   out_140121567557128365[147] = 0.0;
   out_140121567557128365[148] = 0.0;
   out_140121567557128365[149] = 0.0;
   out_140121567557128365[150] = 0.0;
   out_140121567557128365[151] = 0.0;
   out_140121567557128365[152] = 1.0;
   out_140121567557128365[153] = 0.0;
   out_140121567557128365[154] = 0.0;
   out_140121567557128365[155] = 0.0;
   out_140121567557128365[156] = 0.0;
   out_140121567557128365[157] = 0.0;
   out_140121567557128365[158] = 0.0;
   out_140121567557128365[159] = 0.0;
   out_140121567557128365[160] = 0.0;
   out_140121567557128365[161] = 0.0;
   out_140121567557128365[162] = 0.0;
   out_140121567557128365[163] = 0.0;
   out_140121567557128365[164] = 0.0;
   out_140121567557128365[165] = 0.0;
   out_140121567557128365[166] = 0.0;
   out_140121567557128365[167] = 0.0;
   out_140121567557128365[168] = 0.0;
   out_140121567557128365[169] = 0.0;
   out_140121567557128365[170] = 0.0;
   out_140121567557128365[171] = 1.0;
   out_140121567557128365[172] = 0.0;
   out_140121567557128365[173] = 0.0;
   out_140121567557128365[174] = 0.0;
   out_140121567557128365[175] = 0.0;
   out_140121567557128365[176] = 0.0;
   out_140121567557128365[177] = 0.0;
   out_140121567557128365[178] = 0.0;
   out_140121567557128365[179] = 0.0;
   out_140121567557128365[180] = 0.0;
   out_140121567557128365[181] = 0.0;
   out_140121567557128365[182] = 0.0;
   out_140121567557128365[183] = 0.0;
   out_140121567557128365[184] = 0.0;
   out_140121567557128365[185] = 0.0;
   out_140121567557128365[186] = 0.0;
   out_140121567557128365[187] = 0.0;
   out_140121567557128365[188] = 0.0;
   out_140121567557128365[189] = 0.0;
   out_140121567557128365[190] = 1.0;
   out_140121567557128365[191] = 0.0;
   out_140121567557128365[192] = 0.0;
   out_140121567557128365[193] = 0.0;
   out_140121567557128365[194] = 0.0;
   out_140121567557128365[195] = 0.0;
   out_140121567557128365[196] = 0.0;
   out_140121567557128365[197] = 0.0;
   out_140121567557128365[198] = 0.0;
   out_140121567557128365[199] = 0.0;
   out_140121567557128365[200] = 0.0;
   out_140121567557128365[201] = 0.0;
   out_140121567557128365[202] = 0.0;
   out_140121567557128365[203] = 0.0;
   out_140121567557128365[204] = 0.0;
   out_140121567557128365[205] = 0.0;
   out_140121567557128365[206] = 0.0;
   out_140121567557128365[207] = 0.0;
   out_140121567557128365[208] = 0.0;
   out_140121567557128365[209] = 1.0;
   out_140121567557128365[210] = 0.0;
   out_140121567557128365[211] = 0.0;
   out_140121567557128365[212] = 0.0;
   out_140121567557128365[213] = 0.0;
   out_140121567557128365[214] = 0.0;
   out_140121567557128365[215] = 0.0;
   out_140121567557128365[216] = 0.0;
   out_140121567557128365[217] = 0.0;
   out_140121567557128365[218] = 0.0;
   out_140121567557128365[219] = 0.0;
   out_140121567557128365[220] = 0.0;
   out_140121567557128365[221] = 0.0;
   out_140121567557128365[222] = 0.0;
   out_140121567557128365[223] = 0.0;
   out_140121567557128365[224] = 0.0;
   out_140121567557128365[225] = 0.0;
   out_140121567557128365[226] = 0.0;
   out_140121567557128365[227] = 0.0;
   out_140121567557128365[228] = 1.0;
   out_140121567557128365[229] = 0.0;
   out_140121567557128365[230] = 0.0;
   out_140121567557128365[231] = 0.0;
   out_140121567557128365[232] = 0.0;
   out_140121567557128365[233] = 0.0;
   out_140121567557128365[234] = 0.0;
   out_140121567557128365[235] = 0.0;
   out_140121567557128365[236] = 0.0;
   out_140121567557128365[237] = 0.0;
   out_140121567557128365[238] = 0.0;
   out_140121567557128365[239] = 0.0;
   out_140121567557128365[240] = 0.0;
   out_140121567557128365[241] = 0.0;
   out_140121567557128365[242] = 0.0;
   out_140121567557128365[243] = 0.0;
   out_140121567557128365[244] = 0.0;
   out_140121567557128365[245] = 0.0;
   out_140121567557128365[246] = 0.0;
   out_140121567557128365[247] = 1.0;
   out_140121567557128365[248] = 0.0;
   out_140121567557128365[249] = 0.0;
   out_140121567557128365[250] = 0.0;
   out_140121567557128365[251] = 0.0;
   out_140121567557128365[252] = 0.0;
   out_140121567557128365[253] = 0.0;
   out_140121567557128365[254] = 0.0;
   out_140121567557128365[255] = 0.0;
   out_140121567557128365[256] = 0.0;
   out_140121567557128365[257] = 0.0;
   out_140121567557128365[258] = 0.0;
   out_140121567557128365[259] = 0.0;
   out_140121567557128365[260] = 0.0;
   out_140121567557128365[261] = 0.0;
   out_140121567557128365[262] = 0.0;
   out_140121567557128365[263] = 0.0;
   out_140121567557128365[264] = 0.0;
   out_140121567557128365[265] = 0.0;
   out_140121567557128365[266] = 1.0;
   out_140121567557128365[267] = 0.0;
   out_140121567557128365[268] = 0.0;
   out_140121567557128365[269] = 0.0;
   out_140121567557128365[270] = 0.0;
   out_140121567557128365[271] = 0.0;
   out_140121567557128365[272] = 0.0;
   out_140121567557128365[273] = 0.0;
   out_140121567557128365[274] = 0.0;
   out_140121567557128365[275] = 0.0;
   out_140121567557128365[276] = 0.0;
   out_140121567557128365[277] = 0.0;
   out_140121567557128365[278] = 0.0;
   out_140121567557128365[279] = 0.0;
   out_140121567557128365[280] = 0.0;
   out_140121567557128365[281] = 0.0;
   out_140121567557128365[282] = 0.0;
   out_140121567557128365[283] = 0.0;
   out_140121567557128365[284] = 0.0;
   out_140121567557128365[285] = 1.0;
   out_140121567557128365[286] = 0.0;
   out_140121567557128365[287] = 0.0;
   out_140121567557128365[288] = 0.0;
   out_140121567557128365[289] = 0.0;
   out_140121567557128365[290] = 0.0;
   out_140121567557128365[291] = 0.0;
   out_140121567557128365[292] = 0.0;
   out_140121567557128365[293] = 0.0;
   out_140121567557128365[294] = 0.0;
   out_140121567557128365[295] = 0.0;
   out_140121567557128365[296] = 0.0;
   out_140121567557128365[297] = 0.0;
   out_140121567557128365[298] = 0.0;
   out_140121567557128365[299] = 0.0;
   out_140121567557128365[300] = 0.0;
   out_140121567557128365[301] = 0.0;
   out_140121567557128365[302] = 0.0;
   out_140121567557128365[303] = 0.0;
   out_140121567557128365[304] = 1.0;
   out_140121567557128365[305] = 0.0;
   out_140121567557128365[306] = 0.0;
   out_140121567557128365[307] = 0.0;
   out_140121567557128365[308] = 0.0;
   out_140121567557128365[309] = 0.0;
   out_140121567557128365[310] = 0.0;
   out_140121567557128365[311] = 0.0;
   out_140121567557128365[312] = 0.0;
   out_140121567557128365[313] = 0.0;
   out_140121567557128365[314] = 0.0;
   out_140121567557128365[315] = 0.0;
   out_140121567557128365[316] = 0.0;
   out_140121567557128365[317] = 0.0;
   out_140121567557128365[318] = 0.0;
   out_140121567557128365[319] = 0.0;
   out_140121567557128365[320] = 0.0;
   out_140121567557128365[321] = 0.0;
   out_140121567557128365[322] = 0.0;
   out_140121567557128365[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_246987440794206982) {
   out_246987440794206982[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_246987440794206982[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_246987440794206982[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_246987440794206982[3] = dt*state[12] + state[3];
   out_246987440794206982[4] = dt*state[13] + state[4];
   out_246987440794206982[5] = dt*state[14] + state[5];
   out_246987440794206982[6] = state[6];
   out_246987440794206982[7] = state[7];
   out_246987440794206982[8] = state[8];
   out_246987440794206982[9] = state[9];
   out_246987440794206982[10] = state[10];
   out_246987440794206982[11] = state[11];
   out_246987440794206982[12] = state[12];
   out_246987440794206982[13] = state[13];
   out_246987440794206982[14] = state[14];
   out_246987440794206982[15] = state[15];
   out_246987440794206982[16] = state[16];
   out_246987440794206982[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7435016886215278560) {
   out_7435016886215278560[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7435016886215278560[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7435016886215278560[2] = 0;
   out_7435016886215278560[3] = 0;
   out_7435016886215278560[4] = 0;
   out_7435016886215278560[5] = 0;
   out_7435016886215278560[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7435016886215278560[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7435016886215278560[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7435016886215278560[9] = 0;
   out_7435016886215278560[10] = 0;
   out_7435016886215278560[11] = 0;
   out_7435016886215278560[12] = 0;
   out_7435016886215278560[13] = 0;
   out_7435016886215278560[14] = 0;
   out_7435016886215278560[15] = 0;
   out_7435016886215278560[16] = 0;
   out_7435016886215278560[17] = 0;
   out_7435016886215278560[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7435016886215278560[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7435016886215278560[20] = 0;
   out_7435016886215278560[21] = 0;
   out_7435016886215278560[22] = 0;
   out_7435016886215278560[23] = 0;
   out_7435016886215278560[24] = 0;
   out_7435016886215278560[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7435016886215278560[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7435016886215278560[27] = 0;
   out_7435016886215278560[28] = 0;
   out_7435016886215278560[29] = 0;
   out_7435016886215278560[30] = 0;
   out_7435016886215278560[31] = 0;
   out_7435016886215278560[32] = 0;
   out_7435016886215278560[33] = 0;
   out_7435016886215278560[34] = 0;
   out_7435016886215278560[35] = 0;
   out_7435016886215278560[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7435016886215278560[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7435016886215278560[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7435016886215278560[39] = 0;
   out_7435016886215278560[40] = 0;
   out_7435016886215278560[41] = 0;
   out_7435016886215278560[42] = 0;
   out_7435016886215278560[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7435016886215278560[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7435016886215278560[45] = 0;
   out_7435016886215278560[46] = 0;
   out_7435016886215278560[47] = 0;
   out_7435016886215278560[48] = 0;
   out_7435016886215278560[49] = 0;
   out_7435016886215278560[50] = 0;
   out_7435016886215278560[51] = 0;
   out_7435016886215278560[52] = 0;
   out_7435016886215278560[53] = 0;
   out_7435016886215278560[54] = 0;
   out_7435016886215278560[55] = 0;
   out_7435016886215278560[56] = 0;
   out_7435016886215278560[57] = 1;
   out_7435016886215278560[58] = 0;
   out_7435016886215278560[59] = 0;
   out_7435016886215278560[60] = 0;
   out_7435016886215278560[61] = 0;
   out_7435016886215278560[62] = 0;
   out_7435016886215278560[63] = 0;
   out_7435016886215278560[64] = 0;
   out_7435016886215278560[65] = 0;
   out_7435016886215278560[66] = dt;
   out_7435016886215278560[67] = 0;
   out_7435016886215278560[68] = 0;
   out_7435016886215278560[69] = 0;
   out_7435016886215278560[70] = 0;
   out_7435016886215278560[71] = 0;
   out_7435016886215278560[72] = 0;
   out_7435016886215278560[73] = 0;
   out_7435016886215278560[74] = 0;
   out_7435016886215278560[75] = 0;
   out_7435016886215278560[76] = 1;
   out_7435016886215278560[77] = 0;
   out_7435016886215278560[78] = 0;
   out_7435016886215278560[79] = 0;
   out_7435016886215278560[80] = 0;
   out_7435016886215278560[81] = 0;
   out_7435016886215278560[82] = 0;
   out_7435016886215278560[83] = 0;
   out_7435016886215278560[84] = 0;
   out_7435016886215278560[85] = dt;
   out_7435016886215278560[86] = 0;
   out_7435016886215278560[87] = 0;
   out_7435016886215278560[88] = 0;
   out_7435016886215278560[89] = 0;
   out_7435016886215278560[90] = 0;
   out_7435016886215278560[91] = 0;
   out_7435016886215278560[92] = 0;
   out_7435016886215278560[93] = 0;
   out_7435016886215278560[94] = 0;
   out_7435016886215278560[95] = 1;
   out_7435016886215278560[96] = 0;
   out_7435016886215278560[97] = 0;
   out_7435016886215278560[98] = 0;
   out_7435016886215278560[99] = 0;
   out_7435016886215278560[100] = 0;
   out_7435016886215278560[101] = 0;
   out_7435016886215278560[102] = 0;
   out_7435016886215278560[103] = 0;
   out_7435016886215278560[104] = dt;
   out_7435016886215278560[105] = 0;
   out_7435016886215278560[106] = 0;
   out_7435016886215278560[107] = 0;
   out_7435016886215278560[108] = 0;
   out_7435016886215278560[109] = 0;
   out_7435016886215278560[110] = 0;
   out_7435016886215278560[111] = 0;
   out_7435016886215278560[112] = 0;
   out_7435016886215278560[113] = 0;
   out_7435016886215278560[114] = 1;
   out_7435016886215278560[115] = 0;
   out_7435016886215278560[116] = 0;
   out_7435016886215278560[117] = 0;
   out_7435016886215278560[118] = 0;
   out_7435016886215278560[119] = 0;
   out_7435016886215278560[120] = 0;
   out_7435016886215278560[121] = 0;
   out_7435016886215278560[122] = 0;
   out_7435016886215278560[123] = 0;
   out_7435016886215278560[124] = 0;
   out_7435016886215278560[125] = 0;
   out_7435016886215278560[126] = 0;
   out_7435016886215278560[127] = 0;
   out_7435016886215278560[128] = 0;
   out_7435016886215278560[129] = 0;
   out_7435016886215278560[130] = 0;
   out_7435016886215278560[131] = 0;
   out_7435016886215278560[132] = 0;
   out_7435016886215278560[133] = 1;
   out_7435016886215278560[134] = 0;
   out_7435016886215278560[135] = 0;
   out_7435016886215278560[136] = 0;
   out_7435016886215278560[137] = 0;
   out_7435016886215278560[138] = 0;
   out_7435016886215278560[139] = 0;
   out_7435016886215278560[140] = 0;
   out_7435016886215278560[141] = 0;
   out_7435016886215278560[142] = 0;
   out_7435016886215278560[143] = 0;
   out_7435016886215278560[144] = 0;
   out_7435016886215278560[145] = 0;
   out_7435016886215278560[146] = 0;
   out_7435016886215278560[147] = 0;
   out_7435016886215278560[148] = 0;
   out_7435016886215278560[149] = 0;
   out_7435016886215278560[150] = 0;
   out_7435016886215278560[151] = 0;
   out_7435016886215278560[152] = 1;
   out_7435016886215278560[153] = 0;
   out_7435016886215278560[154] = 0;
   out_7435016886215278560[155] = 0;
   out_7435016886215278560[156] = 0;
   out_7435016886215278560[157] = 0;
   out_7435016886215278560[158] = 0;
   out_7435016886215278560[159] = 0;
   out_7435016886215278560[160] = 0;
   out_7435016886215278560[161] = 0;
   out_7435016886215278560[162] = 0;
   out_7435016886215278560[163] = 0;
   out_7435016886215278560[164] = 0;
   out_7435016886215278560[165] = 0;
   out_7435016886215278560[166] = 0;
   out_7435016886215278560[167] = 0;
   out_7435016886215278560[168] = 0;
   out_7435016886215278560[169] = 0;
   out_7435016886215278560[170] = 0;
   out_7435016886215278560[171] = 1;
   out_7435016886215278560[172] = 0;
   out_7435016886215278560[173] = 0;
   out_7435016886215278560[174] = 0;
   out_7435016886215278560[175] = 0;
   out_7435016886215278560[176] = 0;
   out_7435016886215278560[177] = 0;
   out_7435016886215278560[178] = 0;
   out_7435016886215278560[179] = 0;
   out_7435016886215278560[180] = 0;
   out_7435016886215278560[181] = 0;
   out_7435016886215278560[182] = 0;
   out_7435016886215278560[183] = 0;
   out_7435016886215278560[184] = 0;
   out_7435016886215278560[185] = 0;
   out_7435016886215278560[186] = 0;
   out_7435016886215278560[187] = 0;
   out_7435016886215278560[188] = 0;
   out_7435016886215278560[189] = 0;
   out_7435016886215278560[190] = 1;
   out_7435016886215278560[191] = 0;
   out_7435016886215278560[192] = 0;
   out_7435016886215278560[193] = 0;
   out_7435016886215278560[194] = 0;
   out_7435016886215278560[195] = 0;
   out_7435016886215278560[196] = 0;
   out_7435016886215278560[197] = 0;
   out_7435016886215278560[198] = 0;
   out_7435016886215278560[199] = 0;
   out_7435016886215278560[200] = 0;
   out_7435016886215278560[201] = 0;
   out_7435016886215278560[202] = 0;
   out_7435016886215278560[203] = 0;
   out_7435016886215278560[204] = 0;
   out_7435016886215278560[205] = 0;
   out_7435016886215278560[206] = 0;
   out_7435016886215278560[207] = 0;
   out_7435016886215278560[208] = 0;
   out_7435016886215278560[209] = 1;
   out_7435016886215278560[210] = 0;
   out_7435016886215278560[211] = 0;
   out_7435016886215278560[212] = 0;
   out_7435016886215278560[213] = 0;
   out_7435016886215278560[214] = 0;
   out_7435016886215278560[215] = 0;
   out_7435016886215278560[216] = 0;
   out_7435016886215278560[217] = 0;
   out_7435016886215278560[218] = 0;
   out_7435016886215278560[219] = 0;
   out_7435016886215278560[220] = 0;
   out_7435016886215278560[221] = 0;
   out_7435016886215278560[222] = 0;
   out_7435016886215278560[223] = 0;
   out_7435016886215278560[224] = 0;
   out_7435016886215278560[225] = 0;
   out_7435016886215278560[226] = 0;
   out_7435016886215278560[227] = 0;
   out_7435016886215278560[228] = 1;
   out_7435016886215278560[229] = 0;
   out_7435016886215278560[230] = 0;
   out_7435016886215278560[231] = 0;
   out_7435016886215278560[232] = 0;
   out_7435016886215278560[233] = 0;
   out_7435016886215278560[234] = 0;
   out_7435016886215278560[235] = 0;
   out_7435016886215278560[236] = 0;
   out_7435016886215278560[237] = 0;
   out_7435016886215278560[238] = 0;
   out_7435016886215278560[239] = 0;
   out_7435016886215278560[240] = 0;
   out_7435016886215278560[241] = 0;
   out_7435016886215278560[242] = 0;
   out_7435016886215278560[243] = 0;
   out_7435016886215278560[244] = 0;
   out_7435016886215278560[245] = 0;
   out_7435016886215278560[246] = 0;
   out_7435016886215278560[247] = 1;
   out_7435016886215278560[248] = 0;
   out_7435016886215278560[249] = 0;
   out_7435016886215278560[250] = 0;
   out_7435016886215278560[251] = 0;
   out_7435016886215278560[252] = 0;
   out_7435016886215278560[253] = 0;
   out_7435016886215278560[254] = 0;
   out_7435016886215278560[255] = 0;
   out_7435016886215278560[256] = 0;
   out_7435016886215278560[257] = 0;
   out_7435016886215278560[258] = 0;
   out_7435016886215278560[259] = 0;
   out_7435016886215278560[260] = 0;
   out_7435016886215278560[261] = 0;
   out_7435016886215278560[262] = 0;
   out_7435016886215278560[263] = 0;
   out_7435016886215278560[264] = 0;
   out_7435016886215278560[265] = 0;
   out_7435016886215278560[266] = 1;
   out_7435016886215278560[267] = 0;
   out_7435016886215278560[268] = 0;
   out_7435016886215278560[269] = 0;
   out_7435016886215278560[270] = 0;
   out_7435016886215278560[271] = 0;
   out_7435016886215278560[272] = 0;
   out_7435016886215278560[273] = 0;
   out_7435016886215278560[274] = 0;
   out_7435016886215278560[275] = 0;
   out_7435016886215278560[276] = 0;
   out_7435016886215278560[277] = 0;
   out_7435016886215278560[278] = 0;
   out_7435016886215278560[279] = 0;
   out_7435016886215278560[280] = 0;
   out_7435016886215278560[281] = 0;
   out_7435016886215278560[282] = 0;
   out_7435016886215278560[283] = 0;
   out_7435016886215278560[284] = 0;
   out_7435016886215278560[285] = 1;
   out_7435016886215278560[286] = 0;
   out_7435016886215278560[287] = 0;
   out_7435016886215278560[288] = 0;
   out_7435016886215278560[289] = 0;
   out_7435016886215278560[290] = 0;
   out_7435016886215278560[291] = 0;
   out_7435016886215278560[292] = 0;
   out_7435016886215278560[293] = 0;
   out_7435016886215278560[294] = 0;
   out_7435016886215278560[295] = 0;
   out_7435016886215278560[296] = 0;
   out_7435016886215278560[297] = 0;
   out_7435016886215278560[298] = 0;
   out_7435016886215278560[299] = 0;
   out_7435016886215278560[300] = 0;
   out_7435016886215278560[301] = 0;
   out_7435016886215278560[302] = 0;
   out_7435016886215278560[303] = 0;
   out_7435016886215278560[304] = 1;
   out_7435016886215278560[305] = 0;
   out_7435016886215278560[306] = 0;
   out_7435016886215278560[307] = 0;
   out_7435016886215278560[308] = 0;
   out_7435016886215278560[309] = 0;
   out_7435016886215278560[310] = 0;
   out_7435016886215278560[311] = 0;
   out_7435016886215278560[312] = 0;
   out_7435016886215278560[313] = 0;
   out_7435016886215278560[314] = 0;
   out_7435016886215278560[315] = 0;
   out_7435016886215278560[316] = 0;
   out_7435016886215278560[317] = 0;
   out_7435016886215278560[318] = 0;
   out_7435016886215278560[319] = 0;
   out_7435016886215278560[320] = 0;
   out_7435016886215278560[321] = 0;
   out_7435016886215278560[322] = 0;
   out_7435016886215278560[323] = 1;
}
void h_4(double *state, double *unused, double *out_4331234714176828190) {
   out_4331234714176828190[0] = state[6] + state[9];
   out_4331234714176828190[1] = state[7] + state[10];
   out_4331234714176828190[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1057825914325769739) {
   out_1057825914325769739[0] = 0;
   out_1057825914325769739[1] = 0;
   out_1057825914325769739[2] = 0;
   out_1057825914325769739[3] = 0;
   out_1057825914325769739[4] = 0;
   out_1057825914325769739[5] = 0;
   out_1057825914325769739[6] = 1;
   out_1057825914325769739[7] = 0;
   out_1057825914325769739[8] = 0;
   out_1057825914325769739[9] = 1;
   out_1057825914325769739[10] = 0;
   out_1057825914325769739[11] = 0;
   out_1057825914325769739[12] = 0;
   out_1057825914325769739[13] = 0;
   out_1057825914325769739[14] = 0;
   out_1057825914325769739[15] = 0;
   out_1057825914325769739[16] = 0;
   out_1057825914325769739[17] = 0;
   out_1057825914325769739[18] = 0;
   out_1057825914325769739[19] = 0;
   out_1057825914325769739[20] = 0;
   out_1057825914325769739[21] = 0;
   out_1057825914325769739[22] = 0;
   out_1057825914325769739[23] = 0;
   out_1057825914325769739[24] = 0;
   out_1057825914325769739[25] = 1;
   out_1057825914325769739[26] = 0;
   out_1057825914325769739[27] = 0;
   out_1057825914325769739[28] = 1;
   out_1057825914325769739[29] = 0;
   out_1057825914325769739[30] = 0;
   out_1057825914325769739[31] = 0;
   out_1057825914325769739[32] = 0;
   out_1057825914325769739[33] = 0;
   out_1057825914325769739[34] = 0;
   out_1057825914325769739[35] = 0;
   out_1057825914325769739[36] = 0;
   out_1057825914325769739[37] = 0;
   out_1057825914325769739[38] = 0;
   out_1057825914325769739[39] = 0;
   out_1057825914325769739[40] = 0;
   out_1057825914325769739[41] = 0;
   out_1057825914325769739[42] = 0;
   out_1057825914325769739[43] = 0;
   out_1057825914325769739[44] = 1;
   out_1057825914325769739[45] = 0;
   out_1057825914325769739[46] = 0;
   out_1057825914325769739[47] = 1;
   out_1057825914325769739[48] = 0;
   out_1057825914325769739[49] = 0;
   out_1057825914325769739[50] = 0;
   out_1057825914325769739[51] = 0;
   out_1057825914325769739[52] = 0;
   out_1057825914325769739[53] = 0;
}
void h_10(double *state, double *unused, double *out_6474328160559022177) {
   out_6474328160559022177[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6474328160559022177[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6474328160559022177[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_32748343774837024) {
   out_32748343774837024[0] = 0;
   out_32748343774837024[1] = 9.8100000000000005*cos(state[1]);
   out_32748343774837024[2] = 0;
   out_32748343774837024[3] = 0;
   out_32748343774837024[4] = -state[8];
   out_32748343774837024[5] = state[7];
   out_32748343774837024[6] = 0;
   out_32748343774837024[7] = state[5];
   out_32748343774837024[8] = -state[4];
   out_32748343774837024[9] = 0;
   out_32748343774837024[10] = 0;
   out_32748343774837024[11] = 0;
   out_32748343774837024[12] = 1;
   out_32748343774837024[13] = 0;
   out_32748343774837024[14] = 0;
   out_32748343774837024[15] = 1;
   out_32748343774837024[16] = 0;
   out_32748343774837024[17] = 0;
   out_32748343774837024[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_32748343774837024[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_32748343774837024[20] = 0;
   out_32748343774837024[21] = state[8];
   out_32748343774837024[22] = 0;
   out_32748343774837024[23] = -state[6];
   out_32748343774837024[24] = -state[5];
   out_32748343774837024[25] = 0;
   out_32748343774837024[26] = state[3];
   out_32748343774837024[27] = 0;
   out_32748343774837024[28] = 0;
   out_32748343774837024[29] = 0;
   out_32748343774837024[30] = 0;
   out_32748343774837024[31] = 1;
   out_32748343774837024[32] = 0;
   out_32748343774837024[33] = 0;
   out_32748343774837024[34] = 1;
   out_32748343774837024[35] = 0;
   out_32748343774837024[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_32748343774837024[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_32748343774837024[38] = 0;
   out_32748343774837024[39] = -state[7];
   out_32748343774837024[40] = state[6];
   out_32748343774837024[41] = 0;
   out_32748343774837024[42] = state[4];
   out_32748343774837024[43] = -state[3];
   out_32748343774837024[44] = 0;
   out_32748343774837024[45] = 0;
   out_32748343774837024[46] = 0;
   out_32748343774837024[47] = 0;
   out_32748343774837024[48] = 0;
   out_32748343774837024[49] = 0;
   out_32748343774837024[50] = 1;
   out_32748343774837024[51] = 0;
   out_32748343774837024[52] = 0;
   out_32748343774837024[53] = 1;
}
void h_13(double *state, double *unused, double *out_2854439485558780128) {
   out_2854439485558780128[0] = state[3];
   out_2854439485558780128[1] = state[4];
   out_2854439485558780128[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2775929548976754285) {
   out_2775929548976754285[0] = 0;
   out_2775929548976754285[1] = 0;
   out_2775929548976754285[2] = 0;
   out_2775929548976754285[3] = 1;
   out_2775929548976754285[4] = 0;
   out_2775929548976754285[5] = 0;
   out_2775929548976754285[6] = 0;
   out_2775929548976754285[7] = 0;
   out_2775929548976754285[8] = 0;
   out_2775929548976754285[9] = 0;
   out_2775929548976754285[10] = 0;
   out_2775929548976754285[11] = 0;
   out_2775929548976754285[12] = 0;
   out_2775929548976754285[13] = 0;
   out_2775929548976754285[14] = 0;
   out_2775929548976754285[15] = 0;
   out_2775929548976754285[16] = 0;
   out_2775929548976754285[17] = 0;
   out_2775929548976754285[18] = 0;
   out_2775929548976754285[19] = 0;
   out_2775929548976754285[20] = 0;
   out_2775929548976754285[21] = 0;
   out_2775929548976754285[22] = 1;
   out_2775929548976754285[23] = 0;
   out_2775929548976754285[24] = 0;
   out_2775929548976754285[25] = 0;
   out_2775929548976754285[26] = 0;
   out_2775929548976754285[27] = 0;
   out_2775929548976754285[28] = 0;
   out_2775929548976754285[29] = 0;
   out_2775929548976754285[30] = 0;
   out_2775929548976754285[31] = 0;
   out_2775929548976754285[32] = 0;
   out_2775929548976754285[33] = 0;
   out_2775929548976754285[34] = 0;
   out_2775929548976754285[35] = 0;
   out_2775929548976754285[36] = 0;
   out_2775929548976754285[37] = 0;
   out_2775929548976754285[38] = 0;
   out_2775929548976754285[39] = 0;
   out_2775929548976754285[40] = 0;
   out_2775929548976754285[41] = 1;
   out_2775929548976754285[42] = 0;
   out_2775929548976754285[43] = 0;
   out_2775929548976754285[44] = 0;
   out_2775929548976754285[45] = 0;
   out_2775929548976754285[46] = 0;
   out_2775929548976754285[47] = 0;
   out_2775929548976754285[48] = 0;
   out_2775929548976754285[49] = 0;
   out_2775929548976754285[50] = 0;
   out_2775929548976754285[51] = 0;
   out_2775929548976754285[52] = 0;
   out_2775929548976754285[53] = 0;
}
void h_14(double *state, double *unused, double *out_5002123430540527349) {
   out_5002123430540527349[0] = state[6];
   out_5002123430540527349[1] = state[7];
   out_5002123430540527349[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2024962517969602557) {
   out_2024962517969602557[0] = 0;
   out_2024962517969602557[1] = 0;
   out_2024962517969602557[2] = 0;
   out_2024962517969602557[3] = 0;
   out_2024962517969602557[4] = 0;
   out_2024962517969602557[5] = 0;
   out_2024962517969602557[6] = 1;
   out_2024962517969602557[7] = 0;
   out_2024962517969602557[8] = 0;
   out_2024962517969602557[9] = 0;
   out_2024962517969602557[10] = 0;
   out_2024962517969602557[11] = 0;
   out_2024962517969602557[12] = 0;
   out_2024962517969602557[13] = 0;
   out_2024962517969602557[14] = 0;
   out_2024962517969602557[15] = 0;
   out_2024962517969602557[16] = 0;
   out_2024962517969602557[17] = 0;
   out_2024962517969602557[18] = 0;
   out_2024962517969602557[19] = 0;
   out_2024962517969602557[20] = 0;
   out_2024962517969602557[21] = 0;
   out_2024962517969602557[22] = 0;
   out_2024962517969602557[23] = 0;
   out_2024962517969602557[24] = 0;
   out_2024962517969602557[25] = 1;
   out_2024962517969602557[26] = 0;
   out_2024962517969602557[27] = 0;
   out_2024962517969602557[28] = 0;
   out_2024962517969602557[29] = 0;
   out_2024962517969602557[30] = 0;
   out_2024962517969602557[31] = 0;
   out_2024962517969602557[32] = 0;
   out_2024962517969602557[33] = 0;
   out_2024962517969602557[34] = 0;
   out_2024962517969602557[35] = 0;
   out_2024962517969602557[36] = 0;
   out_2024962517969602557[37] = 0;
   out_2024962517969602557[38] = 0;
   out_2024962517969602557[39] = 0;
   out_2024962517969602557[40] = 0;
   out_2024962517969602557[41] = 0;
   out_2024962517969602557[42] = 0;
   out_2024962517969602557[43] = 0;
   out_2024962517969602557[44] = 1;
   out_2024962517969602557[45] = 0;
   out_2024962517969602557[46] = 0;
   out_2024962517969602557[47] = 0;
   out_2024962517969602557[48] = 0;
   out_2024962517969602557[49] = 0;
   out_2024962517969602557[50] = 0;
   out_2024962517969602557[51] = 0;
   out_2024962517969602557[52] = 0;
   out_2024962517969602557[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_7503614556887712841) {
  err_fun(nom_x, delta_x, out_7503614556887712841);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2650454973869903341) {
  inv_err_fun(nom_x, true_x, out_2650454973869903341);
}
void pose_H_mod_fun(double *state, double *out_140121567557128365) {
  H_mod_fun(state, out_140121567557128365);
}
void pose_f_fun(double *state, double dt, double *out_246987440794206982) {
  f_fun(state,  dt, out_246987440794206982);
}
void pose_F_fun(double *state, double dt, double *out_7435016886215278560) {
  F_fun(state,  dt, out_7435016886215278560);
}
void pose_h_4(double *state, double *unused, double *out_4331234714176828190) {
  h_4(state, unused, out_4331234714176828190);
}
void pose_H_4(double *state, double *unused, double *out_1057825914325769739) {
  H_4(state, unused, out_1057825914325769739);
}
void pose_h_10(double *state, double *unused, double *out_6474328160559022177) {
  h_10(state, unused, out_6474328160559022177);
}
void pose_H_10(double *state, double *unused, double *out_32748343774837024) {
  H_10(state, unused, out_32748343774837024);
}
void pose_h_13(double *state, double *unused, double *out_2854439485558780128) {
  h_13(state, unused, out_2854439485558780128);
}
void pose_H_13(double *state, double *unused, double *out_2775929548976754285) {
  H_13(state, unused, out_2775929548976754285);
}
void pose_h_14(double *state, double *unused, double *out_5002123430540527349) {
  h_14(state, unused, out_5002123430540527349);
}
void pose_H_14(double *state, double *unused, double *out_2024962517969602557) {
  H_14(state, unused, out_2024962517969602557);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
