#pragma once

// Começa o jogo, cria o cenário e faz o resto
void comecar_jogo(int linhas , int colunas , int quantidade_de_bombas);

void rodar_jogo(char** campo , char** campo_do_jogador , int linhas , int colunas);

void limpar(char** campo , char** campo_do_jogador , int linhas , int colunas , int i , int j);

void apertar(char** campo , char** campo_do_jogador , int linhas , int colunas , int i , int j);
