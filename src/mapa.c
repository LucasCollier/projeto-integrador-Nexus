/*
 * ============================================================================
 *  NEXUS - Mapa da Fase 1 e objetos interativos
 * ============================================================================
 */

#include "mapa.h"

/* ----------------------------------------------------------------------------
 * Regras do mapa: qual simbolo existe nesta posicao?
 * Usada tanto para desenhar o mapa quanto para testar colisoes (DRY).
 * -------------------------------------------------------------------------- */
char celulaDoMapa(const EstadoJogo *partida, int linha, int coluna) {
    char celula;

    if (linha == 0 || linha == ALTURA_MAPA - 1 ||
        coluna == 0 || coluna == LARGURA_MAPA - 1) {
        celula = PAREDE;                      /* bordas */
    } else if ((linha == 2 && coluna >= 2 && coluna <= 5) ||
               (coluna == 2 && linha >= 3 && linha <= 4)) {
        celula = PAREDE;                      /* paredes internas */
    } else if (linha == PORTA_LINHA && coluna == PORTA_COLUNA) {
        celula = partida->portaAberta ? PORTA_ABERTA : PORTA;
    } else if (coluna == COLUNA_DIVISORIA) {
        celula = PAREDE;
    } else if (linha == PISTA_LINHA && coluna == PISTA_COLUNA && !partida->pistaEncontrada) {
        celula = PISTA;                       /* some depois de lida */
    } else if (linha == C1_LINHA && coluna == C1_COLUNA) {
        celula = COMPUTADOR;
    } else if (linha == C1_LINHA && coluna == C1_COLUNA + 1) {
        celula = '1';
    } else if (linha == C2_LINHA && coluna == C2_COLUNA) {
        celula = COMPUTADOR;
    } else if (linha == C2_LINHA && coluna == C2_COLUNA + 1) {
        celula = '2';
    } else if (linha == CHAVE_LINHA && coluna == CHAVE_COLUNA && !partida->chaveDaVerdade) {
        celula = CHAVE;                       /* some depois de coletada */
    } else {
        celula = CHAO;
    }

    return celula;
}

/* ----------------------------------------------------------------------------
 * Interacao: procura um objeto ativo ao redor do jogador.
 * Um unico laco testa todos os objetos (DRY).
 * -------------------------------------------------------------------------- */
int procurarObjetoProximo(const EstadoJogo *partida) {
    int objeto, objetoProximo;
    int objetoLinha, objetoColuna, objetoLargura;
    int objetoAtivo, pertoDoObjeto;
    int objetoAoLado, aoLadoDoObjeto;    /* ao lado tem prioridade (B1)     */

    objetoProximo = OBJ_NENHUM;
    objetoAoLado = OBJ_NENHUM;
    for (objeto = 1; objeto <= TOTAL_OBJETOS; objeto++) {
        objetoLargura = 1;
        objetoAtivo = 1;
        if (objeto == OBJ_PISTA) {
            objetoLinha = PISTA_LINHA;
            objetoColuna = PISTA_COLUNA;
            objetoAtivo = !partida->pistaEncontrada;
        } else if (objeto == OBJ_COMPUTADOR1) {
            objetoLinha = C1_LINHA;
            objetoColuna = C1_COLUNA;
            objetoLargura = 2;
        } else if (objeto == OBJ_COMPUTADOR2) {
            objetoLinha = C2_LINHA;
            objetoColuna = C2_COLUNA;
            objetoLargura = 2;
        } else if (objeto == OBJ_PORTA) {
            objetoLinha = PORTA_LINHA;
            objetoColuna = PORTA_COLUNA;
            objetoAtivo = !partida->portaAberta;
        } else {
            objetoLinha = CHAVE_LINHA;
            objetoColuna = CHAVE_COLUNA;
            objetoAtivo = partida->portaAberta && !partida->chaveDaVerdade;
        }

        /* "perto" = em qualquer casa vizinha (inclui diagonais) */
        pertoDoObjeto = partida->jogadorLinha >= objetoLinha - 1 &&
                        partida->jogadorLinha <= objetoLinha + 1 &&
                        partida->jogadorColuna >= objetoColuna - 1 &&
                        partida->jogadorColuna <= objetoColuna + objetoLargura;

        /* "ao lado" = vizinho na mesma linha ou na mesma coluna do objeto */
        aoLadoDoObjeto = pertoDoObjeto &&
                         (partida->jogadorLinha == objetoLinha ||
                          (partida->jogadorColuna >= objetoColuna &&
                           partida->jogadorColuna < objetoColuna + objetoLargura));

        if (objetoAoLado == OBJ_NENHUM && objetoAtivo && aoLadoDoObjeto) {
            objetoAoLado = objeto;
        } else if (objetoProximo == OBJ_NENHUM && objetoAtivo && pertoDoObjeto) {
            objetoProximo = objeto;
        }
    }

    /* Objeto ao lado tem prioridade sobre objeto na diagonal:
     * em (5,8) o jogador esta colado ao C2 e na diagonal do C1. */
    if (objetoAoLado != OBJ_NENHUM) {
        objetoProximo = objetoAoLado;
    }

    return objetoProximo;
}
