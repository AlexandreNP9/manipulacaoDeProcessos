/*
Descrição: Programa que cria uma árvore binária completa de processos usando
    chamadas de sistema fork(). Cada processo pai cria dois filhos,
    formando uma estrutura hierárquica até o nível especificado.

Autor: Alexandre Nassar de Peder
Data de criação: 30/09/2025
Última atualização: 30/09/2025
*/

#include <stdio.h>      // para funções de entrada/saída
#include <unistd.h>     // para funções de processo (fork, getpid, getppid)
#include <sys/wait.h>   // para função wait
#include <stdlib.h>     // para funções de conversão e saída

/*
@brief Cria recursivamente uma árvore binária de processos

Esta função usa recursão e chamadas fork() para criar uma árvore binária
    completa de processos. Cada processo pai cria exatamente dois filhos,
    exceto os processos folha no último nível.

@param nivel_atual Nível atual na árvore (começa em 0 para a raiz)
@param nivel_maximo Número máximo de níveis da árvore

@return void
*/
void criar_arvore_processos(int nivel_atual, int nivel_maximo) {
    // condição de parada: quando atingir o nível máximo
    if (nivel_atual >= nivel_maximo) {
        // processo folha - aguarda para visualização com pstree
        sleep(30);
        return;
    }
    
    // cria primeiro processo filho
    pid_t pid_filho1 = fork();
    
    if (pid_filho1 == 0) {
        // código executado apenas pelo primeiro filho
        criar_arvore_processos(nivel_atual + 1, nivel_maximo);
        exit(0);
    } else if (pid_filho1 > 0) {
        // código executado apenas pelo processo pai
        
        // cria segundo processo filho
        pid_t pid_filho2 = fork();
        
        if (pid_filho2 == 0) {
            // código executado apenas pelo segundo filho
            criar_arvore_processos(nivel_atual + 1, nivel_maximo);
            exit(0);
        } else if (pid_filho2 > 0) {
            // processo pai espera ambos os filhos terminarem
            wait(NULL);
            wait(NULL);
        }
    }
}

/*
@brief Função principal do programa

Controla a execução do programa, valida argumentos e inicia a criação
    da árvore de processos. Fornece instruções para visualização da hierarquia.

@param argc Número de argumentos da linha de comando
@param argv Array de argumentos
    argv[0]: nome do programa
    argv[1]: número de níveis (opcional, padrão: 3)

@return int 0 em caso de sucesso, 1 em caso de erro
*/
int main(int argc, char *argv[]) {
    int niveis = 3;  // número padrão de níveis
    
    // verifica se foi passado argumento com número de níveis
    if (argc > 1) {
        niveis = atoi(argv[1]);
    }
    
    // validação do número de níveis
    if (niveis <= 0 || niveis > 5) {
        printf("Uso: %s [níveis]\n", argv[0]);
        printf("Número de níveis deve estar entre 1 e 5\n");
        return 1;
    }
    
    // calcula o total de processos (1 + 2 + 4 + ... + 2^(n-1))
    int total_processos = (1 << niveis) - 1;  // fórmula: 2^n - 1
    
    printf("Criando hierarquia de processos com %d níveis\n", niveis);
    printf("Total de processos criados: %d\n", total_processos);
    printf("Processo raiz PID: %d\n", getpid());
    printf("\n");
    printf("Execute em outro terminal para visualizar a hierarquia:\n");
    printf("pstree -p %d\n", getpid());
    printf("ou\n");
    printf("ps f -o pid,ppid,comm --forest --ppid %d\n", getpid());
    printf("\n");
    printf("Processos ficarão ativos por 30 segundos para visualização...\n");
    
    // cria a árvore de processos começando do nível 0
    criar_arvore_processos(0, niveis);
    
    printf("Hierarquia de processos finalizada\n");
    return 0;
}