#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "mapa.h"


WINDOW* tela1;
WINDOW* tela2;

void limpar(char** campo , char** campo_do_jogador , int linhas , int colunas , int i , int j)
{
	if (campo[i][j] >= '1' && campo[i][j] <= '8' && campo_do_jogador[i][j] == '*')
	{
		campo_do_jogador[i][j] = campo[i][j];
		mvwprintw(tela2 , i , j , "%c" , campo[i][j]);
		return;
	}
	else if (campo[i][j] != ' ' || campo_do_jogador[i][j] == ' ')
		return;
	else
	{
		campo_do_jogador[i][j] = ' ';
		mvwprintw(tela2 , i , j , " ");
	}
	wrefresh(tela2);


	if (i < linhas - 1)
		limpar(campo , campo_do_jogador , linhas , colunas , i+1 , j);
	if (i > 1)
		limpar(campo , campo_do_jogador , linhas , colunas , i-1 , j);
	if (j < colunas - 1)
		limpar(campo , campo_do_jogador , linhas , colunas , i , j+1);
	if (j > 1)
		limpar(campo , campo_do_jogador , linhas , colunas , i , j-1);
}

void apertar(char** campo , char** campo_do_jogador , int linhas , int colunas , int i , int j)
{
	if (campo_do_jogador[i][j] != '*')
		return; // Fazer nada

	if (campo[i][j] == BOMBA)
	{
		mvprintw(0 , 0 , "Perdestes amigo!!!!");
		wattron(tela2 , A_REVERSE);
		mvwprintw(tela2 , i , j , "%c" , BOMBA);
		wrefresh(tela2);
		refresh();
		wrefresh(tela2);
		system("sleep 1");
		exit(0);
	}
	else
	{
		limpar(campo , campo_do_jogador , linhas , colunas , i , j);
	}
}

void rodar_jogo(char** campo , char** campo_do_jogador , int linhas , int colunas)
{
	int input;

	// Posicoes que o jogador vai controlar
	int y = linhas  / 2;
	int x = colunas / 2;

	while (true)
	{
		mostrar_mapa(tela1 , campo            , linhas);
		mostrar_mapa(tela2 , campo_do_jogador , linhas);
		wmove(tela2 , y , x);
		wrefresh(tela1);
		wrefresh(tela2);

		input = getch();
		if (input == 'q')
			break;

		mvwprintw(tela1 , y , x , "%c" , campo_do_jogador[y][x]);

		if (     input == KEY_UP    && y > 1) {
			y--;
		}
		else if (input == KEY_DOWN  && y < linhas - 2) {
			y++;
		}
		else if (input == KEY_LEFT  && x > 1) {
			x--;
		}
		else if (input == KEY_RIGHT && x < colunas - 2) {
			x++;
		}

		else if (input == ' ')
			apertar(campo , campo_do_jogador , linhas , colunas , y , x);

		// else if (input == 'f')
		// 	flag(campo , campo_do_jogador , y , x);
	}

// 		wattroff(tela1 , A_REVERSE);
// 		mvwprintw(tela1 , y , x , campo_do_jogador[y][x]);
	// }
}

void comecar_jogo(int linhas , int colunas , int quantidade_de_bombas)
{
	char** campo = constroi_campo(linhas , colunas , quantidade_de_bombas);
	char** campo_do_jogador = criar_mascara(linhas , colunas);

	int max_y , max_x;
	getmaxyx(stdscr , max_y , max_x);
	tela1 = newwin(linhas , colunas , (max_y-linhas)/2 , 4);
	// tela1 = newwin(linhas , colunas , (max_y-linhas)/2 , (max_x-colunas)/2);
	box(tela1 , 0 , 0);
	wrefresh(tela1);

	tela2 = newwin(linhas , colunas , (max_y-linhas)/2 , max_x/3 - 3);
	box(tela2 , 0 , 0);
	wrefresh(tela2);

	rodar_jogo(campo , campo_do_jogador , linhas , colunas);

	printw("Fechando o jogo.");
	refresh();
	system("sleep 0.5");

	liberar_mapa(campo , linhas);
	liberar_mapa(campo_do_jogador , linhas);
}
