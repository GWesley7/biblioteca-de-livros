#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// --- Definição da estrutura  (struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// --- Função para limpar buffer de entrada ---
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // --- Laço principal do Menu ---
    do {
        // Exibe o menu de opções.
        printf("==============================\n");
        printf("     BIBLIOTECA - PARTE 1     \n");
        printf("==============================\n");
        printf("1 - CADASTRAR NOVO LIVRO\n");
        printf("2 - LISTAR TODOS OS LIVROS\n");
        printf("0 - SAIR\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) { // valida leitura
            printf("Entrada invalida!\n");
            limparBuffer();
            opcao = -1;
        } else {
            limparBuffer(); // limpa '\n' deixado pelo scanf
        }

        // --- Processa a opção escolhida ---
        switch (opcao) {
            case 1: // CADASTRAR NOVO LIVRO
                printf("--- Cadastro de novo livro ---\n\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    if (fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin) == NULL)
                        biblioteca[totalLivros].nome[0] = '\0';
                    else
                        biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';

                    printf("Digite o autor do livro: ");
                    if (fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin) == NULL)
                        biblioteca[totalLivros].autor[0] = '\0';
                    else
                        biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';

                    printf("Digite a editora do livro: ");
                    if (fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin) == NULL)
                        biblioteca[totalLivros].editora[0] = '\0';
                    else
                        biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao do livro: ");
                    if (scanf("%d", &biblioteca[totalLivros].edicao) != 1) {
                        biblioteca[totalLivros].edicao = 0;
                        printf("Edição inválida, definida como 0.\n");
                    }
                    limparBuffer(); // limpa o '\n' após o scanf da edição

                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                }

                printf("\nPRESSIONE ENTER PARA CONTINUAR...");
                getchar(); // pausa
                break;

            case 2: // LISTAGEM DE LIVROS
                printf("--- Lista de todos os livros cadastrados ---\n\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado na biblioteca.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n\n", biblioteca[i].edicao);
                    }
                    printf("------------------------------\n");
                }

                printf("\nPRESSIONE ENTER PARA CONTINUAR...");
                getchar(); // pausa
                break;

            case 0: // SAIR
                printf("Saindo do programa. Até mais!\n");
                break;

            default: // OPÇÃO INVÁLIDA
                printf("Opcao invalida! Tente novamente.\n");
                printf("\nPRESSIONE ENTER PARA CONTINUAR...");
                getchar(); // pausa
                break;
        }

    } while (opcao != 0);

    return 0; // FIM DO PROGRAMA
}
