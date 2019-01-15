#include <stdio.h>
#include <string.h>

#include "funcoes_auxiliares.h"
#include "funcoesBicicletas.h"
#include "funcoesEmprestimos.h"






tipoBicicleta lerDadosBicicleta(void)
{
    tipoBicicleta dados;

    dados.designacao=lerInteiro("\nDesignacao da bicicleta: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
    lerString("\nModelo da bicicleta: ",dados.modelo,MAX_STRING);
    dados.campus=lerInteiro("\nCampus em que se encontra a bicicleta (1 - Residencias; 2 - Campus1; 3 - Campus2; 4 - Campus5) ",1,4); //(1)-Residencias (2)- Campus 1 (3)- Campus 2 (4)- Campus 5
    return dados;
}



int acrescentaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS], int quantBicicletas)
{

    tipoBicicleta dados;
    int posicao;

    if (quantBicicletas == MAX_BICICLETAS)
        {
        printf("\nNao e possivel inserir mais bicicletas.");
        }
    else
        {
        dados=lerDadosBicicleta();
        posicao=pesquisaBicicleta(vetorBicicletas,quantBicicletas,dados.designacao);

        if(posicao!=-1)
        {
            printf("\nDesignacao de bicicleta ja existente.");
        }
        else
        {
            vetorBicicletas[quantBicicletas]=dados;
            vetorBicicletas[quantBicicletas].estado=1; //1- disponível 2-emprestada 3-avariada
            quantBicicletas++;

        }


}

return quantBicicletas;
}

int pesquisaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int designacaoBicicleta)
{
    int posicao,i;
    posicao=-1;

    for(i=0;i<quantBicicletas;i++)
    {
        if(vetorBicicletas[i].designacao == designacaoBicicleta)
        {
            posicao=i;
            i=quantBicicletas;
        }
    }
    return posicao;

}

int pesquisaBicicletaLocal(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int campus)
{
    int posicao,i;                                  //a funçao pesquisa uma bicicleta disponivel num determinado campus
    posicao=-1;

    for (i=0;i<quantBicicletas;i++)
    {
        if (vetorBicicletas[i].campus == campus && vetorBicicletas[i].estado == 1)
        {

        posicao=i;
        i=quantBicicletas;
        }

    }
    return posicao;
}

void listarBicicletas(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas)
{
    int i;

    if (quantBicicletas==0)
    {
        printf("\nNao existem bicicletas inseridas.");
    }
    else
    {
            printf("\n\nDesignacao\tModelo\t\tLocalizacao\t\tEstado");
            for (i=0;i<quantBicicletas;i++)
            {
                printf("\n %d \t\t %s",vetorBicicletas[i].designacao,vetorBicicletas[i].modelo);

                if (vetorBicicletas[i].campus==1)
                {
                printf("\t\tResidencias");
                }
                if (vetorBicicletas[i].campus==2)
                {
                printf("\t\tCampus 1");
                }
                if (vetorBicicletas[i].campus==3)
                {
                printf("\t\t Campus 2");
                }
                if (vetorBicicletas[i].campus==4)
                {
                printf("\t\t Campus 5");
                }

                if(vetorBicicletas[i].estado==1)
                {
                    printf("\t\t Disponivel");
                }
                if(vetorBicicletas[i].estado==2)
                {
                    printf("\t\t Emprestada");
                }
                if(vetorBicicletas[i].estado==3)
                {
                    printf("\t\t Avariada");
                }


            }
}
}


void gravaFichBinarioBic(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas)
{
    FILE *ficheiro;
    int lidos;

    ficheiro=fopen("bicicletas.dat","wb");
    if (ficheiro==NULL)
    {
        printf("Nao foi possivel abrir o ficheiro");
    }
    else
    {
        lidos=fwrite(&quantBicicletas,sizeof(int),1,ficheiro);
        if (lidos != 1)
        {
            printf("Nao foi possivel escrever no ficheiro!");
        }
        lidos=fwrite(vetorBicicletas,sizeof(tipoBicicleta),quantBicicletas,ficheiro);
        if (lidos != quantBicicletas)
        {
            printf("Nao foi possivel escrever no ficheiro!");
        }
    }
    fclose(ficheiro);

}

void lerFichBinarioBic(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int *quantBicicletas)
{

    FILE *ficheiro;

    ficheiro=fopen("bicicletas.dat","rb");
    if (ficheiro == NULL)
    {
        printf("Nao foi possivel ler o ficheiro!");
    }
    else
    {
        fread(quantBicicletas,sizeof(int),1,ficheiro);
        fread(vetorBicicletas,sizeof(tipoBicicleta),*quantBicicletas,ficheiro);

    }
    fclose(ficheiro);
}

void logAvarias(tipoBicicleta avaria, char descricao[MAX_STRING], float distancia)
{
    FILE *ficheiro;
    ficheiro=fopen("log_Avarias.txt","a");

    if (ficheiro == NULL)
    {
        printf("Erro na abertura do ficheiro");
    }
    else
            {

                fprintf(ficheiro,"\nDesignacao da bicicleta: %d ",avaria.designacao);
                fprintf(ficheiro,"\nDistancia percorrida em km: %.2f ",distancia);
                fprintf(ficheiro,"\nDescricao da avaria: %s ",descricao);
                fclose(ficheiro);

            }
}



void AlteraEstado(tipoBicicleta vetorBicicletas[MAX_BICICLETAS], tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEmprestimos, int quantBicicletas, int designBicicleta, int *quantAvarias, float *distPercorrida)
{
    int opcao,posicao,posicao_emprestimo,controlo;
    opcao=0;
    posicao=-1;
    posicao_emprestimo=-1;
    controlo=0;
    char descricao[MAX_STRING];
    float distancia;

        if (quantBicicletas == 0)
        {
            printf("\nNao existem bicicletas!");

        }
        else
            {


                posicao=pesquisaBicicleta(vetorBicicletas,quantBicicletas,designBicicleta);

                if (posicao == -1)
                {
                    printf("Bicicleta inexistente!");
                }
                else
                    {
                        opcao=lerInteiro("\nAlteracao a registar (1) - Avaria; (2) - Reparacao",1,2);
                        if (opcao == 1 )
                            {
                              if (vetorBicicletas[posicao].estado == 3)
                                {
                                          printf("A avaria ja se encontra registada!");

                                }
                                else{
                                        posicao_emprestimo=pesquisaEmprestimo_DesignBicicleta(vetorEmprestimos,quantEmprestimos,designBicicleta);
                                        if (posicao_emprestimo != -1)
                                            {                                     // se a bicicleta estiver emprestada força a devoluçao
                                                devolveBicicleta(vetorEmprestimos,vetorBicicletas,vetorUtentes,distPercorrida,quantEmprestimos,quantBicicletas,quantUtentes,vetorEmprestimos[posicao].numero);
                                                distancia=vetorEmprestimos[posicao].quantidade;
                                                controlo=1;
                                            }

                                        if (controlo != 1)
                                        {
                                            distancia=lerFloat("\nDistancia percorrida em km: ",0,1000);   //para nao pedir a quantidade de km duas vezes, porque também é pedido na funcao da devolucap
                                        }
                                        lerString("Descricao da avaria: ",descricao,MAX_STRING);
                                        vetorBicicletas[posicao].estado=3;//regista como avariada
                                        logAvarias(vetorBicicletas[posicao],descricao,distancia);
                                        (*quantAvarias)++;
                                    }
                            }

                        if (opcao == 2)
                        {
                            if (vetorBicicletas[posicao].estado != 3)
                            {
                                printf("\nA bicicleta nao se encontra avariada!");
                            }
                            else
                            {
                                vetorBicicletas[posicao].estado = 1;
                           }
                        }
                    }
            }

}

void consultaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int designBicicleta)
{
    int posicao;

    posicao=pesquisaBicicleta(vetorBicicletas,quantBicicletas,designBicicleta);

        if (posicao == -1)
            {
                printf("\nBicicleta nao encontrada!");
            }
            else
                    {
                        printf("\nDesignacao: %d ",vetorBicicletas[posicao].designacao);
                        printf("\nModelo: %s ",vetorBicicletas[posicao].modelo);
                        printf("\nEstado: ");
                        switch(vetorBicicletas[posicao].estado)
                            {
                                case 1:printf("Disponivel");
                                break;
                                case 2:printf("Emprestada");
                                break;
                                case 3:printf("Avariada");
                                break;
                            }
                        printf("\nLocalizacao: ");
                        switch(vetorBicicletas[posicao].campus)

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






