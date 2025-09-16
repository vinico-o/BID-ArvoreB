#include "arvoreB.c"
#include "estruturas.h"
#include <stdio.h>
#include <locale.h>

int main ()
{
    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");

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
        printf ("\n1- INSERIR");
        printf ("\n2- REMOVER");
        printf ("\n3- IMPRIMIR ÁRVORE");
        printf ("\n4- BUSCAR");
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
                        printf ("Imprimindo informacoes do atleta:\n");
                        printf ("id: %d  ", arv->regs[i]->id);
                        printf ("cpf: %d  ", arv->regs[i]->cpf);
                        printf ("nome: %s  ", arv->regs[i]->nome);
                        printf ("esta lesionado? %d  ", arv->regs[i]->infos->isLesionado);
                        printf ("perna boa? %d  ", arv->regs[i]->infos->pernaBoa);
                        printf ("finta? %d  ", arv->regs[i]->infos->finta);
                        printf ("pace? %d  ", arv->regs[i]->infos->pace);
                        printf ("pas? %d  ", arv->regs[i]->infos->pas);
                        printf ("defesa? %d  ", arv->regs[i]->infos->defesa);
                        printf ("clube? %s  ", arv->regs[i]->infos->clube);
                        printf ("posicao? %s  ", arv->regs[i]->infos->posicao);
                        
                        printf (" |");
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