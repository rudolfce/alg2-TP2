/* Consideracoes so far: talvez remover a cabeca seja melhor */
#include<stdio.h>
#include "TMemoria.h"

void zeraMemoria(TMemoria* pMemoria){
    int i;

    // Inicializando parametros da lista
    pMemoria->priCelulaDisp = 0;
    pMemoria->primeiro = -1;
    pMemoria->ultimo = -1;
    pMemoria->numOcupadas = 0;

    // Inicializando indices vazios
    for (i = 0; i < MAX_SIZE-1; i++) {
        pMemoria->items[i].prox = i+1;
        pMemoria->items[i].ant = i-1;
    }
    pMemoria->items[MAX_SIZE-1].prox = -1;
    pMemoria->items[MAX_SIZE-1].ant = MAX_SIZE-2;
    //pMemoria->ultCelulaDisp = MAX_SIZE-1;
}

int memoriaVazia(TMemoria* pMemoria){
    if(!pMemoria->numOcupadas) return 1;
    return 0;
}

int numeroOcupadas(TMemoria* pMemoria){
    return pMemoria->numOcupadas;
}

/* encontraLugar e uma funcao auxiliar para encontrar o lugar
   de um Item na sequencia de chaves. O indice retornado corresponde
   ao item depois do qual a sequencia deve ser deslocada para a direita. */
int encontraAnterior(TMemoria* pMemoria, int chave){
    int i, ichave, anti;

    if(memoriaVazia(pMemoria)) return -1;
    anti = -1;
    i = pMemoria->primeiro;
    ichave = pMemoria->items[i].item.chave;

    while((chave > ichave) && (i != -1)){
        anti = i;
        i = pMemoria->items[i].prox;
        ichave = pMemoria->items[i].item.chave;
    }
    return anti;
}

int insereItem(TMemoria* pMemoria, TItem* pItem){
    int idx, antidx, proxidx;
    if(pMemoria->numOcupadas==MAX_SIZE) return 0; // Uma das formas de verificar se ha espaco livre

    idx = pMemoria->priCelulaDisp;
    pMemoria->items[idx].item = *pItem;
    pMemoria->priCelulaDisp = pMemoria->items[idx].prox;
    pMemoria->items[pMemoria->priCelulaDisp].ant = -1;

    if(memoriaVazia(pMemoria)){
        pMemoria->primeiro = idx;
        pMemoria->ultimo = idx;
        pMemoria->items[idx].prox = -1;
        pMemoria->items[idx].ant = -1;
        pMemoria->numOcupadas++;

        return 1;
    }

    // Encontra lugar na sequencia de chaves
    antidx = encontraAnterior(pMemoria, pItem->chave);
    pMemoria->items[idx].ant = antidx;
    // Caso o item ocupe a primeira posicao
    if(antidx == -1){
        proxidx = pMemoria->primeiro;
        pMemoria->primeiro = idx;
    } else{
        proxidx = pMemoria->items[antidx].prox;
        pMemoria->items[antidx].prox = idx;
    }
    pMemoria->items[idx].prox = proxidx;
    if(!(proxidx == -1)) pMemoria->items[proxidx].ant = idx;
    if(pItem->chave>pMemoria->items[pMemoria->ultimo].item.chave) pMemoria->ultimo = idx;
    pMemoria->numOcupadas++;

    return 1;
}

int removePrimeiro(TMemoria* pMemoria, TItem* out_item){
    int pri_idx, novopri_idx;

    pri_idx = pMemoria->primeiro; // Indice do item a ser removido
    if(pri_idx==-1) return 0;
    novopri_idx = pMemoria->items[pri_idx].prox; // Indice do novo primeiro item

    // Atualizando primeiro
    pMemoria->primeiro = novopri_idx;
    if(!novopri_idx==-1) pMemoria->items[novopri_idx].ant = -1;

    // Atualizando lista de memoria livre
    pMemoria->items[pri_idx].prox = pMemoria->priCelulaDisp;
    pMemoria->priCelulaDisp = pri_idx;

    // Setando valor de retorno em out_item
    *out_item = pMemoria->items[pri_idx].item;

    pMemoria->numOcupadas--;
    return 1;
}

int removeUltimo(TMemoria* pMemoria, TItem* out_item){
    int ult_idx, novoult_idx;

    ult_idx = pMemoria->ultimo; // Indice do item a ser removido
    if(ult_idx==-1) return 0;
    novoult_idx = pMemoria->items[ult_idx].ant; // Indice do novo primeiro item

    // Atualizando ultimo
    pMemoria->ultimo = novoult_idx;
    if(novoult_idx!=-1) pMemoria->items[novoult_idx].prox = -1;

    // Atualizando lista de memoria livre
    pMemoria->items[ult_idx].prox = pMemoria->priCelulaDisp;
    pMemoria->priCelulaDisp = ult_idx;

    // Setando valor de retorno em out_item
    *out_item = pMemoria->items[ult_idx].item;

    pMemoria->numOcupadas--;
    return 1;
}

/* Fancy output:
   Imprime sequencia da lista.
   Para fins de ser lindo. Ou quase. */
void imprimeSequencia(TMemoria *pMemoria){
    int i;

    if(memoriaVazia(pMemoria)){
        printf("Memoria toda vazia.\n");
        return;
    }
    i=pMemoria->primeiro;
    printf("Tamanho total: %d\n", pMemoria->numOcupadas);
    printf("addr  key  value\n");
    while(i!=-1){
        printf("%4d %4d %4d\n", i, pMemoria->items[i].item.chave,
                                 pMemoria->items[i].item.data);
        i = pMemoria->items[i].prox;
    }
}

/* Raw output:
   Imprime na sequencia da memoria, sem diferenciar livre de ocupado.
   Para fins de depuracao. */
void rawPrint(TMemoria *pMemoria){
    int i;

    for(i=0; i<MAX_SIZE; i++){
        printf("%4d %4d %4d %4d %4d\n", i, pMemoria->items[i].item.chave,
                                 pMemoria->items[i].item.data,
                                 pMemoria->items[i].ant,
                                 pMemoria->items[i].prox);
    }
}
