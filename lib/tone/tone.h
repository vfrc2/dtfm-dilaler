/**
 * @file
 * #brief Module generate dtmf tomen by char
 * 
 * Samples calc for Fpwm = FCK / QUANT
 * 
 * call tone_pwm_overflow_cb in intracpt of timer owerflow
 */

#include "stdint.h"

#ifndef __tone_H
#define __tone_H

#define FCK 8000000L
#define QUANT 255
#define SAMPLE_COUNT 128

extern int tone_pwm_stop(void);
extern int tone_pwm_start(void);
extern int tone_pwm_setDuty(uint8_t value);

int tone_pwm_overflow_cb(void);

int tone_init();
int tone_play(const char ch);
int tone_stop();

#endif