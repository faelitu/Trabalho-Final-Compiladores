enum {
    PRG, /* programa */
    DVR, /* declaracao variaveis */
    TIP, /* tipo */
    LVR, /* lista variaveis */
    LCM, /* lista comandos */
    LEI, /* leitura */
    ESC, /* escrita */
    REP, /* repeticao */
    SEL, /* selecao */
    ATR, /* atribuicao */
    MUL, /* multiplicacao */
    DIV, /* divisao */
    SOM, /* soma */
    SUB, /* subtracao */
    MAI, /* maior */
    MEN, /* menor */
    IGU, /* igual */
    CON, /* conjuncao */
    DIS, /* disjuncao */
    IDN, /* identificador */
    VAR, /* variavel */
    NUM, /* numero */
    VER, /* verdade */
    FAL, /* falso */
    NAO, /* negacao */
    LRT, /* lista rotinas */
    PRO, /* procedimento */
    LPA, /* lista parametros */
    PAR, /* parametro */
    REF, /* referencia */
    VAL, /* valor */
    CHP, /* chamada procedimento */
    LAR  /* lista argumentos */
};

typedef struct no *ptno;

struct no {
    int tipo;
    char *valor;
    ptno filho, irmao;
};

ptno criaNo (int tipo, char *valor) {
    ptno n = (ptno) malloc (sizeof (struct no));
    n->valor = (char *) malloc (strlen(valor) * sizeof(char)+1);
    strcpy (n->valor, valor);
    n->filho = NULL;
    n->irmao = NULL;
    return n;
}

void adicionaFilho (ptno pai, ptno filho) {
    if (filho) {
        filho->irmao = pai->filho;
        pai->filho = filho;
    }
}

void mostra (ptno raiz, int nivel) {
    ptno p;
    int i;
    for (i=0; i<nivel; i++)
        printf("..");
    switch (raiz->filho) {
        case PRG: printf("programa\n"); break;
        case DVR: printf("declaracao variaveis\n"); break;
        case TIP: printf("tipo: [%s]\n", raiz->valor); break;
        case LVR: printf("lista variaveis\n"); break;
        case LCM: printf("lista comandos\n"); break;
        case LEI: printf("leitura\n"); break;
        case ESC: printf("escrita\n"); break;
        case REP: printf("repeticao\n"); break;
        case SEL: printf("atribuicao\n"); break;
        case MUL: printf("multiplicacao\n"); break;
        case DIV: printf("divisao\n"); break;
        case SOM: printf("soma\n"); break;
        case SUB: printf("subtracao\n"); break;
        case MAI: printf("maior\n"); break;
        case MEN: printf("menor\n"); break;
        case IGU: printf("igual\n"); break;
        case CON: printf("conjuncao\n"); break;
        case DIS: printf("disjuncao\n"); break;
        case VAR: printf("variavel: [%s]\n", raiz->valor); break;
        case IDN: printf("identificador: [%s]\n", raiz->valor); break;
        case NUM: printf("numero: [%s]\n", raiz->valor); break;
        case VER: printf("verdade\n"); break;
        case FAL: printf("falso\n"); break;
        case NAO: printf("negacao\n"); break;
    }
    p = raiz->filho;
    while (p) {
        mostra(p, nivel+1);
        p = p->irmao;
    }
}