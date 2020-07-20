/**
 * @file
 * #brief Module to read matrix 4x3 telephone keyboard
 */

#ifndef __keypad_H
#define __keypad_H

#include <stdint.h>

// R1 - *   *   *   * 1
// R2 - *   *   *   * 2
// R3 - *   *   *   * 4
// R4 - *   +   *   * 8
//      |   |   |   |
//     C1  C2  C3  C4
//      1   2   4   8

// R1 R2 R3 R4 C1 C2 C3 C4

static const char scanCodes[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

typedef enum
{
    KEYPAD_READ_VARIANT_COLUMN,
    KEYPAD_READ_VARIANT_ROWS,
} KeypadReadVariantEnum;

typedef uint8_t (*KeypadReadPortCb)(KeypadReadVariantEnum);

typedef struct {
    KeypadReadPortCb readPortCb;
} KeypadType;

int keypad_init(KeypadType *keypadDef);

char keypad_getkey(KeypadType *keypadDef);
int keypad_getkeys(KeypadType *keypadDef, char *outBuffer, int count);

#endif // __keypad_H