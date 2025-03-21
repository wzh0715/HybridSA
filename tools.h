#pragma once

#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>

#include "config.h"

using namespace hls;
using namespace std;

void LoadBiasNorm(ap_uint<NORM_BIT> *norm, float *bias, unsigned M, bool mode);

void ConvertInputToStream(ap_uint<MAX_INP * BIT> *A, stream<ap_uint<MAX_INP * BIT>> &conv_a, stream<ap_uint<MAX_INP * BIT>> &mm_a, bool mode, unsigned R, unsigned C, unsigned N, unsigned M);

void Padding(stream<ap_uint<MAX_INP * BIT>> &in, stream<ap_uint<MAX_INP * BIT>> &out, unsigned R, unsigned C, unsigned N, unsigned P, bool mode);

void Sliding(stream<ap_uint<MAX_INP * BIT>> &in, stream<ap_uint<MAX_INP * BIT>> &out, unsigned R, unsigned C, unsigned N, unsigned M, unsigned K, unsigned P, unsigned S, bool mode);

void loadWeight(ap_uint<MAX_INP * BIT> *Conv_MM_Weight, unsigned num);

void ConvWeightToStream(stream<ap_uint<MAX_INP * BIT>> fifo_conv_w[MAX_A_COL], unsigned out_r, unsigned num);

void ConvertWeightToStream(ap_uint<MAX_INP * BIT> *Conv_MM_Weight, stream<ap_uint<MAX_INP * BIT>> fifo_conv_w[MAX_A_COL], stream<ap_uint<MAX_OUP * BIT>> &fifo_mm_w, unsigned R, unsigned N, unsigned K, unsigned M, unsigned P, unsigned S, bool mode);

void ConvWeightToArray(stream<ap_uint<MAX_INP * BIT>> fifo_W_in[MAX_A_COL], stream<ap_uint<SA_INP * BIT>> fifo_W_local_out[MAX_A_ROW][MAX_A_COL], unsigned num_w_in, bool mode);

void MMWeightToArray(stream<ap_uint<MAX_OUP * BIT>> &in, stream<ap_uint<SA_OUP * BIT>> out[MAX_A_ROW][MAX_A_COL], unsigned num_w_in, bool mode);

void MuxWeightStream(stream<ap_uint<SA_INP * BIT>> Conv_SA_W[MAX_A_ROW][MAX_A_COL], stream<ap_uint<SA_OUP * BIT>> MM_SA_W[MAX_A_ROW][MAX_A_COL], stream<ap_uint<SA_OUP * BIT>> fifo_SA_W[MAX_A_ROW][MAX_A_COL], unsigned num_w_sa, bool mode);

void ConvertInputToArray(stream<ap_uint<MAX_INP * BIT>> &conv3_sild, stream<ap_uint<MAX_INP * BIT>> &mm_a, stream<ap_uint<SA_INP * BIT>> out[MAX_A_ROW][MAX_A_COL], unsigned num_a_sa, bool mode);

void PE(stream<ap_uint<SA_INP * BIT>> &fifo_A_in, stream<ap_uint<SA_INP * BIT>> &fifo_W_in, stream<float> fifo_C_out[SA_OUP], unsigned C, unsigned num_a_sa, bool mode);

void Compute(stream<ap_uint<SA_INP * BIT>> fifo_SA_A[MAX_A_ROW][MAX_A_COL], stream<ap_uint<SA_OUP * BIT>> fifo_SA_W[MAX_A_ROW][MAX_A_COL], stream<float> fifo_SA_O[MAX_A_ROW][MAX_A_COL][SA_OUP], unsigned num_a_sa, unsigned num, bool mode);

void ConvertToOutStream(stream<float> fifo_SA_O[MAX_A_ROW][MAX_A_COL][SA_OUP], stream<float> conv_out[MAX_OUP], stream<float> mm_out[MAX_OUP], unsigned num, unsigned R, unsigned M, bool mode);

void ConvToOutStream(stream<float> fifo_CONV3_ACC[MAX_OUP], stream<float> CONV3_OUT[MAX_OUP], unsigned OUT_R, unsigned OUT_C, unsigned N, unsigned M, unsigned K, bool mode);

void ConvBiasBN(stream<float> CONV3_OUT[MAX_OUP], stream<float> CONV3_Bias[MAX_OUP], unsigned out_r, unsigned out_c, unsigned M, bool mode);

void ResOutput(stream<float> CONV_RES[MAX_OUP], stream<float> MM_RES[MAX_OUP], ap_uint<MAX_OUP * BIT> *output, unsigned R, unsigned C, unsigned M, unsigned K, unsigned P, unsigned S, bool mode);