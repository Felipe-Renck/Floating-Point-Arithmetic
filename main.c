#include "main.h"


int main()
{
    unionFloat var1, var2;
    var1.f = -9.75;
    var2.f = -0.5625;

    //exibe valores na tela
    printf("var1:   ");
    printBinarioFloat(var1);
    printf("var2:   ");
    printBinarioFloat(var2);
    printf("varOut: ");
    printBinarioFloat(makeAdd(var1, var2));

    //exibe valores na tela
    printf("var1:   ");
    printBinarioFloat(var1);
    printf("var2:   ");
    printBinarioFloat(var2);
    printf("varOut: ");
    printBinarioFloat(makeSub(var1, var2));

    return 0;
}

void printReconstituido(unionFloat var)
{
    printf("numero reconstituido  : %f", pow(-1,(var.field.sinal)) * ( 1.0 + var.field.mantissa / pow(2,23)) * pow(2,(var.field.exponente - 127)));
}

void printBinarioFloat(unionFloat var)
{
    printf("%d ",var.field.sinal);
    printBinario(var.field.exponente, 8);
    printf(" ");
    printBinario(var.field.mantissa, 23);
    printf(" - ");
    printReconstituido(var);
    printf("\n");
}

void printBinarioMantica(unionMantica var)
{
    printBinario(var.field.mantissa0, 1);
    printf(" ");
    printBinario(var.field.mantissa1, 23);
    printf(" ");
    printBinario(var.field.stickyBit, 8);
    printf(" - ");
    printf("decimal  : %d", var.i);
    printf("\n");
}

void printBinario(int n, int i)
{
    int k;
    for (i--; i >= 0; i--)
   {
      k = n >> i;
      if (k & 1)
          printf("1");
      else
         printf("0");
    }
}

unionMantica makeShift(int intMantica, int intShift)
{
    unionMantica varOut;
    varOut.i = 0;
    varOut.field.mantissa0 = 1;
    varOut.field.mantissa1 = intMantica;

    varOut.i = varOut.i >> intShift;

    return varOut;
}

unionFloat normalizeResult(unionMantica varMantica, unsigned int intExponente)
{
    unionFloat varOut;

    while (varMantica.field.mantissa0 != 1)
    {
        varMantica.i = varMantica.i << 1;
        intExponente--;
    }

    varOut.field.exponente = intExponente;
    varOut.field.mantissa = varMantica.field.mantissa1;

    return varOut;
}

unionFloat makeAdd(unionFloat var1, unionFloat var2)
{
    return makeCalc(var1, var2, true);
}

unionFloat makeSub(unionFloat var1, unionFloat var2)
{
    return makeCalc(var1, var2, false);
}

unionFloat makeCalc(unionFloat var1, unionFloat var2, bool blnAdd)
{
    unionFloat varMaior, varMenor, varOut;

    //o varMaior será sempre o de maior expoente
    if ( var1.field.exponente < var2.field.exponente )
    {
        varMaior = var2;
        varMenor = var1;
    }
    else
    {
        varMaior = var1;
        varMenor = var2;
    }

   //pegar manticas
    unionMantica varManMenor, varManMaior;
    varManMaior.i = 0;
    varManMaior.field.mantissa0 = 1;
    varManMaior.field.mantissa1 = varMaior.field.mantissa;

    //faz shift no número menor
    varManMenor = makeShift(varMenor.field.mantissa, ( varMaior.field.exponente - varMenor.field.exponente ));

    //calcula a manticia
    unionMantica varManFinal;
    varManFinal.i = 0;

    //se forem iguais soma (para soma)
    bool fazerSoma = (blnAdd ? varMaior.field.sinal == varMenor.field.sinal : varMaior.field.sinal != varMenor.field.sinal);

    if (fazerSoma)
        varManFinal.field2.mantissa = (varManMaior.field2.mantissa + varManMenor.field2.mantissa);
    else //se não, subtrair
        varManFinal.field2.mantissa = (varManMaior.field2.mantissa - varManMenor.field2.mantissa);

    //normaliza o resultado
    varOut = normalizeResult(varManFinal, varMaior.field.exponente);

    //coloca o sinal da maior no retorno
    varOut.field.sinal = varMaior.field.sinal;

    //retorna o valor calculado
    return varOut;
}
