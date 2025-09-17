#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#include <stdbool.h>
#define TAM_ARQ 33
#define TAM_NOME_ARQUIVO 256
int t;
int id = 1;
/* 

implementar:

    inserção aleatória
    buscas diversificadas (p/ clube, p/ posicao, overall)
    inserção em arquivo binário
    
*/

char *timesSerieA[20] = {
    "Atlético Mineiro",
    "Bahia",
    "Botafogo",
    "Ceará",
    "Corinthians",
    "Cruzeiro",
    "Flamengo",
    "Fluminense",
    "Fortaleza",
    "Grêmio",
    "Internacional",
    "Juventude",
    "Mirassol",
    "Palmeiras",
    "RB Bragantino",
    "Santos",
    "São Paulo",
    "Sport Recife",
    "Vasco da Gama",
    "Vitória"
};

char *titulares[20][11] = {
        // Atlético-MG
        {"Everson", "Natanael", "Rabello", "Vitor Hugo", "Rubens", "Alan Franco", "Patrick", "Scarpa", "Rony", "Igor Gomes", "Hulk"},
        // Bahia
        {"Ronaldo", "Gilberto", "David Duarte", "Ramos Mingo", "Luciano Juba", "Nicolás Acevedo", "Rodrigo Nestor", "Everton Ribeiro", "Kayky", "Cauly", "Willian José"},
        // Botafogo
        {"John", "Vitinho", "Bastos", "Alexander Barbosa", "Marçal", "Gregore", "Marlon Freitas", "Eduardo", "Savarino", "Júnior Santos", "Tiquinho Soares"},
        // Ceará
        {"Richard", "Raí Ramos", "Matheus Felipe", "Ramon Menezes", "Matheus Bahia", "Richardson", "Lourenço", "Guilherme Castilho", "Aylon", "Erick Pulga", "Facundo Barceló"},
        // Corinthians
        {"Hugo Souza", "Matheuzinho", "Gustavo Henrique", "André Ramalho", "Angileri", "Matheus Bidu", "Ryan", "Maycon", "Vitinho", "Kayke", "Gui Negão"},
        // Cruzeiro
        {"Cássio", "Jonathan Jesus", "Fabrício Bruno", "Lucas Villalba", "Kauã Prates", "Walace", "Lucas Silva", "Eduardo", "Matheus Pereira", "Wanderson", "Kaio Jorge"},
        // Flamengo
        {"Rossi", "Wesley", "Léo Ortiz", "Danilo", "Varela", "Pulgar", "De la Cruz", "Arrascaeta", "Gerson", "Plata", "Bruno Henrique"},
        // Fluminense
        {"Fábio", "Guga", "Freytes", "Thiago Silva", "Renê", "Hércules", "Martinelli", "Nonato", "Canobbio", "Serna", "Everaldo"},
        // Fortaleza
        {"João Ricardo", "Tinga", "Brítez", "Cardona", "Bruno Pacheco", "Pol Fernández", "Zé Welison", "Calebe", "Breno Lopes", "Pikachu", "Lucero"},
        // Grêmio
        {"Tiago Volpi", "Gustavo Martins", "Noriega", "Kannemann", "Marlon", "Cuéllar", "Dodi", "Arthur", "Alysson", "Cristian Olivera", "Braithwaite"},
        // Internacional
        {"Anthoni", "Aguirre", "Vitão", "Victor Gabriel", "Bernabei", "Fernando", "Bruno Henrique", "Alan Patrick", "Wanderson", "Lucca", "Enner Valencia"},
        // Juventude
        {"Jandrei", "Reginaldo", "Abner", "Wilker Ángel", "Marcelo Hermes", "Caíque", "Jadson", "Luis Mandaca", "Gabriel Veron", "Gabriel Taliari", "Ênio"},
        // Mirassol
        {"Walter", "Lucas Ramon", "João Victor", "Jemmes", "Reinaldo", "Neto Moura", "Danielzinho", "Yago Felipe", "Gabriel", "Negueba", "Edson Carioca"},
        // Palmeiras
        {"Weverton", "Mayke", "Gustavo Gómez", "Murilo", "Piquerez", "Aníbal Moreno", "Zé Rafael", "Raphael Veiga", "Dudu", "Endrick", "Rony"},
        // Red Bull Bragantino
        {"Cleiton", "Nathan Mendes", "Pedro Henrique", "Luan Cândido", "Juninho Capixaba", "Jadsom", "Eric Ramires", "Lucas Evangelista", "Helinho", "Eduardo Sasha", "Vitinho"},
        // Santos
        {"Gabriel Brazão", "Mayke", "Adonis Frías", "Luan Peres", "Escobar", "Tomás Rincón", "Zé Rafael", "Neymar", "Caballero", "Guilherme", "Tiquinho Soares"},
        // São Paulo
        {"Rafael", "Arboleda", "Alan Franco", "Sabino", "Igor Vinícius", "Luiz Gustavo", "Alisson", "Marcos Antônio", "Wendell", "Luciano", "Calleri"},
        // Sport
        {"Gabriel", "Matheus Alexandre", "Rafael Thyere", "Ramon", "Aderlan", "Christian Rivera", "Zé Lucas", "Lucas Lima", "Matheusinho", "Léo Pereira", "Derik"},
        // Vasco da Gama
        {"Léo Jardim", "Paulo Henrique", "João Victor", "Maurício Lemos", "Lucas Piton", "Paulinho", "Hugo Moura", "Garré", "Coutinho", "Nulo Moreira", "Vegete"},
        // Vitória
        {"Lucas Arcanjo", "Claudinho", "Edu", "Wagner Leonardo", "Lucas Esteves", "Willian Oliveira", "Luan", "Matheuzinho", "Osvaldo", "Luiz Adriano", "Janderson"}
    };

char *posicoes[11] = {
    "Goleiro",
    "Lateral Direito",
    "Zagueiro",
    "Zagueiro",
    "Lateral Esquerdo",
    "Volante",
    "Meia",
    "Meia",
    "Atacante",
    "Atacante",
    "Centroavante"
};



typedef struct {

    int isLesionado;    // está lesionado? (0 - não lesionado | 1 - lesionado)
    int pernaBoa;       // indica qual perna é a favorita (0 - esquerda | 1 - direita)
    int finta;          // nota da finta        (0 a 99)
    int pace;           // nota do pace/ritmo   (0 a 99)
    int pas;            // nota do passe        (0 a 99)
    int defesa;         // nota da defesa        (0 a 99)
    int fisico;         // nota do fisico        (0 a 99)
    int finalizacao;    // nota da finalizacao
    int overall;        // media inteira das outras notas
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
    char *name_arq;
} arvB;

//FUNCAO DE BUSCA
arvB* buscarArv (arvB *r, int k);

//FUNCOES UTILIZADAS NA INSERCAO
arvB* criarNoVazio(bool folha);
arvB* criarNoRaizInicial();
arvB* insereArvoreB(arvB *r, Registro *k);
void insereNaoCheioArvoreB(arvB *x, Registro *k);
void splitChildArvoreB (arvB *x, int i);

//FUNCOES UTILIZADAS NA REMOCAO
arvB* remover(arvB *raiz, int k);
void remover_rec (arvB *x, int k);
void mergeChildArvoreB (arvB *x, int i);
void liberarArvore(arvB *raiz);

//FUNCOES DE IMPRESSAO
void imprimir_informacoes_basicas(arvB *raiz);
void imprimir_acima_de_overall(arvB *raiz, int overall);
void imprimir_atletas_por_posicao(arvB *raiz, char posicao[]);
void imprimir_atletas_por_clube(arvB *raiz, char clube[]);
void imprimir_jogador_por_id(arvB* raiz, int id_buscado);
void imprimir_jogador(Registro* regs);

//FUNCOES DA MAIN
int menu();

//FUNCOES CRIACAO DE JOGADOR
void aleatorizarInformacoes(Registro *r);
Registro* criarJogador();

//FUNCOES ARQUIVO
void leituraBin(arvB* raiz);
void escreverBin(arvB* raiz);
char* GeraNomeArqBin();
void salvarNomeNovaRaiz(arvB *raiz);
bool arquivoExiste(const char *nomeArquivo);
arvB* carregarOuCriarArvore();


#endif