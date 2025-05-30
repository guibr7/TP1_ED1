all: tp.o jogo.o
	@gcc tp.o jogo.o -o exe
tp.o: tp.c
		@gcc tp.c -c
jogo.o: jogo.c
	@gcc jogo.c -c
run:
	@./exe
val:
	@gcc -g -o exeval jogo.c tp.c -Wall
valrun: val
	@valgrind --leak-check=full --track-origins=yes -s ./exeval

