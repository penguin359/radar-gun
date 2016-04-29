/*
 * fft.h
 *
 *  Created on: Apr 28, 2016
 *      Author: lorenl
 */

#ifndef SOURCES_FFT_H_
#define SOURCES_FFT_H_


//extern int32_t data[16];
extern int32_t dinDC[];
extern int32_t din1Hz[];
extern int32_t din1HzShort[];
extern int32_t dinMulti[];
extern int32_t din50ms[];
extern int32_t din20ms[];

void run_fft(void);

#endif /* SOURCES_FFT_H_ */
