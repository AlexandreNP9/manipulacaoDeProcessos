/*
Descrição: Programa que executa comandos do sistema operacional como processos filhos.
    Permite executar qualquer comando do sistema passado como argumento,
    criando um processo filho para sua execução e aguardando sua conclusão.
  
Autor: Alexandre Nassar de Peder
Data de criação: 30/09/2025
Última atualização: 30/09/2025
*/

#include <stdio.h>      // para funções de entrada/saída (printf, perror)
#include <unistd.h>     // para funções de processo (fork, exec, getpid)
#include <sys/wait.h>   // para função wait (esperar processos filhos)
#include <stdlib.h>     // para funções de conversão e alocação de memória

/*
@brief Executa um comando do sistema como processo filho

Esta função cria um processo filho que executa o comando especificado
usando a função execvp. O processo pai aguarda a conclusão do filho
antes de continuar.

@param comando_completo Array de strings contendo o comando e seus argumentos
    O último elemento deve ser NULL
@return void
*/
void executar_comando(char *comando_completo[]) {
    pid_t pid_filho = fork();  // cria um processo filho
    
    if (pid_filho == 0) {
        // código executado apenas pelo processo filho
        printf("Processo filho (PID: %d) executando comando...\n", getpid());
        
        // executa o comando passado como argumento
        execvp(comando_completo[0], comando_completo);
        
        // se execvp retornar, houve um erro na execução
        perror("Erro ao executar comando");
        exit(1);  // termina o processo filho com código de erro
        
    } else if (pid_filho > 0) {
        // código executado apenas pelo processo pai
        printf("Processo pai (PID: %d) aguardando filho terminar...\n\n", getpid());
        
        // espera o processo filho terminar
        int status;
        wait(&status);  // aguarda o término do filho
        
        // verifica se o filho terminou normalmente
        if (WIFEXITED(status)) {
            printf("\nProcesso executa_comando finalizado.\n");
        } else {
            printf("\nProcesso filho terminou anormalmente\n");
        }
        
    } else {
        // tratamento de erro na criação do processo filho
        perror("Erro ao criar processo filho");
    }
}

/*
@brief Função principal do programa

Recebe os argumentos da linha de comando, valida e executa o comando
solicitado através da função executar_comando.

@param argc Número de argumentos passados
@param argv Array de strings com os argumentos
    argv[0]: nome do programa
    argv[1]: comando a ser executado
    argv[2+]: argumentos do comando

@return int 0 em caso de sucesso, 1 em caso de erro
*/
int main(int argc, char *argv[]) {
    
    // verifica se foi passado algum comando como argumento
    if (argc < 2) {
        printf("Uso: %s <comando> [argumentos...]\n", argv[0]);
        printf("\nComandos do sistema sugeridos:\n");
        
        printf("  Sistema:\n");
        printf("  %s uname -a\n", argv[0]);
        printf("  %s lsb_release -a\n", argv[0]);
        printf("  %s uptime\n", argv[0]);
        printf("  %s hostname\n", argv[0]);
        printf("  %s lscpu\n", argv[0]);
        printf("  %s lspci\n", argv[0]);
        printf("  %s lsusb\n", argv[0]);
        printf("  %s cat /proc/interrupts\n", argv[0]);
        printf("  %s ulimit -a\n", argv[0]);
        
        printf("\n  Processos:\n");
        printf("  %s ps aux\n", argv[0]);
        printf("  %s top -n 1\n", argv[0]);
        
        printf("\n  Rede:\n");
        printf("  %s ping 8.8.8.8 -c 3\n", argv[0]);
        printf("  %s ifconfig\n", argv[0]);
        
        printf("\n  Arquivos:\n");
        printf("  %s ls -l\n", argv[0]);
        printf("  %s df -h\n", argv[0]);
        
        return 1;  // retorna código de erro
    }
    
    // exibe informações sobre o comando que será executado
    printf("Executando: ");
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
    
    // chama função para executar o comando (ignora o primeiro argumento que é o nome do programa)
    executar_comando(&argv[1]);
    
    return 0;  // retorna sucesso
}