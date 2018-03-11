#ifndef __B_TYPES_H__
#define __B_TYPES_H__

/**
 * Librería donde se definen los nombres de los tipos de datos
 *
 * Los nombres usados aquí deben ser los que se utilicen siempre
 * para evitar problemas con tamaños de datos y confusiones.
 */

// Enteros de 8 bits
typedef signed char int8;
typedef unsigned char uint8;
typedef unsigned char byte;

// Enteros de 16 bits
typedef signed short int int16;
typedef unsigned short int uint16;

// Enteros largos de 32 bits
typedef signed long int int32;
typedef unsigned long int uint32;

// Booleano
typedef uint8 bool;
				
// Constantes para booleano
// Siempre en minusculas
#define false 0
#define true !false

// Puntero genérico en XDATA (MOVX)
//typedef void xdata* gptr;

// Definición de NULL
//#ifndef NULL
//#define NULL ((void *) 0L)
//#endif

// Callback (puntero a funcion en CODE)
//typedef bool (code *callback) (gptr);
				   
#endif // __B_TYPES_H__
