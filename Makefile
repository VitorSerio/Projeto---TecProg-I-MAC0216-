src = $(wildcard *.c)
obj = $(src:.c=.o)

testes: $(obj)
	gcc -o $@ $(obj)

motor: montador.py motor.c $(obj)
	gcc -o $@ motor.c $(obj)
	rm -f motor.c

motor.c: montador.py
	python3.6 montador.py < $(prog) > motor.c

clean:
	rm -f testes motor* *.o
