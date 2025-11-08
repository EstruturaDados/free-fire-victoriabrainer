#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COMPONENTES 20
// ============================================================================
//                  CÓDIGO DA ILHA – EDIÇÃO FREE FIRE
//                            Nível: Mestre
// ============================================================================
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
// ============================================================================

// Struct Item:
/**
 * @brief Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
 * @note A prioridade indica a importância do item na montagem do plano de fuga.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;


// Enum CriterioOrdenacao:
/**
 * @brief Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
 */
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// ============================================================================
//                        PROTÓTIPOS DAS FUNÇÕES
// ============================================================================

void cadastrarComponente(Componente mochila[], int *numItens);
void removerItem(Componente mochila[], int *numItens);
void mostrarComponentes(const Componente mochila[], int numItens);

long bubbleSortNome(Componente mochila[], int numItens);
long insertionSortTipo(Componente mochila[], int numItens);
long selectionSortPrioridade(Componente mochila[], int numItens);

void menuDeOrdenacao(Componente mochila[], int numItens, bool *ordenadaPorNome);
void buscaBinariaPorNome(const Componente mochila[], int numItens, bool ordenadaPorNome);

void exibirMenu(bool listaOrdenadaPorNome);
void limparTela();
void limparBufferEntrada();

// ============================================================================
//                 VARIÁVEIS GLOBAIS DE CONTROLE
// ============================================================================

int comparacoes = 0;

// ============================================================================
//                          FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    // Vetor mochila:
    // Armazena até 20 componentes coletados.
    Componente mochila[MAX_COMPONENTES];
    int numItens = 0;
    int opcao;
    bool listaOrdenadaPorNome = false;

    do {
        limparTela();
        exibirMenu(listaOrdenadaPorNome);
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarComponente(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                mostrarComponentes(mochila, numItens);
                break;
            case 4:
                menuDeOrdenacao(mochila, numItens, &listaOrdenadaPorNome);
                break;
            case 5:
                buscaBinariaPorNome(mochila, numItens, listaOrdenadaPorNome);
                break;
            case 0:
                printf("Saindo da mochila...\n");
                printf("Encerrando o programa. Até mais!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}


// ============================================================================
//                          FUNÇÕES DO SISTEMA
// ============================================================================

/**
 * @brief Adiciona um novo item à mochila do jogador, se houver espaço disponível.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Ponteiro para o número atual de itens na mochila.
 */
void cadastrarComponente(Componente mochila[], int *numItens) {
    if (*numItens >= MAX_COMPONENTES) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Componente novo;

    printf("\n=== Cadastro de Novo Componente ===\n");
    printf("Nome do componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do componente: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);
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
void removerItem(Componente mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n=== Remover Componente ===\n");
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
void mostrarComponentes(const Componente mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum componente para listar.\n");
        return;
    }

    printf("\n=== Componentes na Mochila ===\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Prioridade");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d\n", 
            mochila[i].nome, 
            mochila[i].tipo, 
            mochila[i].prioridade);
    }
    printf("--------------------------------------------------------\n");
}


/**
 * @brief Ordena os itens na mochila do jogador por nome usando o algoritmo Bubble Sort.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
long bubbleSortNome(Componente mochila[], int numItens) {
    if (numItens < 2) {
        printf("Mochila com poucos itens! Nao e necessario ordenar.\n");
        return 0;
    }

    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    printf("\nOrdenado por Nome (Bubble Sort).\nComparacoes: %ld\nTempo: %.6f segundos\n",
           comparacoes, ((double)(fim - inicio) / CLOCKS_PER_SEC));
    return comparacoes;
}


/**
 * @brief Ordena os itens na mochila do jogador por tipo usando o algoritmo Insertion Sort.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
long insertionSortTipo(Componente mochila[], int numItens) {
    if (numItens < 2) {
        printf("Mochila com poucos itens! Nao e necessario ordenar.\n");
        return 0;
    }

    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < numItens; i++) {
        Componente chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    clock_t fim = clock();
    printf("\nOrdenado por Tipo (Insertion Sort).\nComparacoes: %ld\nTempo: %.6f segundos\n",
           comparacoes, ((double)(fim - inicio) / CLOCKS_PER_SEC));
    return comparacoes;
}


/**
 * @brief Ordena os itens na mochila do jogador por prioridade usando o algoritmo Selection Sort.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 */
long selectionSortPrioridade(Componente mochila[], int numItens) {
    if (numItens < 2) {
        printf("Mochila com poucos itens! Nao e necessario ordenar.\n");
        return 0;
    }

    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < numItens - 1; i++) {
        int indiceMinimo = i;
        for (int j = i + 1; j < numItens; j++) {
            comparacoes++;
            if (mochila[j].prioridade < mochila[indiceMinimo].prioridade) {
                indiceMinimo = j;
            }
        }
        if (indiceMinimo != i) {
            Componente temp = mochila[i];
            mochila[i] = mochila[indiceMinimo];
            mochila[indiceMinimo] = temp;
        }
    }

    clock_t fim = clock();
    printf("\nOrdenado por Prioridade (Selection Sort).\nComparacoes: %ld\nTempo: %.6f segundos\n",
           comparacoes, ((double)(fim - inicio) / CLOCKS_PER_SEC));
    return comparacoes;
}


/**
 * @brief Exibe o menu de ordenação e permite ao jogador escolher o critério.
 * @param mochila Vetor de itens na mochila.
 * @param numItens Número atual de itens na mochila.
 * @param ordenadaPorNome Ponteiro para indicar se a mochila está ordenada por nome.
 */
void menuDeOrdenacao(Componente mochila[], int numItens, bool *ordenadaPorNome) {
    int escolha;
    printf("\n=== Menu de Ordenacao ===\n");
    printf("1. Ordenar por Nome (Bubble Sort)\n");
    printf("2. Ordenar por Tipo (Insertion Sort)\n");
    printf("3. Ordenar por Prioridade (Selection Sort)\n");
    printf("Escolha o criterio de ordenacao: ");
    scanf("%d", &escolha);
    limparBufferEntrada();

    switch ((CriterioOrdenacao)escolha) {
        case ORDENAR_NOME:
            bubbleSortNome(mochila, numItens);
            *ordenadaPorNome = true;
            break;
        case ORDENAR_TIPO:
            insertionSortTipo(mochila, numItens);
            *ordenadaPorNome = false;
            break;
        case ORDENAR_PRIORIDADE:
            selectionSortPrioridade(mochila, numItens);
            *ordenadaPorNome = false;
            break;
        default:
            printf("Criterio invalido! Nenhuma ordenacao realizada.\n");
    }
}


/**
 * @brief Realiza busca binária por nome na mochila do jogador.
 * @param mochila Vetor de itens na mochila (deve estar ordenado por nome).
 * @param numItens Número atual de itens na mochila.
 */
void buscaBinariaPorNome(const Componente mochila[], int numItens, bool ordenadaPorNome) {
    if (numItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    if (!ordenadaPorNome) {
        printf("Mochila nao esta ordenada por nome! A busca binaria nao pode ser realizada.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== Buscar Item por Nome ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int inicio = 0, fim = numItens - 1, comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;

        int resultadoComparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (resultadoComparacao == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
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

    printf("Componente nao encontrado na mochila. Comparacoes realizadas: %d\n", comparacoes);
}


// ============================================================================
//                    FUNÇÃO AUXILIAR
// ============================================================================

/**
 * @brief Exibe o menu principal da mochila e permite escolher operações.
 *
 * Opções do menu:
 * 1. Adicionar um item
 * 2. Remover um item
 * 3. Listar todos os itens
 * 4. Ordenar os itens por critério (nome, tipo, prioridade)
 * 5. Realizar busca binária por nome
 * 0. Sair
 *
 * @param listaOrdenadaPorNome Indica se a lista está ordenada por nome.
 */
void exibirMenu(bool listaOrdenadaPorNome) {
    printf("\n=== MENU DA MOCHILA ===\n");
    printf("Lista atualmente %s para busca binaria.\n\n",
           listaOrdenadaPorNome ? "ORDENADA por nome" : "NAO ordenada por nome");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Mostrar componentes\n");
    printf("4. Ordenar componentes\n");
    printf("5. Buscar item por nome (binaria)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}


/**
 * @brief Simula a limpeza da tela imprimindo várias linhas em branco.
 */
void limparTela() {
    for (int i = 0; i < 15; i++) {
        printf("\n");
    }
}


/**
 * @brief Limpa o buffer de entrada para evitar problemas com fgets após scanf.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
