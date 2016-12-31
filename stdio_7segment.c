
#include "stdio_7segment.h"

unsigned char ascii_2_7segment(unsigned char character)
{
    switch (character)
    {
        case '0': return 0b00111111;
        case '1': return 0b00000110;
        case '2': return 0b01011011;
        case '3': return 0b01001111;
        case '4': return 0b01100110;
        case '5': return 0b01101101;
        case '6': return 0b01111101;
        case '7': return 0b00000111;
        case '8': return 0b01111111;
        case '9': return 0b01101111;

        case 'a':
        case 'A': return 0b01110111;
        case 'b':
        case 'B': return 0b01111100;
        case 'c': return 0b01011000;
        case 'C': return 0b00111001;
        case 'd':
        case 'D': return 0b01011110;
        case 'e': return 0b01111011;
        case 'E': return 0b01111001;
        case 'f':
        case 'F': return 0b01110001;
        case 'g': return 0b01101111;
        case 'G': return 0b00111101;
        case 'h': return 0b01110100;
        case 'H': return 0b01110110;
        case 'i': return 0b00010000;
        case 'I': return 0b00110000;
        case 'j': return 0b00011110;
        case 'J': return 0b00011111;
        case 'k':
        case 'K': return 0b01110000;
        case 'l': return 0b00110000;
        case 'L': return 0b00111000;
        case 'm': return 0b01010100;
        case 'M': return 0b00110111;
        case 'n': return 0b01010100;
        case 'N': return 0b00110111;
        case 'ñ':
        case 'Ñ': return 0b01010101;
        case 'o': return 0b01011100;
        case 'O': return 0b00111111;
        case 'p':
        case 'P': return 0b01110011;
        case 'q': return 0b11011100;
        case 'Q': return 0b10111111;
        case 'r': return 0b01010000;
        case 'R': return 0b01110111;
        case 's':
        case 'S': return 0b01101101;
        case 't': return 0b01111000;
        case 'T': return 0b00110001;
        case 'u': return 0b00011100;
        case 'U': return 0b00111110;
        case 'v': return 0b00011100;
        case 'V': return 0b00111110;
        case 'w': return 0b10011100;
        case 'W': return 0b10111110;
        case 'x':
        case 'X': return 0b01110110;
        case 'y': return 0b01101110;
        case 'Y': return 0b01100110;
        case 'z':
        case 'Z': return 0b01101101;

        case ' ': return 0;
        case '-': return 0b01000000;
        case '!': return 0b10000010;
        case '.':
        case ',': return 0b10000000;

        case '_':
        default: return 0b00001000; //_

    }
}

unsigned char bcd_2_7segment(unsigned char number)
{
    switch (number)
    {
        case 0: return 0b00111111;
        case 1: return 0b00000110;
        case 2: return 0b01011011;
        case 3: return 0b01001111;
        case 4: return 0b01100110;
        case 5: return 0b01101101;
        case 6: return 0b01111101;
        case 7: return 0b00000111;
        case 8: return 0b01111111;
        case 9: return 0b01101111;
        default: return 0b00001000; //_
    }

}

inline unsigned char set_to_port(unsigned char seven_segment, unsigned char port_mask, unsigned char shifts, unsigned char shift_address)
{
    if (shift_address==LSL)
    {
        return ((seven_segment & port_mask) << shifts);
    }
        if (shift_address==LSR)
    {
        return ((seven_segment & port_mask) >> shifts);
    }
    return (seven_segment & port_mask);

}