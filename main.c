#include "arvoreB.c"
#include "estruturas.h"
#include <stdio.h>
#include <locale.h>

int main ()
{
    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");

    printf ("\nBEM VINDO AO BANCO DE DADOS DOS JOGADORES");

    printf ("\nInforme o t: ");
    scanf ("%d", &t);

    if (t < 2)
    {
        printf ("\nVALOR INVALIDO PARA T - encerrando programa");
        return 0;
    }

    arvB *raiz = criarNoRaizInicial();


    int i;

    do
    {
        printf ("\n1- INSERIR ATLETA");
        printf ("\n2- REMOVER ATLETA");
        printf ("\n3- IMPRIMIR BANCO DE DADOS");
        printf ("\n4- BUSCAR ATLETA");
        printf ("\n5- SAIR\n");
        
        printf ("\nInforme sua opcao: ");
        scanf ("%d", &i);

        switch (i)
        {
            int id_remover;
            int id_buscado;
            Registro *novo;
            case 1:{

                novo = criarJogador();

                raiz = insereArvoreB (raiz, novo);

                break;
            }
            case 2:
                printf ("\nInforme o id a ser removido do banco de dados: ");
                scanf ("%d", &id_remover);

                raiz = remover(raiz, id_remover);
            break;

            case 3:
                imprimir_informacoes_basicas (raiz);
            break;

            case 4:
                printf ("\nInforme o id a ser buscado no banco de dados: ");
                scanf ("%d", &id_buscado);

                arvB *arv = buscarArv(raiz, id_buscado);

                if (arv != NULL)
                {
                    int i = 0;

                    while (i < arv->n && arv->regs[i]->id != id_buscado)
                    {
                        i++;
                    }

                    if (arv->regs[i] != NULL)
                    {
                        printf("\n--- Informações do Atleta ---\n");
                        printf("ID: %d\n", arv->regs[i]->id);
                        printf("CPF: %d\n", arv->regs[i]->cpf);
                        printf("Nome: %s\n", arv->regs[i]->nome);
                        printf("Lesionado: %s\n", arv->regs[i]->infos->isLesionado ? "Sim" : "Não");
                        printf("Perna Boa: %s\n", arv->regs[i]->infos->pernaBoa ? "Esquerda" : "Direita");
                        printf("Finta: %d\n", arv->regs[i]->infos->finta);
                        printf("Ritmo: %d\n", arv->regs[i]->infos->pace);
                        printf("Passe: %d\n", arv->regs[i]->infos->pas);
                        printf("Fisico: %d\n", arv->regs[i]->infos->fisico);
                        printf("Finalizacao: %d\n", arv->regs[i]->infos->finalizacao);
                        printf ("Overral: %d\n", (arv->regs[i]->infos->finta + arv->regs[i]->infos->pace + arv->regs[i]->infos->pas +
                                                         arv->regs[i]->infos->fisico + arv->regs[i]->infos->finalizacao) / 5);
                        printf("Defesa: %d\n", arv->regs[i]->infos->defesa);
                        printf("Clube: %s\n", arv->regs[i]->infos->clube);
                        printf("Posição: %s\n", arv->regs[i]->infos->posicao);
                        printf("-----------------------------\n");
                        
                        printf ("\n");
                    }
                
                }
                else
                {
                    printf ("\nAtleta nao encontrado");
                }

            break;

            case 5:
                printf ("\nSAINDO DO BANCO DE DADOS");
                return 0;
            break;

            default:
                printf ("\nEscolha outra opcao");
            break;
        }


    } while (i != 5);
    


    return 0;
}