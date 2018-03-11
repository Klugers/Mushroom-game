/*
 * GccApplication1.c
 *
 * Created: 11/12/2017 19:05:47
 * Author : dark
 */ 

#define F_CPU 16000000UL


#define COMIENZO 0x01
#define PASA_TURNO 0x02
#define RESET 0x02


#define RESPUESTAS 0x08
#define PULSAROJO 0x10
#define PULSAROJOv2 0x12
#define NOTAS 0x20
#define SIMON 0x40
#define SIMONCIEGO 0x04
#define ALEATORIO 0x80

#define MASK_JUEGOS 0xF8





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



void Habilita_Interrupciones_Setas(void);


//Modos de Juegos
//1 - RESPUESTAS --> EL arbitro hace una pregunta y solo podra responder el que sea mas rapido en pulsar
//	(esto tambien vale para echar carreras)


//2 - PULSAROJO--> El Juego consiste en pulsar solo las setas que se ponen con Led de color Rojo.
//	(Con los potenciometros se puede ajustar el tiempo de encindido del led y el tiempo que esta apagado el led)

// Un beep inical
// Encender un led al hazar de los 7 (Lo ideal distribucion en estrella)
// Si se pulsa el boton con el led en rojo Suna un beep
// Si se pulsa otro boton o no se pulsa suena beep de error.
// EL sisterma pude engañar con otros colores  (con boton pasa turno pulsado al selecionar juego)


//3 - NOTAS --> cada uno de los las setas emite una nota musical

//4 - SIMON

//4 - SIMONCIEGO --> Solo suenan notas al azar y hay que pulsar la seta correcta



//5 - Aleatoio --> Que encianda las luces al azar y que no se repita en el bucle. Se evoluciona con boton pasa turno

// Se deben tener las setas pulsadas para saber cuales estan conectadas.
// Al lanzar el Jego se debe indicar "!!!!PARTICIPANTES PULSEN LAS SETAS!!!!
// Selen la pulsacion de las setas durante 5segundos. Durante estos 5 segundos (culaquier que pulse en estos 5 segundos entra en el sorteo)
// Se hace un flipflop con las luces de las setas que esten pulsadas (No hace falta mantenerlas pulsadas solo pulsarlas en estos 5 segundos)
// Pasdos los 5 segundos se genera un beep para marcar el fin del timepo
// se apagna todas las luces
// Se hacen 3 parpadeos
// se queda enecendida solo la luz seleccionada (en Azul)
// Si se pulsa el boton "pasa turno" esta luz se pone en Rojo (Fijo) y se eneciende otra al azar. 
// Antes se hace un flipflop de 3 segundos pos hacer bonito y se enciende el siguiente.
// no se repiten posiciones





void Pasador_De_Turnos(void);
void Notas_Pulsadores(void);
void Azar(void);
void LuzesParaSorterarAlAzar(void);

byte  Setas_Pulsadas[8];
volatile byte i_seta = 0;
volatile byte j_seta = 0;
volatile byte B_CONTROL_ANT = 0;
volatile byte R_ON = 0;
volatile byte G_ON = 0;
volatile byte B_ON = 0;
volatile uint32 SemillaRND =0;

volatile byte SELECT = 0; // Juego seleccionado


int main(void)
{
	cli();
	
	//Configutacion de puertos
	//--------------------------------------------------
	CONF_LEDs_R = 0xFF; //Output --> Luces de salida Rojas
	CONF_LEDs_G = 0xFF; //Output --> Luces de salida Verdes
	CONF_LEDs_B = 0xFF; //Output --> Luces de salida Azules
	CONF_BOTNES = 0x00; //Input --> Puerto 8 bits entero conectado a las setas (partido en 2 por el un tema de una interrupcion externa que esta en otro puerto)
	CONF_B_CONTROL = 0x00; //Input --> Puerto 8 bits entero para selecionar Juego
	//--------------------------------------------------
	// Ini Test Inicial (para comprobar que todas las luces funcionan)
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
	// Fin Test Inicial
	//--------------------------------------------------
		
		
	
	//-----------------------------------------------------------------------------------------------------------------------
    
    while (1) 
    {
		SemillaRND++;
		/////////////////////////////////////////////////////////////////////
		//Boton comienzo
		if ((B_CONTROL & COMIENZO) != 0 || SELECT  != 0x00)
		{
			
			
			if (SELECT == 0x00) //Si no hay juego seleccionado se seleciona uno y se habilitan las interrupciones
			{
				//leer modo de juego
				SELECT  = B_CONTROL & MASK_JUEGOS;	
				
				if (SELECT == PULSAROJO)
				{
					if ((B_CONTROL & PASA_TURNO) != 0)
					{
						SELECT  = PULSAROJOv2;
					}
				}
							
				Habilita_Interrupciones_Setas();
			}
			else //Si hay juego seleccionado paramos todo y permitimos selescionar otro Juego
			{
				if (RESET) //TODO: condicion de boton de reset pulsador
				{
					SELECT  = 0x00;		
					cli();							
				}			
			}
					
			
			switch (SELECT)
			{
				case RESPUESTAS:				
					Pasador_De_Turnos();
				break;
				//----------------------------------------------------------				
				case PULSAROJO:
					// No se como hacerlo
				break;
				//----------------------------------------------------------
				case PULSAROJOv2:
				
				break;
				//----------------------------------------------------------
				case NOTAS:
					Notas_Pulsadores();				
				break;
				//----------------------------------------------------------
				case SIMON:
					//TODO: Buscar un Simon y como mucho retocarlo 				
				break;
				//----------------------------------------------------------
				case SIMONCIEGO:
					//TODO: Buscar un Simon y como mucho retocarlo 
				break;
				//----------------------------------------------------------
				case ALEATORIO:
					Azar();
				break;
				//----------------------------------------------------------
				default:
				//Beep de Error
				break;
			}//Switch	
		}//Boton comienzo				
	} //While (1)
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

void Habilita_Interrupciones_Setas(void)
{
	//Habilitamos las interrupciones para que los pulsadores actuen por interrupcion y valla todo lo mas rapido posible
	//-----------------------------------------------------------------------------------------------------------------------
	//PCMSK0 = 0xFF; //cuales hacen salta interrupcion externa
	//SETBIT(PCICR, PCIE0); //habilita la interruption de grupo PCINT0 --> 0..7
	PCMSK1 = 0xFF; //cuales hacen salta interrupcion externa
	SETBIT(PCICR, PCIE1); //habilita la interruption de grupo PCINT0 --> 0..7
	sei(); //habilita interupciones
}

void Pasador_De_Turnos(void)
{
	if (B_CONTROL_ANT != B_CONTROL)
	{
		B_CONTROL_ANT = B_CONTROL;
		_delay_ms (20);
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
	}
}


void Notas_Pulsadores(void)
{
	if (j_seta < i_seta)
	{
		if (j_seta >= 1)
		{
			R_ON |= (Setas_Pulsadas[j_seta -1]);
			//TODO: Sonar la nota que se ha pulsdo
		}			
		j_seta++;
	}		
}


void Azar(void)
{
	
	
	srand(SemillaRND);// Esto esta en stdlib
	
	LuzesParaSorterarAlAzar();
	
	
	Habilita_Interrupciones_Setas();
	
	//recorrer las setas pulsadas para barajar
	
	
	SemillaRND;
	
	
	
	// varajar los leds de las setas pulsadas
	
	
	
	
	
	//encender leds de uno a uno segun pulsamos boton de pasar turno.
	//Asi hacemos una ordenacion al azar.
	
	
	Pasador_De_Turnos();
	


}

//TODO: Control PWM para sonidos de PC speaker
//TODO: timer para hacer juegos de luces
void LuzesParaSorterarAlAzar(void)
{
	byte contador = 0;
	//TODO: Hacer un coche fantastico durante 5 segunos
	LEDs_R = 0x07;
	_delay_ms (200);
	LEDs_R = LEDs_R  << 1 ;	
	
	if (contador == 0)
}



