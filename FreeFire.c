#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
// ============================================================================
//                  CÓDIGO DA ILHA – EDIÇÃO FREE FIRE
//                            Nível: Novato
// ============================================================================
// Simula o inventário inicial do jogador com itens coletados.
// O jogador pode adicionar, remover, listar e buscar itens na mochila.
// ============================================================================

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Protótipos das funções ---
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBufferEntrada();


int main() {
    // Vetor mochila:
    // Armazena até 10 itens coletados.
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n=== Gerenciamento da Mochila - Free Fire ===\n");
        printf("1. Adicionar um item\n");
        printf("2. Remover um item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// ============================================================================
//                          FUNÇÕES DO SISTEMA
// ============================================================================

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.


/**
 * @brief Adiciona um novo item à mochila do jogador, se houver espaço disponível.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Ponteiro para o número atual de itens na mochila.
 */
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== Cadastro de Novo Item ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma, municao, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBufferEntrada();

    mochila[*numItens] = novo;
    (*numItens)++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *numItens);
}


/**
 * @brief Remove um item da mochila do jogador com base no nome fornecido.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Ponteiro para o número atual de itens na mochila.
 */
void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n=== Remover Item ===\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
            listarItens(mochila, *numItens);
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}


/**
 * @brief Lista todos os itens presentes na mochila do jogador.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
void listarItens(const Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para listar.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d\n", 
            mochila[i].nome, 
            mochila[i].tipo, 
            mochila[i].quantidade);
    }
    printf("--------------------------------------------------------\n");
}


/**
 * @brief Busca um item na mochila do jogador pelo nome.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
void buscarItem(const Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item por Nome ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}


/**
 * @brief Limpa o buffer de entrada para evitar problemas com fgets após scanf.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
