#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "pilha.h"
#include "arena.h"

// #define DEBUG

#ifdef DEBUG
#   define D(X) X
char *CODES[] = {
    "PUSH",
    "POP",
    "DUP",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "JMP",
    "JIT",
    "JIF",
    "CALL",
    "RET",
    "STS",
    "RCS",
    "EQ",
    "GT",
    "GE",
    "LT",
    "LE",
    "NE",
    "STO",
    "RCL",
    "END",
    "PRN",
    "STL",
    "RCE",
    "ALC",
    "FRE",
    "ATR"
};
#else
#   define D(X)
#endif

static void Erro(char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
    Maquina *m = (Maquina*)malloc(sizeof(Maquina));
    if (!m) Fatal("Memória insuficiente",4);
    m->ip = 0;
    m->rbp = 0;
    m->prog = p;
    return m;
}

void destroi_maquina(Maquina *m) {
    free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define rbp (m->rbp)
#define rsp (exec->topo)

void exec_maquina(Maquina *m, int n) {
    int i;

    for (i = 0; i < n; i++) {
        OpCode   opc = prg[ip].instr;
        OPERANDO arg = prg[ip].op;

        D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));

        switch (opc) {
            int tmp;
            OPERANDO tmp1;
            OPERANDO tmp2;
            OPERANDO tmp3;
            case PUSH:
                empilha(pil, arg);
                break;
            case POP:
                desempilha(pil);
                break;
            case DUP:
                tmp1 = desempilha(pil);
                empilha(pil, tmp1);
                empilha(pil, tmp1);
                break;
            case ADD:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp1.val.n += tmp2.val.n;
                    empilha(pil, tmp1);
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case SUB:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp2.val.n -= tmp1.val.n;
                    empilha(pil, tmp2);
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case MUL:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp1.val.n *= tmp2.val.n;
                    empilha(pil, tmp1);
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case DIV:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp2.val.n /= tmp1.val.n;
                    empilha(pil, tmp2);
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case JMP:
                ip = arg.val.n;
                continue;
            case JIT:
                tmp1 = desempilha(pil);
                if (tmp1.t == NUM) {
                    if (tmp1.val.n) {
                        ip = arg.val.n;
                        continue;
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case JIF:
                tmp1 = desempilha(pil);
                if (tmp1.t == NUM) {
                    if (!tmp1.val.n) {
                        ip = arg.val.n;
                        continue;
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case CALL:
                tmp1.t = NUM;
                tmp1.val.n = ip;
                empilha(exec, tmp1);
                // Empilha valor do RBP para ser recuperado depois, com RET.
                tmp1.t = NUM;
                tmp1.val.n = rbp;
                empilha(exec, tmp1);
                /* Atualiza RBP
                Da forma como está, RBP aponta para a primeira posição vazia
                do novo frame, ou seja, para adicionar ou copiar valores ao
                primeiro espaço do frame, se utiliza STL 0 e RCE 0,
                respectivamente. */
                rbp = rsp;
                ip = arg.val.n;
                continue;
            case RET:
                // Recupera valor anterior do RBP.
                if (rsp != rbp) {
                    printf("Linha %d\n", ip);
                    Erro("Aviso: Espaco nao desalocado. Desalocacao forcada.");
                    rsp = rbp;
                }
                tmp1 = desempilha(exec);
                rbp = tmp1.val.n;
                tmp1 = desempilha(exec);
                ip = tmp1.val.n;
                break;
            case EQ:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n == tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case GT:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n < tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case GE:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n <= tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case LT:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n > tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case LE:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n >= tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case NE:
                tmp1 = desempilha(pil);
                tmp2 = desempilha(pil);
                if (tmp1.t == NUM && tmp2.t == NUM) {
                    tmp3.t = NUM;
                    if (tmp1.val.n != tmp2.val.n) {
                        tmp3.val.n = 1;
                        empilha(pil, tmp1);
                    }
                    else {
                        tmp3.val.n = 0;
                        empilha(pil, tmp1);
                    }
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: OPERANDO nao numerico", 4);
            case STO:
                if (arg.val.n < 0 || arg.val.n > MAXMEM) {
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Acesso fora dos limites da memoria", 4);
                }
                m->Mem[arg.val.n] = desempilha(pil);
                break;
            case RCL:
                if (arg.val.n < 0 || arg.val.n > MAXMEM) {
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Acesso fora dos limites da memoria", 4);
                }
                empilha(pil, m->Mem[arg.val.n]);
                break;
            case END:
                return;
            case PRN:
                printf("%s\n", toString(desempilha(pil)));
                break;
            /* STL e RCE verificam se o índice dado vai estar dentro dos
            limites do frame antes de executar suas ações. */
            case STL:
                /* Adiciona o valor de uma variável local na pilha de execução
                na posição dada */
                tmp = arg.val.n + rbp;
                if (tmp > rsp - 1 || arg.val.n < 0)
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Posicao fora do limite do frame", 4);
                exec->val[tmp] = desempilha(pil);
                break;
            case RCE:
                /* Empilha o valor de uma variável local da pilha de execução,
                na posição dada, para a pilha de dados */
                tmp = arg.val.n + rbp;
                if (tmp > rsp - 1 || arg.val.n < 0)
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Posicao fora do limite do frame", 4);
                empilha(pil, exec->val[tmp]);
                break;
            case ALC:
                /* Move RSP para alocar espaço suficiente para variáveis locais
                em um novo frame. Verifica se a alocação não ultrapassa o
                tamanho da pilha. */
                tmp = rsp + arg.val.n;
                if (tmp > PILMAX)
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Alocacao fora do limite da pilha", 4);
                rsp = tmp;
                break;
            case FRE:
                /* Move RSP para desalocar espaço de variáveis locais no frame
                atual. Verifica se a desalocação não excede o limite do
                frame. */
                tmp = rsp - arg.val.n;
                if (tmp < rbp)
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Desalocacao fora do limite do frame", 4);
                rsp = tmp;
                break;
            case ATR:
                /*  */
                tmp1 = desempilha(pil);
                if (tmp1.t != CELULA) {
                    printf("Linha %d\n", ip);
                    Fatal("Erro: Atributos só podem ser obtidos de celulas", 4);
                }
                tmp2.t = NUM;
                switch (arg.val.n) {
                    case 1:
                        tmp2.val.n = tmp1.val.cel.terreno;
                        break;
                    case 2:
                        tmp2.val.n = tmp1.val.cel.cristais;
                        break;
                    case 3:
                        tmp2.val.n = tmp1.val.cel.ocupado;
                        break;
                    default:
                        printf("Linha %d\n", ip);
                        Fatal("Erro: Argumento ilegal para atributo", 4);
                }
                break;
            case SIS:
                /*  */
                if (arg.t == ACAO) {
                    tmp1 = Sistema(arg);
                    if (tmp1.val.ac.t == GET) empilha(pil, tmp1);
                    break;
                }
                printf("Linha %d\n", ip);
                Fatal("Erro: O sistema so pode ser chamado por uma acao", 4);
            default:
                printf("Linha %d\n", ip);
                Fatal("Erro: Instrucao nao definida", 4);
        }
        D(imprime(pil,5));
        D(puts("\n"));

        ip++;
    }
}
