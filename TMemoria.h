#ifndef _TMEMORIA_
#define _TMEMORIA_

#define MAX_SIZE 10

typedef struct{
    int chave;
    int data;
} TItem;

typedef struct{
    TItem item;
    int prox, ant;
} TCelula;

typedef struct{
    TCelula items[MAX_SIZE];
    int priCelulaDisp;
    int primeiro, ultimo;
    int numOcupadas;
} TMemoria;

void zeraMemoria(TMemoria *);
int memoriaVazia(TMemoria *);
int numeroOcupadas(TMemoria *);
int encontraAnterior(TMemoria *, int);
int insereItem(TMemoria *, TItem *);
void mantemOrganizado(TMemoria *, int);
int removePrimeiro(TMemoria *, TItem *);
int removeUltimo(TMemoria *, TItem *);
void imprimeSequencia(TMemoria *);
void rawPrint(TMemoria *);

#endif
