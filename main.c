#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TMemoria.h"

int verbose;

/* Funcao leItem foi implementada apenas para testar as rotinas de TMemoria,
   e, por isso, nao esta inclusa no TAD. */
TItem leItem(){
    TItem item;

    if(verbose) printf("Digite a chave: ");
    scanf("%d", &(item.chave));
    if(verbose) printf("Digite o valor a ser estocado: ");
    scanf("%d", &(item.data));

    return item;
}

void printItem(TItem item){
    printf("Chave: %d / ", item.chave);
    printf("Dado: %d\n", item.data);
}

int main(int argc, char* argv[]){
    int i, numcel;

    TItem item;
    TMemoria* pMemoria;

    if(argc>1){
        if(!strcmp("-v", argv[1])){
            verbose = 1;
        }
        else{
            fprintf(stderr, "Parametro desconhecido: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    if((pMemoria=(TMemoria *)malloc(sizeof(TMemoria)))==NULL){
        fprintf(stderr, "Erro ao alocar memoria. Quebrando...\n");
        exit(EXIT_FAILURE);
    }

    zeraMemoria(pMemoria);
    if(verbose) printf("Insira o numero desejado de celulas: ");
    scanf("%d", &numcel);

    for(i=0; i<numcel; i++){
        if(verbose) printf("Item numero %d: ", i);
	item = leItem();
        if(!insereItem(pMemoria, &item)) fprintf(stderr, "Item nao incluido.\n");
	if(verbose) printf("Ocupadas: %d\n", numeroOcupadas(pMemoria));
    }
    if(verbose) printf("Removendo dois items:\n");
    if(!removePrimeiro(pMemoria, &item))  fprintf(stderr, "Memoria vazia.\n");
    if(verbose) printItem(item);
    if(!removePrimeiro(pMemoria, &item))  fprintf(stderr, "Memoria vazia.\n");
    if(verbose) printItem(item);


    if(verbose) printf("Item numero %d: ", i);
    item = leItem();
    if(!(insereItem(pMemoria, &item))) fprintf(stderr, "Item nao incluido.\n");

    removeUltimo(pMemoria, &item);
    removeUltimo(pMemoria, &item);

    if(verbose) printf("Imprimindo:\n");
    imprimeSequencia(pMemoria);
    rawPrint(pMemoria);

    free(pMemoria);
    exit(EXIT_SUCCESS);
}
