#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

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
    BID *infos;

} Registro;


typedef struct no{

    int n;
    bool folha;
    Registro **regs;
    struct no **filho;

} arvB;

#endif