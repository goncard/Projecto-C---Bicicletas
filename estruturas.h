#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
#include "constantes.h"


typedef struct{
    int dia,mes,ano;
    }tipoData;
typedef struct{
    int hora,minuto;
    }tipoHora;
typedef struct{
    int designacao,estado,campus;
    char modelo[MAX_STRING];
    }tipoBicicleta;
typedef struct{
    int codigoUtente,telefone,tipo,designa_bicicleta,quant_emp;
    char nome[MAX_STRING];
    }tipoUtente;
typedef struct{
    int numero,codigoUtente,designacaoBicicleta,campusOrigem,campusDestino;
    float quantidade;
    tipoData data;
    tipoData dataDevolucao;
    tipoHora hora;
    }tipoEmprestimo;

#endif // ESTRUTURAS_H_INCLUDED
