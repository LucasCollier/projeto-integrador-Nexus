/*
 * ============================================================================
 *  NEXUS - Interface e entrada do terminal (Windows)
 * ============================================================================
 *
 *  Funcoes de apresentacao e leitura de teclas:
 *    - desenharTela:     limpa o terminal e mostra a tela atual
 *    - lerTecla:         le e valida a tecla para a tela atual
 *    - mostrarDespedida: mensagem final ao sair do jogo
 *
 *  As funcoes recebem o jogo como const: a interface nao altera o estado.
 * ============================================================================
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "jogo.h"

/* Limpa a tela e desenha a tela atual, a mensagem do rodape (se houver)
 * e a lista de teclas aceitas. */
void desenharTela(const Jogo *jogo);

/* Espera uma tecla valida para a tela atual (avisando as invalidas na
 * mesma linha) e a devolve em maiuscula. */
char lerTecla(const Jogo *jogo);

/* Mensagem exibida ao encerrar o jogo. */
void mostrarDespedida(void);

#endif /* TERMINAL_H */
