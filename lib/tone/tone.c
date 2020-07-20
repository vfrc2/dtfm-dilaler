#include "tone.h"

// DTMF Tone Matrix
// fb/fa  1209 Hz 1336 Hz 1477 Hz 1633 Hz
// 697 Hz 1       2       3       A
// 770 Hz 4       5       6       B
// 852 Hz 7       8       9       C
// 941 Hz *       0       #       D

#define SAMPLE_COUNT 128
#define FACTOR ((float)SAMPLE_COUNT / 62500.0)

static const int samples[SAMPLE_COUNT] = {
    64, 67,
    70, 73,
    76, 79,
    82, 85,
    88, 91,
    94, 96,
    99, 102,
    104, 106,
    109, 111,
    113, 115,
    117, 118,
    120, 121,
    123, 124,
    125, 126,
    126, 127,
    127, 127,
    127, 127,
    127, 127,
    126, 126,
    125, 124,
    123, 121,
    120, 118,
    117, 115,
    113, 111,
    109, 106,
    104, 102,
    99, 96,
    94, 91,
    88, 85,
    82, 79,
    76, 73,
    70, 67,
    64, 60,
    57, 54,
    51, 48,
    45, 42,
    39, 36,
    33, 31,
    28, 25,
    23, 21,
    18, 16,
    14, 12,
    10, 9,
    7, 6,
    4, 3,
    2, 1,
    1, 0,
    0, 0,
    0, 0,
    0, 0,
    1, 1,
    2, 3,
    4, 6,
    7, 9,
    10, 12,
    14, 16,
    18, 21,
    23, 25,
    28, 31,
    33, 36,
    39, 42,
    45, 48,
    51, 54,
    57, 60};

static inline int getSample(const uint8_t pos)
{
    if (pos > SAMPLE_COUNT)
        return samples[pos % SAMPLE_COUNT];
    else
        return samples[pos];
}

static float faSteps[4] = {
    697 * FACTOR,
    770 * FACTOR,
    852 * FACTOR,
    941 * FACTOR
};

static float fbSteps[4] = {
    1209 * FACTOR,
    1336 * FACTOR,
    1477 * FACTOR,
    1633 * FACTOR
};

static inline float getFaStep(const char ch)
{
    switch (ch)
    {
    case '1':
    case '2':
    case '3':
    case 'A':
        return faSteps[0];
    case '4':
    case '5':
    case '6':
    case 'B':
        return faSteps[1];
    case '7':
    case '8':
    case '9':
    case 'C':
        return faSteps[2];
    case '*':
    case '0':
    case '#':
    case 'D':
        return faSteps[3];
    default:
        return 0;
    }
}

static inline float getFbStep(const char ch)
{
    switch (ch)
    {
    case '1':
    case '4':
    case '7':
    case '*':
        return fbSteps[0];
    case '2':
    case '5':
    case '8':
    case '0':
        return fbSteps[1];
    case '3':
    case '6':
    case '9':
    case '#':
        return fbSteps[2];
    case 'A':
    case 'B':
    case 'C':
    case 'D':
        return fbSteps[3];
    default:
        return 0;
    }
}

static float posA = 0;
static float posB = 0;
static float stepA = 0;
static float stepB = 0;

int tone_pwm_overflow_cb()
{
    static uint8_t actualPosA;
    static uint8_t actualPosB;

    posA += stepA;
    posB += stepB;

    actualPosA = (uint8_t)((int64_t)posA % SAMPLE_COUNT);
    actualPosB = (uint8_t)((int64_t)posB % SAMPLE_COUNT);

    tone_pwm_setDuty(getSample(actualPosA) + (getSample(actualPosB) - (getSample(actualPosB) >> 2)));

    return 0;
}

int tone_init()
{
    tone_pwm_stop();

    posA = 0;
    posB = 0;
    stepA = 0;
    stepB = 0;

    for (int i = 0; i < 4; i++)
    {
    }

    return 0;
}

int tone_play(const char ch)
{
    tone_pwm_stop();

    stepA = getFaStep(ch);
    stepB = getFbStep(ch);

    tone_pwm_start();

    return 0;
}

int tone_stop()
{
    tone_pwm_stop();
    return 0;
}
