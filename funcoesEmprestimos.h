#ifndef FUNCOESEMPRESTIMOS_H_INCLUDED
#define FUNCOESEMPRESTIMOS_H_INCLUDED
#include "estruturas.h"

tipoEmprestimo *insereEmprestimo(tipoEmprestimo *vetorEmprestimos, tipoEmprestimo *vetorListaEspera, tipoBicicleta vetorBicicletas[MAX_BICICLETAS], tipoUtente vetorUtentes[MAX_UTENTES], int *quantEmprestimos,int quantBicicletas, int *quantEspera, int quantUtentes, tipoEmprestimo **pontLista, int *ultimoCodigo);
void mostraListaEspera(tipoEmprestimo *vetorListaEspera,int quantEspera);
int pesquisaEmprestimo(tipoEmprestimo *vetorEmprestimos,int *quantEmprestimos,int codigoEmprestimo);
int pesquisaEmprestimo_DesignBicicleta(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos, int designBicicleta);
void devolveBicicleta(tipoEmprestimo *vetorEmprestimos,tipoBicicleta vetorBicicletas[MAX_BICICLETAS], tipoUtente vetorUtentes[MAX_UTENTES], float *distPercorrida, int quantEmprestimos, int quantBicicletas,int quantUtentes,int codEmprestimo);
void listaEmprestimos(tipoEmprestimo *vetorEmprestimos,int *quantEmprestimos);
tipoEmprestimo *lerFichBin_Emprestimos(tipoEmprestimo *vetorEmprestimos,tipoEmprestimo *vetorListaEspera, int *quantEspera, int *quantEmprestimos,tipoEmprestimo **pontLista);
void gravaFichBinarioEmprestimos(tipoEmprestimo *vetorEmprestimos, tipoEmprestimo *vetorListaEspera, int quantEspera, int quantEmprestimos);
void ordenaData (tipoEmprestimo *vetorEmprestimos, int quantEmprestimos);
void historicoEmprestimos(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES], int quantEmprestimos, int quantUtentes,int codUtente);
int pesquisaListaEspera(tipoEmprestimo *vetorListaEspera,int quantEspera, int codigo);
tipoEmprestimo *eliminaListaEspera(tipoEmprestimo *vetorListaEspera, int *quantEspera, int codEmprestimo);
void alteraDestino(tipoEmprestimo *elementoLista, int quantEspera);
tipoEmprestimo *verificaSeHaBicicleta(tipoEmprestimo *vetorListaEspera, tipoEmprestimo *vetorEmprestimos, tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int *quantEspera,int *quantEmprestimos,tipoEmprestimo **pontLista);
void consultaEmprestimo(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEmprestimos,int codEmprestimo);
void consultaListaEspera(tipoEmprestimo *vetorListaEspera, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEspera, int codElemento);
void ordenarListaEspera_tUtente(tipoEmprestimo *vetorListaEspera, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEspera);
void ordenaListaEspera(tipoEmprestimo *vetorListaEspera, int quantEspera);
int defineCriterio(int criterio_atual,tipoEmprestimo *vetorListaEspera,tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes,int quantEspera,int novo_criterio);
void ordenarDistancia(tipoEmprestimo *vetorListaEspera, int quantEspera);





#endif // FUNCOESEMPRESTIMOS_H_INCLUDED
