/**
 * @file
 * #brief Module generate dtmf tomen by char
 * 
 * Samples calc for Fpwm = 62.5KHz
 * 
 * call tone_pwm_overflow_cb in intracpt of timer owerflow
 */

#ifndef __tone_H
#define __tone_H

#include "stdint.h"

extern int tone_pwm_stop(void);
extern int tone_pwm_start(void);
extern int tone_pwm_setDuty(uint8_t value);

int tone_pwm_overflow_cb(void);

int tone_init();
int tone_play(const char ch);
int tone_stop();

#endif