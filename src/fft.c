#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fft.h"



doublec convertFromQ31(int32c value)
{
	doublec retval;

	retval.re = (double)value.re / 2147483648.;
	retval.im = (double)value.im / 2147483648.;

	return retval;
}

int32c convertToQ31(doublec value)
{
	int32c retval;

	retval.re = (int32_t)(value.re * 2147483648. + .0);
	retval.im = (int32_t)(value.im * 2147483648. + .0);

	return retval;
}


doublec complexAdd(doublec a, doublec b)
{
	doublec retval;
	
	retval.re = a.re + b.re;
	retval.im = a.im + b.im;

	return retval;
}

doublec complexMultiply(doublec a, doublec b)
{
	doublec retval;

	retval.re = a.re * b.re - a.im * b.im;
	retval.im = a.re * b.im + a.im * b.re;

	return retval;
}

doublec complexExp(double val)
{
	doublec retval;

	retval.re = cos(val);
	retval.im = sin(val);

	return retval;
}

void mips_fft32(int32c *dout, int32c *din, int32c *twiddles, int32c *scratch, int log2N)
{
	int samples = 1 << log2N;
	int n;
	int k;
	double theta;
	doublec dinReal, doutReal;
	doublec e, p;
	doublec sum;

	(void)twiddles[0].re; /* Stop unused warnings */
	(void)scratch[0].re;
	//output[n] = 1/(2^log2(N))*sum(din[k]*exp(-j*2*pi*k*n/N),k=0,N-1)
	for(n = 0; n < samples; n++) {
		sum.re = 0.; sum.im = 0.;
		for(k = 0; k < samples; k++) {
			dinReal = convertFromQ31(din[k]);
			theta = -2. * M_PI * (double)k * (double)n / (double)samples;
			e = complexExp(theta);
			p = complexMultiply(dinReal, e);
			//printf("n:%2d, k:%2d, theta = %f, exp(%f, %f)\n", n, k, theta, e.re, e.im);
			//printf("n:%2d, k:%2d, din(%f, %f) X exp(%f, %f) = p(%f, %f)\n", n, k, dinReal.re, dinReal.im, e.re, e.im, p.re, p.im);
			sum = complexAdd(sum, complexMultiply(dinReal, complexExp(theta)));
			//printf("n:%2d, k:%2d, sum(%f, %f)\n", n, k, sum.re, sum.im);
		}
		doutReal.re = sum.re / (double)samples;
		doutReal.im = sum.im / (double)samples;
		dout[n] = convertToQ31(doutReal);
	}
}

int32_t find_peak_frequency(const int32c *din, int log2N, int fs)
{
	int16_t len = 1 << log2N;
	int16_t i;
	int32_t max_value = 0;
	int16_t max_bin = 0;

	for(i = 0; i < len; i++) {
		int32_t value = din[i].re*-1;
		if(value > max_value) {
			max_value = value;
			max_bin = i;
		}
		value = din[i].im*-1;
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

#define LOG_2N	6
#define N	64	/* 2^LOG_2N */

int32c din[N];
int32c dout[N];
int32c fft[N];
int32c scratch[N];

const char *filein = "signal.bin";
const char *fileout = "fft.bin";

//int main(int argc, char **argv)
int main2()
{
	FILE *fp;

	memset(din, 0L, sizeof(din));
	memset(dout, 0L, sizeof(dout));
	memset(fft, 0L, sizeof(fft));
	memset(scratch, 0L, sizeof(scratch));

	errno = 0;
	if((fp = fopen(filein, "r")) == NULL) {
		perror("fopen()");
		exit(1);
	}

	errno = 0;
	if(fread(din, sizeof(din), 1, fp) != 1) {
		perror("fread()");
		exit(1);
	}

	fclose(fp);

	mips_fft32(dout, din, fft, scratch, LOG_2N);

	errno = 0;
	if((fp = fopen(fileout, "w")) == NULL) {
		perror("fopen()");
		exit(1);
	}

	errno = 0;
	if(fwrite(dout, sizeof(dout), 1, fp) != 1) {
		perror("fwrite()");
		exit(1);
	}

	fclose(fp);

	exit(0);
}
