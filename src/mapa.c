#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"

void mostrar_mapa(WINDOW* tela , char** mapa , int linhas)
{
	for (int i = 1; i < linhas - 1; ++i)
		mvwprintw(tela , i , 1 , *(&mapa[i]) + 1);

	wrefresh(tela);
}

void liberar_mapa(char** mapa , int linhas)
{
	for (int i = 0; i < linhas; ++i)
		free(mapa[i]);
	free(mapa);
}

char** criar_mapa(int linhas , int colunas)
{
	char** mapa = malloc(sizeof(char*[linhas]));

	for (int i = 0; i < linhas; ++i)
	{
		mapa[i] = malloc(sizeof(char[colunas]) + 1);

		for (int j = 0; j < colunas; ++j)
			mapa[i][j] = ' '; // N SEI PQ É NECESSÁRIO!!!!!

		mapa[i][colunas] = '\0';
		mapa[i][colunas - 1] = '\0';
	}

	return mapa;
}

char** criar_mascara(int linhas , int colunas)
{
	char** campo_mascara = criar_mapa(linhas , colunas);

	for (int i = 1; i < linhas - 1; ++i)
		for (int j = 1; j < colunas - 1; ++j)
			campo_mascara[i][j] = '*';

	return campo_mascara;
}

void preencher_bombas(char** mapa , int linhas , int colunas , int quantidade_de_bombas)
{
	// Preencher o mapa com as bombas
	// srand(time(NULL));
	int y , x;

	int bombas_criadas = 0;
	while (bombas_criadas < quantidade_de_bombas)
	{
		y = 1 + rand() % (linhas  - 2);
		x = 1 + rand() % (colunas - 2);

		if (mapa[y][x] == BOMBA)
			continue;

		mapa[y][x] = BOMBA;
		bombas_criadas++;
	}
}

int pegar_quantidade_de_bombas_adjacentes(char** mapa , int i , int j)
{
	return (mapa[i  ][j+1] == BOMBA) +
		   (mapa[i  ][j-1] == BOMBA) +
		   (mapa[i+1][j  ] == BOMBA) +
		   (mapa[i+1][j+1] == BOMBA) +
		   (mapa[i+1][j-1] == BOMBA) +
		   (mapa[i-1][j  ] == BOMBA) +
		   (mapa[i-1][j+1] == BOMBA) +
		   (mapa[i-1][j-1] == BOMBA);
}

void preencher_numeros(char** mapa , int linhas , int colunas)
{
	// Pegar a quantidade de bombas adjacentes
	char quantidade_de_adjacentes;

	for (int i = 1; i < linhas - 1; ++i)
	{
		for (int j = 1; j < colunas - 1; ++j)
		{
			if (mapa[i][j] == BOMBA)
				continue;

			quantidade_de_adjacentes = pegar_quantidade_de_bombas_adjacentes(
				mapa , i , j);

			if (quantidade_de_adjacentes == 0)
				mapa[i][j] = ' ';
			else
				mapa[i][j] = '0' + quantidade_de_adjacentes;
		}
	}
}

// Constrói o mapa preenchido com as bombas
char** constroi_campo(int linhas , int colunas , int quantidade_de_bombas)
{
	char** mapa = criar_mapa(linhas , colunas);
	preencher_bombas(mapa , linhas , colunas , quantidade_de_bombas);
	preencher_numeros(mapa , linhas , colunas);
	return mapa;
}
