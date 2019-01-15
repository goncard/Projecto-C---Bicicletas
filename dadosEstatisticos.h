#ifndef CALCULOS_H_INCLUDED
#define CALCULOS_H_INCLUDED
#include "constantes.h"
#include "estruturas.h"

#include "funcoes_auxiliares.h"

int PedirCodigoBic(void);
void mediaDistanciaBic(tipoEmprestimo *vetorEmprestimos,tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantEmprestimos,int quantBicicletas);
void quantEmprestimosPorData(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos);
void percEmprestimosTipoUtente(tipoEmprestimo *vetorEmprestimos,tipoUtente vetorUtentes[MAX_UTENTES],int quantEmprestimos, int quantUtentes);
void campusMaior(tipoEmprestimo *vetorEmprestimos, int quantEmprestimos);
void quantUtentes_Bicicleta(tipoEmprestimo *vetorEmprestimos, tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int quantEmprestimos,int designBicicleta);
void escreveCampus(int indice, int contador[4]);




#endif // CALCULOS_H_INCLUDED
