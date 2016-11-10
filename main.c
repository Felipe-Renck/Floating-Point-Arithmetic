#include <stdio.h>
#include <stdlib.h>
#include<time.h>


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

int shiftRight(int valor, int posicoes)
{
    printf("\nNumero deslocado  : %d",valor >> posicoes);
    return valor >> posicoes;
}

int comparaExpoente(union_1 conjunto1 , union_2 conjunto2)
{
    if(conjunto1.field.expoente_1<conjunto2.field.expoente_2)
    {
        return conjunto1.field.mantissa_1  ;
    }
    else
    {
        return conjunto2.field.mantissa_2;
    }
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
    union_1.valor_1 = 2345.125;
    printf("%d ",union_1.field.sinal_1);
    binary(union_1.field.expoente_1, 8);
    printf(" ");
    binary(union_1.field.mantissa_1, 23);
    printf("\n");

    //Segundo Valor
    union_2 union_2;
    union_2.valor_2 =  0.75;
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
    unsigned int mantissaShiftada;

        //Check menor expoente entre os dois mantissa e retorna a mantissa de menor expoente
        if(union_1.field.expoente_1 != union_2.field.expoente_2)
        {
            unsigned int mantissa = comparaExpoente(union_1, union_2);
            //Desloca para a direita o menor operando com o expoente resultante
            mantissaShiftada = shiftRight(mantissa,resultado.expoente_resultante);
            printf("\n");
            //struct_resultante.field.mantissa_25 = binary(mantissaShiftada,25);
        }


    int posicoes = 25;
    int *bits = convertToBinaryArray(mantissaShiftada, posicoes);

    int i;
    for(i=posicoes-1; i>=0;i--)
    {
       printf("%d ", bits[i]);
    }
    printf("\n");


    // Contador de tempo
    timeEnd = clock();

    total_time = ((double) (timeEnd - timeStart)) / CLK_TCK;//calulate total time

    printf("\nTempo total: %f", total_time);

    time = clock() - time;
    double time_taken = ((double)time)/CLOCKS_PER_SEC; // in seconds

    printf("\nfun() took %f seconds to execute \n", time_taken);

    system("PAUSE");
    return 0;
}
