/*
 * fft.c
 *
 *  Created on: Apr 28, 2016
 *      Author: lorenl
 */

#include <stdint.h>
#include <arm_math.h>
#include <arm_const_structs.h>

/* Including needed modules to compile this module/procedure */
#include "CLS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "test_data.h"


const static arm_cfft_instance_q15 *S;

//int32_t data[16] = { 0, };

void calculate_fft(q15_t *data, uint16_t length)
{
	switch (length) {
		case 16:
			S = &arm_cfft_sR_q15_len16;
			break;
		case 32:
			S = &arm_cfft_sR_q15_len32;
			break;
		case 64:
			S = &arm_cfft_sR_q15_len64;
			break;
		case 128:
			S = &arm_cfft_sR_q15_len128;
			break;
		case 256:
			S = &arm_cfft_sR_q15_len256;
			break;
		case 512:
			S = &arm_cfft_sR_q15_len512;
			break;
		case 1024:
			S = &arm_cfft_sR_q15_len1024;
			break;
		case 2048:
			S = &arm_cfft_sR_q15_len2048;
			break;
		case 4096:
			S = &arm_cfft_sR_q15_len4096;
			break;
		default:
			return;
	}

	arm_cfft_q15(S, data, 0, 1);
}

#define fft_it(data)	(calculate_fft(data, (sizeof(data)/sizeof(data[0])/2)))
void run_fft(void)
{
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	//fft_it(dinDC);
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	//fft_it(din1Hz);
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	//fft_it(din1HzShort);
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	//fft_it(dinMulti);
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	//fft_it(din50ms);
	CLS1_SendStr(".\r\n", CLS1_GetStdio()->stdOut);
	fft_it(din20ms);
	//fft_it(din20msNoise);
	//fft_it(din20msBigNoise);
	//fft_it(din20msGiantNoise);
	//fft_it(din20ms10m_up);
	//fft_it(din20ms10m_down);
}

int32_t find_peak_frequency(const q15_t *din, int log2N, int fs)
{
	int16_t len = 1 << log2N;
	int16_t i;
	int32_t max_value = 0;
	int16_t max_bin = 0;

	for(i = 0; i < len/2; i++) {
		int32_t value = din[i*2]*-1;
		if(value > max_value) {
			max_value = value;
			max_bin = i;
		}
		value = din[i*2+1]*-1;
		if(value > max_value) {
			max_value = value;
			max_bin = i;
		}
	}

	return max_bin*fs;
}

int32_t convertToSpeed(int32_t freq)
{
	return freq*3/112;
}

