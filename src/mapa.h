/*
 * ============================================================================
 *  NEXUS - Mapa da Fase 1 e objetos interativos
 * ============================================================================
 *
 *  Constantes do mapa e funcoes de consulta:
 *    - celulaDoMapa:          qual simbolo existe em uma posicao do mapa
 *    - procurarObjetoProximo: qual objeto o jogador alcanca com a tecla E
 * ============================================================================
 */

#ifndef MAPA_H
#define MAPA_H

#include "jogo.h"

/* ----------------------------------------------------------------------------
 * OBJETOS COM QUE O JOGADOR PODE INTERAGIR (tecla E)
 * -------------------------------------------------------------------------- */
#define OBJ_NENHUM       0
#define OBJ_PISTA        1
#define OBJ_COMPUTADOR1  2
#define OBJ_COMPUTADOR2  3
#define OBJ_PORTA        4
#define OBJ_CHAVE        5
#define TOTAL_OBJETOS    5

/* ----------------------------------------------------------------------------
 * MAPA DA FASE 1 (7 linhas x 24 colunas)
 * Em vez de guardar o mapa em uma matriz, cada posicao (linha, coluna) e
 * "calculada" por regras com if/else. Assim, o mesmo conjunto de regras
 * serve para desenhar o mapa E para testar colisoes.
 *
 *      # # # # # # # # # # # # # # # # # # # # # # # #
 *      # P . . . . . ? . . . . . . . # . . . . . . . #
 *      # . # # # # . . . . . . . . . # . . . K . . . #
 *      # . # . . . . . . . . . . . . D . . . . . . . #
 *      # . # . . . C 1 . . . . . . . # . . . . . . . #
 *      # . . . . . . . . C 2 . . . . # . . . . . . . #
 *      # # # # # # # # # # # # # # # # # # # # # # # #
 * -------------------------------------------------------------------------- */
#define ALTURA_MAPA       7
#define LARGURA_MAPA      24
#define COLUNA_DIVISORIA  15   /* parede que separa a sala da chave         */

#define INICIO_LINHA      1    /* posicao inicial do jogador                */
#define INICIO_COLUNA     1
#define PISTA_LINHA       1
#define PISTA_COLUNA      7
#define C1_LINHA          4    /* computador C1 ocupa 2 casas: 'C' e '1'    */
#define C1_COLUNA         6
#define C2_LINHA          5    /* computador C2 ocupa 2 casas: 'C' e '2'    */
#define C2_COLUNA         9
#define PORTA_LINHA       3
#define PORTA_COLUNA      COLUNA_DIVISORIA
#define CHAVE_LINHA       2
#define CHAVE_COLUNA      19

/* Simbolos do mapa */
#define JOGADOR       'P'
#define PAREDE        '#'
#define CHAO          '.'
#define PISTA         '?'
#define COMPUTADOR    'C'
#define CHAVE         'K'
#define PORTA         'D'
#define PORTA_ABERTA  '/'

/* Simbolo da posicao (linha, coluna), conforme o progresso da partida
 * (a pista e a chave somem depois de usadas; a porta pode estar aberta). */
char celulaDoMapa(const EstadoJogo *partida, int linha, int coluna);

/* Objeto ativo ao redor do jogador (OBJ_NENHUM se nao houver nenhum).
 * Objeto ao lado tem prioridade sobre objeto na diagonal (B1). */
int procurarObjetoProximo(const EstadoJogo *partida);

#endif /* MAPA_H */
