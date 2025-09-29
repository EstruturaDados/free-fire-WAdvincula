#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// =====================
// STRUCTS
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =====================
// VARIÁVEIS GLOBAIS
// =====================
// Versão com vetor
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Versão com lista encadeada
No* mochilaLista = NULL;

// Contadores de comparações
int comparacoesSeq = 0;
int comparacoesBin = 0;

// =====================
// FUNÇÕES - VETOR
// =====================
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia (vetor)!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor++] = novo;
    printf("✅ Item inserido no vetor!\n");
}

void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("\nMochila (vetor) vazia.\n");
        return;
    }
    printf("\n--- Mochila Vetor ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void removerItemVetor() {
    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("🗑️ Item removido do vetor!\n");
            return;
        }
    }
    printf("❌ Item não encontrado no vetor.\n");
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSeq = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSeq++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("✅ Encontrado no vetor: %s (%s, %d)\n", 
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            return i;
        }
    }
    printf("❌ Não encontrado no vetor.\n");
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = i + 1; j < totalItensVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("✅ Vetor ordenado!\n");
}

int buscarBinariaVetor(char nome[]) {
    comparacoesBin = 0;
    int ini = 0, fim = totalItensVetor - 1;

    while (ini <= fim) {
        comparacoesBin++;
        int meio = (ini + fim) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            printf("✅ Encontrado (binária): %s (%s, %d)\n", 
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("❌ Não encontrado (binária).\n");
    return -1;
}

// =====================
// FUNÇÕES - LISTA ENCADEADA
// =====================
void inserirItemLista() {
    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("✅ Item inserido na lista!\n");
}

void listarItensLista() {
    if (mochilaLista == NULL) {
        printf("\nMochila (lista) vazia.\n");
        return;
    }
    printf("\n--- Mochila Lista ---\n");
    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerItemLista() {
    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("🗑️ Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado na lista.\n");
}

void buscarSequencialLista(char nome[]) {
    comparacoesSeq = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoesSeq++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("✅ Encontrado na lista: %s (%s, %d)\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return;
        }
        atual = atual->proximo;
    }
    printf("❌ Não encontrado na lista.\n");
}

// =====================
// MENU PRINCIPAL
// =====================
int main() {
    int opcao, estrutura;
    char nome[30];

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Usar Vetor\n");
        printf("2. Usar Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\n--- Mochila Vetor ---\n");
                printf("1. Inserir Item\n2. Remover Item\n3. Listar Itens\n4. Buscar Sequencial\n5. Ordenar Vetor\n6. Buscar Binária\n0. Voltar\nOpção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: printf("Nome para buscar: "); scanf(" %[^\n]", nome);
                            buscarSequencialVetor(nome);
                            printf("Comparações: %d\n", comparacoesSeq); break;
                    case 5: ordenarVetor(); break;
                    case 6: printf("Nome para buscar: "); scanf(" %[^\n]", nome);
                            buscarBinariaVetor(nome);
                            printf("Comparações: %d\n", comparacoesBin); break;
                }
            } while (opcao != 0);

        } else if (estrutura == 2) {
            do {
                printf("\n--- Mochila Lista ---\n");
                printf("1. Inserir Item\n2. Remover Item\n3. Listar Itens\n4. Buscar Sequencial\n0. Voltar\nOpção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: printf("Nome para buscar: "); scanf(" %[^\n]", nome);
