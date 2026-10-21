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
 *  continuam como variaveis locais.
 *
 *  Tambem ficam aqui as constantes de telas, mensagens e regras da fase,
 *  usadas por nexus.c e terminal.c.
 * ============================================================================
 */

#ifndef JOGO_H
#define JOGO_H

/* ----------------------------------------------------------------------------
 * TELAS DO JOGO
 * O jogo e uma "maquina de estados": telaAtual guarda em qual tela o jogador
 * esta. Cada tela tem um numero (constante) diferente.
 * -------------------------------------------------------------------------- */
#define TELA_MENU             0   /* menu inicial (US01)                      */
#define TELA_INSTRUCOES       1   /* lista de comandos (US02)                 */
#define TELA_MAPA             2   /* exploracao do mapa (US03 e US04)         */
#define TELA_PISTA            3   /* leitura da pista (US05)                  */
#define TELA_COMPUTADOR1      4   /* afirmacoes da IA (US06)                  */
#define TELA_COMPUTADOR2      5   /* filtro de confianca (US07)               */
#define TELA_INVENTARIO       6   /* chaves e progresso (tecla I)             */
#define TELA_CHAVE            7   /* Chave da Verdade obtida (US07)           */
#define TELA_FIM_FASE         8   /* resumo e "jogar novamente?"              */
#define TELA_CONFIRMAR_SAIDA  9   /* confirmacao antes de sair                */
#define TELA_ENCERRAR         10  /* encerra o game loop                      */

/* ----------------------------------------------------------------------------
 * MENSAGENS DE RETORNO (exibidas no rodape, apos uma acao)
 * -------------------------------------------------------------------------- */
#define MSG_NENHUMA         0
#define MSG_PAREDE          1
#define MSG_NADA_PROXIMO    2
#define MSG_C1_BLOQUEADO    3
#define MSG_C2_BLOQUEADO    4
#define MSG_PORTA_TRANCADA  5
#define MSG_SALVAR          6
#define MSG_ACERTO          7
#define MSG_ERRO_P          8
#define MSG_ERRO_NAO_P      9
#define MSG_ERRO_TABELA     10
#define MSG_PORTA_ABERTA    11

/* ----------------------------------------------------------------------------
 * PONTUACAO E REGRAS DA FASE
 * -------------------------------------------------------------------------- */
#define PONTOS_PISTA       10
#define PONTOS_COMPUTADOR  20
#define PONTOS_CHAVE       30
#define PONTUACAO_MAXIMA   (PONTOS_PISTA + 2 * PONTOS_COMPUTADOR + PONTOS_CHAVE)
#define ETAPAS_C1          2   /* C1: julgar p e depois ~p                  */
#define VALOR_P_C1         0   /* C1: p = "servidor ligado"; a pista diz que
                                * foi desligado, entao p e F (0)           */
#define LINHAS_TABELA      4   /* C2: 4 linhas da tabela-verdade de p ^ q   */
#define TOTAL_CHAVES       3
#define FASE_INICIAL       1

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

/* ----------------------------------------------------------------------------
 * FLUXO E REGRAS DO JOGO (jogo.c)
 * -------------------------------------------------------------------------- */

/* Estado ao abrir o programa: menu inicial, partida zerada. */
void iniciarJogo(Jogo *jogo);

/* Zera o progresso da fase se "Iniciar jogo" ou "Jogar novamente"
 * foram escolhidos na volta anterior do game loop. */
void reiniciarSePedido(Jogo *jogo);

/* Aplica o movimento pendente (W/A/S/D) se a tela atual e o mapa:
 * move o jogador ou avisa que o caminho esta bloqueado. */
void aplicarMovimento(Jogo *jogo);

/* Processa uma tecla ja validada para a tela atual: regras, pontuacao,
 * desafios e transicao para a proxima tela. */
void processarTecla(Jogo *jogo, char tecla);

#endif /* JOGO_H */
