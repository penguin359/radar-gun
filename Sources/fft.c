/*
 * fft.c
 *
 *  Created on: Apr 28, 2016
 *      Author: lorenl
 */

#include <stdint.h>
#include <arm_math.h>
#include <arm_const_structs.h>

#include "test_data.h"


const static arm_cfft_instance_q31 *S;

//int32_t data[16] = { 0, };

void calculate_fft(q31_t *data, uint16_t length)
{
	switch (length) {
		case 16:
			S = &arm_cfft_sR_q31_len16;
			break;
		case 32:
			S = &arm_cfft_sR_q31_len32;
			break;
		case 64:
			S = &arm_cfft_sR_q31_len64;
			break;
		case 128:
			S = &arm_cfft_sR_q31_len128;
			break;
		case 256:
			S = &arm_cfft_sR_q31_len256;
			break;
		case 512:
			S = &arm_cfft_sR_q31_len512;
			break;
		case 1024:
			S = &arm_cfft_sR_q31_len1024;
			break;
		case 2048:
			S = &arm_cfft_sR_q31_len2048;
			break;
		case 4096:
			S = &arm_cfft_sR_q31_len4096;
			break;
	}

	arm_cfft_q31(S, data, 0, 0);
}

void run_fft(void)
{
	size_t length = sizeof(dinDC)/sizeof(dinDC[0])/2;
	calculate_fft(dinDC, length);
}
