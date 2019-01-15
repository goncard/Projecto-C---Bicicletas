#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_auxiliares.h"
#include "funcoesBicicletas.h"

int PedirCodigoBic()
{
    int codigo;
    codigo=lerInteiro("\n\nDesignacao da bicicleta: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
    return codigo;
}


void mediaDistanciaBic(tipoEmprestimo *vetorEmprestimos,tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantEmprestimos,int quantBicicletas)
{
    float media,soma;
    int i,j,total;

    total=0;
    soma=0;
    media=0;

     if (quantBicicletas == 0)
     {
         printf("\nNao existem bicicletas inseridas!");
     }
     else
     {




            for (j=0;j<quantBicicletas;j++)
            {
                total=0;
                soma=0;


                  for (i=0;i<quantEmprestimos;i++)
                        {
                            if (vetorEmprestimos[i].designacaoBicicleta == vetorBicicletas[j].designacao && vetorEmprestimos[i].quantidade != -1)
                            {

                                soma+=vetorEmprestimos[i].quantidade;
                                total++;
                            }

                        }

                        if (total != 0)
                        {

                            media=(float)soma/total;
                            printf("\n\nbicicleta N %d :  %.2f km",vetorBicicletas[j].designacao,media);
                        }
                        else
                        {
                            printf("\nbicicleta N %d : Sem dados",vetorBicicletas[j].designacao);
                        }

            }



}

}

void percEmprestimosTipoUtente(tipoEmprestimo *vetorEmprestimos,tipoUtente vetorUtentes[MAX_UTENTES],int quantEmprestimos, int quantUtentes)
{
    int i,j,conta_estudante,conta_tecn,conta_docente,conta_conv;
    float perc_estudante,perc_docente,perc_conv,perc_tecn;

    conta_estudante=0;
    conta_docente=0;
    conta_conv=0;
    conta_tecn=0;

    perc_estudante=0;
    perc_conv=0;
    perc_docente=0;
    perc_tecn=0;

     if (quantUtentes == 0 || quantEmprestimos == 0)
     {
         printf("\nNao existem utentes ou emprestimos registados!");
     }
     else
     {
            for (j=0;j<quantUtentes;j++)
            {
                  for (i=0;i<quantEmprestimos;i++)
                        {
                            if (vetorUtentes[j].tipo == 1 && vetorEmprestimos[i].codigoUtente == vetorUtentes[j].codigoUtente)
                            {
                                conta_estudante++;


                            }
                            if (vetorUtentes[j].tipo == 2 && vetorEmprestimos[i].codigoUtente == vetorUtentes[j].codigoUtente)
                            {
                                conta_docente++;


                            }
                            if (vetorUtentes[j].tipo == 3 && vetorEmprestimos[i].codigoUtente == vetorUtentes[j].codigoUtente)
                            {
                                conta_tecn++;


                            }
                            if (vetorUtentes[j].tipo == 4 && vetorEmprestimos[i].codigoUtente == vetorUtentes[j].codigoUtente)
                            {
                                conta_conv++;


                            }

                        }

            }
    perc_estudante=conta_estudante*100/quantEmprestimos;
    perc_conv=conta_conv*100/quantEmprestimos;
    perc_docente=conta_docente*100/quantEmprestimos;
    perc_tecn=conta_tecn*100/quantEmprestimos;


    printf("\n\nEstudante: %.2f %%",perc_estudante);
    printf("\nDocente: %.2f %%",perc_docente);
    printf("\nTecnico administrativo: %.2f %%",perc_tecn);
    printf("\nConvidado:  %.2f %%",perc_conv);



}

}


void quantEmprestimosPorData(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos)
{
    int i, n_emprestimos;
    tipoData data1;
    tipoData data2;
    n_emprestimos=0; //inicializa contador de numero de emprestimos que encontrar
    if (quantEmprestimos == 0)
    {
        printf("Nao existem emprestimos!");

    }
    else
            {

                printf("\nA partir de: ");
                data1=lerData();
                printf("\nAté: ");
                data2=lerData();
                if ((data2.ano < data1.ano) || (data2.ano == data1.ano && data2.mes < data1.mes) || (data2.ano == data1.ano && data2.mes == data1.mes && data2.dia < data1.dia ))
                {
                    printf("\nA primeira data deve ser menor que a segunda!");

                }

                else
                {



                for (i=0;i<quantEmprestimos;i++)
                {

                if (data1.ano != data2.ano)
                {
                    if(vetorEmprestimos[i].data.ano>=data1.ano && vetorEmprestimos[i].data.ano<=data2.ano)
                    {
                        n_emprestimos++;
                    }
                }
                if (data1.mes != data2.mes && data1.ano == data2.ano)
                {
                    if (vetorEmprestimos[i].data.mes>=data1.mes && vetorEmprestimos[i].data.mes<=data2.mes && vetorEmprestimos[i].data.ano>=data1.ano && vetorEmprestimos[i].data.ano<=data2.ano)
                    {

                        n_emprestimos++;
                    }
                }
                if (data1.dia != data2.dia && data1.mes == data2.mes && data1.ano == data2.ano)
                    {
                        if(vetorEmprestimos[i].data.dia>=data1.dia && vetorEmprestimos[i].data.dia<=data2.dia && vetorEmprestimos[i].data.mes>=data1.mes && vetorEmprestimos[i].data.mes<=data2.mes && vetorEmprestimos[i].data.ano>=data1.ano && vetorEmprestimos[i].data.ano<=data2.ano)
                        {
                            n_emprestimos++;
                        }
                    }
                }

                printf("\nEntre %2d/%2d/%4d e %2d/%2d/%4d foram feitos %d emprestimos",data1.dia,data1.mes,data1.ano,data2.dia,data2.mes,data2.ano,n_emprestimos);

            }
            }
}
void escreveCampus(int indice, int contador[4])
{



    switch(indice)
    {
        case 1: printf("\nResidencias (%d Emprestimos)",contador[0]);
        break;
        case 2: printf("\nCampus 1 (%d Emprestimos)",contador[1]);
        break;
        case 3: printf("\nCampus 2 (%d Emprestimos)",contador[2]);
        break;
        case 4: printf("\nCampus 5 (%d Emprestimos)",contador[3]);
        break;
    }
}


void campusMaior(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos) //imprime o campus de origem com maior numero de emprestimos
{
    int maior,i;
    int contador[4]; //contador[0] - residencias   contador[1] - campus 1  contador[2] - campus 2    contador[3] - campus 5

    contador[0]=0;
    contador[1]=0;
    contador[2]=0;
    contador[3]=0;

    if (quantEmprestimos == 0)
    {
        printf("\nNao existem emprestimos registados!");
    }
    else
        {

             for (i=0;i<quantEmprestimos;i++)        //conta quantos empréstimos tem cada campus de origem
                {
                    switch (vetorEmprestimos[i].campusOrigem)
                        {
                            case 1:contador[0]++;
                            break;
                            case 2:contador[1]++;
                            break;
                            case 3:contador[2]++;
                            break;
                            case 4:contador[3]++;
                            break;
                        }
                }



                maior=contador[0];

                for (i=0;i<4;i++)           //verifica qual é o maior
                {
                    if (contador[i]>maior)
                        {
                            maior=contador[i];
                        }
                }

                printf("\n\nCampus com mais emprestimos: ");

                for (i=0;i<4;i++)         // escreve quais sao os campus com maior numero de emprestimos
                {
                    if (contador[i] == maior)
                        {
                            escreveCampus(i+1,contador);
                        }
                }




}
}

void quantUtentes_Bicicleta(tipoEmprestimo *vetorEmprestimos, tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int quantEmprestimos,int designBicicleta)
{
    int i, conta, aux, posicao;
    aux=-1;
    conta=0;
    posicao=0;
    if (quantEmprestimos == 0 || quantBicicletas == 0)
    {
        printf("\nNao existem dados!");
    }
    else{

    posicao=pesquisaBicicleta(vetorBicicletas,quantBicicletas,designBicicleta);

            if (posicao == -1)
            {
                printf("\nDesignacao de bicicleta invalida!");
            }
            else
            {

                        for (i=0;i<quantEmprestimos;i++)
                            {
                                if (vetorEmprestimos[i].designacaoBicicleta == designBicicleta && vetorEmprestimos[i].codigoUtente != aux)
                                {
                                    conta++;
                                    aux=vetorEmprestimos[i].codigoUtente;


                                }
                        }
                        printf("\nA Bicicleta N %d foi utilizada por %d utilizadores",designBicicleta,conta);
            }
    }

}
