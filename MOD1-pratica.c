#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes globais ---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// --- Definição da estrutura (struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para sim, 0 para não
};

// Nova struct para armazenar informações do empréstimo
struct Emprestimo {
    int indiceLivro; // índice do livro no array 'biblioteca'
    char nomeUsuario[TAM_STRING];
}; // <- ponto-e-vírgula obrigatório

// --- Função para limpar buffer de entrada ---
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = calloc(MAX_LIVROS, sizeof(struct Livro));
    emprestimos = malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memória\n");
        free(biblioteca);
        free(emprestimos);
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("==================================================\n");
        printf("      BIBLIOTECA - PARTE 2\n");
        printf("==================================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar empréstimo\n");
        printf("4 - Listar empréstimos\n");
        printf("0 - Sair\n");
        printf("==================================================\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Saindo.\n");
            break;
        }
        limparBuffer(); // Limpa o buffer após a leitura do inteiro

        switch (opcao) {
            case 1: // CADASTRAR LIVRO
                printf("--- Cadastro de Novo Livro ---\n");
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    if (fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin) == NULL) {
                        printf("Erro ao ler nome.\n");
                        break;
                    }

                    printf("Digite o autor: ");
                    if (fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin) == NULL) {
                        printf("Erro ao ler autor.\n");
                        break;
                    }

                    printf("Digite a editora: ");
                    if (fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin) == NULL) {
                        printf("Erro ao ler editora.\n");
                        break;
                    }

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0;
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

                    printf("Digite a edição: ");
                    if (scanf("%d", &biblioteca[totalLivros].edicao) != 1) {
                        printf("Edição inválida.\n");
                        limparBuffer();
                        break;
                    }
                    limparBuffer();

                    biblioteca[totalLivros].disponivel = 1;
                    totalLivros++;
                    printf("Livro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2: // LISTAR LIVROS
                printf("--- Lista de Livros Cadastrados ---\n\n");
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("-----------------------------------\n");
                        printf("Livro %d:\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponível" : "Emprestado");
                    }
                    printf("-----------------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 3: // REALIZAR EMPRÉSTIMO
                printf("--- Realizar Empréstimo ---\n\n");
                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de empréstimos atingido!\n");
                } else {
                    printf("Livros disponíveis para empréstimo:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponível para empréstimo.\n");
                    } else {
                        printf("Digite o número do livro que deseja emprestar: ");
                        int numLivro;
                        if (scanf("%d", &numLivro) != 1) {
                            printf("Entrada inválida.\n");
                            limparBuffer();
                        } else {
                            limparBuffer();
                            int indice = numLivro - 1;
                            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                                printf("Digite o nome do usuário que está pegando o livro: ");
                                if (fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin) == NULL) {
                                    printf("Erro ao ler nome do usuário.\n");
                                } else {
                                    emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = 0;
                                    emprestimos[totalEmprestimos].indiceLivro = indice;
                                    biblioteca[indice].disponivel = 0;
                                    totalEmprestimos++;
                                    printf("Empréstimo realizado com sucesso!\n");
                                }
                            } else {
                                printf("Opção inválida ou livro indisponível.\n");
                            }
                        }
                    }
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 4: // LISTAR EMPRÉSTIMOS
                printf("--- Lista de Empréstimos ---\n\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum empréstimo realizado ainda.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("-----------------------------------\n");
                        printf("Empréstimo %d:\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuário: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("-----------------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    free(biblioteca);
    free(emprestimos);

    printf("Memória liberada com sucesso.\n");
    return 0;
}
