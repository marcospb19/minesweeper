/* mapa.h */
#pragma once
#define BOMBA '@'

// Pega na minha pomba
char** constroi_campo(int linhas , int colunas , int quantidade_de_bombas);

// Pega na minha pomba
int pegar_quantidade_de_bombas_adjacentes(char** mapa , int i , int j);

// Pega na minha pomba
char** criar_mascara(int linhas , int colunas);

// Pega na minha pomba
void liberar_mapa(char** mapa , int linhas);

// Pega na minha pomba
void mostrar_mapa(WINDOW* tela , char** mapa , int linhas);
