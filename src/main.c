#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include "jogo.h"


void start_ncurses()
{
	initscr();
	noecho();
	refresh();
	keypad(stdscr , true);
}

void exit_function()
{
	endwin();
}

int main()
{
	char input;
	printf("Bem vindo ao campo minado\n\n");

	while (true)
	{
		printf("Selecione o tamanho do tabuleiro:\n"
		       " 1 -  9x9  - terá 10 minas\n"
		       " 2 - 16x16 - terá 40 minas\n"
		       " 3 - 16x30 - terá 99 minas\n"
		       "\n"
		       " -> ");
		scanf(" %c" , &input);

		// Quando der certo, saia desse loop infernal
		if ('1' <= input && input <= '3')
			break;

		printf("Amigo opcão invalida\n");
	}

	int linhas , colunas , quantidade_de_bombas;

	if (input == '1')
	{
		linhas = colunas = 9;
		quantidade_de_bombas = 10;
	}
	else if (input == '2')
	{
		linhas = colunas = 16;
		quantidade_de_bombas = 40;
	}
	else
	{
		linhas  = 16;
		colunas = 30;
		quantidade_de_bombas = 99;
	}

	start_ncurses();
	atexit(exit_function);

	comecar_jogo(linhas + 2 , colunas + 2 , quantidade_de_bombas);

	endwin(); // Finalizando ncurses
	return 0;
}
