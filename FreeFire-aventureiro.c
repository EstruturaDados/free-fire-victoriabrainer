#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITENS 10
// ============================================================================
//                  CÓDIGO DA ILHA – EDIÇÃO FREE FIRE
//                            Nível: Aventureiro
// ============================================================================
// Duas versões do sistema de mochila:
// - Mochila com VETOR (lista sequencial)
// - Mochila com LISTA ENCADEADA (estrutura dinâmica)
// ============================================================================

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================================================================
//                 PROTÓTIPOS DAS FUNÇÕES (VETOR)
// ============================================================================

void inserirItemVetor(Item mochila[], int *numItens);
void removerItemVetor(Item mochila[], int *numItens);
void listarItensVetor(const Item mochila[], int numItens);
void buscaSequencialVetor(const Item mochila[], int numItens);
void ordenarVetor(Item mochila[], int numItens);
void buscaBinariaVetor(const Item mochila[], int numItens);
void limparBufferEntrada();

// ============================================================================
//                 PROTÓTIPOS DAS FUNÇÕES (LISTA)
// ============================================================================

void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
void buscarItemLista(No *inicio);
void liberarMemoriaLista(No **inicio);

// ============================================================================
//                 VARIÁVEIS GLOBAIS DE CONTROLE
// ============================================================================

int comparacoes = 0;

// ============================================================================
//                          FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    int escolhaEstrutura;
    printf("\n=== Gerenciamento da Mochila - Free Fire ===\n");
    printf("1. Usar mochila com vetor\n");
    printf("2. Usar mochila com lista encadeada\n");
    printf("Escolha: ");
    scanf("%d", &escolhaEstrutura);
    limparBufferEntrada();


    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    
    if (escolhaEstrutura == 1) {
        // ===================== MODO VETOR =====================

        // Vetor mochila:
        // Armazena até 10 itens coletados.
        Item mochila[MAX_ITENS];
        int numItens = 0;
        int opcao;

        do {
            printf("\n=== Menu da Mochila (Vetor) ===\n");
            printf("1. Adicionar um item\n");
            printf("2. Remover um item\n");
            printf("3. Listar todos os itens\n");
            printf("4. Buscar item (sequencial)\n");
            printf("5. Ordenar itens por nome\n");
            printf("6. Buscar item (binaria)\n");
            printf("0. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            limparBufferEntrada();
    
            switch (opcao) {
                case 1:
                    inserirItemVetor(mochila, &numItens);
                    break;
                case 2:
                    removerItemVetor(mochila, &numItens);
                    break;
                case 3:
                    listarItensVetor(mochila, numItens);
                    break;
                case 4:
                    buscaSequencialVetor(mochila, numItens);
                    break;
                case 5:
                    ordenarVetor(mochila, numItens);
                    break;
                case 6:
                    buscaBinariaVetor(mochila, numItens);
                    break;
                case 0:
                    printf("Saindo da mochila com vetor.\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
            }
        } while (opcao != 0);
    }
    else if (escolhaEstrutura == 2) {
        // ===================== MODO LISTA ENCADEADA =====================

        No *inicio = NULL;
        int opcao;

        do {
            printf("\n=== Menu da Mochila (Lista Encadeada) ===\n");
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
                    inserirItemLista(&inicio);
                    break;
                case 2:
                    removerItemLista(&inicio);
                    break;
                case 3:
                    listarItensLista(inicio);
                    break;
                case 4:
                    buscarItemLista(inicio);
                    break;
                case 0:
                    printf("Saindo da mochila com lista encadeada.\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
            }
        } while (opcao != 0);

        liberarMemoriaLista(&inicio);
    }
    else {
        printf("Opcao invalida! Encerrando o programa. Até mais!\n");
    }

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


// ============================================================================
//                    IMPLEMENTAÇÕES - VERSÃO VETOR
// ============================================================================


/**
 * @brief Adiciona um novo item à mochila do jogador, se houver espaço disponível.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Ponteiro para o número atual de itens na mochila.
 */
void inserirItemVetor(Item mochila[], int *numItens) {
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
}


/**
 * @brief Remove um item da mochila do jogador com base no nome fornecido.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Ponteiro para o número atual de itens na mochila.
 */
void removerItemVetor(Item mochila[], int *numItens) {
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
void listarItensVetor(const Item mochila[], int numItens) {
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
void buscaSequencialVetor(const Item mochila[], int numItens) {
    int comparacoes = 0;
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item (Sequencial) ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
    }

    printf("Item nao encontrado na mochila. Comparacoes realizadas: %d\n", comparacoes);
}


/**
 * @brief Ordena os itens na mochila do jogador por nome usando o algoritmo Bubble Sort.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
void ordenarVetor(Item mochila[], int numItens) {
    if (numItens < 2) {
        printf("Mochila com poucos itens! Nao e necessario ordenar.\n");
        return;
    }

    comparacoes = 0;
    Item temp;
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("\nItens ordenados por nome com sucesso! Comparacoes realizadas: %d\n", comparacoes);
}


/**
 * @brief Realiza busca binária por nome na mochila do jogador.
 * @param mochila Vetor de itens na mochila (deve estar ordenado por nome).
 * @param numItens Número atual de itens na mochila.
 */
void buscaBinariaVetor(const Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item (Binaria) ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int inicio = 0, fim = numItens - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;
        int resultadoComparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (resultadoComparacao == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
        else if (resultadoComparacao < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("Item nao encontrado na mochila. Comparacoes realizadas: %d\n", comparacoes);
}

// ============================================================================
//                    IMPLEMENTAÇÕES - VERSÃO LISTA
// ============================================================================


/**
 * @brief Adiciona um novo item à mochila do jogador (lista encadeada).
 * @param inicio Ponteiro para o ponteiro do início da lista.
 */
void inserirItemLista(No **inicio) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memoria para novo item.\n");
        return;
    }

    printf("\n=== Cadastro de Novo Item ===\n");
    printf("Nome do item: ");
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';

    printf("Tipo (arma, municao, cura, etc): ");
    fgets(novoNo->dados.tipo, sizeof(novoNo->dados.tipo), stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBufferEntrada();

    novoNo->proximo = *inicio;
    *inicio = novoNo;

    printf("\nItem adicionado com sucesso!\n");
}


/**
 * @brief Remove um item da mochila do jogador (lista encadeada) com base no nome fornecido.
 * @param inicio Ponteiro para o ponteiro do início da lista.
 */
void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n=== Remover Item ===\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na mochila.\n");
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
}


/**
 * @brief Lista todos os itens presentes na mochila do jogador (lista encadeada).
 * @param inicio Ponteiro para o início da lista.
 */
void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia! Nenhum item para listar.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------------\n");
    for (No *atual = inicio; atual != NULL; atual = atual->proximo) {
        printf("%-20s %-15s %-10d\n", 
            atual->dados.nome, 
            atual->dados.tipo, 
            atual->dados.quantidade);
    }
    printf("--------------------------------------------------------\n");
}


/**
 * @brief Busca um item na mochila do jogador pelo nome (lista encadeada).
 * @param inicio Ponteiro para o início da lista.
 */
void buscarItemLista(No *inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBuscar[30];
    printf("\n=== Buscar Item ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    int comparacoes = 0;
    for (No *atual = inicio; atual != NULL; atual = atual->proximo) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nomeBuscar) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoes);
            return;
        }
    }

    printf("Item nao encontrado na mochila. Comparacoes realizadas: %d\n", comparacoes);
}


/**
 * @brief Libera toda a memória alocada para a lista encadeada.
 * @param inicio Ponteiro para o ponteiro do início da lista.
 */
void liberarMemoriaLista(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

// ============================================================================
//                    FUNÇÃO AUXILIAR
// ============================================================================


/**
 * @brief Limpa o buffer de entrada para evitar problemas com fgets após scanf.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
