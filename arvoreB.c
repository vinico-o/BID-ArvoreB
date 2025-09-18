#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"

void liberarArvore(arvB *raiz)
{
    if (raiz != NULL) {
        // Libera a memória dos filhos primeiro
        if (raiz->folha == false) {
            for (int i = 0; i <= raiz->n; i++) {
                liberarArvore(raiz->filho[i]);
            }
            free(raiz->filho);
        }
        // Libera a memória dos registros e suas informações
        for(int i = 0; i < raiz->n; i++){
            free(raiz->regs[i]->infos);
            free(raiz->regs[i]);
        }
        free(raiz->regs);
        // Libera o nome do arquivo e o nó raiz
        free(raiz->name_arq);
        free(raiz);
    }
}
void aleatorizarInformacoes(Registro *r)
{
    int pos_clube = (rand() % 20);
    int pos_posicao = (rand() % 11);

    r->infos = malloc(sizeof(BID));

    r->cpf = rand() % 1000000;
    strcpy(r->infos->clube, timesSerieA[pos_clube]);
    strcpy(r->nome, titulares[pos_clube][pos_posicao]);

    r->infos->isLesionado = rand() % 2;
    r->infos->pernaBoa = rand() % 2;

    r->infos->finta = rand() % 70 + 30;
    r->infos->pace = rand() % 70 + 30;
    r->infos->pas = rand() % 70 + 30;
    r->infos->defesa = rand() % 70 + 30;
    r->infos->fisico = rand() % 70 + 30;
    r->infos->finalizacao = rand() % 70 + 30;
    r->infos->overall = (r->infos->finta + r->infos->pace + r->infos->pas + r->infos->fisico + r->infos->finalizacao) / 5;

    strcpy(r->infos->posicao, posicoes[pos_posicao]);
}

Registro* criarJogador()
{
    Registro *reg = malloc(sizeof(Registro));

    reg->id = id;
    id++;

    aleatorizarInformacoes(reg);
    printf("JOGADOR INSERIDO COM SUCESSO!");
    imprimir_jogador(reg);

    return reg;
}
char* GeraNomeArqBin() {
    char *name_bin = malloc(TAM_ARQ * sizeof(char));
    if (name_bin == NULL) {
        printf("Erro de alocação de memória para nome do arquivo.\n");
        exit(1);
    }
    for(int i=0; i<18; i++) {
        name_bin[i] = 'a' + (rand() % 26);
    }
    name_bin[18] = '\0';
    strcat(name_bin,".bin");
    return name_bin;
}
arvB* criarNoRaizInicial()
{
    arvB *novoNo = malloc(sizeof(arvB));

    novoNo->regs = malloc((2*t-1) * sizeof(Registro*));
    novoNo->filho = malloc((2*t) * sizeof(arvB*));
    novoNo->name_arq = GeraNomeArqBin();
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
    escreverBin(novoNo);
    return novoNo;
}
arvB* criarNoVazio(bool folha)
{
    arvB *novoNo = malloc(sizeof(arvB));
    novoNo->regs = malloc((2*t-1) * sizeof(Registro*));
    novoNo->filho = malloc((2*t) * sizeof(arvB*));
    novoNo->name_arq = GeraNomeArqBin(); // Gera nome único
    novoNo->n = 0;
    novoNo->folha = folha;
    for (int i = 0; i < 2*t; i++) {
        novoNo->filho[i] = NULL;
    }
    return novoNo;
}
void leituraBin(arvB* raiz) {
    FILE *arq = fopen(raiz->name_arq,"rb");
    if(!arq) {
        printf("Erro ao abrir arquivo %s!\n",raiz->name_arq);
        return;
    }
    fread(&raiz->n,sizeof(int),1,arq);
    fread(&raiz->folha,sizeof(bool),1,arq);
    
    // Aloca o tamanho máximo, não apenas raiz->n
    raiz->regs = (Registro**) malloc((2*t-1) * sizeof(Registro*));
    for(int i=0;i<raiz->n;i++) {
        raiz->regs[i] = malloc(sizeof(Registro));
        fread(raiz->regs[i], sizeof(Registro), 1, arq);
        raiz->regs[i]->infos = malloc(sizeof(BID));
        fread(raiz->regs[i]->infos, sizeof(BID), 1, arq);
    }
    
    if(raiz->folha==false) {
        raiz->filho = (arvB**) malloc((2*t) * sizeof(arvB*)); // capacidade total
        char nome_filho[TAM_ARQ];
        for(int i=0;i<=raiz->n;i++) {
            fread(nome_filho, sizeof(char), TAM_ARQ, arq);
            raiz->filho[i] = (arvB*) malloc(sizeof(arvB));
            raiz->filho[i]->name_arq = (char*) malloc(TAM_ARQ);
            strcpy(raiz->filho[i]->name_arq, nome_filho);
            leituraBin(raiz->filho[i]);
        }
        // inicializa filhos restantes como NULL
        for (int i=raiz->n+1;i<2*t;i++) raiz->filho[i] = NULL;
    } else {
        raiz->filho = (arvB**) malloc((2*t) * sizeof(arvB*));
        for (int i=0;i<2*t;i++) raiz->filho[i] = NULL;
    }
    fclose(arq);
}

void escreverBin(arvB* raiz)
{
    FILE *arq = fopen(raiz->name_arq,"wb");
    if(!arq) {
        printf("Erro ao abrir o arquivo %s!\n",raiz->name_arq);
        return;
    }
    fwrite(&raiz->n,sizeof(int),1,arq);
    fwrite(&raiz->folha,sizeof(bool),1,arq);
    for(int i=0;i<raiz->n;i++) {
        fwrite(raiz->regs[i], sizeof(Registro), 1, arq);
        fwrite(raiz->regs[i]->infos, sizeof(BID), 1, arq);
    }
    if (raiz->folha == false) {
        for(int i=0;i<=raiz->n;i++) {
            fwrite(raiz->filho[i]->name_arq, sizeof(char), TAM_ARQ, arq);
        }
        for(int i=0;i<=raiz->n;i++) {
            escreverBin(raiz->filho[i]);
        }
    }
    fclose(arq);
}

void salvarNomeNovaRaiz(arvB *raiz) {
    char caminho_completo[] = "meta_raiz.txt";
    FILE *arq = fopen(caminho_completo, "w");
    if (arq != NULL) {
        fprintf(arq, "%s", raiz->name_arq);
        fclose(arq);
    }
}

bool arquivoExiste(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "rb");
    if (arq) {
        fclose(arq);
        return true;
    }
    return false;
}

arvB* carregarOuCriarArvore() {
    char caminho_completo_meta[] = "meta_raiz.txt";
    char nome_do_arquivo_raiz[TAM_NOME_ARQUIVO];
    FILE *meta_arq = fopen(caminho_completo_meta, "r");
    if (meta_arq != NULL) {
        fscanf(meta_arq, "%s", nome_do_arquivo_raiz);
        fclose(meta_arq);
        printf("\nCarregando arvore a partir de %s...\n", nome_do_arquivo_raiz);
        arvB *raiz = malloc(sizeof(arvB));
        raiz->name_arq = (char*) malloc(strlen(nome_do_arquivo_raiz) + 1);
        strcpy(raiz->name_arq, nome_do_arquivo_raiz);
        leituraBin(raiz);
        
        // ajusta o ID global pra evitar duplicatas
        id = encontrarMaiorID(raiz) + 1;
        
        return raiz;
    } else {
        printf("\nCriando nova arvore...\n");
        arvB *raiz = criarNoRaizInicial();
        salvarNomeNovaRaiz(raiz);
        return raiz;
    }
}

int encontrarMaiorID(arvB *raiz) {
    if (raiz == NULL) return 0;
    
    int maiorID = 0;
    
    // percorre todos os registros do nó atual
    for (int i = 0; i < raiz->n; i++) {
        if (raiz->regs[i]->id > maiorID) {
            maiorID = raiz->regs[i]->id;
        }
    }
    
    // se não é folha, verifica os filhos
    if (!raiz->folha) {
        for (int i = 0; i <= raiz->n; i++) {
            if (raiz->filho[i] != NULL) {
                int idFilho = encontrarMaiorID(raiz->filho[i]);
                if (idFilho > maiorID) {
                    maiorID = idFilho;
                }
            }
        }
    }
    
    return maiorID;
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
    arvB *z = criarNoVazio(true);

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
    escreverBin(y);
    escreverBin(z);
    escreverBin(x);
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
        escreverBin(x);
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
        leituraBin(x->filho[i]);

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
        arvB *s = criarNoVazio(false);
        s->folha = false;
        s->filho[0] = r;
        splitChildArvoreB(s, 0);
        insereNaoCheioArvoreB(s, k);
        salvarNomeNovaRaiz(s);
        return s;   // manter a raiz atualizada
    }
    // se não estiver cheio, insere normalmente
    else {
        insereNaoCheioArvoreB(r, k);

        return r;   // manter a raiz atualizada
    }
}

void imprimir_no_recursivo(arvB *no, int nivel)
{
    if (no == NULL)
    {
        return;
    }

    for (int i = 0; i < nivel; i++)
    {
        printf("    "); //espacos por nivel
    }

    printf("[");
    for (int i = 0; i < no->n; i++)
    {
        printf("id: %d nome: %s", no->regs[i]->id, no->regs[i]->nome);
        if (i < no->n - 1)
        {
            printf(" | ");
        }
    }
    printf("]\n");

    for (int i = 0; i < no->n + 1; i++)
    {
        imprimir_no_recursivo(no->filho[i], nivel + 1);
    }
}

void imprimir_informacoes_basicas(arvB *raiz)
{
    if (raiz == NULL)
    {
        printf("A arvore está vazia.\n");
        return;
    }
    printf("\n--- JOGADORES REGISTRADOS ---\n");
    imprimir_no_recursivo(raiz, 0);
    printf("\n\n");
}

void imprimir_acima_de_overall(arvB *raiz, int overall, int nivel)
{
    if (raiz == NULL)
    {
        return;
    }

    for (int i = 0; i < nivel; i++)
    {
        printf("    "); // indentação por nível
    }

    printf("[");
    int encontrado = 0; // para controlar se algum atleta foi exibido
    for (int i = 0; i < raiz->n; i++)
    {
        if (raiz->regs[i]->infos->overall >= overall)
        {
            if (encontrado)
                printf(" | ");
            printf("id: %d nome: %s", raiz->regs[i]->id, raiz->regs[i]->nome);
            encontrado = 1;
        }
    }
    printf("]\n");

    for (int i = 0; i < raiz->n + 1; i++)
    {
        imprimir_acima_de_overall(raiz->filho[i], overall, nivel + 1);
    }
}

void imprimir_atletas_por_posicao(arvB* raiz, char posicao[], int nivel)
{
    if (raiz == NULL)
    {
        return;
    }

    for (int i = 0; i < nivel; i++)
    {
        printf("    "); // indentação por nível
    }

    printf("[");
    int encontrado = 0; // para controlar se algum atleta foi exibido
    for (int i = 0; i < raiz->n; i++)
    {
        if (strcmp(raiz->regs[i]->infos->posicao, posicao) == 0)
        {
            if (encontrado)
                printf(" | ");
            printf("id: %d nome: %s", raiz->regs[i]->id, raiz->regs[i]->nome);
            encontrado = 1;
        }
    }
    printf("]\n");

    for (int i = 0; i < raiz->n + 1; i++)
    {
        imprimir_atletas_por_posicao(raiz->filho[i], posicao, nivel + 1);
    }
}

void imprimir_atletas_por_clube(arvB *raiz, char clube[], int nivel)
{
    if (raiz == NULL)
    {
        return;
    }

    for (int i = 0; i < nivel; i++)
    {
        printf("    "); // indentação por nível
    }

    printf("[");
    int encontrado = 0;
    for (int i = 0; i < raiz->n; i++)
    {
        if (strcmp(raiz->regs[i]->infos->clube, clube) == 0)
        {
            if (encontrado)
                printf(" | ");
            printf("id: %d nome: %s", raiz->regs[i]->id, raiz->regs[i]->nome);
            encontrado = 1;
        }
    }
    printf("]\n");

    for (int i = 0; i < raiz->n + 1; i++)
    {
        imprimir_atletas_por_clube(raiz->filho[i], clube, nivel + 1);
    }
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

    liberarArvore(z);
    x->filho[x->n + 1] = NULL;
    escreverBin(y);
    escreverBin(x);

}

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
            free(x->regs[i]->infos);
            free(x->regs[i]);
            for (int j = i; j < x->n - 1; j++)
            {
                x->regs[j] = x->regs[j+1];
            }

            x->n--;
            escreverBin(x);
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
            free(x->regs[i]->infos);
            free(x->regs[i]);
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
            free(x->regs[i]->infos);
            free(x->regs[i]);
            x->regs[i] = sucessor;               // copiando o valor

            remover_rec (x->filho[i+1], sucessor->id);     // removendo o número original
        }


        // c - merge
        else                                        // os dois estão com o mínimo de chaves (não é possível substituir)
        {
            mergeChildArvoreB(x, i);                // merge - junta os filhos

            remover_rec(y, k);                          // o k (desceu ao filho_merge) precisa ser removido
        }
        escreverBin(x);
        
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
            free(raiz->filho);
            free(raiz->regs);
            free(raiz);
            raiz = novaRaiz;
        } 
        else {
            free(raiz->filho);
            free(raiz->regs);            
            free(raiz);
            raiz = criarNoVazio(true);
        }
    }

    return raiz;
}

int menu()
{
    int i;

    printf ("\n1- INSERIR ATLETA");
    printf ("\n2- REMOVER ATLETA");
    printf ("\n3- IMPRIMIR BANCO DE DADOS");
    printf ("\n4- FICHA TECNICA DO ATLETA");
    printf ("\n5- IMPRIMIR ATLETAS POR CLUBE");
    printf ("\n6- IMPRIMIR ATLETAS POR POSICAO");
    printf ("\n7- IMPRIMIR ATLETAS ACIMA DE X OVERALL");
    printf ("\n10- SAIR\n");
    
    printf ("\nInforme sua opcao: ");
    scanf ("%d", &i);

    return i;
}

void imprimir_jogador_por_id(arvB* raiz, int id_buscado)
{
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
                        imprimir_jogador(arv->regs[i]);
                    }
                
                }
                else
                {
                    printf ("\nAtleta nao encontrado");
                }
}

void imprimir_jogador(Registro* regs)
{
    printf("\n+---------------------------------------+\n");
    printf("|          INFORMACOES DO ATLETA        |\n");
    printf("+---------------------------------------+\n");
    printf("| %-12s | %-22d |\n", "ID", regs->id);
    printf("| %-12s | %-22d |\n", "CPF", regs->cpf);
    printf("| %-12s | %-22s |\n", "Nome", regs->nome);
    printf("| %-12s | %-22s |\n", "Clube", regs->infos->clube);
    printf("| %-12s | %-22s |\n", "Posicao", regs->infos->posicao);
    printf("+---------------------------------------+\n");
    printf("|             STATUS FISICO             |\n");
    printf("+---------------------------------------+\n");
    printf("| %-12s | %-22s |\n", "Lesionado", regs->infos->isLesionado ? "Sim" : "Nao");
    printf("| %-12s | %-22s |\n", "Perna Boa", regs->infos->pernaBoa ? "Esquerda" : "Direita");
    printf("+---------------------------------------+\n");
    printf("|              ATRIBUTOS                |\n");
    printf("+------------------+--------------------+\n");
    printf("| %-12s | %-3d %-16s   |\n", "Ritmo", regs->infos->pace, "");
    printf("| %-12s | %-3d %-16s   |\n", "Finalizacao", regs->infos->finalizacao, "");
    printf("| %-12s | %-3d %-16s   |\n", "Passe", regs->infos->pas, "");
    printf("| %-12s | %-3d %-16s   |\n", "Finta", regs->infos->finta, "");
    printf("| %-12s | %-3d %-16s   |\n", "Defesa", regs->infos->defesa, "");
    printf("| %-12s | %-3d %-16s   |\n", "Fisico", regs->infos->fisico, "");
    printf("+------------------+--------------------+\n");
    printf("| %-12s | %-22d |\n", "OVERALL", regs->infos->overall);
    printf("+---------------------------------------+\n\n");
    
    printf ("\n");
}

void imprimir_clubes()
{
    printf("\n--- Times do Brasileirao Serie A ---\n\n");

    for (int i = 0; i < 20; i += 2)
    {
        printf("%-20s    %-20s\n", timesSerieA[i], timesSerieA[i + 1]);
    }

    printf("\n");
}

void imprimir_posicoes()
{
    printf("\n--- Posicoes dos Jogadores ---\n\n");

    printf("Goleiro             Lateral Direito\n");
    printf("Zagueiro            Lateral Esquerdo\n");
    printf("Volante             Meia\n");
    printf("Atacante            Centroavante\n");

    printf("\n");
}