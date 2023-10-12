#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


//Struct feita para armazenar as informações do tempo
typedef struct {

    int dia;
        int mes;
            int ano;

} Data;

//Retorna true se a data comparada for mais antiga que a data base
bool ComparadorDeData (Data data_comparada, Data data_inicial) {

    if (data_comparada.ano < data_inicial.ano) return true;

        else if (data_comparada.mes < data_inicial.mes) return true;
            
            else if (data_comparada.dia < data_inicial.dia) return true;

                    return false;
}

//Struct feita para armazenar as informações da tarefa
typedef struct {

    int codigo;
        char nome[30];
            char projeto[30];
                Data inicio;
                    Data termino;
                        int status;
                            int prioridade;

} Tarefa;

//Struct de Nó para ser utilizado na Lista
typedef struct No{

    Tarefa * tarefa;
        struct No * proximo_no;

} No;

//Definindo o nome lista para a struct No
typedef No Lista;

//Struct feita para armazenar as informações da fila
typedef struct {

    No * inicio;
        No * fim;

} Fila;

//Cria uma lista vazia
Lista * criaLista() {

    return NULL;
}

//Se a lista estiver vazia, retorna true
bool ListaVazia(Lista * lista) {

    if (lista == NULL) return true;
        
        return false;
}


//Cria uma nova fila com o início e o fim nulos
Fila * criaFila() {

    Fila * nova_fila = (Fila *) malloc(sizeof(Fila));

                nova_fila->fim = NULL;
                    nova_fila->inicio = NULL;

    return nova_fila;
}

//Se a fila estiver vazia, retorna true
bool FilaVazia(Fila * fila) {

    if (fila->inicio == NULL) {
        
        return true;
    }
    else{
                    return false;
    }
}

No * TiraFila(Fila * fila) {
        
        if (!FilaVazia(fila)) {
        
            No * no_removido = fila->inicio;
        
                fila->inicio = fila->inicio->proximo_no;
                         return no_removido;
    }

    return NULL;
}

void UsaFflush() {

    fflush(stdin);
    
}

//Função que pega a tarefa com o código que foi inserido pelo usário
Tarefa * BuscaTarefa (int codigo, Lista * pendentes, Fila ** filas) {

    while (pendentes != NULL) {
        
        if (pendentes->tarefa->codigo == codigo) return pendentes->tarefa;
                 pendentes = pendentes->proximo_no;

    }

    for (int i = 0; i < 3; i++) {

        No * no_atual = filas[i]->inicio;
            while (no_atual != NULL) {
            
                if (no_atual->tarefa->codigo == codigo) return no_atual->tarefa;
                        no_atual = no_atual->proximo_no;

        }
    }

    return NULL; 
}

//Cria um novo nó com uma dada tarefa e o insere na fila
void insereFila(Fila * fila, Tarefa * tarefa){

    No * novo_no = (No *) malloc(sizeof(No));
            novo_no->tarefa = tarefa;

    if (FilaVazia(fila)){
            
            fila->fim = novo_no;
                fila->inicio = novo_no;
                        novo_no->proximo_no = NULL;

    } 

    else{

        fila->fim->proximo_no = novo_no;
            fila->fim = novo_no;
                fila->fim->proximo_no = NULL;

    }
}


No * removeTarefa(int codigo, Lista ** pendentes, Fila ** filas) {

    Tarefa * tarefa = BuscaTarefa(codigo, * pendentes, filas);
    No * no_retirado;
    
    //Procura na lista de pendentes
    if (tarefa->status == -1) {

        if ((* pendentes)->tarefa == tarefa) {

            no_retirado = * pendentes;
                    (* pendentes) = (* pendentes)->proximo_no;

        }

        else {

            Lista * pendentes_aux = * pendentes;

    while (pendentes_aux->proximo_no->tarefa != tarefa && pendentes_aux->proximo_no != NULL) {
                
                    pendentes_aux = pendentes_aux->proximo_no;
            }

                    no_retirado = pendentes_aux->proximo_no;
                    
                    pendentes_aux->proximo_no = pendentes_aux->proximo_no->proximo_no;
        }
    }

    else {

        Fila * fila = filas[tarefa->prioridade - 1];

            if (fila->inicio->tarefa == tarefa) {
            
                no_retirado = fila->inicio;
                    fila->inicio = fila->inicio->proximo_no;
        }

        else {
            
            No * no_aux;

            bool tarefa_encontrada = false;

    while (!tarefa_encontrada ) {

                no_aux = TiraFila(fila);

            if (no_aux->tarefa->codigo == codigo) {
                
                    no_retirado = no_aux;
                        tarefa_encontrada  = true;

                } 
            else {

                    insereFila(fila, no_aux->tarefa);
                        free(no_aux);

                }
            }
        }
    }

    return no_retirado;
}

//Cria um novo nó com uma dada tarefa e o insere na posição ordenado pela data de término
void insereLista(Lista ** lista, Tarefa * tarefa) {

    No * novo_no = (No *) malloc(sizeof(No));
            novo_no->tarefa = tarefa;
                novo_no->proximo_no = NULL;
    
    Lista * no_momento = *lista;

    //Insere no início
    if (ListaVazia(no_momento) || ComparadorDeData(tarefa->termino, no_momento ->tarefa->termino)) {

        novo_no->proximo_no = no_momento ;
            (*lista) = novo_no;
    } 

    //Insere da posição 1 pra frente
    else {

        while(no_momento ->proximo_no != NULL && ComparadorDeData(no_momento ->tarefa->termino, tarefa->termino)) {
            no_momento  = no_momento ->proximo_no;
        }

                novo_no->proximo_no = no_momento ->proximo_no;
                     no_momento ->proximo_no = novo_no;
    }
}

//printa todos os detalhes da tarefa
void MostraTarefa(Tarefa tarefa) {

    printf("\n\n-> Tarefa \"%s\":\n\n", tarefa.nome);

        printf("- Codigo: %d; \n", tarefa.codigo);
            
            printf("- Prioridade: %d; \n", tarefa.prioridade);
        
                printf("- Projeto: \"%s\"; \n", tarefa.projeto);
    
                    printf("- Data de Inicio: %02d/%02d/%04d; \n", tarefa.inicio.dia, tarefa.inicio.mes, tarefa.inicio.ano);
                
                        printf("- Data de Encerramento: %02d/%02d/%04d; \n", tarefa.termino.dia, tarefa.termino.mes, tarefa.termino.ano);
    
                            printf("- Status: %d; \n", tarefa.status);
                        

}

//Printa todos os codigos da lista seguindo a ordem 
void MostraLista(Lista * lista, bool concluida) {

    if (!ListaVazia(lista)) {

         if (concluida) {
            
            Lista * lista_aux = lista;

                printf("\n-> Concluidas com Atraso <-\n");

        while (!ListaVazia(lista)) {

                if (lista->tarefa->status == 1)

                    MostraTarefa(*(lista->tarefa));
                        
                        lista = lista->proximo_no;
            }

            lista = lista_aux;

                printf("\n-> Concluidas sem Atraso <-\n");
        
        while (!ListaVazia(lista)) {

                if (lista->tarefa->status == 0) 

                    MostraTarefa(*(lista->tarefa));

                        lista = lista->proximo_no;
            }
            
        } 
    else {
        
        while (!ListaVazia(lista)) {

                MostraTarefa(*(lista->tarefa));

                    lista = lista->proximo_no;
            }
        }
    }

    else printf("\n - A lista esta vazia. \n");
}

void MostraFila(Fila * fila) {

    No * inicio = fila->inicio;
    
        if (!FilaVazia(fila)) {
            
            while (inicio != NULL) {

                MostraTarefa(*(inicio->tarefa));
                        inicio = inicio->proximo_no;

        }
    }

    else printf("\n - Esta fila esta vazia.\n");
}


Tarefa * GeraTarefa(int * codigo_atual, int hoje[]) {
    
    Tarefa * nova_tarefa = (Tarefa *) malloc(sizeof(Tarefa));

        printf("-> Nova Tarefa <- \n\n");
        printf("**********************\n\n");

    //Deixa o usuário decidir o nome da nova Tarefa
            printf("-> Digite o nome que deseja atribuir a tarefa: ");
    
                UsaFflush();
                    fgets(nova_tarefa->nome, 30, stdin);

            int nome_i = 0;
                while (nova_tarefa->nome[nome_i] != '\n') nome_i++;
                            nova_tarefa->nome[nome_i] = '\0';

    //Deixa o usuário decidir o nome do Projeto da nova tarefa
            printf("\n -> Digite o nome para atribuir ao projeto: ");
    
                    fgets(nova_tarefa->projeto, 30, stdin);

            int projeto_i = 0;
                while (nova_tarefa->projeto[projeto_i] != '\n') projeto_i++;
                            nova_tarefa->projeto[projeto_i] = '\0';

    //Deixa o usuário decidir a data de inicio da tarefa no sistema
            printf("\n->  Essa e a data de inicio: %d/%d/%d", hoje[0], hoje[1], hoje[2]);
    
                nova_tarefa->inicio.dia = hoje[0];
                    nova_tarefa->inicio.mes = hoje[1];
                        nova_tarefa->inicio.ano = hoje[2];

    //Deixa o usuário decidir a data de finalização da tarefa no sistema
            printf("\n-> Indique a data de encerramento: ");
                
                printf("\n - Dia: "); 
                
                    UsaFflush();
                    
                        scanf("%d", &nova_tarefa->termino.dia);
                    
                printf(" - Mes: "); 
                    
                    UsaFflush();
                    
                        scanf("%d", &nova_tarefa->termino.mes);
                        
                printf(" - Ano: "); 
                        
                    UsaFflush(); 
                                
                        scanf("%d", &nova_tarefa->termino.ano);

    //Define o status da nova tarefa baseado na data digitada
            if (ComparadorDeData(nova_tarefa->termino, nova_tarefa->inicio)) nova_tarefa->status = 1;
                    
                    else nova_tarefa->status = 0;

    //Deixa o usuário decidir a prioridade da nova tarefa
            printf("\n-> Indique a prioridade desta tarefa: \n\n[1] Alta; \n\n[2] Normal; \n\n[3] Baixa.");

               UsaFflush();

                    scanf("%d", &nova_tarefa->prioridade);
                            
                            getchar();

    //Indica ao usuário qual será o código da nova tarefa
            nova_tarefa->codigo = *codigo_atual;

                printf("\n -> Essa tarefa esta representada pelo codigo: %d", *codigo_atual);

                         (*codigo_atual)++;

    return nova_tarefa;
}

//Recebe uma tarefa e insere em uma das filas ou na lista de pendentes
void ColocaTarefaCriada(Fila ** filas, Tarefa * tarefa) {

        insereFila(filas[tarefa->prioridade - 1], tarefa);
    
}

void ExcluiTarefa(int codigo, Lista ** pendentes, Fila ** filas) {

    No * no_livre = removeTarefa(codigo, pendentes, filas);
        free(no_livre->tarefa);
            free(no_livre);}


//Recebe o codigo de uma tarefa e altera as suas informacoes
void editaTarefa(int codigo, Fila ** filas, Lista ** pendentes) {

    Tarefa * tarefa = BuscaTarefa(codigo, * pendentes, filas);
    
        printf("-> Editar Tarefa <- \n\n");

            printf("Indique qual elemento deseja alterar:\n[0] Nome; \n[1] Projeto; \n[2] Data de inicio; \n[3] Data de encerramento; \n[4] Status; \n[5] Prioridade; \n -> ");

    int escolha;

        UsaFflush();
            scanf("%d", &escolha);

    switch (escolha) {

        case 0:

            printf("\n -> Novo nome: ");
            
                UsaFflush();
                    fgets(tarefa->nome, 30, stdin);
                    
                int nome_i = 0;
                
                while (tarefa->nome[nome_i] != '\n') nome_i++;
                        tarefa->nome[nome_i] = '\0';
                 break;

        case 1:

            printf("\n -> Novo projeto: ");
                
                UsaFflush();
                    fgets(tarefa->projeto, 30, stdin);

                int projeto_i = 0;
                
                while (tarefa->projeto[projeto_i] != '\n') projeto_i++;
                        tarefa->projeto[projeto_i] = '\0';
                        break;

        case 2:

            printf(" -> Nova data de inicio:");

                printf("\n - Dia: "); 
                    
                    UsaFflush(); 
                        
                        scanf("%d", &tarefa->inicio.dia);

                printf(" - Mes: "); 
                
                    UsaFflush(); 
                        
                        scanf("%d", &tarefa->inicio.mes);

                printf(" - Ano: "); 
                    
                    UsaFflush();
                    
                        scanf("%d", &tarefa->inicio.ano);

                            break;

        case 3:

            printf(" -> Nova data de termino:");

                printf("\n - Dia: "); 
                    
                    UsaFflush(); 
                        
                        scanf("%d", &tarefa->termino.dia);

                printf(" - Mes: "); 
                    
                    UsaFflush();
                    
                        scanf("%d", &tarefa->termino.mes);

            printf(" - Ano: "); 

                    UsaFflush();
                    
                         scanf("%d", &tarefa->termino.ano);
                            
                            break;

        case 4:

            printf(" -> Novo status: ");

                UsaFflush();
                int novo_status;

                scanf("%d", &novo_status);

            if (novo_status == -1) {
                free(removeTarefa(codigo, pendentes, filas));
                insereLista(pendentes, tarefa);
            }

            else if(novo_status == 0 || novo_status == 1) {

                free(removeTarefa(codigo, pendentes, filas));
                    insereFila(filas[tarefa->prioridade - 1], tarefa);
            }
    
                        tarefa->status = novo_status;

                            break;

        case 5:

            printf(" -> Nova prioridade: ");

                UsaFflush();

                    free(removeTarefa(codigo, pendentes, filas));

                        scanf("%d", &tarefa->prioridade);

                            insereFila(filas[tarefa->prioridade -1], tarefa);

                            break;

        default: 
        
            printf(" -> Escolha invalida.");
                            break;
    }
        if (ComparadorDeData(tarefa->termino, tarefa->inicio) && tarefa->status != -1) tarefa->status = 1;
}
