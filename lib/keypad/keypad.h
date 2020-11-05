/**
 * @file
 * #brief Module to read matrix 4x3 telephone keyboard
 */

// Phone keyboard layout
// x  c1 c2 c3 r1 r2 r3 r4
// Normal  
// c1 c2 c3 c4 r1 r2 r3 r4
// 
//    c1 c2 c3 c4
// r1 1  2  3  A
// r2 4  5  6  B
// r3 7  8  9  C
// r4 *  0  #  D

// 1 - 0b01001000
// 2 - 0b00101000
// 3 - 0b00011000

// 4 - 0b01000100
// 5 - 0b00100100
// 6 - 0b00010100



#ifndef __keypad_H
#define __keypad_H

extern void keypad_on_press(const char ch);
extern void keypad_on_release(void);

void keypad_tick(void);

#endif // __keypad_H