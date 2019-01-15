#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesBicicletas.h"
#include "funcoesEmprestimos.h"
#include "funcoes_Utentes.h"
#include "dadosEstatisticos.h"
#include "menus.h"

int main()
{
   tipoBicicleta vetorBicicletas[MAX_BICICLETAS];
   tipoUtente vetorUtentes[MAX_UTENTES];
   tipoEmprestimo *vetorEmprestimos;
   tipoEmprestimo *vetorListaEspera;
   tipoEmprestimo **pontLista;
   int quantBicicletas,quantAvarias,quantEmprestimos, quantEspera, quantUtentes,codigoEliminar,codElemento,posElemento,ultimoCodigo,criterioLista,novo_criterio,codUtente,designBicicleta;
   float distPercorrida;
   char opc, opcSubmenu;

   vetorEmprestimos=NULL;
   vetorListaEspera=NULL;
   pontLista=&vetorListaEspera;
   quantBicicletas=0;
   quantEspera=0;
   quantAvarias=0;
   quantEmprestimos=0;
   distPercorrida=0;
   quantUtentes=0;
   codigoEliminar=0;
   codElemento=0;
   posElemento=0;
   ultimoCodigo=0;
   criterioLista=1;//criterio de atribuicao de bicicletas a pedidos em lista de espera por defeito é 1 (por ordem de entrada).
                          //Pode ser alterado para 2 (Por tipo de utente) ou para 3(por distancia a percorrer)
   novo_criterio=0;
   codUtente=0;
   designBicicleta=0;



   do{
   opc=menu(quantEmprestimos,quantUtentes,quantEspera,distPercorrida);

           switch(opc)
           {
               case 'A': do{
                                opcSubmenu=subMenuBicicletas();
                                switch (opcSubmenu)
                                {
                                    case 'A':quantBicicletas=acrescentaBicicleta(vetorBicicletas,quantBicicletas);
                                            vetorEmprestimos=verificaSeHaBicicleta(vetorListaEspera,vetorEmprestimos,vetorBicicletas,quantBicicletas,&quantEspera,&quantEmprestimos,pontLista);
                                    break;
                                    case 'B':listarBicicletas(vetorBicicletas,quantBicicletas);
                                    break;
                                    case 'C':designBicicleta=lerInteiro("\nDesignacao da bicicleta: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
                                             AlteraEstado(vetorBicicletas,vetorEmprestimos,vetorUtentes,quantUtentes,quantEmprestimos,quantBicicletas,designBicicleta,&quantAvarias,&distPercorrida);
                                    break;
                                    case 'D':designBicicleta=lerInteiro("\nDesignacao da bicicleta: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
                                             consultaBicicleta(vetorBicicletas,quantBicicletas,designBicicleta);
                                    break;

                                }
                            }while (opcSubmenu != 'S');
                break;
                case 'B': do {
                                opcSubmenu=subMenuUtentes();
                                switch (opcSubmenu)
                                    {
                                        case 'A':quantUtentes=acrescentaUtente(vetorUtentes,quantUtentes);
                                        break;
                                        case 'B':mostrarDados(vetorUtentes,quantUtentes);
                                        break;
                                        case 'C':codUtente=lerInteiro("\nCodigo de Utente: ",MIN_NUMERO_UTENTE,MAX_NUMERO_UTENTE);
                                                 consultaUltimaBicicleta(vetorEmprestimos,vetorUtentes,vetorBicicletas,quantBicicletas,quantEmprestimos,quantUtentes,codUtente);
                                        break;
                                        case 'D':codUtente=lerInteiro("\nCodigo de utente: ",MIN_NUMERO_UTENTE,MAX_NUMERO_UTENTE);
                                                 historicoEmprestimos(vetorEmprestimos,vetorUtentes,quantEmprestimos,quantUtentes,codUtente);
                                        break;
                                        case 'E':listaUtentesDecrescente(vetorUtentes,quantUtentes);
                                        break;
                                        case 'F':codUtente=lerInteiro("\nCodigo do utente: ",MIN_NUMERO_UTENTE,MAX_NUMERO_UTENTE);
                                                 consultaUtente(vetorUtentes,quantUtentes,codUtente);
                                    break;
                                    }
                             }while (opcSubmenu != 'S');

                break;
                case 'C': do{
                                opcSubmenu=subMenuEmprestimos();
                                switch (opcSubmenu)
                                    {
                                        case 'A':vetorEmprestimos=insereEmprestimo(vetorEmprestimos,vetorListaEspera,vetorBicicletas,vetorUtentes,&quantEmprestimos,quantBicicletas,&quantEspera,quantUtentes,pontLista,&ultimoCodigo);
                                        break;
                                        case 'B':listaEmprestimos(vetorEmprestimos,&quantEmprestimos);
                                        break;
                                        case 'C':codElemento=lerInteiro("\nCodigo de emprestimo: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
                                                 devolveBicicleta(vetorEmprestimos, vetorBicicletas, vetorUtentes, &distPercorrida,quantEmprestimos, quantBicicletas,quantUtentes,codElemento);
                                                 vetorEmprestimos=verificaSeHaBicicleta(vetorListaEspera,vetorEmprestimos,vetorBicicletas,quantBicicletas,&quantEspera,&quantEmprestimos,pontLista);
                                        break;
                                        case 'D':codElemento=lerInteiro("\nCodigo de emprestimo: ",1,9999);
                                                 consultaEmprestimo(vetorEmprestimos,vetorUtentes,quantUtentes,quantEmprestimos,codElemento);
                                        break;

                                    }
                            }while (opcSubmenu != 'S');
                break;
                case 'D': do {
                                                    opcSubmenu=subMenuListaEspera();
                                                    switch (opcSubmenu)
                                                    {
                                                    case 'A':mostraListaEspera(vetorListaEspera,quantEspera);
                                                        break;
                                                    case 'B':
                                                                codigoEliminar=lerInteiro("\nCodigo de pedido: ",1,9999);
                                                                vetorListaEspera=eliminaListaEspera(vetorListaEspera,&quantEspera,codigoEliminar);

                                                        break;
                                                    case 'C':
                                                                codElemento=lerInteiro("\nCodigo de pedido: ",1,9999);
                                                                posElemento=pesquisaListaEspera(vetorListaEspera,quantEspera,codElemento);
                                                                alteraDestino(&vetorListaEspera[posElemento],quantEspera);
                                                                vetorEmprestimos=verificaSeHaBicicleta(vetorListaEspera,vetorEmprestimos,vetorBicicletas,quantBicicletas,&quantEspera,&quantEmprestimos,pontLista);


                                                        break;
                                                        case 'D':codElemento=lerInteiro("\nCodigo de pedido: ",1,9999);
                                                                 consultaListaEspera(vetorListaEspera,vetorUtentes,quantUtentes,quantEspera,codElemento);
                                                        break;
                                                        case 'E':  novo_criterio=lerInteiro("\nOpcoes: (1)-Por ordem de entrada de pedido (2)-Por tipo de utente (3)-Por distancia a percorrer  ",1,3);
                                                                   criterioLista=defineCriterio(criterioLista,vetorListaEspera,vetorUtentes,quantUtentes,quantEspera,novo_criterio);
                                                        break;
                                                    }
                                                    } while (opcSubmenu != 'S');
                break;
                case 'E': do {
                                opcSubmenu=subMenuFicheiros();
                                switch(opcSubmenu)
                                {
                                    case 'A':gravaFichBinarioBic(vetorBicicletas,quantBicicletas);
                                             gravaFicheiroBinario(vetorUtentes,quantUtentes);
                                             gravaFichBinarioEmprestimos(vetorEmprestimos,vetorListaEspera,quantEspera,quantEmprestimos);
                                    break;
                                    case 'B':lerFichBinarioBic(vetorBicicletas,&quantBicicletas);
                                             lerFicheiroBinario(vetorUtentes,&quantUtentes);
                                             vetorEmprestimos=lerFichBin_Emprestimos(vetorEmprestimos,vetorListaEspera,&quantEspera,&quantEmprestimos,pontLista);
                                    break;
                                }
                            }while (opcSubmenu != 'S');
                break;
                case 'F': do {
                                opcSubmenu=subMenuEstatistica();
                                switch (opcSubmenu)
                                {
                                    case 'A':mediaDistanciaBic(vetorEmprestimos,vetorBicicletas,quantEmprestimos,quantBicicletas);
                                    break;
                                    case 'B':quantEmprestimosPorData(vetorEmprestimos,quantEmprestimos);
                                    break;
                                    case 'C':percEmprestimosTipoUtente(vetorEmprestimos,vetorUtentes,quantEmprestimos,quantUtentes);
                                    break;
                                    case 'D':campusMaior(vetorEmprestimos,quantEmprestimos);
                                    break;
                                    case 'E':designBicicleta=lerInteiro("\nDesignacao da bicicleta: ",MIN_DESIGNACAO,MAX_DESIGNACAO);
                                    quantUtentes_Bicicleta(vetorEmprestimos,vetorBicicletas,quantBicicletas,quantEmprestimos,designBicicleta);
                                    break;
                                }
                            } while(opcSubmenu!='S');
                break;


           }
   }while(opc!='S');

free(vetorEmprestimos);
free(vetorListaEspera);
return 0;
}
