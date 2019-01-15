#include <stdio.h>
#include <stdlib.h>

#include "funcoes_auxiliares.h"
#include "funcoes_Utentes.h"
#include "funcoesEmprestimos.h"
#include "funcoesBicicletas.h"

tipoUtente lerDadosUtente(void)
{

    tipoUtente dados;
    lerString("\nNome: ", dados.nome, MAX_STRING);
    do{
        dados.telefone = lerInteiro("\nNumero de telefone",MIN_TELEFONE, MAX_TELEFONE);
            if (dados.telefone > 999999999 ||  dados.telefone < 900000000)
            {
            printf("\nNumero de telefone invalido!");
            }
    }
    while (dados.telefone > 999999999 || dados.telefone < 900000000);
    dados.tipo = lerInteiro("\n Tipo de Utente (1- Estudante \t 2- Docente \t 3- Tecnico Administrativo \t 4- Convidado):  ", MIN_TIPO, MAX_TIPO);
    dados.designa_bicicleta=-1;
    dados.quant_emp=0;

    return dados;
}




int acrescentaUtente(tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes)
{

    tipoUtente e;
    int posicao,codUtente;

    posicao=-1;
    codUtente=0;


    if (quantUtentes == MAX_UTENTES)
    {
        printf("\nAtingiu o numero maximo de Utentes!");
    }
    else
    {
        codUtente = lerInteiro("\nCodigo do Utente", MIN_NUMERO_UTENTE, MAX_NUMERO_UTENTE);
        posicao=procuraUtente(vetorUtentes,quantUtentes,codUtente);

        if (posicao != -1)
        {
            printf("\nEste utente ja se encontra registado!");

        }

        else{
                e = lerDadosUtente();
                vetorUtentes[quantUtentes]=e;
                vetorUtentes[quantUtentes].codigoUtente=codUtente;
                quantUtentes++;
            }




    }
    return quantUtentes;
}

int procuraUtente (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes, int numero)
{

    int posicao,i;
    posicao=-1;


    for (i=0;i<quantUtentes;i++)
    {
        if (vetorUtentes[i].codigoUtente == numero)
        {
            posicao = i;
            i = quantUtentes;
        }
    }

    return posicao;
}



void mostrarDados(tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes)
{
    int i;

    if (quantUtentes == 0)
    {
        printf("\n\nAinda nao existem Utentes!\n\n");

    }
    else
    {
        printf("\n\nCodigo \tNome: \t\t Telefone: \t Tipo: \t\t\t\t Bicicleta N: ");
        for (i=0; i<quantUtentes; i++)
        {
                printf("\n%d\t%s\t%d", vetorUtentes[i].codigoUtente, vetorUtentes[i].nome, vetorUtentes[i].telefone);
                    if (vetorUtentes[i].tipo == 1){
                printf("\t\t Estudante");
                    }
                if (vetorUtentes[i].tipo == 2){
                    printf("\t\t Docente");
                }
                if (vetorUtentes[i].tipo == 3){
                    printf("\t\t Tecnico Administrativo");
                }
                if (vetorUtentes[i].tipo == 4){
                    printf("\t\t Convidado");
                }
                if (vetorUtentes[i].designa_bicicleta != -1)
                {
                    printf("\t\t\t\t%d",vetorUtentes[i].designa_bicicleta);

                }
                else
                {
                    printf("\t\t\t\tSem bicicleta");

                }
            }

        }

}


void gravaFicheiroBinario (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes)
{

    FILE *ficheiro;

    ficheiro = fopen("dadosUtentes.dat","wb");

    if (ficheiro == NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro!");
    }
    else
    {
        fwrite(&quantUtentes, sizeof(int),1,ficheiro);
        fwrite(vetorUtentes, sizeof(tipoUtente),quantUtentes,ficheiro);
        fclose(ficheiro);

    }
}

void lerFicheiroBinario (tipoUtente vetorUtentes[MAX_UTENTES], int*quantUtentes)
{

    FILE *ficheiro;

    ficheiro = fopen("dadosUtentes.dat","rb");

    if (ficheiro == NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro!");
    }
    else
    {
        fread(quantUtentes, sizeof(int),1,ficheiro);
        fread(vetorUtentes, sizeof(tipoUtente),*quantUtentes,ficheiro);
        fclose(ficheiro);

    }
}

void gravaFicheiroTexto (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes)
{

    FILE *ficheiro;
    int i;

    ficheiro = fopen("dadosUtentes.txt","w");

    if (ficheiro == NULL)
    {
        printf("\nErro na criacao do ficheiro/abertura do ficheiro!");
    }
    else
    {
        fprintf(ficheiro,"\n\n Codigo \t Nome \t Telefone \t Tipo \n");
        for (i=0; i<quantUtentes; i++)
        {
            fprintf(ficheiro,"\n%d \t\t%s",vetorUtentes[i].codigoUtente,vetorUtentes[i].nome);

            if(vetorUtentes[i].codigoUtente == -1)
            {
                fprintf(ficheiro,"\tSem Codigo!");
            }
            else
            {
                fprintf(ficheiro,"%d \t %s \t %d \t %d", vetorUtentes[i].codigoUtente, vetorUtentes[i].nome, vetorUtentes[i].tipo, vetorUtentes[i].designa_bicicleta);
            }
            fclose(ficheiro);
        }

    }
}


void consultaUltimaBicicleta(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES], tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int quantEmprestimos,int quantUtentes, int codUtente)
{
    int codBicicleta,posicao,i;

    codUtente=0;
    posicao=0;
    codBicicleta=0;

    if (quantEmprestimos == 0)
    {
        printf("\nNao existem emprestimos registados!");
    }
    else{
    posicao=procuraUtente(vetorUtentes,quantUtentes,codUtente);

    if (posicao == -1)
    {
        printf("\nCodigo de utente invalido!");
    }
    else
                {
                    ordenaData(vetorEmprestimos,quantEmprestimos); //ordena vetor por data decrescente

                    for (i=0;i<quantEmprestimos;i++) //o primeiro elemento encontrado com codigo utente inserido sera o emprestimo mais recente
                    {
                        if (vetorEmprestimos[i].codigoUtente == codUtente)
                        {
                            codBicicleta=vetorEmprestimos[i].designacaoBicicleta;
                            i=quantEmprestimos;

                        }
                    }

            posicao=pesquisaBicicleta(vetorBicicletas,quantBicicletas,codBicicleta);
            if (posicao == -1)
            {

            printf("\nO utente ainda nao utilizou nenhuma bicicleta");
            }
            else
            {

            printf("\nUltima Bicicleta utilizada pelo utente N %d",codUtente);
            consultaBicicleta(vetorBicicletas,quantBicicletas,vetorBicicletas[posicao].designacao);
            }


            }

    }


}

void listaUtentesDecrescente(tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes)
{

    int i,j,hatrocas;
    tipoUtente aux;


    for (i=0;i<quantUtentes-1 && hatrocas!=0;i++)
    {
        hatrocas=0;
        for (j=0;j<quantUtentes-i-1;j++)
        {
            if (vetorUtentes[j+1].quant_emp>vetorUtentes[j].quant_emp)
            {
                aux=vetorUtentes[j];
                vetorUtentes[j]=vetorUtentes[j+1];
                vetorUtentes[j+1]=aux;
                hatrocas=1;
            }
        }
    }

    mostrarDados(vetorUtentes,quantUtentes);

}

void consultaUtente(tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes, int codUtente)
{
    int posicao;

    posicao=procuraUtente(vetorUtentes,quantUtentes,codUtente);

            if(posicao == -1)
                {
                    printf("\nCodigo de utente invalido!");
                }
                    else
                            {
                                printf("\nCodigo: %d",vetorUtentes[posicao].codigoUtente);
                                printf("\nNome: %s",vetorUtentes[posicao].nome);
                                printf("\nTelefone: %d",vetorUtentes[posicao].telefone);
                                printf("\nTipo: ");

                                 switch(vetorUtentes[posicao].tipo)

                                    {
                                        case 1: printf("Estudante");
                                        break;
                                        case 2:printf("Docente");
                                        break;
                                        case 3:printf("Tecnico Administrativo");
                                        break;
                                        case 4:printf("Convidado");
                                        break;
                                    }
                                printf("\nBicicleta: ");
                                if (vetorUtentes[posicao].designa_bicicleta != -1)
                                {
                                    printf("%d",vetorUtentes[posicao].designa_bicicleta);
                                }
                                else
                                    {

                                        printf("Sem bicicleta");
                                    }
                                printf("\nQuantidade de emprestimos: %d",vetorUtentes[posicao].quant_emp);


                            }
}


