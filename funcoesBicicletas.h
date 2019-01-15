#ifndef FUNCOESBICICLETAS_H_INCLUDED
#define FUNCOESBICICLETAS_H_INCLUDED
#include "estruturas.h"

tipoBicicleta lerDadosBicicleta(void);
int acrescentaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS], int quantBicicletas);
int pesquisaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int designacaoBicicleta);
void listarBicicletas(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas);
void gravaFichBinarioBic(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas);
void lerFichBinarioBic(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int *quantBicicletas);
int pesquisaBicicletaLocal(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int campus);
void AlteraEstado(tipoBicicleta vetorBicicletas[MAX_BICICLETAS], tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes, int quantEmprestimos, int quantBicicletas, int designBicicleta, int *quantAvarias, float *distPercorrida);
void logAvarias(tipoBicicleta avaria, char descricao[MAX_STRING], float distancia);
void consultaBicicleta(tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int designBicicleta);








#endif // FUNCOESBICICLETAS_H_INCLUDED
