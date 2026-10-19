/*
 * ============================================================================
 *  NEXUS - Estruturas de estado do jogo
 * ============================================================================
 *
 *  As variaveis que precisam durar de uma volta do game loop para a outra
 *  ficam agrupadas em structs:
 *    - EstadoJogo:      dados da partida (jogador, progresso da fase)
 *    - EstadoInterface: controle das telas e mensagens
 *    - Jogo:            reune os dois estados em uma unica variavel
 *
 *  Variaveis temporarias (tecla lida, contadores de laco, calculos do mapa)
 *  continuam como variaveis locais em nexus.c.
 * ============================================================================
 */

#ifndef JOGO_H
#define JOGO_H

/* ----------------------------------------------------------------------------
 * ESTADO DA PARTIDA
 * Tudo o que e zerado quando a fase reinicia.
 * -------------------------------------------------------------------------- */
typedef struct {
    /* ---------------- Jogador ---------------- */
    int jogadorLinha;           /* posicao atual no mapa           */
    int jogadorColuna;
    int pontos;                 /* pontuacao acumulada             */
    int faseAtual;              /* fase em que o jogador esta      */
    int chaveDaVerdade;         /* 1 = chave obtida, 0 = nao       */
    int chaveDaPrivacidade;     /* fase 2 (proximas etapas)        */
    int chaveDaJustica;         /* fase 3 (proximas etapas)        */

    /* ---------------- Progresso da Fase 1 ---------------- */
    int pistaEncontrada;        /* jogador ja leu a pista?         */
    int etapaComputador1;       /* 0 = julgar p, 1 = julgar ~p     */
    int linhaTabela;            /* linha atual da tabela no C2     */
    int computador1Resolvido;
    int computador2Resolvido;
    int portaAberta;            /* porta D: C1 E C2 resolvidos     */
    int respostasIncorretas;    /* usado no resumo da fase         */

    /* ---------------- Movimento pendente ----------------
     * Definido ao ler W/A/S/D e aplicado no proximo desenho do mapa. */
    int destinoLinha;           /* para onde o jogador quer ir     */
    int destinoColuna;
    int tentouMover;            /* ultima tecla foi W, A, S ou D?  */
} EstadoJogo;

/* ----------------------------------------------------------------------------
 * ESTADO DA INTERFACE
 * Controla qual tela aparece e o que e mostrado no rodape.
 * -------------------------------------------------------------------------- */
typedef struct {
    int telaAtual;              /* tela exibida neste momento      */
    int origemConfirmacao;      /* de onde veio o pedido de saida  */
    int reiniciarJogo;          /* 1 = zerar o progresso da fase   */
    int mensagem;               /* mensagem do rodape              */
} EstadoInterface;

/* ----------------------------------------------------------------------------
 * JOGO COMPLETO
 * -------------------------------------------------------------------------- */
typedef struct {
    EstadoJogo partida;
    EstadoInterface ui;
} Jogo;

#endif /* JOGO_H */
