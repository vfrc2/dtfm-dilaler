#include "keypad.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


int keypadInit(KeypadType* keypad) {
    return 0;
}

static uint8_t encode4to2(uint8_t input) {
    uint8_t y1 = (input & (1 << 1)) == (1 << 1);
    uint8_t y2 = (input & (1 << 2)) == (1 << 2);
    uint8_t y3 = (input & (1 << 3)) == (1 << 3);

    return (y1 || y3) | ((y2 || y3) << 1);
}

static char getCharByScanCode(uint8_t scancode) {
    const uint8_t rowScan = (scancode & 0b11110000) >> 4;
    const uint8_t colScan = scancode & 0b00001111;

    if (rowScan == 0 || colScan == 0)
        return 0;

    const uint8_t row = encode4to2(rowScan);
    const uint8_t col = encode4to2(colScan);

    if (col > 3 || row > 3)
        return 0;

    return scanCodes[row][col];
}

char keypad_getkey(KeypadType* keypad) {
    assert(keypad != NULL);

    uint8_t cols = keypad->readPortCb(KEYPAD_READ_VARIANT_COLUMN);
    uint8_t rows = keypad->readPortCb(KEYPAD_READ_VARIANT_ROWS);

    uint8_t scanCode = (cols & 0b00001111) | (rows & 0b11110000);

    return getCharByScanCode(scanCode);
}
