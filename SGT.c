#include <time.h>
#include "biblioteca.h"

//Função utilizada para limpar a tela para um melhor ambiente para o usuário
void limpador() {

        system("cls");
}

void ColocarTarefa (Fila ** filas,  int * codigo_atual, int hoje[]) {

    limpador();

        ColocaTarefaCriada (filas, GeraTarefa(codigo_atual, hoje));

}

void VerTarefas (Fila ** filas, Lista * pendentes, Lista * concluidas) {

    limpador();
        
        printf("\n***************************\n");
        printf("-> Quais tarefas deseja ver: \n[0] Todas; \n[1] Em Processo; \n[2] Pendentes; \n[3] Concluidas; \n[4] Voltar. \n");
        printf("\n***************************\n");
        printf("\n -> ");
    
    int decisao; 
    
        scanf("%d", &decisao);

    switch (decisao) {

        case 0:

            limpador();

                printf("-> Tarefas em Processo <- \n");

                    for (int i = 0; i < 3; i++) {

                        printf("\n -> Prioridade %d: ", i + 1);

                            MostraFila(filas[i]);

                                    }

                printf("\n -> Tarefas Pendentes <- ");

                        MostraLista(pendentes, false);

                            printf("\n -> Tarefas Concluidas <- ");

                                MostraLista(concluidas, true);

                                        break;

        case 1:

            limpador();

                printf("-> Tarefas em Processo <- \n");

                     for (int i = 0; i < 3; i++) {

                        printf("\n -> Prioridade %d: ", i + 1);

                            MostraFila(filas[i]);

                                    }
                                         break;

        case 2:

            limpador();

                printf("\n -> Tarefas Pendentes <- ");

                    MostraLista(pendentes, false);

                            break;

        case 3:

            limpador();

                printf("\n-> Tarefas Concluidas <- ");

                    MostraLista(concluidas, true);
            
                            break;

        case 4:

             default: 
        
                    limpador();
                        
                            break;
    }
}

void AbrirTarefa (Lista ** pendentes, Lista * filas[], Lista ** concluidas, int hoje[]){

    limpador();

        printf("-> Digite o codigo da tarefa que deseja abrir: ");
            
            UsaFflush();

    int codigo;

        scanf("%d",&codigo);

    Tarefa * tarefa = BuscaTarefa(codigo, * pendentes, filas);

        limpador();

            MostraTarefa(*tarefa);

                printf("\n*****************************\n");
                printf(" -> Escolha qual opção deseja: \n [0] Editar; \n [1] Excluir; \n [2] Concluir Tarefa; \n [3] Sair.");
                printf("\n*****************************\n");

    int resposta;

        scanf("%d", &resposta);

    switch (resposta) {

        case 0:
            editaTarefa(codigo, filas, pendentes);

                limpador();

                    printf("-> Sua tarefa foi atualizada com sucesso.");

                        MostraTarefa(*tarefa);
                                break;

        case 1:

            limpador();

                ExcluiTarefa(codigo, pendentes, filas);

                     printf("-> Sua tarefa foi excluida com sucesso.");

                            break;
            
        case 2:

            limpador();

                free(removeTarefa(codigo, pendentes, filas));

                     insereLista(concluidas, tarefa);

                        tarefa->termino.dia = hoje[0];
                            tarefa->termino.mes = hoje[1];
                                tarefa->termino.ano = hoje[2];

                            printf("-> Sua tarefa foi atualizada como concluida com sucesso.");
                            break;
                        

        case 3:

                            break;

            default:
                    
                    break;
    }
                            limpador();

}

int main() {

    limpador();

    int codigo_atual = 0;
    bool finalDoMenu = false;

    // Utilizado para definir a data atual dentro do progama
    time_t tempo_atual;
    struct tm *info_tempo;

        time(&tempo_atual);
            info_tempo = localtime(&tempo_atual);

    int hoje[3] = { info_tempo->tm_mday, info_tempo->tm_mon + 1, info_tempo->tm_year + 1900 };


     //Cria as filas de tarefas por prioridade
    Fila * filas[3];

        for (int i = 0; i < 3; i++) {
            filas[i] = criaFila(); 
    }
    
     //Cria as listas nomeadas de pendentes e concluídas
    Lista * pendentes = criaLista();
        Lista * concluidas = criaLista();  


    //Menu de interações do usuário
    printf("*********************************************************\n");
        printf("\n ----------  Sistema Gerenciador de Tarefas ----------- \n");
            printf("\n |||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    
        while (!finalDoMenu) {
            
            printf("\n*******************************\n");
            printf(" -> Selecione o item que deseja:\n \n[0] Tarefas presentes; \n[1] Nova tarefa; \n[2] Abrir tarefa; \n[3] Fechar. \n ");
            printf("\n*******************************\n -> ");
        
        int resposta; 
            
            fflush(stdin);
                
                scanf("%d", &resposta);
        
        switch (resposta){

            case 0:

                    VerTarefas(filas, pendentes, concluidas);
                
                            break;
                    
            case 1:

                    ColocarTarefa(filas, &codigo_atual, hoje);
                
                            break;

            case 2:
                
                    AbrirTarefa(&pendentes, filas, &concluidas, hoje);
                
                            break;
            case 3:

                    finalDoMenu = true;
                
                            break;
            default: 
                    
                    limpador();

                        printf("Item invalido.\n");

                            break;
        }
    }

                         printf("\n");

    return 0;
}
