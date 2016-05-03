#ifndef _FFT_H_
#define _FFT_H_


#include <stdint.h>

typedef struct
{
	int32_t re;
	int32_t im;
} int32c;

typedef struct
{
	double re;
	double im;
} doublec;

doublec convertFromQ31(int32c value);
int32c convertToQ31(doublec value);

doublec complexAdd(doublec a, doublec b);
doublec complexMultiply(doublec a, doublec b);
doublec complexExp(double val);

void mips_fft32(int32c *dout, int32c *din, int32c *twiddles, int32c *scratch, int log2N);
int32_t find_peak_frequency(const int32c *din, int log2N, int fs);
int32_t convertToSpeed(int32_t freq);



#endif /* _FFT_H_ */
