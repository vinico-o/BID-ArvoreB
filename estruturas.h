#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>

#define TAM_ARQ 33
#define TAM_NOME_ARQUIVO 256

int t;
int id = 1;

char *timesSerieA[20] = {
    "Atletico Mineiro",
    "Bahia",
    "Botafogo",
    "Ceara",
    "Corinthians",
    "Cruzeiro",
    "Flamengo",
    "Fluminense",
    "Fortaleza",
    "Gremio",
    "Internacional",
    "Juventude",
    "Mirassol",
    "Palmeiras",
    "RB Bragantino",
    "Santos",
    "Sao Paulo",
    "Sport Recife",
    "Vasco da Gama",
    "Vitoria"
};

char *titulares[20][11] = {
        // Atletico-MG
        {"Everson", "Natanael", "Rabello", "Vitor Hugo", "Rubens", "Alan Franco", "Patrick", "Scarpa", "Rony", "Igor Gomes", "Hulk"},
        // Bahia
        {"Ronaldo", "Gilberto", "David Duarte", "Ramos Mingo", "Luciano Juba", "Nicolas Acevedo", "Rodrigo Nestor", "Everton Ribeiro", "Kayky", "Cauly", "Willian Jose"},
        // Botafogo
        {"John", "Vitinho", "Bastos", "Alexander Barbosa", "Marcal", "Gregore", "Marlon Freitas", "Eduardo", "Savarino", "Junior Santos", "Tiquinho Soares"},
        // Ceara
        {"Richard", "Rai Ramos", "Matheus Felipe", "Ramon Menezes", "Matheus Bahia", "Richardson", "Lourenco", "Guilherme Castilho", "Aylon", "Erick Pulga", "Facundo Barcelo"},
        // Corinthians
        {"Hugo Souza", "Matheuzinho", "Gustavo Henrique", "Andre Ramalho", "Angileri", "Matheus Bidu", "Ryan", "Maycon", "Vitinho", "Kayke", "Gui Negao"},
        // Cruzeiro
        {"Cassio", "Jonathan Jesus", "Fabricio Bruno", "Lucas Villalba", "Kaua Prates", "Walace", "Lucas Silva", "Eduardo", "Matheus Pereira", "Wanderson", "Kaio Jorge"},
        // Flamengo
        {"Rossi", "Wesley", "Leo Ortiz", "Danilo", "Varela", "Pulgar", "De la Cruz", "Arrascaeta", "Gerson", "Plata", "Bruno Henrique"},
        // Fluminense
        {"Fabio", "Guga", "Freytes", "Thiago Silva", "Rene", "Hercules", "Martinelli", "Nonato", "Canobbio", "Serna", "Everaldo"},
        // Fortaleza
        {"Joao Ricardo", "Tinga", "Britez", "Cardona", "Bruno Pacheco", "Pol Fernandez", "Ze Welison", "Calebe", "Breno Lopes", "Pikachu", "Lucero"},
        // Gremio
        {"Tiago Volpi", "Gustavo Martins", "Noriega", "Kannemann", "Marlon", "Cuellar", "Dodi", "Arthur", "Alysson", "Cristian Olivera", "Braithwaite"},
        // Internacional
        {"Anthoni", "Aguirre", "Vitao", "Victor Gabriel", "Bernabei", "Fernando", "Bruno Henrique", "Alan Patrick", "Wanderson", "Lucca", "Enner Valencia"},
        // Juventude
        {"Jandrei", "Reginaldo", "Abner", "Wilker Angel", "Marcelo Hermes", "Caique", "Jadson", "Luis Mandaca", "Gabriel Veron", "Gabriel Taliari", "Enio"},
        // Mirassol
        {"Walter", "Lucas Ramon", "Joao Victor", "Jemmes", "Reinaldo", "Neto Moura", "Danielzinho", "Yago Felipe", "Gabriel", "Negueba", "Edson Carioca"},
        // Palmeiras
        {"Weverton", "Mayke", "Gustavo Gomez", "Murilo", "Piquerez", "Anibal Moreno", "Ze Rafael", "Raphael Veiga", "Dudu", "Endrick", "Rony"},
        // Red Bull Bragantino
        {"Cleiton", "Nathan Mendes", "Pedro Henrique", "Luan Candido", "Juninho Capixaba", "Jadsom", "Eric Ramires", "Lucas Evangelista", "Helinho", "Eduardo Sasha", "Vitinho"},
        // Santos
        {"Gabriel Brazao", "Mayke", "Adonis Frias", "Luan Peres", "Escobar", "Tomas Rincon", "Ze Rafael", "Neymar", "Caballero", "Guilherme", "Tiquinho Soares"},
        // Sao Paulo
        {"Rafael", "Arboleda", "Alan Franco", "Sabino", "Igor Vinicius", "Luiz Gustavo", "Alisson", "Marcos Antonio", "Wendell", "Luciano", "Calleri"},
        // Sport
        {"Gabriel", "Matheus Alexandre", "Rafael Thyere", "Ramon", "Aderlan", "Christian Rivera", "Ze Lucas", "Lucas Lima", "Matheusinho", "Leo Pereira", "Derik"},
        // Vasco da Gama
        {"Leo Jardim", "Paulo Henrique", "Joao Victor", "Mauricio Lemos", "Lucas Piton", "Paulinho", "Hugo Moura", "Garre", "Coutinho", "Nulo Moreira", "Vegete"},
        // Vitoria
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

} BID;

typedef struct {

    int id; 
    int cpf;
    char nome[50];
    BID *infos;

} Registro;


typedef struct no {

    int n;
    bool folha;
    Registro **regs;
    struct no **filho;
    char *name_arq;
} arvB;

// FUNCAO DE BUSCA
arvB* buscarArv (arvB *r, int k);

// FUNCOES UTILIZADAS NA INSERCAO
arvB* criarNoVazio(bool folha);
arvB* criarNoRaizInicial();
arvB* insereArvoreB(arvB *r, Registro *k);
void insereNaoCheioArvoreB(arvB *x, Registro *k);
void splitChildArvoreB (arvB *x, int i);

// FUNCOES UTILIZADAS NA REMOCAO
arvB* remover(arvB *raiz, int k);
void remover_rec (arvB *x, int k);
void mergeChildArvoreB (arvB *x, int i);
void liberarArvore(arvB *raiz);

// FUNCOES DE IMPRESSAO
void imprimir_informacoes_basicas(arvB *raiz);
void imprimir_acima_de_overall(arvB *raiz, int overall, int nivel);
void imprimir_atletas_por_posicao(arvB *raiz, char posicao[], int nivel);
void imprimir_atletas_por_clube(arvB *raiz, char clube[], int nivel);
void imprimir_jogador_por_id(arvB* raiz, int id_buscado);
void imprimir_jogador(Registro* regs);

// FUNCOES DA MAIN
int menu();

// FUNCOES CRIACAO DE JOGADOR
void aleatorizarInformacoes(Registro *r);
Registro* criarJogador();

// FUNCOES ARQUIVO
void leituraBin(arvB* raiz);
void escreverBin(arvB* raiz);
char* GeraNomeArqBin();
void salvarNomeNovaRaiz(arvB *raiz);
bool arquivoExiste(const char *nomeArquivo);
arvB* carregarOuCriarArvore();

// FUNCAO PARA CONTROLE DE ID
int encontrarMaiorID(arvB *raiz);

void imprimir_clubes();
void imprimir_posicoes();


#endif