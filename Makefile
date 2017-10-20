all: arena

arena: arena.c, arena.h
	gcc -o arena arena.c exercito.c robo.c maq.c pilha.c operando.c arena.c

exercito: exercito.c robo.c maq.c pilha.c operando.c arena.c
	gcc -o exercito exercito.c robo.c maq.c pilha.c operando.c arena.c

maq: maq.c pilha.c operando.c arena.c
	gcc -o maq maq.c pilha.c operando.c arena.c

motor: motor.c maq.c pilha.c operando.c arena.c
	gcc -o motor motor.c maq.c pilha.c operando.c arena.c

operando: operando.c operando.h acao.h celula.h
	gcc -o operando operando.c

pilha: pilha.c
	gcc -o pilha pilha.c

robo: robo.c maq.c pilha.c operando.c arena.c
	gcc -o robo robo.c maq.c pilha.c operando.c arena.c

clean:
	rm -f arena maq motor operando pilha
