#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes_auxiliares.h"

char menu(int quantEmprestimos, int quantUtentes, int quantEspera, float distPercorrida)
{
    char opcao;

    do{

    printf("\n\n\n\t\t**************MENU PRINCIPAL**************");
    printf("\nA - MENU BICICLETAS");
    printf("\t\t\t\tQuantidade de emprestimos: %d",quantEmprestimos);
    printf("\nB - MENU UTENTES");
    printf("\t\t\t\tQuantidade de utentes %d",quantUtentes);
    printf("\nC - MENU EMPRESTIMOS");
    printf("\t\t\t\tDistancia percorrida: %.2f KM ",distPercorrida);
    printf("\nD - MENU LISTA DE ESPERA");
    printf("\t\t\tPedidos em lista de espera: %d ",quantEspera);
    printf("\nE - OPERACOES DE FICHEIROS");
    printf("\nF - DADOS ESTATISTICOS");
    printf("\nS - SAIR");
    printf("\n\nInsira a opcao: ");
    scanf(" %c",&opcao);
    limpaBufferStdin();
    opcao=toupper(opcao);

    } while (opcao != 'A' && opcao !='B' && opcao !='C' && opcao !='D' && opcao !='E' && opcao !='F' && opcao !='S');

return opcao;
}

char subMenuBicicletas()
{
    char opcao;

    do{
        printf("\n\n\n\t\t**************MENU BICICLETAS**************");
        printf("\nA - INSERIR BICICLETAS");
        printf("\nB - LISTAR BICICLETAS");
        printf("\nC - REGISTAR AVARIA/REPARACAO");
        printf("\nD - CONSULTAR BICICLETA");

        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao !='D' && opcao !='S');
return opcao;
}

char subMenuFicheiros()
{
    char opcao;

    do{
        printf("\n\n\n\t\t**************OPERACOES DE FICHEIROS**************");
        printf("\nA - GRAVAR DADOS EM FICHEIROS");
        printf("\nB - LER DADOS DE FICHEIROS");
        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while (opcao != 'A' && opcao != 'B' && opcao !='S');
return opcao;
}




char subMenuEstatistica()
{


    char opcao;

    do{
        printf("\n\n\n\t\t**************MENU DADOS ESTATISTICOS**************");
        printf("\nA - DISTANCIA MEDIA PERCORRIDA POR BICICLETA");
        printf("\nB - QUANTIDADE DE EMPRESTIMOS EFECTUADOS ENTRE DUAS DATAS");
        printf("\nC - PERCENTAGEM DE EMPRESTIMOS EFECTUADOS POR TIPO DE UTENTE");
        printf("\nD - CAMPUS DE ORIGEM COM MAIOR QUANTIDADE DE EMPRESTIMOS");
        printf("\nE - QUANTIDADE DE UTENTES QUE UTILIZARAM UMA BICICLETA");
        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao !='S');

return opcao;
}

char subMenuEmprestimos()
{
    char opcao;

    do{
        printf("\n\n\n\t\t**************MENU EMPRESTIMOS**************");
        printf("\nA - INSERIR EMPRESTIMO");
        printf("\nB - LISTAR EMPRESTIMOS");
        printf("\nC - DEVOLVER BICICLETA");
        printf("\nD - CONSULTAR EMPRESTIMO");

        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao !='S');
return opcao;
}

char subMenuUtentes()
{
    char opcao;

    do{
        printf("\n\n\n\t\t**************MENU UTENTES**************");
        printf("\nA - INSERIR UTENTE");
        printf("\nB - LISTAR UTENTES");
        printf("\nC - CONSULTAR DADOS ULTIMA BICICLETA UTILIZADA");
        printf("\nD - CONSULTAR HISTORICO DE EMPRESTIMOS");
        printf("\nE - LISTAR UTENTES POR QUANTIDADE DE EMPRESTIMOS");
        printf("\nF - CONSULTAR UTENTE");


        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while(opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao!='F' && opcao !='S');

return opcao;
}

char subMenuListaEspera()
{
    char opcao;
    do{
        printf("\n\n\n\t\t**************MENU LISTA DE ESPERA**************");
        printf("\nA - CONSULTAR LISTA DE ESPERA");
        printf("\nB - ELIMINAR PEDIDO");
        printf("\nC - ALTERAR DESTINO");
        printf("\nD - CONSULTAR PEDIDO");
        printf("\nE - ALTERAR CRITERIO ATRIBUICAO BICICLETAS");
        printf("\nS - SAIR");
        printf("\n\nInsira a opcao: ");
        scanf(" %c",&opcao);
        limpaBufferStdin();
        opcao=toupper(opcao);

        }while(opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao !='E' && opcao !='S');

return opcao;
}


