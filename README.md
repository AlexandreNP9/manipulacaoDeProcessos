# manipulacaoDeProcessos
Referente à atividade laboratório 2 da disciplina de Sistemas Operacionais (UTFPR-CM professor dr. Rodrigo Campiolo)

# Sistema de Programas em C - Processos e Sistemas Operacionais

## Descrição Geral
Dois programas em C para estudo de processos em sistemas operacionais: executor de comandos e criador de árvore de processos binária.

## Estrutura do Projeto
manipulacaoDeProcessos/  
├── comandos_linux-sistema_processo.txt  
├── hierarquia  
├── hierarquia.c  
├── Laboratorio 02 - processos.pdf  
├── pai-espera-filho  
├── pai-espera-filho.c  
└── README.md  


## Programas
### Hierarquia (`hierarquia.c`)
Descrição: Executa comandos do sistema como processos filhos com monitoramento.

Compilação:  
gcc -o hierarquia hierarquia.c

Exemplos:  
./hierarquia uname -a  
./hierarquia ps aux  
./hierarquia df -h

### Pai Espera Filho (`pai-espera-filho.c`)
Descição: cria árvore binária de processos usando fork() recursivo.

Compilação:  
gcc -o pai-espera-filho pai-espera-filho.c 

## Bibliotecas Utilizadas
stdio.h, stdlib.h, unistd.h, sys/wait.h  
Todas as bibliotecas são padrão do sistema

## Casos de Teste
./hierarquia ls -la  
./hierarquia ps aux  
./pai-espera-filho 2  
./pai-espera-filho

# Informações
Autor: Alexandre Nassar de Peder  
Data: 30/09/2025  
Disciplina: Sistemas Operacionais (BCC5001)  
Professor dr. Rodrigo Campiolo  
Universidade Tecnológia Federal do Paraná, Campus Campo Mourão (UTFPR-CM)
