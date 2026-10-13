/*
 * ============================================================================
 *  NEXUS - Jogo educativo de aventura e exploracao no terminal
 *  Projeto Integrador - CESAR School
 *  Disciplina: Programacao Imperativa e Funcional (PIF)
 *  Etapa 1: nucleo imperativo em C  ->  Menu + Fase 1 (Central da Verdade)
 *  Plataforma: Windows (terminal: Prompt de Comando, PowerShell ou
 *              Windows Terminal)
 * ============================================================================
 *
 *  Conteudos de C usados:
 *    - Entrada e saida formatada (printf e leitura de teclas com _getch)
 *    - Variaveis, tipos de dados (int e char) e constantes (#define)
 *    - Operadores aritmeticos, relacionais, logicos, atribuicao composta,
 *      incremento e operador condicional ternario ( ? : )
 *    - Estruturas de repeticao: while e for
 *    - Estruturas de decisao: if / else
 *
 *  Organizacao do game loop (laco principal, repetido ate o jogador sair):
 *    (A) reinicia a fase, se pedido
 *    (B) desenha a tela atual
 *    (C) le e valida a tecla (sem precisar apertar ENTER)
 *    (D) processa a tecla e decide qual sera a proxima tela
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>   /* system("cls"): limpa a tela do terminal do Windows */
#include <conio.h>    /* _getch(): le uma tecla na hora, sem precisar de ENTER */

/* ----------------------------------------------------------------------------
 * LEITURA DE TECLAS (Windows)
 * Com scanf/getchar, o terminal so entrega o que foi digitado depois do
 * ENTER. A funcao _getch(), da biblioteca conio.h, le a tecla assim que ela
 * e apertada e nao a mostra na tela.
 * Setas e teclas F1..F12 enviam DOIS codigos: primeiro 0 ou 224, depois o
 * codigo da tecla. O jogo descarta esses dois codigos.
 * -------------------------------------------------------------------------- */
#define TECLA_ESPECIAL_1  0
#define TECLA_ESPECIAL_2  224

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

/* ----------------------------------------------------------------------------
 * PONTUACAO E REGRAS DA FASE
 * -------------------------------------------------------------------------- */
#define PONTOS_PISTA       10
#define PONTOS_COMPUTADOR  20
#define PONTOS_CHAVE       30
#define PONTUACAO_MAXIMA   (PONTOS_PISTA + 2 * PONTOS_COMPUTADOR + PONTOS_CHAVE)
#define ETAPAS_C1          2   /* C1: julgar p e depois ~p                  */
#define LINHAS_TABELA      4   /* C2: 4 linhas da tabela-verdade de p ^ q   */
#define TOTAL_CHAVES       3
#define FASE_INICIAL       1

/* Aparencia */
#define SEPARADOR   " ==================================================\n"
#define LINHA_FINA  " --------------------------------------------------\n"

int main(void) {
    /* ---------------- Estado do jogador ---------------- */
    int jogadorLinha = INICIO_LINHA;     /* posicao atual no mapa           */
    int jogadorColuna = INICIO_COLUNA;
    int pontos = 0;                      /* pontuacao acumulada             */
    int faseAtual = FASE_INICIAL;        /* fase em que o jogador esta      */
    int chaveDaVerdade = 0;              /* 1 = chave obtida, 0 = nao       */
    int chaveDaPrivacidade = 0;          /* fase 2 (proximas etapas)        */
    int chaveDaJustica = 0;              /* fase 3 (proximas etapas)        */

    /* ---------------- Progresso da Fase 1 ---------------- */
    int pistaEncontrada = 0;             /* jogador ja leu a pista?         */
    int computador1Resolvido = 0;
    int computador2Resolvido = 0;
    int portaAberta = 0;                 /* porta D: C1 E C2 resolvidos     */

    /* ---------------- Controle do jogo ---------------- */
    int telaAtual = TELA_MENU;           /* tela exibida neste momento      */
    int origemConfirmacao = TELA_MENU;   /* de onde veio o pedido de saida  */
    int reiniciarJogo = 0;               /* 1 = zerar o progresso da fase   */
    int mensagem = MSG_NENHUMA;          /* mensagem do rodape              */

    /* ---------------- Entrada do usuario ---------------- */
    int teclaLida;                       /* codigo lido por _getch()        */
    char tecla = ' ';                    /* tecla ja convertida p/ maiuscula */
    int entradaValida;
    int tentativasInvalidas;

    /* ---------------- Movimento e desenho do mapa ---------------- */
    int destinoLinha = INICIO_LINHA;     /* para onde o jogador quer ir     */
    int destinoColuna = INICIO_COLUNA;
    int tentouMover = 0;                 /* ultima tecla foi W, A, S ou D?  */
    int passo;                           /* 0 = checar colisao, 1 = desenhar */
    int linha, coluna;
    char celula;                         /* simbolo calculado da posicao    */
    char celulaDestino = CHAO;           /* simbolo na casa de destino      */

    /* ========================================================================
     * GAME LOOP: repete ate o jogador escolher sair
     * ====================================================================== */
    while (telaAtual != TELA_ENCERRAR) {

        /* ------------------------------------------------------------------
         * (A) REINICIO DA FASE
         * Um unico bloco zera o progresso. E usado tanto por "Iniciar jogo"
         * quanto por "Jogar novamente" (evita repetir codigo - DRY).
         * ---------------------------------------------------------------- */
        if (reiniciarJogo) {
            jogadorLinha = INICIO_LINHA;
            jogadorColuna = INICIO_COLUNA;
            destinoLinha = jogadorLinha;
            destinoColuna = jogadorColuna;
            pontos = 0;
            faseAtual = FASE_INICIAL;
            chaveDaVerdade = 0;
            pistaEncontrada = 0;
            computador1Resolvido = 0;
            computador2Resolvido = 0;
            portaAberta = 0;
            tentouMover = 0;
            mensagem = MSG_NENHUMA;
            reiniciarJogo = 0;
        }

        /* ------------------------------------------------------------------
         * (B) DESENHO DA TELA ATUAL
         * ---------------------------------------------------------------- */
        system("cls");   /* limpa a tela do terminal */

        /* Barra de status: aparece em todas as telas de jogo */
        if (telaAtual >= TELA_MAPA && telaAtual <= TELA_CHAVE) {
            printf(SEPARADOR);
            printf("  NEXUS | FASE %d - CENTRAL DA VERDADE\n", faseAtual);
            printf("  Pontos: %d | Chaves: %d/%d\n", pontos,
                   chaveDaVerdade + chaveDaPrivacidade + chaveDaJustica, TOTAL_CHAVES);
            printf(SEPARADOR);
        }

        if (telaAtual == TELA_MENU) {
            /* ---------- MENU INICIAL (US01) ---------- */
            printf(SEPARADOR);
            printf("     _   _  _____ __  __ _   _  ____  \n");
            printf("    | \\ | || ____|\\ \\/ /| | | |/ ___| \n");
            printf("    |  \\| ||  _|   \\  / | | | |\\___ \\ \n");
            printf("    | |\\  || |___  /  \\ | |_| | ___) |\n");
            printf("    |_| \\_||_____|/_/\\_\\ \\___/ |____/ \n");
            printf(SEPARADOR);
            printf("  Voce esta preso em um sistema digital controlado\n");
            printf("  por uma Inteligencia Artificial chamada NEXUS.\n");
            printf("  Corrija os erros do sistema e reuna as tres chaves\n");
            printf("  para escapar.\n\n");
            printf("    [1] INICIAR JOGO\n");
            printf("    [2] INSTRUCOES\n");
            printf("    [3] SAIR\n");

        } else if (telaAtual == TELA_INSTRUCOES) {
            /* ---------- INSTRUCOES (US02) ---------- */
            printf(SEPARADOR);
            printf("  INSTRUCOES\n");
            printf(SEPARADOR);
            printf("  Basta apertar a tecla (nao e preciso apertar ENTER).\n\n");
            printf("    W - Cima            S - Baixo\n");
            printf("    A - Esquerda        D - Direita\n");
            printf("    E - Interagir com um objeto proximo\n");
            printf("    I - Inventario\n");
            printf("    P - Salvar progresso\n");
            printf("    Q - Sair\n\n");
            printf("  Simbolos do mapa:\n");
            printf("    P jogador   # parede   . chao   ? pista\n");
            printf("    C computador   D porta   K chave\n\n");
            printf("  Objetivo: encontre a pista, investigue os computadores,\n");
            printf("  corrija o sistema e pegue a Chave da Verdade.\n\n");
            printf("  [Qualquer tecla] Voltar ao menu\n");

        } else if (telaAtual == TELA_MAPA) {
            /* ---------- MAPA (US03 e US04) ---------- */
            /* Objetivo atual: muda conforme o progresso do jogador */
            printf("  Objetivo: ");
            if (!pistaEncontrada) {
                printf("explore a sala e encontre a pista (?).\n\n");
            } else if (!computador1Resolvido) {
                printf("investigue o computador C1.\n\n");
            } else if (!computador2Resolvido) {
                printf("corrija o filtro do computador C2.\n\n");
            } else {
                printf("a porta D esta aberta! Pegue a chave K.\n\n");
            }

            /*
             * O mapa e percorrido DUAS vezes com as MESMAS regras (DRY):
             *   passo 0 -> descobre o simbolo da casa de destino e move o
             *              jogador se ela estiver livre (colisao);
             *   passo 1 -> desenha o mapa na tela.
             */
            for (passo = 0; passo < 2; passo++) {
                for (linha = 0; linha < ALTURA_MAPA; linha++) {
                    if (passo == 1) {
                        printf("   ");
                    }
                    for (coluna = 0; coluna < LARGURA_MAPA; coluna++) {
                        /* Regras do mapa: qual simbolo existe nesta posicao? */
                        if (linha == 0 || linha == ALTURA_MAPA - 1 ||
                            coluna == 0 || coluna == LARGURA_MAPA - 1) {
                            celula = PAREDE;                      /* bordas */
                        } else if ((linha == 2 && coluna >= 2 && coluna <= 5) ||
                                   (coluna == 2 && linha >= 3 && linha <= 4)) {
                            celula = PAREDE;                      /* paredes internas */
                        } else if (linha == PORTA_LINHA && coluna == PORTA_COLUNA) {
                            celula = portaAberta ? PORTA_ABERTA : PORTA;
                        } else if (coluna == COLUNA_DIVISORIA) {
                            celula = PAREDE;
                        } else if (linha == PISTA_LINHA && coluna == PISTA_COLUNA && !pistaEncontrada) {
                            celula = PISTA;                       /* some depois de lida */
                        } else if (linha == C1_LINHA && coluna == C1_COLUNA) {
                            celula = COMPUTADOR;
                        } else if (linha == C1_LINHA && coluna == C1_COLUNA + 1) {
                            celula = '1';
                        } else if (linha == C2_LINHA && coluna == C2_COLUNA) {
                            celula = COMPUTADOR;
                        } else if (linha == C2_LINHA && coluna == C2_COLUNA + 1) {
                            celula = '2';
                        } else if (linha == CHAVE_LINHA && coluna == CHAVE_COLUNA && !chaveDaVerdade) {
                            celula = CHAVE;                       /* some depois de coletada */
                        } else {
                            celula = CHAO;
                        }

                        if (passo == 0) {
                            /* guarda o simbolo da casa para onde o jogador quer ir */
                            if (linha == destinoLinha && coluna == destinoColuna) {
                                celulaDestino = celula;
                            }
                        } else {
                            /* desenha (o jogador aparece por cima do chao) */
                            if (linha == jogadorLinha && coluna == jogadorColuna) {
                                printf("%c ", JOGADOR);
                            } else {
                                printf("%c ", celula);
                            }
                        }
                    }
                    if (passo == 1) {
                        printf("\n");
                    }
                }

                /* Fim do passo 0: aplica o movimento (nao atravessa obstaculos) */
                if (passo == 0 && tentouMover) {
                    if (celulaDestino == CHAO || celulaDestino == PORTA_ABERTA) {
                        jogadorLinha = destinoLinha;
                        jogadorColuna = destinoColuna;
                    } else {
                        mensagem = MSG_PAREDE;
                    }
                    tentouMover = 0;
                }
            }

            printf("\n  P voce  # parede  ? pista  C computador  D porta  K chave\n");
            printf(LINHA_FINA);
            printf("  [W A S D] mover  [P] salvar  [Q] sair\n");

        } else if (telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* ---------- CONFIRMAR SAIDA ---------- */
            if (origemConfirmacao == TELA_MENU) {
                printf("\n  Deseja realmente sair do NEXUS?\n\n");
            } else {
                printf("\n  Deseja voltar ao menu? O progresso da fase sera perdido.\n\n");
            }
            printf("    [S] Sim    [N] Nao\n");
        }

        /* Mensagem do rodape: resultado da ultima acao */
        if (mensagem != MSG_NENHUMA) {
            printf("\n  >> ");
            if (mensagem == MSG_PAREDE) {
                printf("Caminho bloqueado! Voce nao pode atravessar obstaculos.\n");
            } else if (mensagem == MSG_NADA_PROXIMO) {
                printf("Nada para interagir aqui. Chegue perto de ?, C, D ou K.\n");
            } else if (mensagem == MSG_C1_BLOQUEADO) {
                printf("O computador C1 esta bloqueado. Encontre a pista (?) primeiro.\n");
            } else if (mensagem == MSG_C2_BLOQUEADO) {
                printf("Acesso negado ao C2. Primeiro corrija as afirmacoes do C1.\n");
            } else if (mensagem == MSG_PORTA_TRANCADA) {
                printf("Porta D trancada: ela so abre se C1 E C2 estiverem corrigidos.\n");
            } else if (mensagem == MSG_SALVAR) {
                printf("O salvamento em arquivo sera implementado na proxima etapa.\n");
            } else if (mensagem == MSG_ACERTO) {
                printf("Correto!\n");
            } else if (mensagem == MSG_ERRO_P) {
                printf("Incorreto. A pista diz que o servidor foi DESLIGADO, entao p e Falsa.\n");
            } else if (mensagem == MSG_ERRO_NAO_P) {
                printf("Incorreto. A negacao inverte o valor: se p = F, entao ~p = V.\n");
            } else if (mensagem == MSG_ERRO_TABELA) {
                printf("Incorreto. p ^ q so e V quando p E q sao V ao mesmo tempo.\n");
            } else {
                printf("Correto! A porta D foi DESTRANCADA.\n");
            }
            mensagem = MSG_NENHUMA;   /* cada mensagem aparece uma unica vez */
        }

        /* ------------------------------------------------------------------
         * (C) LEITURA E VALIDACAO DA TECLA (sem ENTER)
         * O laco while so termina quando a tecla for valida para a tela
         * atual. Teclas erradas nunca travam nem encerram o programa.
         * ---------------------------------------------------------------- */
        printf("\n  Teclas aceitas: ");
        if (telaAtual == TELA_MENU || telaAtual == TELA_FIM_FASE) {
            printf("1, 2 ou 3\n");
        } else if (telaAtual == TELA_INSTRUCOES) {
            printf("qualquer tecla\n");
        } else if (telaAtual == TELA_MAPA) {
            printf("W, A, S, D, P ou Q\n");
        } else if (telaAtual == TELA_PISTA || telaAtual == TELA_CHAVE) {
            printf("E\n");
        } else if (telaAtual == TELA_COMPUTADOR1) {
            printf("%s\n", computador1Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (telaAtual == TELA_COMPUTADOR2) {
            printf("%s\n", computador2Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (telaAtual == TELA_INVENTARIO) {
            printf("I ou Q\n");
        } else {
            printf("S ou N\n");
        }

        entradaValida = 0;
        tentativasInvalidas = 0;
        while (!entradaValida) {
            teclaLida = _getch();          /* le a tecla sem esperar ENTER */

            /* Setas e teclas de funcao enviam dois codigos: descarta os dois */
            if (teclaLida == TECLA_ESPECIAL_1 || teclaLida == TECLA_ESPECIAL_2) {
                teclaLida = _getch();
                teclaLida = ' ';
            }

            tecla = (char) teclaLida;

            /* converte minuscula em maiuscula: 'w' -> 'W' */
            if (tecla >= 'a' && tecla <= 'z') {
                tecla = tecla - ('a' - 'A');
            }

            /* A tecla e valida para a tela atual? */
            if (tecla == ' ' || tecla == '\n' || tecla == '\r' || tecla == '\t') {
                entradaValida = 0;           /* espacos, ENTER e setas sao ignorados */
            } else if (telaAtual == TELA_MENU || telaAtual == TELA_FIM_FASE) {
                entradaValida = (tecla >= '1' && tecla <= '3');
            } else if (telaAtual == TELA_INSTRUCOES) {
                entradaValida = 1;
            } else if (telaAtual == TELA_MAPA) {
                entradaValida = (tecla == 'W' || tecla == 'A' || tecla == 'S' ||
                                 tecla == 'D' || tecla == 'P' || tecla == 'Q');
            } else if (telaAtual == TELA_PISTA || telaAtual == TELA_CHAVE) {
                entradaValida = (tecla == 'E');
            } else if (telaAtual == TELA_COMPUTADOR1) {
                if (computador1Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (telaAtual == TELA_COMPUTADOR2) {
                if (computador2Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (telaAtual == TELA_INVENTARIO) {
                entradaValida = (tecla == 'I' || tecla == 'Q');
            } else {
                entradaValida = (tecla == 'S' || tecla == 'N');
            }

            /* Aviso para teclas invalidas (espacos, ENTER e setas nao contam) */
            if (!entradaValida && tecla != ' ' && tecla != '\n' &&
                tecla != '\r' && tecla != '\t') {
                tentativasInvalidas++;
                printf("  Tecla '%c' invalida! Tente novamente. (avisos: %d)\n",
                       tecla, tentativasInvalidas);
            }
        }

        /* ------------------------------------------------------------------
         * (D) PROCESSAMENTO DA TECLA
         * Usamos if / else if: apenas o bloco da tela atual e executado.
         * ---------------------------------------------------------------- */
        if (telaAtual == TELA_MENU) {
            /* 1 = iniciar, 2 = instrucoes, 3 = sair (com confirmacao) */
            if (tecla == '1') {
                reiniciarJogo = 1;
                telaAtual = TELA_MAPA;
            } else if (tecla == '2') {
                telaAtual = TELA_INSTRUCOES;
            } else {
                origemConfirmacao = TELA_MENU;
                telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (telaAtual == TELA_INSTRUCOES) {
            telaAtual = TELA_MENU;               /* qualquer tecla volta */

        } else if (telaAtual == TELA_MAPA) {
            if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
                /* Movimento: (tecla == 'S') vale 1 se verdadeiro e 0 se falso.
                 * A colisao e verificada no passo 0 do desenho do mapa. */
                destinoLinha = jogadorLinha + (tecla == 'S') - (tecla == 'W');
                destinoColuna = jogadorColuna + (tecla == 'D') - (tecla == 'A');
                tentouMover = 1;

            } else if (tecla == 'P') {
                mensagem = MSG_SALVAR;
            } else {                              /* Q */
                origemConfirmacao = TELA_MAPA;
                telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* S confirma; N volta para a tela de origem */
            if (tecla == 'N') {
                telaAtual = origemConfirmacao;
            } else if (origemConfirmacao == TELA_MENU) {
                telaAtual = TELA_ENCERRAR;
            } else {
                telaAtual = TELA_MENU;
            }
        }
    }

    printf("\n  Obrigado por jogar NEXUS! Ate a proxima.\n\n");
    return 0;
}
