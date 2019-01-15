#ifndef FUNCOES_UTENTES_H_INCLUDED
#define FUNCOES_UTENTES_H_INCLUDED
#include "estruturas.h"
#include "constantes.h"

tipoUtente lerDadosUtente(void);
int acrescentaUtente(tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes);
int procuraUtente (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes, int numero);
void mostrarDados(tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes);
void gravaFicheiroBinario (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes);
void lerFicheiroBinario (tipoUtente vetorUtentes[MAX_UTENTES], int*quantUtentes);
void gravaFicheiroTexto (tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes);
void listaUtentesDecrescente(tipoUtente vetorUtentes[MAX_UTENTES],int quantUtentes);
void consultaUltimaBicicleta(tipoEmprestimo *vetorEmprestimos, tipoUtente vetorUtentes[MAX_UTENTES], tipoBicicleta vetorBicicletas[MAX_BICICLETAS],int quantBicicletas,int quantEmprestimos,int quantUtentes,int codUtente);
void consultaUtente(tipoUtente vetorUtentes[MAX_UTENTES], int quantUtentes,int codUtente);


#endif // FUNCOES_UTENTES_H_INCLUDED
