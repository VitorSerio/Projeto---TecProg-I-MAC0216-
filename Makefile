prog?=prog

testes: main.o arena.o exercito.o robo.o maq.o pilha.o operando.o
	gcc -o $@ $^

motor: montador.py $(prog) arena.o exercito.o robo.o maq.o pilha.o operando.o
	python3.6 montador.py < $(prog) > motor.c
	gcc -o motor motor.c arena.o exercito.o robo.o maq.o pilha.o operando.o

clean:
	rm -f testes motor* *.o
