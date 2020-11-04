#include "unity.h"
#include "../lib/tone/tone.h"
#include <stdio.h>
#include <stdbool.h>

bool runing = false;
uint8_t duty = 0;

int tone_pwm_stop(void) {
    runing = false;
}

int tone_pwm_start(void) {
    runing = true;
}

int tone_pwm_setDuty(uint8_t value) {
    duty = value;
}

void TestOne() {
    tone_init();
    tone_play('*');
    for (int i = 0; i < 512; i++) {
        tone_pwm_overflow_cb();
        printf("%i,\n", duty);
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(TestOne);

    return UNITY_END();
}
