/*+--------------------------------------------------------------------+
  |             UNIFAL - Universidade Federal de Alfenas               |
  |               BACHARELADO EM CIENCIA DA COMPUTACAO.                |
  | Trabalho..: Compilador Simples - Procedimentos                     |
  | Disciplina: Compiladores                                           |
  | Professor.: Luiz Eduardo da Silva                                  |
  | Aluno.....: Rafael Felipe dos Santos Machado                       |
  | Data......: 04/12/2019                                             |
  +--------------------------------------------------------------------+*/

/*----------------------------------------------------------------------
*   Estruturas e Rotinas Utilitarias do Compilador
*
*   Por Luiz Eduardo da Silva
*   Implementado por Rafael Felipe dos Santos Machado
*-----------------------------------------------------------------------*/

#include <stdarg.h>

/*----------------------------------------------------------------------
*   Limites das estruturas
*-----------------------------------------------------------------------*/

#define TAM_TSIMB 100 /* Tamanho da tabela de simbolos */
#define TAM_PSEMA 100 /* Tamanho da pilha semantica */

/*----------------------------------------------------------------------
*   Variaveis globais
*-----------------------------------------------------------------------*/

int TOPO_TSIMB      = 0; /* TOPO da tabela de simbolos */
int TOPO_PSEMA      = 0; /* TOPO da pilha semantica */
int ROTULO          = 0; /* Proximo numero de rotulo */
int CONTA_VARS      = 0; /* Numero de variaveis */
int POS_SIMB;            /* Posicao na tabela de simbolos */
int aux;                 /* Variavel auxiliar */
int numLinha        = 1; /* Numero da linha no programa */
char atomo[30];          /* Nome de um identificador ou numero */

/*----------------------------------------------------------------------
*   Rotina geral de tratamento de erro
*-----------------------------------------------------------------------*/

void ERRO (char *msg, ...) {
    char formato [255];
    va_list arg;
    va_start (arg, msg);
    sprintf (formato, "\n%d: ", numLinha);
    strcat (formato, msg);
    strcat (formato, "\n\n");
    printf ("\nERRO no programa");
    vprintf (formato, arg);
    va_end (arg);
    exit (1);
}

/*----------------------------------------------------------------------
*   Tabela de Simbolos
*-----------------------------------------------------------------------*/

struct elem_tab_simbolos {
    char id[30];
    int desloca;
} TSIMB [TAM_TSIMB], elem_tab;

/*----------------------------------------------------------------------
*   Pilha Semantica
*-----------------------------------------------------------------------*/

int PSEMA[TAM_PSEMA];

/*----------------------------------------------------------------------
*   Funcao que BUSCA um simbolo na tabela de simbolos.
*       Retorna -1 se o simbolo nao esta' na tabela
*       Retorna i, onde i e' o indice do simbolo na tabela
*           se o simbolo esta' na tabela
*-----------------------------------------------------------------------*/

int busca_simbolo (char *ident) {
    int i = TOPO_TSIMB - 1;
    for (;strcmp (TSIMB[i].id, ident) && i >= 0; i--);
    return i;
}

/*----------------------------------------------------------------------
*   Funcao que INSERE um simbolo na tabela de simbolos
*       Se ja' existe um simbolo com mesmo nome e mesmo nivel
*       uma mensagem de erro e' apresentada e o programa e'
*       interrompido.
*-----------------------------------------------------------------------*/

void insere_simbolo (struct elem_tab_simbolos *elem) {
    if (TOPO_TSIMB == TAM_TSIMB) {
        ERRO ("OVERFLOW - tabela de simbolos");
    } else {
        POS_SIMB = busca_simbolo(elem->id);
        if (POS_SIMB != -1) {
            ERRO ("Identificador [%s] duplicado", elem->id);
        }
        TSIMB[TOPO_TSIMB] = *elem;
        TOPO_TSIMB++;
    }
}

/*----------------------------------------------------------------------
*   Funcao de insercao de uma variavel na tabela de simbolos
*-----------------------------------------------------------------------*/

void insere_variavel (char *ident) {
    strcpy (elem_tab.id, ident);
    elem_tab.desloca = CONTA_VARS;
    insere_simbolo(&elem_tab);
}

/*----------------------------------------------------------------------
*   Rotinas para manutencao da PILHA SEMANTICA
*-----------------------------------------------------------------------*/

void empilha (int n) {
    if (TOPO_PSEMA == TAM_PSEMA) {
        ERRO ("OVERFLOW - Pilha Semantica");
    }
    PSEMA[TOPO_PSEMA++] = n;
}

int desempilha () {
    if (TOPO_PSEMA == 0) {
        ERRO ("UNDERFLOW - Pilha Semantica");
    }
    return PSEMA[--TOPO_PSEMA];
}