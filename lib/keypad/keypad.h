/**
 * @file
 * #brief Module to read matrix 4x3 telephone keyboard
 */

#ifndef __keypad_H
#define __keypad_H

extern void keypad_on_press(const char ch);
extern void keypad_on_release(void);

void keypad_tick(void);

#endif // __keypad_H