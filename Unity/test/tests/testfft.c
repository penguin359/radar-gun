#include <math.h>
#include <string.h>

#include "unity.h"
#include "fft.h"
#include "test_data.h"


#define BUFFER_GUARD	64
#define LOG_2N		11
#define N_SAMPLES	(1 << LOG_2N)

#define UNUSED_BYTE	0x5a

static q15_t doutBuffer   [2*N_SAMPLES + 2*2*BUFFER_GUARD];
static q15_t dinBuffer    [2*N_SAMPLES + 2*2*BUFFER_GUARD];
static q15_t fftcBuffer   [2*N_SAMPLES + 2*2*BUFFER_GUARD];
static q15_t scratchBuffer[2*N_SAMPLES + 2*2*BUFFER_GUARD];

static q15_t * const doutPtr    = doutBuffer    + 2*BUFFER_GUARD;
static q15_t * const dinPtr     = dinBuffer     + 2*BUFFER_GUARD;
static q15_t * const fftcPtr    = fftcBuffer    + 2*BUFFER_GUARD;
static q15_t * const scratchPtr = scratchBuffer + 2*BUFFER_GUARD;

void setUp(void)
{
	memset(doutBuffer,    UNUSED_BYTE, sizeof(doutBuffer));
	memset(dinBuffer,     UNUSED_BYTE, sizeof(dinBuffer));
	memset(fftcBuffer,    UNUSED_BYTE, sizeof(fftcBuffer));
	memset(scratchBuffer, UNUSED_BYTE, sizeof(scratchBuffer));
}

void tearDown(void)
{
}

void testConvertFromQ15(void)
{
	q15_t in[2];
	doublec out;

	in[0] =   0; in[1] =   0;
	out = convertFromQ15(in);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.im);

	in[0] =   1 << 14; in[1] =   0;
	out = convertFromQ15(in);
	TEST_ASSERT_EQUAL_DOUBLE(  .5, out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.im);

	in[0] =   1 << 13; in[1] =   1 << 12;
	out = convertFromQ15(in);
	TEST_ASSERT_EQUAL_DOUBLE(  .25, out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  .125, out.im);
}

void testConvertToQ15(void)
{
	doublec in;
	q15_t out[2];

	/* TODO Check rounding for Q15 conversion */

	in.re =   0.; in.im =   0.;
	convertToQ15(in, out);
	TEST_ASSERT_EQUAL_INT16(  0, out[0]);
	TEST_ASSERT_EQUAL_INT16(  0, out[1]);

	in.re =   .5; in.im =   0.;
	convertToQ15(in, out);
	TEST_ASSERT_EQUAL_INT16(  1 << 14, out[0]);
	TEST_ASSERT_EQUAL_INT16(  0, out[1]);

	in.re =   .25; in.im =   .125;
	convertToQ15(in, out);
	TEST_ASSERT_EQUAL_INT16(  1 << 13, out[0]);
	TEST_ASSERT_EQUAL_INT16(  1 << 12, out[1]);

	in.re =   .75 + (1.1 / 4294967296.); in.im =   .125;
	convertToQ15(in, out);
	TEST_ASSERT_EQUAL_INT16(  3 << 13, out[0]);
	TEST_ASSERT_EQUAL_INT16(  1 << 12, out[1]);
}

#if 0
//void testConvertFromQ31(void)
{
	int32c in;
	doublec out;

	in.re =   0; in.im =   0;
	out = convertFromQ31(in);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.im);

	in.re =   1 << 30; in.im =   0;
	out = convertFromQ31(in);
	TEST_ASSERT_EQUAL_DOUBLE(  .5, out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., out.im);

	in.re =   1 << 29; in.im =   1 << 28;
	out = convertFromQ31(in);
	TEST_ASSERT_EQUAL_DOUBLE(  .25, out.re);
	TEST_ASSERT_EQUAL_DOUBLE(  .125, out.im);
}

//void testConvertToQ31(void)
{
	doublec in;
	int32c out;

	/* TODO Check rounding for Q31 conversion */

	in.re =   0.; in.im =   0.;
	out = convertToQ31(in);
	TEST_ASSERT_EQUAL_INT32(  0, out.re);
	TEST_ASSERT_EQUAL_INT32(  0, out.im);

	in.re =   .5; in.im =   0.;
	out = convertToQ31(in);
	TEST_ASSERT_EQUAL_INT32(  1 << 30, out.re);
	TEST_ASSERT_EQUAL_INT32(  0, out.im);

	in.re =   .25; in.im =   .125;
	out = convertToQ31(in);
	TEST_ASSERT_EQUAL_INT32(  1 << 29, out.re);
	TEST_ASSERT_EQUAL_INT32(  1 << 28, out.im);

	in.re =   .75 + (1.1 / 4294967296.); in.im =   .125;
	out = convertToQ31(in);
	TEST_ASSERT_EQUAL_INT32(  3 << 29, out.re);
	TEST_ASSERT_EQUAL_INT32(  1 << 28, out.im);
}
#endif

void testAddComplex(void)
{
	doublec	a;
	doublec	b;
	doublec x;

	a.re =  10.; a.im =   0.;
	b.re =   3.; b.im =   0.;
	x = complexAdd(a, b);
	TEST_ASSERT_EQUAL_DOUBLE( 13., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.im);

	a.re =   7.; a.im =   0.;
	b.re =  -8.; b.im =   0.;
	x = complexAdd(a, b);
	TEST_ASSERT_EQUAL_DOUBLE( -1., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.im);

	a.re =  -2.; a.im =   4.;
	b.re =  -3.; b.im =   5.;
	x = complexAdd(a, b);
	TEST_ASSERT_EQUAL_DOUBLE( -5., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  9., x.im);
}

void testMultiplyComplex(void)
{
	doublec	a;
	doublec	b;
	doublec x;

	a.re =  10.; a.im =   0.;
	b.re =   3.; b.im =   0.;
	x = complexMultiply(a, b);
	TEST_ASSERT_EQUAL_DOUBLE( 30., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.im);

	a.re =   0.; a.im =  10.;
	b.re =   0.; b.im =   3.;
	x = complexMultiply(a, b);
	TEST_ASSERT_EQUAL_DOUBLE(-30., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.im);

	a.re =  10.; a.im =   0.;
	b.re =   0.; b.im =   3.;
	x = complexMultiply(a, b);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.re);
	TEST_ASSERT_EQUAL_DOUBLE( 30., x.im);

	a.re =   0.; a.im =  10.;
	b.re =   3.; b.im =   0.;
	x = complexMultiply(a, b);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.re);
	TEST_ASSERT_EQUAL_DOUBLE( 30., x.im);
}

void testComplexExp(void)
{
	doublec x;

	x = complexExp(0.);
	TEST_ASSERT_EQUAL_DOUBLE(  1., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  0., x.im);

	x = complexExp(M_PI);
	TEST_ASSERT_EQUAL_DOUBLE( -1., x.re);
	TEST_ASSERT_DOUBLE_WITHIN(1e-15,  0., x.im);

	x = complexExp(M_PI/2.);
	TEST_ASSERT_DOUBLE_WITHIN(1e-15,  0., x.re);
	TEST_ASSERT_EQUAL_DOUBLE(  1., x.im);
}

static void checkBufferGuards(void)
{
	static char * const bufferList[] = {
		(char *)doutBuffer,
		(char *)dinBuffer,
		(char *)fftcBuffer,
		(char *)scratchBuffer,
	};
	static const int bufferGuardBytes = BUFFER_GUARD * sizeof(q15_t)*2;
	static const int nSamplesBytes = N_SAMPLES * sizeof(q15_t)*2;
	size_t i;
	int j;
	char *buffer;

	for(i = 0; i < sizeof(bufferList)/sizeof(bufferList[0]); i++) {
		buffer = bufferList[i];
		for(j = 0; j < bufferGuardBytes; j++) {
			TEST_ASSERT_EQUAL_HEX8(UNUSED_BYTE, buffer[j]);
			TEST_ASSERT_EQUAL_HEX8(UNUSED_BYTE, buffer[bufferGuardBytes + nSamplesBytes + j]);
		}
	}
}

static void checkBufferContents(const q15_t *expected, const q15_t *buffer, int log2N, const char *msg)
{
	int samples = 1 << log2N;
	int i;

	for(i = 0; i < samples*2; i++) {
		/* XXX There seems to be an off-by-one rounding error somewhere */
		TEST_ASSERT_INT16_WITHIN_MESSAGE(1, expected[i], buffer[i], msg);
	}
}

#if 0
static void printBufferContents(const int32c *buffer, int log2N, const char *name)
{
	int samples = 1 << log2N;
	int i;

	printf("int32c %s = {\n", name);
	for(i = 0; i < samples; i++) {
		printf("  { %9d, %9d },\n", buffer[i].re, buffer[i].im);
	}
	printf("};\n");
}
#endif

static const q15_t dinZero[N_SAMPLES*2] = { 0, };

static void loadBuffer(q15_t *buffer, const q15_t *contents)
{
	int i;

	for(i = 0; i < N_SAMPLES*2; i++)
		buffer[i] = contents[i];
}

void testBufferChecks(void)
{
	checkBufferGuards();
	checkBufferContents(dinBuffer, dinPtr, LOG_2N, "dinBuffer");
	loadBuffer(doutPtr, dinZero);
	loadBuffer(dinPtr, dinZero);
	loadBuffer(fftcPtr, dinZero);
	loadBuffer(scratchPtr, dinZero);
	checkBufferContents(dinZero, dinPtr, LOG_2N, "dinZero");
	checkBufferGuards();
}

void testBufferCheckBoundaries(void)
{
	TEST_IGNORE();
	*(dinPtr - 1*2) = 0;
	*(dinPtr - 1*2+1) = 0;
	*(dinPtr + N_SAMPLES*2) = 0;
	*(dinPtr + N_SAMPLES*2+1) = 0;
	checkBufferGuards();
}

void testZeroFFT(void)
{
	loadBuffer(dinPtr, dinZero);
	checkBufferContents(dinZero, dinPtr, LOG_2N, "dinZero");
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, LOG_2N);
	checkBufferContents(dinZero, doutPtr, LOG_2N, "doutZero");
	checkBufferGuards();
}

void testOneSampleFFT(void)
{
	int32_t i;

	for(i = 0; i < 32; i++) {
		dinPtr[0] = i; dinPtr[1] = 0;
		/* Check FFT with a sample size of 2^0 = 1 */
		mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, 0);
		TEST_ASSERT_EQUAL_INT16(i, doutPtr[0]);
		TEST_ASSERT_EQUAL_INT16(0, doutPtr[1]);
	}

	/* Verify no buffer overrun from mips_fft32() */
	TEST_ASSERT_EQUAL_INT(UNUSED_BYTE, *(char *)(dinPtr+1*2));

	checkBufferGuards();
}

void testTwoSampleFFT(void)
{
	int32_t i;

	for(i = 0; i < 32; i++) {
		dinPtr[0*2] = i; dinPtr[0*2+1] = 0;
		dinPtr[1*2] = i; dinPtr[1*2+1] = 0;
		/* Check FFT with a sample size of 2^1 = 2 */
		mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, 1);
		TEST_ASSERT_EQUAL_INT16(i, doutPtr[0*2+0]);
		TEST_ASSERT_EQUAL_INT16(0, doutPtr[0*2+1]);
		TEST_ASSERT_EQUAL_INT16(0, doutPtr[1*2+0]);
		TEST_ASSERT_EQUAL_INT16(0, doutPtr[1*2+1]);
	}

	/* Verify no buffer overrun from mips_fft32() */
	TEST_ASSERT_EQUAL_INT(UNUSED_BYTE, *(char *)(dinPtr+2*2));

	checkBufferGuards();
}

void testDataDCFFT(void)
{
	loadBuffer(dinPtr, dinDC);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2NDC);
	//printBufferContents(dinPtr, log2NDC, "dinPtr");
	//printBufferContents(doutPtr, log2NDC, "doutPtr");
	//printBufferContents(fftDC, log2NDC, "fftDC");
	checkBufferContents(fftDC, doutPtr, log2NDC, "fftDC");
	checkBufferGuards();
}

void testData1HzShortFFT(void)
{
	//TEST_IGNORE_MESSAGE("Broken, must be fixed!!!");
	loadBuffer(dinPtr, din1HzShort);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N1HzShort);
	//printBufferContents(dinPtr, log2N1HzShort, "dinPtr");
	//printBufferContents(doutPtr, log2N1HzShort, "doutPtr");
	//printBufferContents(fft1HzShort, log2N1HzShort, "fft1HzShort");
	checkBufferContents(fft1HzShort, doutPtr, log2N1HzShort, "fft1HzShort");
	checkBufferGuards();
}

void testData1HzFFT(void)
{
	loadBuffer(dinPtr, din1Hz);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N1Hz);
	//printBufferContents(dinPtr, log2N1Hz, "dinPtr");
	//printBufferContents(doutPtr, log2N1Hz, "doutPtr");
	checkBufferContents(fft1Hz, doutPtr, log2N1Hz, "fft1Hz");
	checkBufferGuards();
}

void testDataMultiFFT(void)
{
	loadBuffer(dinPtr, dinMulti);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2NMulti);
	//printBufferContents(dinPtr, log2NMulti, "dinPtr");
	//printBufferContents(doutPtr, log2NMulti, "doutPtr");
	//printBufferContents(fftMulti, log2NMulti, "fftMulti");
	checkBufferContents(fftMulti, doutPtr, log2NMulti, "fftMulti");
	checkBufferGuards();
}

void testData50msFFT(void)
{
	loadBuffer(dinPtr, din50ms);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N50ms);
	checkBufferContents(fft50ms, doutPtr, log2N50ms, "fft50ms");
	checkBufferGuards();
}

void testData20msFFT(void)
{
	loadBuffer(dinPtr, din20ms);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20ms);
	checkBufferContents(fft20ms, doutPtr, log2N20ms, "fft20ms");
	checkBufferGuards();
}

void testData20msNoiseFFT(void)
{
	loadBuffer(dinPtr, din20msNoise);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20msNoise);
	checkBufferContents(fft20msNoise, doutPtr, log2N20msNoise, "fft20msNoise");
	checkBufferGuards();
}

void testData20ms10m_upFFT(void)
{
	loadBuffer(dinPtr, din20ms10m_up);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20ms10m_up);
	checkBufferContents(fft20ms10m_up, doutPtr, log2N20ms10m_up, "fft20ms10m_up");
	checkBufferGuards();
}

void testData20ms10m_downFFT(void)
{
	loadBuffer(dinPtr, din20ms10m_down);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20ms10m_down);
	checkBufferContents(fft20ms10m_down, doutPtr, log2N20ms10m_down, "fft20ms10m_down");
	checkBufferGuards();
}

void testFindPeakFrequencyDC(void)
{
	int32_t freq;

	freq = find_peak_frequency(fftDC, log2NDC, 1);
	TEST_ASSERT_EQUAL_INT32(0, freq);
}

void testFindPeakFrequency1Hz(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft1Hz, log2N1Hz, 1);
	TEST_ASSERT_EQUAL_INT32(1, freq);
}

void testFindPeakFrequency50ms(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft50ms, log2N50ms, 4);
	TEST_ASSERT_EQUAL_INT32(1868, freq);
}

void testFindPeakFrequency20ms(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft20ms, log2N20ms, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
}

void testFindPeakFrequency20msNoise(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft20msNoise, log2N20msNoise, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
}

void testFindPeakFrequency20ms10m_up(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft20ms10m_up, log2N20ms10m_up, 4);
	TEST_ASSERT_EQUAL_INT32(852, freq);
}

void testFindPeakFrequency20ms10m_down(void)
{
	int32_t freq;

	freq = find_peak_frequency(fft20ms10m_down, log2N20ms10m_down, 4);
	TEST_ASSERT_EQUAL_INT32(640, freq);
}

void testConvertToSpeedDC(void)
{
	int32_t freq;
	int32_t speed;

	freq = 0;
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(speed, 0);
}

void testConvertToSpeed100Hz(void)
{
	int32_t freq;
	int32_t speed;

	freq = 100;
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(2, speed);
}

void testConvertToSpeed50ms(void)
{
	int32_t freq;
	int32_t speed;

	freq = 1868;
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(50, speed);
}

void testFromCaptureToSpeed50ms(void)
{
	int32_t freq;
	int32_t speed;

	loadBuffer(dinPtr, din50ms);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N50ms);
	freq = find_peak_frequency(doutPtr, log2N50ms, 4);
	TEST_ASSERT_EQUAL_INT32(1868, freq);
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(50, speed);
}

void testFromCaptureToSpeed20ms(void)
{
	int32_t freq;
	int32_t speed;

	loadBuffer(dinPtr, din20ms);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20ms);
	freq = find_peak_frequency(doutPtr, log2N20ms, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(20, speed);
}

void testFromCaptureToSpeed20msNoise(void)
{
	int32_t freq;
	int32_t speed;

	loadBuffer(dinPtr, din20msNoise);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20msNoise);
	freq = find_peak_frequency(doutPtr, log2N20msNoise, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(20, speed);
}

void testFromCaptureToSpeed20msBigNoise(void)
{
	int32_t freq;
	int32_t speed;

	loadBuffer(dinPtr, din20msBigNoise);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20msBigNoise);
	freq = find_peak_frequency(doutPtr, log2N20msBigNoise, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(20, speed);
}

void testFromCaptureToSpeed20msGiantNoise(void)
{
	int32_t freq;
	int32_t speed;

	loadBuffer(dinPtr, din20msGiantNoise);
	mips_fft32(doutPtr, dinPtr, fftcPtr, scratchPtr, log2N20msGiantNoise);
	freq = find_peak_frequency(doutPtr, log2N20msGiantNoise, 4);
	TEST_ASSERT_EQUAL_INT32(748, freq);
	speed = convertToSpeed(freq);
	TEST_ASSERT_EQUAL_INT32(20, speed);
}

/* Test convert to/from Q31/float */
