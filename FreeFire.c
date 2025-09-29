#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura que representa cada item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor que armazena os itens
Item mochila[MAX_ITENS];
int totalItens = 0; // Controla quantos itens estão cadastrados

// Função para cadastrar um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);  // Lê string com espaços
    printf("Digite o tipo do item (arma, munição, cura, ferramenta): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️ Mochila vazia, nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Desloca os itens para "fechar o buraco"
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\n🗑️ Item removido com sucesso!\n");
    } else {
        printf("\n❌ Item não encontrado.\n");
    }
}

// Função para listar os itens cadastrados
void listarItens() {
    if (totalItens == 0) {
        printf("\n📦 Mochila vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("-------------------------\n");
}

// Função de busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️ Mochila vazia, não há itens para buscar.\n");
        return;
    }

    char nomeBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBuscar);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado.\n");
}

// Função principal com menu
int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); listarItens(); break;
            case 2: removerItem(); listarItens(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\nSaindo do jogo... Até mais!\n"); break;
            default: printf("\nOpção inválida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
