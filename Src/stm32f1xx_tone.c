#include "tone.h"
#include "main.h"
#include "tim.h"

int tone_pwm_start(void) {
    // do stuf to start PWM
    return 0;
}

int tone_pwm_stop(void) {
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
    return 0;
}

int tone_pwm_setDuty(uint8_t duty) {
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, duty);
    return 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM4) {
        tone_pwm_overflow_cb();
    }
}