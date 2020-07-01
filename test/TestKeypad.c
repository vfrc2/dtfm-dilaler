#include "unity.h"
#include "keypad.h"
#include <stdio.h>

uint8_t colRead = 0b11110000;
uint8_t rowRead = 0b00001111;

uint8_t mockKeypadRead(KeypadReadVariantEnum variant)
{
    if (variant == KEYPAD_READ_VARIANT_ROWS)
        return rowRead;
    else
        return colRead;
}

static KeypadType t = {&mockKeypadRead};

void TestNoPresed()
{
    char res = keypad_getkey(&t);
    TEST_ASSERT_EQUAL_INT(0, res);
}

void TestPressAll()
{
    const char exp[16] = {
        '1',
        '2',
        '3',
        'A',
        '4',
        '5',
        '6',
        'B',
        '7',
        '8',
        '9',
        'C',
        '*',
        '0',
        '#',
        'D',
    };
    int pos = 0;
    for (uint8_t col = 1; col <= 8; col *= 2)
    {
        for (uint8_t row = 1; row <= 8; row *= 2)
        {
            rowRead = 0b00001111 | (col << 4);
            colRead = 0b11110000 | row;
            char expected = exp[pos];

            char res = keypad_getkey(&t);
            char buff[40];
            sprintf(buff, "Expect '%c', receive '%c' %d", expected, res, res);
            TEST_ASSERT_MESSAGE(expected == res, buff);
            pos += 1;
        }
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TestNoPresed);
    RUN_TEST(TestPressAll);
    return UNITY_END();
}
