#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <math.h>
#endif // MAIN_H_INCLUDED

typedef enum { false, true } bool;

typedef union {
	float f;
	struct {
		unsigned int mantissa : 23;
		unsigned int exponente : 8;
		unsigned int sinal : 1;
	} field;

} unionFloat;

typedef union {
	unsigned int i : 32;
	struct {
	    unsigned int stickyBit : 8;
		unsigned int mantissa1 : 23;
		unsigned int mantissa0 : 1;
	} field;
	struct {
	    unsigned int stickyBit : 8;
		unsigned int mantissa : 24;
	} field2;
} unionMantica;


//escrita na tela
void printReconstituido(unionFloat var);
void printBinarioFloat(unionFloat var);
void printBinarioMantica(unionMantica var);
void printBinario(int n, int i);

//calculos
unionMantica makeShift(int intMantica, int intShift);
unionFloat normalizeResult(unionMantica varMantica, unsigned int intExponente);
unionFloat makeAdd(unionFloat var1, unionFloat var2);
unionFloat makeSub(unionFloat var1, unionFloat var2);
unionFloat makeCalc(unionFloat var1, unionFloat var2, bool blnAdd);

//comeco
//int main()
