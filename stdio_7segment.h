/* 
 * File:   stdio_7segment.h
 * Author: josefe
 *
 * Created on 26 de diciembre de 2016, 0:23
 */

#ifndef STDIO_7SEGMENT_H
#define	STDIO_7SEGMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef inline
#define inline
#endif

#define NO_SHIFT 0
#define LSL 1
#define LSR 2

//#define PORTB_MASK          0b11110000
//#define PORTB_SHIFT_ADD     NO_SHIFT
//#define PORTB_SHIFTS        0
//
//#define PORTC_1_MASK       0b00000001
//#define PORTC_1_SHIFT_ADD   LSL
//#define PORTC_1_SHIFTS      7
//
//#define PORTC_2_MASK        0b00001110
//#define PORTC_2_SHIFT_ADD   LSR
//#define PORTC_2_SHIFTS      1

#define PORTB_1_MASK          0b11100000
#define PORTB_1_SHIFT_ADD     LSR
#define PORTB_1_SHIFTS        1

#define PORTB_2_MASK          0b00010000
#define PORTB_2_SHIFT_ADD     LSL
#define PORTB_2_SHIFTS        3

#define PORTC_1_MASK        0b00000011
#define PORTC_1_SHIFT_ADD   LSL
#define PORTC_1_SHIFTS      1

#define PORTC_2_MASK        0b00001100
#define PORTC_2_SHIFT_ADD   LSL
#define PORTC_2_SHIFTS      4

 unsigned char ascii_2_7segment(unsigned char);
 unsigned char bcd_2_7segment(unsigned char);
 inline unsigned char set_to_port(unsigned char, unsigned char, unsigned char, unsigned char);

#ifdef	__cplusplus
}
#endif

#endif	/* STDIO_7SEGMENT_H */

