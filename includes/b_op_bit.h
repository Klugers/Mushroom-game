#ifndef __B_OP_BIT_H
#define __B_OP_BIT_H

/**
 * Librería con macros de tratamientos e bit
 *
 * En esta librería aparecen funciones basicas para trabjar con bits
 */


//
#define bit_get(p,m) ((p) & (m))

// Pone un bit a uno
#define bit_set(p,m) ((p) |= (m))

//Pone un bit a cero
#define bit_clear(p,m) ((p) &= ~(m))

//invierte un bit
#define bit_flip(p,m) ((p) ^= (m))

//
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))

//
#define BIT(x) (0x01 << (x))

//
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))



// from AVR035: Efficient C Coding for AVR

// Pone un bit a uno
#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))

//Pone un bit a cero
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))

//invierte un bit
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))

//
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

//Mascara para poner bits a uno
#define SETBITMASK(x,y) (x |= (y))

//Mascara para poner bits a cero
#define CLEARBITMASK(x,y) (x &= (~y))

//Mascara para invertir bits
#define FLIPBITMASK(x,y) (x ^= (y))

//
#define CHECKBITMASK(x,y) (x & (y))

//
#define VARFROMCOMB(x, y) x

//
#define BITFROMCOMB(x, y) y

//
#define C_SETBIT(comb) SETBIT(VARFROMCOMB(comb), BITFROMCOMB(comb))

//
#define C_CLEARBIT(comb) CLEARBIT(VARFROMCOMB(comb), BITFROMCOMB(comb))

//
#define C_FLIPBIT(comb) FLIPBIT(VARFROMCOMB(comb), BITFROMCOMB(comb))

//
#define C_CHECKBIT(comb) CHECKBIT(VARFROMCOMB(comb), BITFROMCOMB(comb)) 




//As an additional item to check if a bit is clear: 
/*
if ( ( foo & 0x80 ) == 0 )
{
  ...
} */



#endif // __B_OP_BIT_H
