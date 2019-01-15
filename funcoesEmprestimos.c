#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_auxiliares.h"
#include "funcoesBicicletas.h"
#include "funcoes_Utentes.h"





tipoEmprestimo lerDadosEmprestimos()
{
    tipoEmprestimo dados;
    dados.data=lerData();
    dados.hora=lerHora();
    dados.campusOrigem=lerInteiro("\nCampus de origem (1) - Residencias; (2) - Campus 1; (3)- Campus 2; (4) - Campus 5:  ",1,4);
    dados.campusDestino=lerInteiro("Campus de destino (1 - Residencias; 2- Campus1; 3- Campus2; 4- Campus5): ",1,4);
return dados;

}





tipoEmprestimo *insereEmprestimo(tipoEmprestimo *vetorEmprestimos, tipoEmprestimo *vetorListaEspera, tipoBicicleta vetorBicicletas[MAX_BICICLETAS],tipoUtente vetorUtentes[MAX_UTENTES],int *quantEmprestimos,int quantBicicletas, int *quantEspera,int quantUtentes, tipoEmprestimo **pontLista, int *ultimoCodigo)
{
    int posicao,posicaoUtente,codUtente;
    tipoEmprestimo *pont;
    tipoEmprestimo *pont_Lespera;
    pont=vetorEmprestimos;
    pont_Lespera=vetorListaEspera;
    posicao=0;
    posicaoUtente=0;
    codUtente=0;
    tipoEmprestimo dados;



    if (quantBicicletas == 0)
    {
        printf("\nAinda nao foram introduzidas bicicletas.");
    }
            else
            {
                codUtente=lerInteiro("\nCodigo de utente: ",MIN_NUMERO_UTENTE,MAX_NUMERO_UTENTE);
                posicaoUtente=procuraUtente(vetorUtentes,quantUtentes,codUtente);
                if (posicaoUtente == -1)
                {
                    printf("\nUtente inexistente!");
                }

                else
                {

                        if (vetorUtentes[posicaoUtente].designa_bicicleta != -1)

                        {
                            printf("\nSo e possivel fazer um emprestimo por utente!");
                        }
                        else{


                dados=lerDadosEmprestimos();
                dados.codigoUtente=codUtente;
                posicao=pesquisaBicicletaLocal(vetorBicicletas,quantBicicletas,dados.campusOrigem); //verifica se exsite alguma bicicleta disponivel no campus de origem
                if (posicao != -1)
                {


                vetorEmprestimos=realloc(vetorEmprestimos,(*quantEmprestimos+1)*sizeof(tipoEmprestimo));

                if (vetorEmprestimos == NULL)
                {
                    printf("Memoria insuficiente!");
                    vetorEmprestimos=pont;
                }

                else
                    {

                        dados.designacaoBicicleta=vetorBicicletas[posicao].designacao;
                        vetorUtentes[posicaoUtente].designa_bicicleta=vetorBicicletas[posicao].designacao; //Altera numero de bicicleta que x utente está a alugar
                        vetorUtentes[posicaoUtente].quant_emp++; //incrementa contador quantidade de emprestimos feitos pelo utente
                        dados.numero=(*quantEmprestimos)+1;
                        dados.quantidade=-1;
                        dados.dataDevolucao.ano=-1;//
                        dados.dataDevolucao.mes=-1;
                        dados.dataDevolucao.dia=-1;
                        vetorEmprestimos[*quantEmprestimos]=dados;
                        vetorBicicletas[posicao].estado=2; //emprestada
                        vetorBicicletas[posicao].campus=dados.campusDestino;
                        (*quantEmprestimos)++;


                }

                }
                else
                        {
                            vetorListaEspera=realloc(vetorListaEspera,(*quantEspera+1)*sizeof(tipoEmprestimo));  //Insere na lista de espera
                            if (vetorListaEspera == NULL)
                                {
                                    printf("Memoria insuficiente!");
                                    vetorListaEspera=pont_Lespera;
                                }
                                else
                                        {
                                            vetorListaEspera[*quantEspera].designacaoBicicleta=-1;
                                            dados.numero=(*quantEspera)+1;
                                            *ultimoCodigo=dados.numero; //guarda ultimo codigo de pedido atribuido para evitar dois pedidos com o mesmo codigo quando algum for eliminado
                                            vetorListaEspera[*quantEspera]=dados;
                                            *pontLista=vetorListaEspera;
                                            (*quantEspera)++;


                                        }

                        }

                    }
                }

            }





return vetorEmprestimos;

}

void listaEmprestimos(tipoEmprestimo *vetorEmprestimos,int *quantEmprestimos)
{
    int i;


    if (*quantEmprestimos==0)
    {
        printf("\nAinda nao existem emprestimos!");
    }
    else{
        printf("\nCodigo\tUtente n \tBicicleta n\tData\t\tHora\t\tOrigem\t\tDestino\t\n");

        for (i=0;i<*quantEmprestimos;i++)
        {
            printf("\n%d\t%d\t\t%d\t\t%2d/%2d/%4d\t%2d:%2d\t\t",vetorEmprestimos[i].numero,vetorEmprestimos[i].codigoUtente,vetorEmprestimos[i].designacaoBicicleta,vetorEmprestimos[i].data.dia,vetorEmprestimos[i].data.mes,vetorEmprestimos[i].data.ano,vetorEmprestimos[i].hora.hora,vetorEmprestimos[i].hora.minuto);

        switch(vetorEmprestimos[i].campusOrigem)
        {
            case 1: printf("Residencias\t");
            break;
            case 2: printf("Campus 1\t");
            break;
            case 3: printf("Campus 2\t");
            break;
            case 4: printf("Campus 5\t");
            break;

        }

        switch(vetorEmprestimos[i].campusDestino)
        {
            case 1: printf("Residencias\t");
            break;
            case 2: printf("Campus 1\t");
            break;
            case 3: printf("Campus 2\t");
            break;
            case 4: printf("Campus 5\t");
            break;

        }
    }

    }

}

void mostraListaEspera(tipoEmprestimo *vetorListaEspera,int quantEspera)
{
    int i;
     if (quantEspera==0)
    {
        printf("\nLista de espera vazia!");
    }
    else {
    printf("\nCodigo\tUtente n\tData\t\tHora\t\tOrigem\tDestino\n");

    for (i=0;i<quantEspera;i++)
    {
            printf("\n%d\t%d\t\t%2d/%2d/%4d\t%2d:%2d\t\t",vetorListaEspera[i].numero,vetorListaEspera[i].codigoUtente,vetorListaEspera[i].data.dia,vetorListaEspera[i].data.mes,vetorListaEspera[i].data.ano,vetorListaEspera[i].hora.hora,vetorListaEspera[i].hora.minuto);

        switch(vetorListaEspera[i].campusOrigem)
        {
            case 1: printf("Residencias\t");
            break;
            case 2: printf("Campus 1\t");
            break;
            case 3: printf("Campus 2\t");
            break;
            case 4: printf("Campus 5\t");
            break;

        }
        switch(vetorListaEspera[i].campusDestino)
        {
            case 1: printf("Residencias\t");
            break;
            case 2: printf("Campus 1\t");
            break;
            case 3: printf("Campus 2\t");
            break;
            case 4: printf("Campus 5\t");
            break;

        }

    }
    }

}




int pesquisaEmprestimo(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos, int codigoEmprestimo)
{
    int posicao,i;
    posicao=-1;

    for(i=0;i<quantEmprestimos;i++)
    {
        if(vetorEmprestimos[i].numero == codigoEmprestimo)
        {
            posicao=i;
            i=quantEmprestimos;
        }
    }
    return posicao;

}

int pesquisaEmprestimo_DesignBicicleta(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos, int designBicicleta)
{
    int posicao,i;                                  //pesquisa no vetor um emprestimo com determinada designacao de bicicleta que nao tenha data de devolucao
    posicao=-1;

    for(i=0;i<quantEmprestimos;i++)
    {
        if(vetorEmprestimos[i].designacaoBicicleta == designBicicleta && vetorEmprestimos[i].dataDevolucao.ano == -1  && vetorEmprestimos[i].dataDevolucao.mes == -1  && vetorEmprestimos[i].dataDevolucao.dia == -1)
        {
            posicao=i;
            i=quantEmprestimos;
        }
    }
    return posicao;

}

void devolveBicicleta(tipoEmprestimo *vetorEmprestimos,tipoBicicleta vetorBicicletas[MAX_BICICLETAS], tipoUtente vetorUtentes[MAX_UTENTES], float *distPercorrida, int quantEmprestimos, int quantBicicletas,int quantUtentes, int codEmprestimo)
{
    int posicao,posBicicleta,posUtente;
    float dist;

    if (quantEmprestimos == 0)
    {
        printf("Nao existem emprestimos!");
    }
    else
        {
            posicao=pesquisaEmprestimo(vetorEmprestimos,quantEmprestimos,codEmprestimo);
            if (posicao == -1)
            {
                printf("Codigo de emprestimo invalido");
            }
            else
                {
                posBicicleta=pesquisaBicicleta(vetorBicicletas, quantBicicletas, vetorEmprestimos[posicao].designacaoBicicleta);
                if (vetorBicicletas[posBicicleta].estado != 2) //verifica se a bicicleta ja foi devolvida
                {
                    printf("\nA bicicleta ja se encontra devolvida!");
                }
                        else{

                vetorEmprestimos[posBicicleta].dataDevolucao=lerData();
                dist=lerFloat("\nDistancia percorrida em KM: ",0,1000);
                posUtente=procuraUtente(vetorUtentes,quantUtentes,vetorEmprestimos[posicao].codigoUtente);
                vetorUtentes[posUtente].designa_bicicleta=-1;
                *distPercorrida+=dist;
                vetorEmprestimos[posicao].quantidade=dist;
                vetorBicicletas[posBicicleta].estado=1;


                            }

    }
}
}

void gravaFichBinarioEmprestimos(tipoEmprestimo *vetorEmprestimos, tipoEmprestimo *vetorListaEspera, int quantEspera, int quantEmprestimos)
{
    FILE *ficheiro, *ficheiro_lista;                         //grava em ficheiro binario dados dos emprestimos e da lista de espera
    int lidos,lidos_lista;
    lidos=0;
    lidos_lista=0;

    ficheiro=fopen("emprestimos.dat","wb");
    ficheiro_lista=fopen("lista_espera.dat","wb");
    if (ficheiro==NULL || ficheiro_lista==NULL)
        {
            printf("Nao foi possivel abrir o ficheiro1");
        }
         else
            {
                lidos=fwrite(&quantEmprestimos,sizeof(int),1,ficheiro);
                lidos_lista=fwrite(&quantEspera,sizeof(int),1,ficheiro_lista);
                if (lidos != 1 || lidos_lista != 1)
                    {
                        printf("Nao foi possivel escrever no ficheiro!2");
                    }
                lidos=fwrite(vetorEmprestimos,sizeof(tipoEmprestimo),quantEmprestimos,ficheiro);
                lidos_lista=fwrite(vetorListaEspera,sizeof(tipoEmprestimo),quantEspera,ficheiro_lista);
                if (lidos != quantEmprestimos || lidos_lista != quantEspera)
                    {
                        printf("Nao foi possivel escrever no ficheiro!3");
                    }
            }
    fclose(ficheiro);
    fclose(ficheiro_lista);

}

tipoEmprestimo *lerFichBin_Emprestimos(tipoEmprestimo *vetorEmprestimos,tipoEmprestimo *vetorListaEspera, int *quantEspera, int *quantEmprestimos,tipoEmprestimo **pontLista)
{
    int quantlidos,quantlidos_lista;
    FILE *ficheiro,*ficheiro_lista;

    quantlidos=0;
    quantlidos_lista=0;


    ficheiro=fopen("emprestimos.dat","rb");
    ficheiro_lista=fopen("lista_espera.dat","rb");

    if (ficheiro == NULL || ficheiro_lista == NULL)
        {
            printf("\nNao foi possivel ler o ficheiro!");
            free(vetorEmprestimos);
            free(vetorListaEspera);
            vetorEmprestimos=NULL;
            vetorListaEspera=NULL;
            *quantEmprestimos=0;
            *quantEspera=0;
        }
        else
            {

                quantlidos=fread(quantEmprestimos,sizeof(int),1,ficheiro);
                quantlidos_lista=fread(quantEspera,sizeof(int),1,ficheiro_lista);

                if (quantlidos != 1)
                    {
                        printf("\nErro ao ler ficheiro de emprestimos!");
                    }
                    else
                        {
                            vetorEmprestimos=realloc(vetorEmprestimos,(*quantEmprestimos)*sizeof(tipoEmprestimo));
                             if (vetorEmprestimos == NULL)
                                    {
                                        printf("\nErro ao reservar memoria!");

                                    }

                                        else {
                                                quantlidos=fread(vetorEmprestimos,sizeof(tipoEmprestimo),*quantEmprestimos,ficheiro);
                                                if(quantlidos != *quantEmprestimos)
                                                    {
                                                        printf("\nErro ao ler ficheiro!");
                                                    }
                                             }
                        }




                 if (quantlidos_lista != 1)
                    {
                        printf("\nErro ao ler ficheiro da lista de espera!");
                    }
                    else
                            {
                                vetorListaEspera=realloc(vetorListaEspera,(*quantEspera)*sizeof(tipoEmprestimo));
                                if (vetorListaEspera == NULL)
                                    {
                                        printf("\nErro ao reservar memoria!");

                                    }
                                    else
                                            {

                                                quantlidos_lista=fread(vetorListaEspera,sizeof(tipoEmprestimo),*quantEspera,ficheiro_lista);
                                                if(quantlidos_lista != *quantEspera)
                                                    {
                                                        printf("\nErro ao ler ficheiro!");
                                                    }
                                                    else
                                                        {
                                                            *pontLista=vetorListaEspera;
                                                        }
                                             }
                            }

            }



        fclose(ficheiro);
        fclose(ficheiro_lista);


return vetorEmprestimos;

}

void ordenaData (tipoEmprestimo *vetorEmprestimos, int quantEmprestimos)
{
    int hatrocas,i,j;
    tipoEmprestimo aux;

    hatrocas=1;


    for (i=0;i<quantEmprestimos-1 && hatrocas!=0;i++)
    {
        hatrocas=0;
            for(j=0;j<quantEmprestimos-i-1;j++)
            {
                if (vetorEmprestimos[j+1].data.ano != vetorEmprestimos[j].data.ano && vetorEmprestimos[j+1].data.ano > vetorEmprestimos[j].data.ano)
                {
                  hatrocas=1;
                  aux=vetorEmprestimos[j];
                  vetorEmprestimos[j]=vetorEmprestimos[j+1];
                  vetorEmprestimos[j+1]=aux;
                }
                if (vetorEmprestimos[j+1].data.mes != vetorEmprestimos[j].data.mes && vetorEmprestimos[j+1].data.ano == vetorEmprestimos[j].data.ano && vetorEmprestimos[j+1].data.mes>vetorEmprestimos[j].data.mes)
                {
                    hatrocas=1;
                    aux=vetorEmprestimos[j];
                    vetorEmprestimos[j]=vetorEmprestimos[j+1];
                    vetorEmprestimos[j+1]=aux;

                }
                if (vetorEmprestimos[j+1].data.dia != vetorEmprestimos[j].data.dia && vetorEmprestimos[j+1].data.mes == vetorEmprestimos[j].data.mes && vetorEmprestimos[j+1].data.ano == vetorEmprestimos[j].data.ano && vetorEmprestimos[j+1].data.dia > vetorEmprestimos[j].data.dia)
                    {
                        hatrocas=1;
                        aux=vetorEmprestimos[j];
                        vetorEmprestimos[j]=vetorEmprestimos[j+1];
                        vetorEmprestimos[j+1]=aux;

                    }
            }
    }


}

void historicoEmprestimos(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES], int quantEmprestimos, int quantUtentes, int codUtente)
{
    int i,posicao, conta;
    posicao=0;
    conta=0;

    if (quantEmprestimos == 0)
    {
        printf("\nNao existem emprestimos registados!");

    }
        else

        {
            posicao=procuraUtente(vetorUtentes,quantUtentes,codUtente);

            if(posicao == -1)
            {
                printf("\nNumero de utente invalido!");
            }
            else
                {

                    for (i=0;i<quantEmprestimos;i++)  //conta todos os emprestimos com codigo de utente introduzido
                    {
                        if(vetorEmprestimos[i].codigoUtente == vetorUtentes[posicao].codigoUtente)
                        {
                            conta++;

                        }
                    }
                    if (conta == 0)   //verifica se existem emprestimos com o codigo de utente introduzido
                    {
                        printf("\nO utente N %d nao possui emprestimos registados!",codUtente);

                    }
                    else
                            {

                            printf("\nCodigo\tUtente n \tBicicleta n\tData\t\tHora\t\tOrigem\t\tDestino\t\n");

                            for (i=0;i<quantEmprestimos;i++)
                            {
                                if(vetorEmprestimos[i].codigoUtente == vetorUtentes[posicao].codigoUtente)
                                {

                                    printf("%d\t%d\t\t%d\t\t%2d/%2d/%4d\t%2d:%2d\t\t",vetorEmprestimos[i].numero,vetorEmprestimos[i].codigoUtente,vetorEmprestimos[i].designacaoBicicleta,vetorEmprestimos[i].data.dia,vetorEmprestimos[i].data.mes,vetorEmprestimos[i].data.ano,vetorEmprestimos[i].hora.hora,vetorEmprestimos[i].hora.minuto);
                                    switch(vetorEmprestimos[i].campusOrigem)
                                    {
                                        case 1: printf("Residencias\t");
                                        break;
                                        case 2: printf("Campus 1\t");
                                        break;
                                        case 3: printf("Campus 2\t");
                                        break;
                                        case 4: printf("Campus 5\t");
                                        break;

                                    }

                                    switch(vetorEmprestimos[i].campusDestino)
                                    {
                                        case 1: printf("Residencias\t");
                                        break;
                                        case 2: printf("Campus 1\t");
                                        break;
                                        case 3: printf("Campus 2\t");
                                        break;
                                        case 4: printf("Campus 5\t");
                                        break;
                                    }


                                }
                            }
                            }
                }
        }





}


int pesquisaListaEspera(tipoEmprestimo *vetorListaEspera,int quantEspera, int codigo)
{
    int posicao,i;
    posicao = -1;

                for (i=0;i<quantEspera;i++)
                {
                    if (vetorListaEspera[i].numero == codigo)
                    {
                        posicao=i;
                        i=quantEspera;
                    }
                }
return posicao;
}


tipoEmprestimo *eliminaListaEspera(tipoEmprestimo *vetorListaEspera, int *quantEspera, int codEmprestimo)
{
    int i,posicao;
    tipoEmprestimo *pont;
    pont=vetorListaEspera;

    if (*quantEspera == 0)
    {
        printf("\nNao existem pedidos em lista de espera!");

    }
    else
            {
                posicao=pesquisaListaEspera(vetorListaEspera,*quantEspera,codEmprestimo);
                if (posicao == -1)
                {
                    printf("\nCodigo de emprestimo invalido");

                }
                else
                {
                    for (i=posicao;i<*quantEspera;i++)
                    {
                        vetorListaEspera[i]=vetorListaEspera[i+1];

                    }
                    vetorListaEspera=realloc(vetorListaEspera,(*quantEspera-1)*sizeof(tipoEmprestimo));
                    if (vetorListaEspera == NULL && *quantEspera!=1)

                    {
                        printf("\nMemoria insuficiente!");
                        vetorListaEspera=pont;

                    }
                    (*quantEspera)--;

                }

            }
return vetorListaEspera;
}



tipoEmprestimo *verificaSeHaBicicleta(tipoEmprestimo *vetorListaEspera, tipoEmprestimo *vetorEmprestimos, tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int *quantEspera,int *quantEmprestimos,tipoEmprestimo **pontLista)
{
    int i,j,posicao,posLista,codEliminar;
    tipoEmprestimo *pont;
    pont=vetorEmprestimos;
    posicao=-1;
    codEliminar=0;
    posLista=0;



    for (j=0;j<*quantEspera;j++)
                for (i=0;i<quantBicicletas;i++)  //verifica se ha alguma bicicleta disponivel para um pedido em lista de espera
                {
                    if (vetorListaEspera[j].campusOrigem == vetorBicicletas[i].campus && vetorBicicletas[i].estado==1)
                    {
                        posicao=i;
                        posLista=j;
                        codEliminar=vetorListaEspera[j].numero;
                        i=quantBicicletas;
                        j=*quantEspera;

                    }
                }




    if (posicao != -1)   // se encontrar faz o emprestimo
    {
            vetorEmprestimos=realloc(vetorEmprestimos,(*quantEmprestimos+1)*sizeof(tipoEmprestimo));

            if (vetorEmprestimos == NULL)
            {
                printf("\nMemoria insuficiente!");
                vetorEmprestimos=pont;
            }
            else
            {
            vetorEmprestimos[*quantEmprestimos]=vetorListaEspera[posLista];
            vetorEmprestimos[*quantEmprestimos].numero=*quantEmprestimos+1;
            vetorEmprestimos[*quantEmprestimos].designacaoBicicleta=vetorBicicletas[posicao].designacao;
            vetorEmprestimos[*quantEmprestimos].quantidade=-1;
            vetorBicicletas[posicao].estado=2;
            vetorBicicletas[posicao].campus=vetorEmprestimos[*quantEmprestimos].campusDestino;
            vetorListaEspera=eliminaListaEspera(vetorListaEspera,quantEspera,codEliminar);
            *pontLista=vetorListaEspera;
            (*quantEmprestimos)++;
            }
    }
return vetorEmprestimos;
}


void alteraDestino(tipoEmprestimo *elementoLista,int quantEspera)
{
    int alteracao;

    if (quantEspera == 0)
    {
        printf("\nNao existem pedidos em lista de espera!");

    }
    else{


    alteracao=lerInteiro("\nAlterar para: 1 - Residencias; 2 - Campus 1; 3 - Campus 2; 4 - Campus 5",1,4);
    if (alteracao == elementoLista->campusOrigem || alteracao == elementoLista->campusDestino)
    {
        printf("\nOpcao invalida!");
    }
    else{
    switch (alteracao)
    {
        case 1:elementoLista->campusOrigem=1;
        break;
        case 2:elementoLista->campusOrigem=2;
        break;
        case 3:elementoLista->campusOrigem=3;
        break;
        case 4:elementoLista->campusOrigem=4;
        break;
    }
    }
    }
}


void consultaEmprestimo(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEmprestimos,int codEmprestimo)
{
    int posicao,posicao_ut;

    posicao=pesquisaEmprestimo(vetorEmprestimos,quantEmprestimos,codEmprestimo);

    if (posicao == -1)
        {
            printf("\nEmprestimo inexistente!");

        }
            else
            {
                posicao_ut=procuraUtente(vetorUtentes,quantUtentes,vetorEmprestimos[posicao].codigoUtente);
                printf("\nCodigo: %d",vetorEmprestimos[posicao].numero);
                printf("\nCodigo do utente: %d",vetorEmprestimos[posicao].codigoUtente);
                printf("\nNome do utente: %s",vetorUtentes[posicao_ut].nome);
                printf("\nDesignacao da bicicleta: %d",vetorEmprestimos[posicao].designacaoBicicleta);
                printf("\nData e hora: %2d:%2d:%4d   %2d:%2d",vetorEmprestimos[posicao].data.dia,vetorEmprestimos[posicao].data.mes,vetorEmprestimos[posicao].data.ano,vetorEmprestimos[posicao].hora.hora,vetorEmprestimos[posicao].hora.minuto);
                printf("\nCampus origem: ");
                switch (vetorEmprestimos[posicao].campusOrigem)
                    {
                        case 1:printf("Residencias");
                        break;
                        case 2:printf("Campus 1");
                        break;
                        case 3:printf("Campus 2");
                        break;
                        case 4:printf("Campus 5");
                        break;
                    }
                printf("\nCampus destino: ");

                switch (vetorEmprestimos[posicao].campusDestino)
                    {
                        case 1:printf("Residencias");
                        break;
                        case 2:printf("Campus 1");
                        break;
                        case 3:printf("Campus 2");
                        break;
                        case 4:printf("Campus 5");
                        break;
                    }
                    printf("\nDistancia percorrida: ");
                if (vetorEmprestimos[posicao].quantidade != -1)
                    {
                    printf("%f",vetorEmprestimos[posicao].quantidade);
                    }
                    else
                    {
                        printf(" Sem dados");
                    }

                    printf("\nData da devolucao: ");

                if (vetorEmprestimos[posicao].dataDevolucao.ano != -1 && vetorEmprestimos[posicao].dataDevolucao.mes != -1 && vetorEmprestimos[posicao].dataDevolucao.dia != -1)
                    {
                    printf("%2d/%2d/%4d",vetorEmprestimos[posicao].dataDevolucao.dia,vetorEmprestimos[posicao].dataDevolucao.mes,vetorEmprestimos[posicao].dataDevolucao.ano);
                    }
                    else
                        {
                            printf("Sem dados");

                        }

            }
}

void consultaListaEspera(tipoEmprestimo *vetorListaEspera, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEspera, int codElemento)
{
    int posicao,posicao_ut;

    if (quantEspera == 0)
        {
            printf("\nLista de espera vazia!");

        }
        else
        {

            posicao=pesquisaListaEspera(vetorListaEspera,quantEspera,codElemento);

            if (posicao == -1)
                {
                    printf("\nPedido inexistente!");

                }
                    else
                    {
                        posicao_ut=procuraUtente(vetorUtentes,quantUtentes,vetorListaEspera[posicao].codigoUtente);
                        printf("\nCodigo: %d",vetorListaEspera[posicao].numero);
                        printf("\nCodigo do utente: %d",vetorListaEspera[posicao].codigoUtente);
                        printf("\nNome do utente: %s",vetorUtentes[posicao_ut].nome);
                        printf("\nData e hora: %2d/%2d/%4d   %2d:%2d",vetorListaEspera[posicao].data.dia,vetorListaEspera[posicao].data.mes,vetorListaEspera[posicao].data.ano,vetorListaEspera[posicao].hora.hora,vetorListaEspera[posicao].hora.minuto);
                        printf("\nCampus origem: ");
                        switch (vetorListaEspera[posicao].campusOrigem)
                            {
                                case 1:printf("Residencias");
                                break;
                                case 2:printf("Campus 1");
                                break;
                                case 3:printf("Campus 2");
                                break;
                                case 4:printf("Campus 5");
                                break;
                            }
                        printf("\nCampus destino: ");

                        switch (vetorListaEspera[posicao].campusDestino)
                            {
                                case 1:printf("Residencias");
                                break;
                                case 2:printf("Campus 1");
                                break;
                                case 3:printf("Campus 2");
                                break;
                                case 4:printf("Campus 5");
                                break;
                            }


                    }
        }
}


void ordenarListaEspera_tUtente(tipoEmprestimo *vetorListaEspera, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEspera)
{
    int i,j,hatrocas,posicao,posicao2;                              //Ordena o vetor da lista de espera de forma a dar prioridade ao estudante, depois docente, depois tec. administrativo e depois convidado
    tipoEmprestimo aux;

    hatrocas=1;

    for (i=0;i<quantEspera-1 && hatrocas!=0;i++)
        {
            hatrocas=0;
                       for (j=0;j<quantEspera-i-1;j++)
                       {
                           posicao=procuraUtente(vetorUtentes,quantUtentes,vetorListaEspera[j].numero);
                           posicao2=procuraUtente(vetorUtentes,quantUtentes,vetorListaEspera[j+1].numero);

                           if (vetorUtentes[posicao2].tipo < vetorUtentes[posicao].tipo)
                           {
                               printf("\nAQUI1");
                               hatrocas=1;
                               aux=vetorListaEspera[j];
                               vetorListaEspera[j]=vetorListaEspera[j+1];
                               vetorListaEspera[j+1]=aux;
                           }
                       }
        }


}

void ordenaListaEspera(tipoEmprestimo *vetorListaEspera, int quantEspera)
{
    int i,j,hatrocas;
    tipoEmprestimo aux;
    hatrocas=1;

    for (i=0;i<quantEspera-1 && hatrocas!=0;i++)
        {
            hatrocas=0;
           for (j=0;j<quantEspera-i-1;j++)
           {
               if (vetorListaEspera[j+1].numero<vetorListaEspera[j].numero)
               {


                   hatrocas=1;
                   aux=vetorListaEspera[j];
                   vetorListaEspera[j]=vetorListaEspera[j+1];
                   vetorListaEspera[j+1]=aux;
               }
           }
        }
}

void ordenarDistancia(tipoEmprestimo *vetorListaEspera, int quantEspera)
{
    int i,j,hatrocas,tot_distancia,tot_distancia_2;
    tipoEmprestimo aux;
    tot_distancia=0;
    tot_distancia_2=0;

    for (i=0;i<quantEspera-1 && hatrocas!=0;i++)
        {
            hatrocas=0;
           for (j=0;j<quantEspera-i-1;j++)
           {
               if ((vetorListaEspera[j+1].campusOrigem == 1 && vetorListaEspera[j+1].campusDestino == 4) || (vetorListaEspera[j+1].campusOrigem == 4 && vetorListaEspera[j+1].campusDestino == 1) )
               {
                   tot_distancia=RESID_CAMPUS1+CAMPUS1_CAMPUS2+CAMPUS2_CAMPUS5;
               }
               if ((vetorListaEspera[j].campusOrigem == 1 && vetorListaEspera[j].campusDestino == 4) || (vetorListaEspera[j].campusOrigem == 4 && vetorListaEspera[j].campusDestino == 1) )
               {
                   tot_distancia_2=RESID_CAMPUS1+CAMPUS1_CAMPUS2+CAMPUS2_CAMPUS5;
               }
               if ((vetorListaEspera[j+1].campusOrigem == 1 && vetorListaEspera[j+1].campusDestino == 3) ||( vetorListaEspera[j+1].campusOrigem == 3 && vetorListaEspera[j+1].campusDestino == 1))
               {
                   tot_distancia=RESID_CAMPUS1+CAMPUS1_CAMPUS2;
               }
               if ((vetorListaEspera[j].campusOrigem == 1 && vetorListaEspera[j].campusDestino == 3) || (vetorListaEspera[j].campusOrigem == 3 && vetorListaEspera[j].campusDestino == 1) )
               {
                   tot_distancia_2=RESID_CAMPUS1+CAMPUS1_CAMPUS2;
               }
               if ((vetorListaEspera[j+1].campusOrigem == 2 && vetorListaEspera[j+1].campusDestino == 4) || (vetorListaEspera[j+1].campusOrigem == 4 && vetorListaEspera[j+1].campusDestino == 2) )
               {
                   tot_distancia=CAMPUS1_CAMPUS2+CAMPUS2_CAMPUS5;
               }
               if ((vetorListaEspera[j].campusOrigem == 2 && vetorListaEspera[j].campusDestino == 4) || (vetorListaEspera[j].campusOrigem == 4 && vetorListaEspera[j].campusDestino == 2) )
               {
                   tot_distancia_2=CAMPUS1_CAMPUS2+CAMPUS2_CAMPUS5;
               }
               if ((vetorListaEspera[j+1].campusOrigem == 1 && vetorListaEspera[j+1].campusDestino == 2) || (vetorListaEspera[j+1].campusOrigem == 2 && vetorListaEspera[j+1].campusDestino == 1) )
               {
                   tot_distancia=RESID_CAMPUS1;
               }
               if ((vetorListaEspera[j].campusOrigem == 1 && vetorListaEspera[j].campusDestino == 2) || (vetorListaEspera[j].campusOrigem == 2 && vetorListaEspera[j].campusDestino == 1 ))
               {
                   tot_distancia_2=RESID_CAMPUS1;

               }

               if ((vetorListaEspera[j+1].campusOrigem == 2 && vetorListaEspera[j+1].campusDestino == 3) || (vetorListaEspera[j+1].campusOrigem == 3 && vetorListaEspera[j+1].campusDestino == 2) )
               {
                   tot_distancia=CAMPUS1_CAMPUS2;
               }
               if ((vetorListaEspera[j].campusOrigem == 2 && vetorListaEspera[j].campusDestino == 3) || (vetorListaEspera[j].campusOrigem == 3 && vetorListaEspera[j].campusDestino == 2) )
               {
                   tot_distancia_2=CAMPUS1_CAMPUS2;
               }
               if ((vetorListaEspera[j+1].campusOrigem == 3 && vetorListaEspera[j+1].campusDestino == 4) || (vetorListaEspera[j+1].campusOrigem == 4 && vetorListaEspera[j+1].campusDestino == 3) )
               {
                   tot_distancia=CAMPUS2_CAMPUS5;
               }
               if ((vetorListaEspera[j].campusOrigem == 3 && vetorListaEspera[j].campusDestino == 4 )|| (vetorListaEspera[j].campusOrigem == 4 && vetorListaEspera[j].campusDestino == 3) )
               {
                   tot_distancia_2=CAMPUS2_CAMPUS5;
               }



               if (tot_distancia>tot_distancia_2)
               {

                   hatrocas=1;
                   aux=vetorListaEspera[j];
                   vetorListaEspera[j]=vetorListaEspera[j+1];
                   vetorListaEspera[j+1]=aux;
               }
           }
        }
}





int defineCriterio(int criterio_atual,tipoEmprestimo *vetorListaEspera,tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes,int quantEspera, int novo_criterio)
{
    novo_criterio=lerInteiro("Opcao: ",1,3);

        if (criterio_atual == novo_criterio)
            {
                printf("\nOpcao seleccionada ja se encontra activa!");
            }
            else
            {
                  if (novo_criterio==1)
                {
                    ordenaListaEspera(vetorListaEspera,quantEspera);
                }

                if (novo_criterio==2)
                {


                    ordenarListaEspera_tUtente(vetorListaEspera,vetorUtentes,quantUtentes,quantEspera);
                }
                if (novo_criterio==3)
                {
                    ordenarDistancia(vetorListaEspera,quantEspera);
                }

            }

return novo_criterio;
}




