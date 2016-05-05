#ifndef _FFT_H_
#define _FFT_H_


#include <stdint.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/*
typedef struct
{
	int32_t re;
	int32_t im;
} int32c;
*/
typedef int16_t q15_t;

typedef struct
{
	double re;
	double im;
} doublec;

doublec convertFromQ15(q15_t *value);
void convertToQ15(doublec value, q15_t *retval);

doublec complexAdd(doublec a, doublec b);
doublec complexMultiply(doublec a, doublec b);
doublec complexExp(double val);

void mips_fft32(q15_t *dout, q15_t *din, q15_t *twiddles, q15_t *scratch, int log2N);
int32_t find_peak_frequency(const q15_t *din, int log2N, int fs);
int32_t convertToSpeed(int32_t freq);



#endif /* _FFT_H_ */
