#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define POSICOES 25
/*
IEEE floating point number:
 sign         31           sign bit (0 == positive, 1 == negative)
 exponent     30-23        exponent (biased by 127)
 mantissa     22-0         mantissa (bits to right of binary point)
*/
typedef union
{
      float valor_1;
      struct
      {
        unsigned int mantissa_1 : 23; //23 bits
        unsigned int expoente_1 : 8;  //8 bits
        unsigned int sinal_1 : 1;     //1 bit
       } field;
} union_1;

typedef union
{
      float valor_2;
      struct
      {
        unsigned int mantissa_2 : 23; //23 bits
        unsigned int expoente_2 : 8;  //8 bits
        unsigned int sinal_2 : 1;     //1 bit
       } field;
} union_2;

struct {
   unsigned int resultado : 32;
   unsigned int expoente_resultante : 8;
   unsigned int mantissa_resultante : 23;
} resultado;

struct{
    unsigned int mantissa_x_25 : 25;
    unsigned int mantissa_y_25 : 25;
}structMantissa;

void binary(int valor, int tamanho)
{
    int k;
    for (tamanho--; tamanho >= 0; tamanho--)
   {
      k = valor >> tamanho;
      if (k & 1)
          printf("1");
      else
         printf("0");
    }
}

int *convertToBinaryArray(int numero, int bit){
  //Pode ser um valor fixo, não precisa desse malloc
  int *array = malloc(sizeof(int) * bit);

  int k;
  for(k=0; k<bit; k++){
    int mask =  1 << k;
    int masked_n = numero & mask;
    int thebit = masked_n >> k;
    array[k] = thebit;
  }

  return array;
}

union{
    unsigned int mantissa_x_23 : 23;
    struct
    {
        unsigned int mantissa_x_22 : 22;
        unsigned int mantissa_x_1 : 1;
    } valorX;
}unionTmpX;

union{
    unsigned int mantissa_y_23 : 23;
    struct
    {
        unsigned int mantissa_y_22 : 22;
        unsigned int mantissa_y_1 : 1;
    } valorY;
}unionTmpY;

unsigned int hiddenBitX(int valor, int posicoes)
{
    unionTmpX.mantissa_x_23 = valor;
    unionTmpX.mantissa_x_23 = unionTmpX.mantissa_x_23 >> 1;
    unionTmpX.valorX.mantissa_x_1 = 1;
    unionTmpX.mantissa_x_23 = unionTmpX.mantissa_x_23 >> (posicoes-1);

    return unionTmpX.mantissa_x_23;
}
unsigned int hiddenBitY(int valor)
{
    unionTmpY.mantissa_y_23 = valor;
    unionTmpY.mantissa_y_23 = unionTmpY.mantissa_y_23 >> 1;
    unionTmpY.valorY.mantissa_y_1 = 1;
    //unionTmpY.mantissa_y_23 = unionTmp.mantissa_y_23 >> (posicoes-1);

    return unionTmpY.mantissa_y_23;
}

unsigned int shifRight(int valor, int posicoes)
{
    printf("\nNumero deslocado  : %d",valor >> posicoes);
    return valor >> posicoes;
}



int comparaExpoente(union_1 conjunto1 , union_2 conjunto2)
{
    if(conjunto1.field.expoente_1<conjunto2.field.expoente_2)
    {
        structMantissa.mantissa_y_25 = conjunto2.field.mantissa_2;
        return conjunto1.field.mantissa_1  ;
    }

    structMantissa.mantissa_y_25 = conjunto1.field.mantissa_1;
    return conjunto2.field.mantissa_2;
}

int main()
{

    // Contador de tempo
    //Variaveis de tempo
    double total_time;
    clock_t timeStart, timeEnd;
    clock_t time;
    time = clock();
    timeStart = clock();//Inicia o time
    // Contador de tempo

    //Primeiro Valor
    union_1 union_1;
    union_1.valor_1 = 9.75;
    printf("%d ",union_1.field.sinal_1);
    binary(union_1.field.expoente_1, 8);
    printf(" ");
    binary(union_1.field.mantissa_1, 23);
    printf("\n");

    //Segundo Valor
    union_2 union_2;
    union_2.valor_2 =  0.5625;
    printf("%d ",union_2.field.sinal_2);
    binary(union_2.field.expoente_2, 8);
    printf(" ");
    binary(union_2.field.mantissa_2, 23);
    printf("\n");


        // Passos para resolver a soma

        //1º Passo: Diferença entre os expoentes
        if(union_1.field.expoente_1 > union_2.field.expoente_2)
        {
            resultado.expoente_resultante = (union_1.field.expoente_1 - union_2.field.expoente_2);
        }
        else if (union_1.field.expoente_1 < union_2.field.expoente_2)
        {
            resultado.expoente_resultante = (union_2.field.expoente_2 - union_1.field.expoente_1);
        }

    //print decimal
    printf("%d ",resultado.expoente_resultante);
    printf("\n");

    //print binario
    binary(resultado.expoente_resultante,8);
    unsigned int mantissaDeslocadaX;

        //Check menor"%d" expoente entre os dois mantissa e retorna a mantissa de menor expoente
        if(union_1.field.expoente_1 != union_2.field.expoente_2)
        {
            //Compara os expoentes e seta as mantissas corretas;
            unsigned int mantissa = comparaExpoente(union_1, union_2);
            //Desloca para a direita o menor operando com o expoente resultante
            mantissaDeslocadaX = hiddenBitX(mantissa,resultado.expoente_resultante);
            printf("\n");
            //printf("%d ",mantissaDeslocadaX);
            structMantissa.mantissa_x_25 = mantissaDeslocadaX;
            printf("\n");
        }

            structMantissa.mantissa_y_25 = hiddenBitY(structMantissa.mantissa_y_25);

            printf("%d ",structMantissa.mantissa_y_25);
            printf("\n");
            binary(structMantissa.mantissa_x_25,)
            printf("%d ",structMantissa.mantissa_x_25);
//
//            printf("\n");
//            printf("%d ",structMantissa.mantissa_y_25);
//            printf("\n");
//            binary(structMantissa.mantissa_y_25,24);
//            printf("\n");
//            //binary(hiddenBitY(structMantissa.mantissa_y_25),24);
//
//            printf("\n");
//            binary(structMantissa.mantissa_x_25,24);


    // Contador de tempo
//    timeEnd = clock();
//
//    total_time = ((double) (timeEnd - timeStart)) / CLK_TCK;//calulate total time
//
//    printf("\nTempo total: %f", total_time);
//
//    time = clock() - time;
//    double time_taken = ((double)time)/CLOCKS_PER_SEC; // in seconds
//
//    printf("\nfun() took %f seconds to execute \n", time_taken);

    system("PAUSE");
    return 0;
}
