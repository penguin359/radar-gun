/*
 * fft.h
 *
 *  Created on: Apr 28, 2016
 *      Author: lorenl
 */

#ifndef SOURCES_FFT_H_
#define SOURCES_FFT_H_


#include <stdint.h>
#include <arm_math.h>

//extern q15_t data[16];
extern q15_t dinDC[];
extern q15_t din1Hz[];
extern q15_t din1HzShort[];
extern q15_t dinMulti[];
extern q15_t din50ms[];
extern q15_t din20ms[];
extern const int log2N20ms;

void run_fft(void);

int32_t find_peak_frequency(const q15_t *din, int log2N, int fs);
int32_t convertToSpeed(int32_t freq);

#endif /* SOURCES_FFT_H_ */
