src = $(wildcard *.c)
obj = $(src:.c=.o)

compila: compila.tab.o lex.yy.o $(obj)
	gcc -o $@ $^ -lm -lfl

compila.tab.o: compila.y
	bison -d compila.y
	gcc -c compila.tab.c

lex.yy.o: compila.l
	flex compila.l
	gcc -c lex.yy.c

clean:
	rm -f *.o lex.yy.c compila.tab.c compila.tab.h *~ compila
