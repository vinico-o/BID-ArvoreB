#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int t;
int id = 1;

/* 

implementar:

    inserção aleatória
    buscas diversificadas (p/ clube, p/ posicao, overall)
    inserção em arquivo binário
    
*/





typedef struct {

    bool isLesionado;   // está lesionado? (false - não lesionado | true - lesionado)
    int pernaBoa;       // indica qual perna é a favorita (0 - esquerda | 1 - direita)
    float finta;        // nota da finta        (0 a 99)
    float pace;         // nota do pace/ritmo   (0 a 99)
    float pas;          // nota do passe        (0 a 99)
    float defesa;       // nota da defesa        (0 a 99)
    float fisico;       // nota do fisico        (0 a 99)
    char clube[50];     // nome do clube        
    char posicao[50];   // nome da posicao      

}BID;

typedef struct {

    int id;
    int cpf;
    char nome[50];
    struct BID *infos;

} Registro;


typedef struct no{

    int n;
    bool folha;
    Registro **regs;
    struct no **filho;

} arvB;

arvB* criarNoRaizInicial()
{
    arvB *novoNo = malloc(sizeof(arvB));

    novoNo->regs = malloc((2*t-1) * sizeof(Registro*));
    novoNo->filho = malloc((2*t) * sizeof(arvB*));

    novoNo->n = 0;
    novoNo->folha = true;


    for (int i = 0; i < 2*t - 1; i++)
    {
        novoNo->regs[i] = NULL;
    }

    for (int i = 0; i < 2*t; i++)
    {
        novoNo->filho[i] = NULL;
    }


    return novoNo;
}


arvB* buscarArv (arvB *r, int k)
{
    int i = 0;

    while (i < r->n && k > r->regs[i]->id)
    {
        i++;
    }

    
    if (i < r->n && k == r->regs[i]->id)
    {
        printf ("\nRegistro encontrado! Informacoes do registro:");
        printf ("\n[ ");
        printf ("id: %d  ", r->regs[i]->id);
        printf ("cpf: %d  ", r->regs[i]->cpf);
        printf ("nome: %s ]", r->regs[i]->nome);

        printf ("\n");
        return r;
    }

    if (r->folha == true)
    {
        printf ("\nRegistro nao encontrado!");
        return NULL;
    }

    else
    {
        return buscarArv (r->filho[i], k);
    }
}



void splitChildArvoreB (arvB *x, int i) // função de split -> recebe o nó pai e o índice do filho que será dividido
{
    // novo nó
    arvB *z = criarNoRaizInicial();

    // ponteiro ao filho que sofrerá split
    arvB *y = x->filho[i];

    // como as chaves e os filhos serão divididos entre os dois nós, eles são "iguais" no quesito folha ou árvore
    // logo recebem o mesmo "estado"
    z->folha = y->folha;

    // o novo nó terá metade das chaves de y, pois eles serão divididos 
    z->n = t - 1;

    // passando os ultimos t-1 chaves ao novo nó (z)
    for (int j = 0; j < t - 1; j++)
    {
        z->regs[j] = y->regs[j + t]; 
    }

    // se o nó cheio tem filhos, é necessário passar esses filhos ao novo nó (z)
    if (y->folha == false)
    {
        // como tem b+1 filhos, passam-se os ultimos t filhos 
        for (int j = 0; j < t; j++)
        {
            z->filho[j] = y->filho[j + t];
        }
    }

    // ajusta a quantidade de chaves no nó que anteriormente estava cheio para t-1 (metade) 
    y->n = t-1;

    // passa os filhos a direita de i para a direta
    for (int j = x->n; j >= i + 1; j--)
    {
        x->filho[j+1] = x->filho[j];
    }

    // insere o novo filho na posição a direita de i, ou seja, i + 1
    x->filho[i+1] = z;

    // abrindo espaço para a mediana do y (quando estava cheio!)
    for (int j = x->n; j >= i; j--)
    {
        x->regs[j+1] = x->regs[j];    
    }
    
    // inserindo a mediana e atualizando o valor de n
    x->regs[i] = y->regs[t-1];
    x->n++;

}

void insereNaoCheioArvoreB(arvB *x, Registro *k)
{
    // contador
    int i = x->n - 1;

    
    // se o nó for folha -> pode inserir direto
    if (x->folha == true)
    {
        // loop para que os valores maiores que o k "pulem" para direita no vetor -> ordenação
        while (i >= 0 && k->id < x->regs[i]->id)
        {
            x->regs[i+1] = x->regs[i];
            i--;
        }

        // inserção
        x->regs[i+1] = k;

        // indicando que há mais um número
        x->n++;

        // escrevendo no disco

    }
    
    // se o nó não é folha -> busca o filho
    else {
        
        // encontrando a posição que o número deveria ser inserido se fosse folha 
        // ou seja, estamos procurando o filho que receberá k
        while (i >= 0 && k->id < x->regs[i]->id)
        {
            i--;
        }

        // ajuste
        i++;


        // verifica se o nó filho está cheio
        if (x->filho[i]->n == 2*t - 1)
        {
            // se estiver, faz o split na posição i
            splitChildArvoreB(x, i);

            // verifica se o número k é maior que o número que "subiu" com o split
            // se k for maior, faz o reajuste (i++) 
            if (k->id > x->regs[i]->id)
            {
                i++;
            }
        }

        // chama a função de inserção no nó filho
        // lembrando que: só pode inserir em nó folha!
        insereNaoCheioArvoreB(x->filho[i], k);

    }
}


arvB* insereArvoreB(arvB *r, Registro *k)  // função de inserir
{
    // se o nó estiver cheio, cria-se um novo nó (não folha, 0 chaves, primeiro filho como o nó anterior(que estava cheio) e insere o k no novo nó)
    if (r->n == 2*t - 1)          
    {
        arvB *s = criarNoRaizInicial();
        s->folha = false;
        s->filho[0] = r;
        splitChildArvoreB(s, 0);
        insereNaoCheioArvoreB(s, k);

        return s;   // manter a raiz atualizada
    }
    // se não estiver cheio, insere normalmente
    else {
        insereNaoCheioArvoreB(r, k);

        return r;   // manter a raiz atualizada
    }
}




void imprimir_arvore(arvB *arv, int nivel)
{
    if (arv != NULL)
    {
        printf ("\nnivel - %d  ", nivel);
        printf ("n = %d   ", arv->n);
        printf ("\n");
        for (int i = 0; i < arv->n; i++)
        {
            printf ("| ");
            printf ("id: %d   ", arv->regs[i]->id);
            printf ("cpf: %d   ", arv->regs[i]->cpf);
            printf ("nome: %s   ", arv->regs[i]->nome);
            printf (" |");

            printf ("\n");
        }

        if (arv->folha == false)
        {
            for (int i = 0; i < arv->n + 1; i++)
            {
                if (arv->filho[i] != NULL)
                {
                    imprimir_arvore(arv->filho[i], nivel + 1);
                }
            }
        }
    }

}

void imprimir(arvB *raiz)
{
    printf ("\n\n\nIMPRIMINDO ARVORE-B\n");

    imprimir_arvore(raiz, 0);
}


void mergeChildArvoreB (arvB *x, int i) // função merge
{
    // ponteiros aos filhos
    arvB *y = x->filho[i];
    arvB *z = x->filho[i+1];

    // desce a mediana (entre os filhos) do pai
    y->regs[y->n] = x->regs[i];

    y->n++;

    // passando as chaves
    for (int j = 0; j < z->n; j++)
    {
        y->regs[t + j] = z->regs[j];
    }

    // se y não é folha (z tbm não é) -> passa os filhos
    if (y->folha == false)
    {
        for (int j = 0; j < z->n+1; j++)
        {
            y->filho[t + j] = z->filho[j];
        }
    }

    y->n += z->n;
        
    // y se juntou ao z 

    // falta ajustar o nó pai em relação ao número que desceu!

    x->n--;

    // removendo a mediana(número entre os filhos que sofreram merge) do pai (já que ela desceu)
    for (int j = i; j < x->n; j++)
    {
        x->regs[j] = x->regs[j+1];
    }

    // ajustando os filhos
    for (int j = i + 1; j < x->n + 1; j++)
    {
        x->filho[j] = x->filho[j+1];
    }

    free (z);
    x->filho[x->n + 1] = NULL;


}

// implementando a remoção de um número K
// caso 1: k no nó folha -> remoção direta -> mais simples -> reajuste e x->n-- 

// caso 2: t-1 -> mínimo de chaves no nó -> logo, para se retirar precisa ter no minimo t para substituição
// a - encontrar um predecessor na posição i de k -> k'
//      coloca o k' no lugar do k
//      remove o k' (original)

// b - encontrar um sucessor na posição i+1 de k -> k'
//      coloca k' no lugar do k
//      remove o k' (original)

// c - os dois nós estão com o mínimo (t - 1)
//      merge nos filhos (i, i+1)
//      remove o k

// caso 3: esse caso não remove apenas garante que os filhos tenham pelo menos t chaves 
// a - filho i tem t-1 chaves
//      passa a chave ao filho que tem só t-1 chaves
//      passa ao pai (x) um elemento do filho que tem pelo menos t chaves
//              -> se o filho for da direita: pega o menor
//              -> se o filho for da esquerda: pega o maior

// b - os dois filhos tem apenas t-1 chaves
//      merge nos filhos
//      insere o elemento do pai no nó filho tbm


void remover_rec (arvB *x, int k) // a remoção usará os casos acima + função merge
{
    int i = 0;

    if (x == NULL){
        printf ("\nELEMENTO NAO ENCONTRADO! - null");

        return;
    }

    while (i < x->n && k > x->regs[i]->id)
    {
        i++;
    }

    // caso 1 - nó folha + ACHOU O VALOR
    if (x->folha == true)
    {
        if (i < x->n && x->regs[i]->id == k)
        {

            for (int j = i; j < x->n - 1; j++)
            {
                x->regs[j] = x->regs[j+1];
            }

            x->n--;

            // escrever(x);

            printf ("\n\nELEMENTO REMOVIDO!!");
        }
        
        else 
        {
            printf ("\n\nELEMENTO NAO ENCONTRADO!!");
        }

        return;
    }

    // caso 2 - nó interno + ACHOU O VALOR

    else if (i < x->n && x->regs[i]->id == k)
    {

        // ponteiros
        arvB *y = x->filho[i];      // esquerda

        arvB *z = x->filho[i+1];    // direita

        // a - predecessor
        if (y != NULL && y->n >= t)                           // filho a esquerda tem mais que o minimo de chaves
        {
            Registro *predecessor;

            while (y->folha == false)
            {
                y = y->filho[y->n]; // tem que pegar o maior valor (entre os filhos) menor que K -> isso leva em considereção a todos os filhos
            }

            predecessor = y->regs[y->n - 1];

            x->regs[i] = predecessor;              // copiando o valor para o nó pai

            remover_rec(x->filho[i], predecessor->id);                // removendo o número original
        }

        // b - sucessor
        else if (z != NULL && z->n >= t)                      // o filho a direita tem mais que o minimo de chaves
        {

            Registro *sucessor;

            while (z->folha == false)
            {
                z = z->filho[0]; // tem que pegar o menor valor (entre os filhos) maior que K -> isso leva em consideração a todos os filhos
            }

            sucessor = z->regs[0];

            x->regs[i] = sucessor;               // copiando o valor

            remover_rec (x->filho[i+1], sucessor->id);     // removendo o número original
        }


        // c - merge
        else                                        // os dois estão com o mínimo de chaves (não é possível substituir)
        {
            mergeChildArvoreB(x, i);                // merge - junta os filhos

            remover_rec(y, k);                          // o k (desceu ao filho_merge) precisa ser removido
        }

        // escrever(x);
    }

    // caso 3 - nao achou o valor
    else
    {
        // ponteiros

        arvB *filhoAlvo = x->filho[i];
       
        arvB *irmaoEsq;

        if (i > 0){
            irmaoEsq = x->filho[i - 1];
        }
        else {
            irmaoEsq = NULL;
        }

        arvB *irmaoDir;

        if (i < x->n)
        {
            irmaoDir = x->filho[i + 1];
        }
        else 
        {
            irmaoDir = NULL;
        }
        

        // filhoAlvo - próximo nó a ser buscado k
        // filhoAlvo tem t-1 chaves (minimo) - para evitar mais merge, faremos trocas de valores entre os filhos a esquerda e direita dele!
        if (filhoAlvo->n == t - 1)
        {

            // caso a
            // irmaoEsquerda tem mais que o minimo (t-1)
            if (irmaoEsq != NULL && irmaoEsq->n >= t)
            {
                Registro *numero_que_vai_para_o_pai = irmaoEsq->regs[irmaoEsq->n - 1];

                Registro *numero_que_vai_para_o_filho_alvo = x->regs[i - 1];

                // colocando o valor no nó pai
                x->regs[i - 1] = numero_que_vai_para_o_pai;

                // abrindo espaço para o filhoAlvo
                for (int j = filhoAlvo->n; j > 0; j--)
                {
                    filhoAlvo->regs[j] = filhoAlvo->regs[j - 1]; 
                }

                // inserindo o pai->chave[i] no filhoAlvo
                filhoAlvo->regs[0] = numero_que_vai_para_o_filho_alvo;
            
                // se o filho da esquerda não for folha -> tem filhos -> precisa passar os filhos ao filhoAlvo
                if (irmaoEsq->folha == false)
                {
                    for (int j = filhoAlvo->n + 1; j > 0; j--)
                    {
                        filhoAlvo->filho[j] = filhoAlvo->filho[j - 1];
                    }

                    filhoAlvo->filho[0] = irmaoEsq->filho[irmaoEsq->n];                    
                }
            
                // ajustando n de cada nó
                irmaoEsq->n--;
                filhoAlvo->n++;


            }

            // caso b
            // irmaoDireita tem mais que o minimo (t-1)
            else if (irmaoDir != NULL && irmaoDir->n >= t)
            {
                Registro *numero_que_vai_para_o_pai = irmaoDir->regs[0];

                Registro *numero_que_vai_para_o_filho_alvo = x->regs[i];
                
                // colocando o valor no nó pai
                x->regs[i] = numero_que_vai_para_o_pai;

                // colocando o valor do pai no filhoAlvo
                filhoAlvo->regs[filhoAlvo->n] = numero_que_vai_para_o_filho_alvo;

                // se o filho da direita não for folha -> tem filhos -> precisa passar os filhos ao filhoAlvo
                if (irmaoDir->folha == false)
                {
                    filhoAlvo->filho[filhoAlvo->n + 1] = irmaoDir->filho[0];
                }


                // ajustando os valores do irmao da direita
                for (int j = 0; j < irmaoDir->n - 1; j++)
                {
                    irmaoDir->regs[j] = irmaoDir->regs[j + 1];
                }

                // ajustando os filhos do irmao da direita
                for (int j = 0; j < irmaoDir->n; j++)
                {
                    irmaoDir->filho[j] = irmaoDir->filho[j + 1];
                }


                // ajustando n de cada nó
                irmaoDir->n--;
                filhoAlvo->n++;
            }

            // c - os dois tem t-1 chaves -> merge
            else
            {
                
                // so para garantir que estamos mesclando vetores existentes
                if (i < x->n)
                {
                    mergeChildArvoreB(x, i);
                }

                // evita que faça merge entre: ultimo filho e um filho inexistente
                else {
                    mergeChildArvoreB (x, i-1);
                }
                

            }

        }


        remover_rec(filhoAlvo, k);
    }

}


// "nova função" - criada para atualizar a raiz
// as vezes o o nó raiz sofria merge e a raiz não se atualizava
arvB* remover(arvB *raiz, int k)
{
    remover_rec(raiz, k);

    if (raiz->n == 0) {
        
        if (raiz->folha == false) {
            arvB *novaRaiz = raiz->filho[0];
            free(raiz);
            raiz = novaRaiz;
        } 
        else {
            
            free(raiz);
            raiz = criarNoRaizInicial();
        }
    }

    return raiz;
}







int main ()
{
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
        printf ("\n3- IMPRIMIR");
        printf ("\n4- BUSCAR");
        printf ("\n5- SAIR\n");
        
        printf ("\nInforme sua opcao: ");
        scanf ("%d", &i);

        switch (i)
        {
            int cpf;
            char nome[50];
            int id_buscado;
            int id_remover;

            case 1:

                printf ("\nInforme o cpf: ");
                scanf ("%d", &cpf);

                getchar();

                printf ("\nInforme o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                Registro *novo = malloc(sizeof(Registro));
                novo->id = id;
                novo->cpf = cpf;
                strcpy(novo->nome, nome);

                id++;

                raiz = insereArvoreB (raiz, novo);
            break;

            case 2:
                printf ("\nInforme o id a ser removido do banco de dados: ");
                scanf ("%d", &id_remover);

                raiz = remover(raiz, id_remover);
            break;

            case 3:
                imprimir (raiz);
            break;

            case 4:
                printf ("\nInforme o id a ser buscado no banco de dados: ");
                scanf ("%d", &id_buscado);

                buscarArv(raiz, id_buscado);
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