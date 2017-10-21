all: arena

arena: arena.o exercito.o robo.o maq.o pilha.o operando.o
	gcc -o $@ $^

exercito: arena.o exercito.o robo.o maq.o pilha.o operando.o
	gcc -o $@ $^

robo: arena.o robo.o maq.o pilha.o operando.o
	gcc -o $@ $^

maq: arena.o maq.o pilha.o operando.o
	gcc -o $@ $^

pilha: pilha.o operando.o
	gcc -o $@ $^

operando: operando.o
	gcc -o $@ $^

motor: arena.o maq.o pilha.o operando.o
	gcc -o $@ $^

motor.c: montador prog
	python3.6 montador < prog > motor.c

clean:
	rm -f arena exercito robo maq pilha operando motor *.o
