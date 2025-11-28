#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char tipo;
    int id;
} Peca;

//Contador Para os IDs
int next_id = 1;

#define MAX_PECAS 5

//Estrutura Para Controlar a Fila
typedef struct {
    Peca Sequel[MAX_PECAS];
    int inicio;
    int fim;
    int total;
} Ordem_Pecas;

//Funcao Para Limpar o Buffer
void ClearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void InicializarFila(Ordem_Pecas *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int FilaCheia(Ordem_Pecas *f){
    return f->total == MAX_PECAS;
}

int FilaVazia(Ordem_Pecas *f){
    return f->total == 0;
}

void Enqueue(Ordem_Pecas *f, Peca p){
    if(FilaCheia(f)){
        printf("Maximo de Pecas Alcancado\n");
        return;
    }

    f->Sequel[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_PECAS;
    f->total++;
    printf("Peca [%c, %d] Inserida com Sucesso\n", p.tipo, p.id);
}

int dequeue(Ordem_Pecas *f, Peca *p){
    if (FilaVazia(f)){
        printf("Ainda Nao Ha Pecas\n");
        return 0;
    }

    *p = f->Sequel[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS;
    f->total--;
    printf("==Peca [%c, %d] Removida...\n", p->tipo, p->id);
    return 1;
}

void MostrarPecas(Ordem_Pecas *f){
    for (int i = 0, indice = f->inicio; i < f->total; i++, indice = (indice + 1) % MAX_PECAS){
        printf("[%c, %d]", f->Sequel[indice].tipo, f->Sequel[indice].id);
    }
}

Peca GerarPecas(){
    Peca Peca_Nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int num_tipos = 4;

    Peca_Nova.tipo = tipos[rand() % num_tipos];
    Peca_Nova.id = next_id++;

    return Peca_Nova;
}

int main(){
    srand(time(NULL));

    Ordem_Pecas game;   
    InicializarFila(&game);
    Peca remove_peca;
    int opcao;

    //Gerando as primeiras pecas e as listando
    printf("\n---TETRIS---\n");
    for (int i = 0; i < MAX_PECAS; i++){
        Enqueue(&game, GerarPecas());
    }
    MostrarPecas(&game);

    do {
        printf("\n\n---TETRIS MENU---\n");
        printf("1 - Jogar Peca\n");
        printf("0 - Sair do Jogo\n");
        printf("Escolha Uma Opcao: ");
        scanf("%d", &opcao);
        ClearBuffer();

        switch (opcao){
            case 1:
            printf("\n---JOGANDO PECA---\n");
            if (dequeue(&game, &remove_peca)){
                printf("\n--INSERINDO NOVA PECA--\n");
                Enqueue(&game, GerarPecas());
            }
            MostrarPecas(&game);
            break;

            case 0:
            printf("Saindo do Programa...\n");
            break;

            default:
            printf("\nOpcao Invalida. Por Favor Tente Novamente\n");
        }
        
    } while(opcao != 0);


    return 0;
}