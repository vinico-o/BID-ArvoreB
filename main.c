#include "arvoreB.c"
#include "estruturas.h"
#include <stdio.h>
#include <locale.h>

int main ()
{
    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");

    printf("\nBEM VINDO AO BANCO DE DADOS DOS JOGADORES");
    printf("\nSISTEMA FEITO POR: CAUAN SIMOES, FELIPE ZANARDI, IGOR ROMERO E VINICIUS MARDEGAN");
    printf("\nSE NAO EXISTIR UMA ARVORE, ELA SERA CRIADA.");
    printf("\nSE A ARVORE JA EXISTIR, INFORME O MESMO INDICE T DELA!");

    printf("\nInforme o t: ");
    scanf("%d", &t);

    if (t < 2)
    {
        printf ("\nVALOR INVALIDO PARA T - encerrando programa");
        return 0;
    }

    int escolha;
    arvB *raiz = carregarOuCriarArvore();

    do
    {
        escolha = menu();

        switch (escolha)
        {
            int id_remover;
            char clube_buscado[30];
            char posicao_buscada[30];
            int id_buscado;
            int overall_buscado;
            Registro *novo;

            case 1:
                novo = criarJogador();
                raiz = insereArvoreB(raiz, novo);
                break;

            case 2:
                printf("Informe o id a ser removido: ");
                scanf("%d", &id_remover);
                fflush(stdin);
                raiz = remover(raiz, id_remover);
                break;

            case 3:
                imprimir_informacoes_basicas(raiz);
                break;

            case 4:
                printf ("\nInforme o id a ser buscado no banco de dados: ");
                scanf ("%d", &id_buscado);
                fflush(stdin);
                imprimir_jogador_por_id(raiz, id_buscado);
                break;

            case 5:
                imprimir_clubes();
                printf("Digite o nome do Clube desejado: ");
                scanf("%s", clube_buscado);
                fflush(stdin);
                imprimir_atletas_por_clube(raiz, clube_buscado, 0);
                break;

            case 6:
                imprimir_posicoes();
                printf("Digite a Posicao desejada: ");
                scanf("%s", posicao_buscada);
                fflush(stdin);
                imprimir_atletas_por_posicao(raiz, posicao_buscada, 0);
                break;

            case 7:
                printf("Digite o OVERALL minimo: ");
                scanf("%d", &overall_buscado);
                fflush(stdin);
                imprimir_acima_de_overall(raiz, overall_buscado, 0);
                break;

            case 10:
                printf("SAINDO DO SISTEMA");
                break;

            default:
                printf("VALOR INVALIDO, DIGITE OUTRO!");
                break;
        } 

    } while (escolha != 10);
    


    return 0;
}