/*
 * GccApplication1.c
 *
 * Created: 11/12/2017 19:05:47
 * Author : dark
 */ 

#define F_CPU 16000000UL

#define PASA_TURNO 0x02
#define COMIENZO 0x01

#define LEDs_R PORTA
#define LEDs_G PORTA //PORTJ
#define LEDs_B PORTC
//#define BOTONES PINB
#define BOTONES PINJ
#define B_CONTROL PINK

#define CONF_LEDs_R DDRA
#define CONF_LEDs_G DDRA//DDRJ
#define CONF_LEDs_B DDRC
//#define CONF_BOTNES DDRB
#define CONF_BOTNES DDRJ
#define CONF_B_CONTROL DDRK


#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "includes/b_op_bit.h"
#include "includes/b_types.h"


byte  Setas_Pulsadas[8];
volatile byte i_seta = 0;
volatile byte j_seta = 0;
volatile byte B_CONTROL_ANT = 0;
volatile byte R_ON = 0;
volatile byte G_ON = 0;
volatile byte B_ON = 0;
volatile uint16 semilla =0;
int main(void)
{
	
	//Configutacion de puertos
	//--------------------------------------------------
	CONF_LEDs_R = 0xFF; //Output
	CONF_LEDs_G = 0xFF; //Output
	CONF_LEDs_B = 0xFF; //Output
	CONF_BOTNES = 0x00; //Input
	CONF_B_CONTROL = 0x00; //Input
	//--------------------------------------------------
	//test
	//--------------------------------------------------
	LEDs_R = 0x55;
	LEDs_G = 0x55;
	LEDs_B = 0x55;	
	_delay_ms (500);
	LEDs_R = 0xAA;
	LEDs_G = 0xAA;
	LEDs_B = 0xAA;
	_delay_ms (500);
	LEDs_R = 0x00;
	LEDs_G = 0x00;
	LEDs_B = 0x00;	
	
	LEDs_R = 0xFF;
	//--------------------------------------------------
	//FIN test
	//--------------------------------------------------
		
	//PCMSK0 = 0xFF; //cuales hacen salta interrupcion externa
	//SETBIT(PCICR, PCIE0); //habilita la interruption de grupo PCINT0 --> 0..7		
	PCMSK1 = 0xFF; //cuales hacen salta interrupcion externa
	SETBIT(PCICR, PCIE1); //habilita la interruption de grupo PCINT0 --> 0..7
	sei(); //habilita interupciones
	
    /* Replace with your application code */
    while (1) 
    {
		semilla++;
		
		
		if (B_CONTROL_ANT != B_CONTROL)
		{
			B_CONTROL_ANT = B_CONTROL;
			_delay_ms (20);
			
			/////////////////////////////////////////////////////////////////////	
			//Boton pasa turno
			if ((B_CONTROL & PASA_TURNO) != 0) 
			{
				if (j_seta < i_seta)
				{
					if (j_seta >= 1)
					{
						R_ON |= (Setas_Pulsadas[j_seta -1]);
						LEDs_R = ~R_ON;					
					}
					
					LEDs_B = (Setas_Pulsadas[j_seta]);							
					j_seta++;
				}
			}
			/////////////////////////////////////////////////////////////////////
			
			//leer analogicas para tiempos de luz ON
			/*
			digitalWrite(pinArray[count], HIGH);
			delay(map (LEDON, 0, 1023, 0, 2023)); // tiempo que esta encendido el led  con los mapeos para añadir resitencias (map (LEDON, 0, 1023, 0, 1023))
			digitalWrite(pinArray[count], LOW);
			delay(map (LEDOFF, 0, 1023, 0, 3623));  // tiempo que esta apagado el led (map (LEDOFF, 0, 1023, 0, 1023))
			*/
			/////////////////////////////////////////////////////////////////////
			
			//Control PWM para sonidos de PC speaker
			
			/////////////////////////////////////////////////////////////////////
			//Boton comienzo
			if ((B_CONTROL & COMIENZO) != 0) 
			{
				//leer modo de juego
			
			}
			
		}			
	}
}


//ISR(PCINT0_vect)
ISR(PCINT1_vect)
{	
	//----------------------------------
	if (RESPUESTAS)		
	{
		byte SETAS_PUL = BOTONES & (PCMSK1>>1);	
		PCMSK1 &= (~(SETAS_PUL <<1)); //deshabilita la interrupcion de ese pulsador		
		Setas_Pulsadas[i_seta] = SETAS_PUL;
		i_seta++;	
	}
	//----------------------------------
	
}