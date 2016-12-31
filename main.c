
#define _XTAL_FREQ 8000000

#include <xc.h>
#include "config.h"
#include "stdio_7segment.h"
//#include "roms.h" //External messages

/*Update flag values*/
#define UPDATE 1
#define UPDATED 0

/*Timer*/
#define t0_treshold 18 //600 ms Rolling speed. 33 ms each step.

/*Function prototypes*/
inline void osc_init(void);
inline void port_init(void);
inline void timer_init (void);
inline void sw_init(void);
inline void interrupts_init (void);
inline void check_end (void);
inline void set_data (unsigned char);
void update_output_buffers(unsigned char*);

#ifndef ROMS_H //Allows external messages
const unsigned char message[] = "0123456789 \0";
#endif



unsigned char index;                            //Data pointer
unsigned char ttl_counter;                      //TTL timeout counter
unsigned char data_B, data_C;                   //Output buffers
unsigned char updating_flag;


void main(void)
{
    osc_init();
    port_init();
    sw_init();    
    timer_init();
    interrupts_init();
    INTCONbits.GIE = 1;    //Global interrupts enable
    while(1)
    {
        update_output_buffers(&updating_flag);
        check_end();
        
    }     
}

inline void osc_init(void)
{
        /*Oscillator configurations*/
     OSCCONbits.SPLLEN=0;       //Main PLL disabled
     OSCCONbits.IRCF=0b1110;    //8 MHz clock source
     OSCCONbits.SCS=0b11;       //Internal clock source
     while(!OSCSTATbits.HFIOFR);
}

inline void port_init(void)
{
        /*Port configurations*/
    TRISA = 0;
    ANSELA = 0;          //No analog inputs
    INLVLA = 0;          //TTL
    LATA = 4;            //Power latch

    TRISB=0;
    ANSELB = 0;          //No analog inputs
    INLVLB = 0;          //TTL
    LATB = 0xFF;

    TRISC=0;
    ANSELC = 0;
    INLVLC = 0;          //TTL
    LATC = 0xFF;

}

inline void sw_init(void)
{
    set_data(ascii_2_7segment(message[index]));
    updating_flag=UPDATED;
    index=0;
}

inline void timer_init(void)
{
        /*Timer0 configurations*/
    OPTION_REGbits.PSA=0;       //Prescaler is asigned
    OPTION_REGbits.PS=7;        //256 Prescaler
    OPTION_REGbits.T0CS=0;      //Fosc/4
    TMR0=0;                     //Clear TTL timer
    ttl_counter=0;
}



inline void interrupts_init (void)
{

    /*Interrupts Configuration*/ 
    PIE1bits.ADIE = 0;         //Disable ADC interrupt
    INTCONbits.TMR0IE=1;       //Enable timer0 interrupts
    INTCONbits.TMR0IF=0;       //Clear timer0 interrupt
    INTCONbits.PEIE=1;         //Peripheral interrupts enable
}

inline void check_end(void)
{
    if (message[index] == 0)
    {
        index=0;    
        LATB=0xFF;
        LATC=0xFF;
        LATA=0;             //Turns power off
        INTCONbits.GIE=0;   //Global interrupt disabled
        asm("RESET");       //Resets system
    }

 }

void update_output_buffers(unsigned char* flag)
{
    if ((*flag)==UPDATE)
    {
        set_data(ascii_2_7segment(message[index]));
        (*flag)=UPDATED;
    }
}

inline void set_data (unsigned char current_char)
{
   data_B = ~(set_to_port(current_char, PORTB_1_MASK, PORTB_1_SHIFTS, PORTB_1_SHIFT_ADD ) | set_to_port(current_char, PORTB_2_MASK, PORTB_2_SHIFTS, PORTB_2_SHIFT_ADD ));
   data_C = ~(set_to_port(current_char, PORTC_1_MASK, PORTC_1_SHIFTS, PORTC_1_SHIFT_ADD ) | set_to_port(current_char, PORTC_2_MASK, PORTC_2_SHIFTS, PORTC_2_SHIFT_ADD ));
}

void interrupt ISR(void)
{
  if(INTCONbits.T0IF){
      INTCONbits.T0IF=0;    //Clear flag
      ttl_counter++;
      if (ttl_counter >=t0_treshold){          
          LATB = data_B;   //Update outputs
          LATC = data_C;
          index++;
          updating_flag=UPDATE;
          ttl_counter=0;   //Clear counter
      }
  }

  

}