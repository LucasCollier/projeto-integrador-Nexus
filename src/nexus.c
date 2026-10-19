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
 *    - Structs (typedef struct) e ponteiros para structs (operador ->)
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
#include "jogo.h"     /* structs com o estado da partida e da interface */
#include "mapa.h"     /* mapa da Fase 1 e objetos interativos */

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
    /* ---------------- Estado do jogo (structs de jogo.h) ---------------- */
    Jogo jogo;
    EstadoJogo *partida = &jogo.partida;     /* atalho: partida->pontos   */
    EstadoInterface *ui = &jogo.ui;          /* atalho: ui->telaAtual     */

    /* Estado do jogador */
    partida->jogadorLinha = INICIO_LINHA;
    partida->jogadorColuna = INICIO_COLUNA;
    partida->pontos = 0;
    partida->faseAtual = FASE_INICIAL;
    partida->chaveDaVerdade = 0;
    partida->chaveDaPrivacidade = 0;
    partida->chaveDaJustica = 0;

    /* Progresso da Fase 1 */
    partida->pistaEncontrada = 0;
    partida->etapaComputador1 = 0;
    partida->linhaTabela = 0;
    partida->computador1Resolvido = 0;
    partida->computador2Resolvido = 0;
    partida->portaAberta = 0;
    partida->respostasIncorretas = 0;

    /* Movimento pendente */
    partida->destinoLinha = INICIO_LINHA;
    partida->destinoColuna = INICIO_COLUNA;
    partida->tentouMover = 0;

    /* Controle das telas */
    ui->telaAtual = TELA_MENU;
    ui->origemConfirmacao = TELA_MENU;
    ui->reiniciarJogo = 0;
    ui->mensagem = MSG_NENHUMA;

    /* ---------------- Entrada do usuario ---------------- */
    int teclaLida;                       /* codigo lido por _getch()        */
    char tecla = ' ';                    /* tecla ja convertida p/ maiuscula */
    int entradaValida;
    int tentativasInvalidas;

    /* ---------------- Desenho do mapa ---------------- */
    int passo;                           /* 0 = checar colisao, 1 = desenhar */
    int linha, coluna;
    char celula;                         /* simbolo calculado da posicao    */
    char celulaDestino = CHAO;           /* simbolo na casa de destino      */

    /* ---------------- Interacao e computadores ---------------- */
    int objetoProximo;                   /* objeto alcancado com a tecla E  */
    char respostaEsperada;
    int linhaExibida, valorP, valorQ;    /* linhas da tabela-verdade        */

    /* ========================================================================
     * GAME LOOP: repete ate o jogador escolher sair
     * ====================================================================== */
    while (ui->telaAtual != TELA_ENCERRAR) {

        /* ------------------------------------------------------------------
         * (A) REINICIO DA FASE
         * Um unico bloco zera o progresso. E usado tanto por "Iniciar jogo"
         * quanto por "Jogar novamente" (evita repetir codigo - DRY).
         * ---------------------------------------------------------------- */
        if (ui->reiniciarJogo) {
            partida->jogadorLinha = INICIO_LINHA;
            partida->jogadorColuna = INICIO_COLUNA;
            partida->destinoLinha = partida->jogadorLinha;
            partida->destinoColuna = partida->jogadorColuna;
            partida->pontos = 0;
            partida->faseAtual = FASE_INICIAL;
            partida->chaveDaVerdade = 0;
            partida->pistaEncontrada = 0;
            partida->etapaComputador1 = 0;
            partida->linhaTabela = 0;
            partida->computador1Resolvido = 0;
            partida->computador2Resolvido = 0;
            partida->portaAberta = 0;
            partida->respostasIncorretas = 0;
            partida->tentouMover = 0;
            ui->mensagem = MSG_NENHUMA;
            ui->reiniciarJogo = 0;
        }

        /* ------------------------------------------------------------------
         * (B) DESENHO DA TELA ATUAL
         * ---------------------------------------------------------------- */
        system("cls");   /* limpa a tela do terminal */

        /* Barra de status: aparece em todas as telas de jogo */
        if (ui->telaAtual >= TELA_MAPA && ui->telaAtual <= TELA_CHAVE) {
            printf(SEPARADOR);
            printf("  NEXUS | FASE %d - CENTRAL DA VERDADE\n", partida->faseAtual);
            printf("  Pontos: %d | Chaves: %d/%d\n", partida->pontos,
                   partida->chaveDaVerdade + partida->chaveDaPrivacidade + partida->chaveDaJustica, TOTAL_CHAVES);
            printf(SEPARADOR);
        }

        if (ui->telaAtual == TELA_MENU) {
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

        } else if (ui->telaAtual == TELA_INSTRUCOES) {
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

        } else if (ui->telaAtual == TELA_MAPA) {
            /* ---------- MAPA (US03 e US04) ---------- */
            /* Objetivo atual: muda conforme o progresso do jogador */
            printf("  Objetivo: ");
            if (!partida->pistaEncontrada) {
                printf("explore a sala e encontre a pista (?).\n\n");
            } else if (!partida->computador1Resolvido) {
                printf("investigue o computador C1.\n\n");
            } else if (!partida->computador2Resolvido) {
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
                        celula = celulaDoMapa(partida, linha, coluna);

                        if (passo == 0) {
                            /* guarda o simbolo da casa para onde o jogador quer ir */
                            if (linha == partida->destinoLinha && coluna == partida->destinoColuna) {
                                celulaDestino = celula;
                            }
                        } else {
                            /* desenha (o jogador aparece por cima do chao) */
                            if (linha == partida->jogadorLinha && coluna == partida->jogadorColuna) {
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
                if (passo == 0 && partida->tentouMover) {
                    if (celulaDestino == CHAO || celulaDestino == PORTA_ABERTA) {
                        partida->jogadorLinha = partida->destinoLinha;
                        partida->jogadorColuna = partida->destinoColuna;
                    } else {
                        ui->mensagem = MSG_PAREDE;
                    }
                    partida->tentouMover = 0;
                }
            }

            printf("\n  P voce  # parede  ? pista  C computador  D porta  K chave\n");
            printf(LINHA_FINA);
            printf("  [W A S D] mover  [E] interagir  [I] inventario\n");
            printf("  [P] salvar       [Q] sair\n");

        } else if (ui->telaAtual == TELA_PISTA) {
            /* ---------- PISTA (US05) ---------- */
            printf("  PISTA ENCONTRADA!  (+%d pontos)\n\n", PONTOS_PISTA);
            printf("  Um bilhete do tecnico de plantao diz:\n\n");
            printf("     \"O servidor principal foi desligado as 22h.\"\n\n");
            printf("  Guarde essa informacao: a IA NEXUS pode afirmar o\n");
            printf("  contrario. Quando uma IA afirma algo falso como se\n");
            printf("  fosse verdade, chamamos isso de ALUCINACAO.\n\n");
            printf("  Investigue o computador C1.\n\n");
            printf("  [E] Continuar\n");

        } else if (ui->telaAtual == TELA_COMPUTADOR1) {
            /* ---------- COMPUTADOR C1 - afirmacoes da IA (US06) ---------- */
            printf("  COMPUTADOR C1 - AFIRMACOES DA IA NEXUS\n");
            printf(LINHA_FINA);
            printf("  Pista: \"O servidor principal foi desligado as 22h.\"\n\n");
            printf("  A IA NEXUS afirma:\n");
            printf("   p : \"O servidor principal esta ligado.\"\n");
            printf("       Valor logico: %c\n", partida->etapaComputador1 > 0 ? 'F' : '?');
            printf("   ~p: \"Nao e verdade que o servidor principal\n");
            printf("        esta ligado.\"\n");
            printf("       Valor logico: %c\n\n", partida->etapaComputador1 > 1 ? 'V' : '?');

            if (partida->etapaComputador1 == 0) {
                printf("  Qual o valor logico de p?\n");
                printf("  [V] Verdadeiro  [F] Falso  [Q] Sair do computador\n");
            } else if (partida->etapaComputador1 == 1) {
                printf("  Qual o valor logico de ~p (negacao de p)?\n");
                printf("  [V] Verdadeiro  [F] Falso  [Q] Sair do computador\n");
            } else {
                printf("  SISTEMA CORRIGIDO! A afirmacao p era uma ALUCINACAO:\n");
                printf("  parecia certa, mas contradiz a pista.\n\n");
                printf("  [E] Voltar ao mapa\n");
            }

        } else if (ui->telaAtual == TELA_COMPUTADOR2) {
            /* ---------- COMPUTADOR C2 - filtro de confianca (US07) ---------- */
            printf("  COMPUTADOR C2 - FILTRO DE CONFIANCA\n");
            printf(LINHA_FINA);
            printf("  Uma resposta da IA so e CONFIAVEL se:\n");
            printf("    p = \"a resposta cita uma fonte\"\n");
            printf("    q = \"o dado confere com as pistas\"\n");
            printf("    confiavel = p ^ q   (conjuncao \"E\"; em C: p && q)\n\n");
            printf("  Complete a ultima coluna da tabela-verdade:\n\n");
            printf("       p | q | p ^ q\n");
            printf("      ---+---+-------\n");
            for (linhaExibida = 0; linhaExibida < LINHAS_TABELA; linhaExibida++) {
                valorP = (linhaExibida < 2);           /* linhas 0 e 1: p = V */
                valorQ = (linhaExibida % 2 == 0);      /* linhas pares: q = V */
                printf("       %c | %c |   ", valorP ? 'V' : 'F', valorQ ? 'V' : 'F');
                if (linhaExibida < partida->linhaTabela) {
                    printf("%c\n", (valorP && valorQ) ? 'V' : 'F');   /* ja respondida */
                } else if (linhaExibida == partida->linhaTabela) {
                    printf("?   <- sua vez\n");
                } else {
                    printf("?\n");
                }
            }

            if (partida->linhaTabela < LINHAS_TABELA) {
                printf("\n  Qual o valor de p ^ q nessa linha?\n");
                printf("  [V] Verdadeiro  [F] Falso  [Q] Sair do computador\n");
            } else {
                printf("\n  FILTRO CORRIGIDO! A porta D foi destrancada.\n\n");
                printf("  [E] Voltar ao mapa\n");
            }

        } else if (ui->telaAtual == TELA_INVENTARIO) {
            /* ---------- INVENTARIO (tecla I) ---------- */
            printf("  INVENTARIO\n");
            printf(LINHA_FINA);
            printf("   [%c] Chave da Verdade\n", partida->chaveDaVerdade ? 'X' : ' ');
            printf("   [%c] Chave da Privacidade\n", partida->chaveDaPrivacidade ? 'X' : ' ');
            printf("   [%c] Chave da Justica\n\n", partida->chaveDaJustica ? 'X' : ' ');
            printf("   Pista encontrada:        %s\n", partida->pistaEncontrada ? "sim" : "nao");
            printf("   Computadores corrigidos: %d/2\n", partida->computador1Resolvido + partida->computador2Resolvido);
            printf("   Porta D:                 %s\n\n", partida->portaAberta ? "aberta" : "trancada");
            printf("  [I] Fechar inventario\n");

        } else if (ui->telaAtual == TELA_CHAVE) {
            /* ---------- CHAVE DA VERDADE (US07) ---------- */
            printf("  *** CHAVE DA VERDADE OBTIDA! ***  (+%d pontos)\n\n", PONTOS_CHAVE);
            printf("  A Central da Verdade voltou a funcionar.\n\n");
            printf("  Licao: uma IA pode \"alucinar\" e afirmar algo falso com\n");
            printf("  confianca. Sempre confira as respostas com fontes e\n");
            printf("  informacoes confiaveis.\n\n");
            printf("  [E] Continuar\n");

        } else if (ui->telaAtual == TELA_FIM_FASE) {
            /* ---------- FIM DA FASE - jogar novamente? ---------- */
            printf(SEPARADOR);
            printf("  FASE 1 CONCLUIDA!\n");
            printf(SEPARADOR);
            printf("  Pontuacao:            %d de %d pontos\n", partida->pontos, PONTUACAO_MAXIMA);
            printf("  Respostas incorretas: %d\n", partida->respostasIncorretas);
            printf("  Desempenho:           ");
            if (partida->respostasIncorretas == 0) {
                printf("perfeito!\n\n");
            } else if (partida->respostasIncorretas <= 2) {
                printf("muito bom!\n\n");
            } else {
                printf("continue praticando!\n\n");
            }
            printf("  As fases 2 (Setor de Privacidade) e 3 (Nucleo da\n");
            printf("  Justica) estarao disponiveis nas proximas etapas.\n\n");
            printf("  Deseja jogar novamente?\n");
            printf("    [1] Jogar novamente\n");
            printf("    [2] Voltar ao menu\n");
            printf("    [3] Sair do jogo\n");

        } else if (ui->telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* ---------- CONFIRMAR SAIDA ---------- */
            if (ui->origemConfirmacao == TELA_MENU) {
                printf("\n  Deseja realmente sair do NEXUS?\n\n");
            } else {
                printf("\n  Deseja voltar ao menu? O progresso da fase sera perdido.\n\n");
            }
            printf("    [S] Sim    [N] Nao\n");
        }

        /* Mensagem do rodape: resultado da ultima acao */
        if (ui->mensagem != MSG_NENHUMA) {
            printf("\n  >> ");
            if (ui->mensagem == MSG_PAREDE) {
                printf("Caminho bloqueado! Voce nao pode atravessar obstaculos.\n");
            } else if (ui->mensagem == MSG_NADA_PROXIMO) {
                printf("Nada para interagir aqui. Chegue perto de ?, C, D ou K.\n");
            } else if (ui->mensagem == MSG_C1_BLOQUEADO) {
                printf("O computador C1 esta bloqueado. Encontre a pista (?) primeiro.\n");
            } else if (ui->mensagem == MSG_C2_BLOQUEADO) {
                printf("Acesso negado ao C2. Primeiro corrija as afirmacoes do C1.\n");
            } else if (ui->mensagem == MSG_PORTA_TRANCADA) {
                printf("Porta D trancada: ela so abre se C1 E C2 estiverem corrigidos.\n");
            } else if (ui->mensagem == MSG_SALVAR) {
                printf("O salvamento em arquivo sera implementado na proxima etapa.\n");
            } else if (ui->mensagem == MSG_ACERTO) {
                printf("Correto!\n");
            } else if (ui->mensagem == MSG_ERRO_P) {
                printf("Incorreto. A pista diz que o servidor foi DESLIGADO, entao p e Falsa.\n");
            } else if (ui->mensagem == MSG_ERRO_NAO_P) {
                printf("Incorreto. A negacao inverte o valor: se p = F, entao ~p = V.\n");
            } else if (ui->mensagem == MSG_ERRO_TABELA) {
                printf("Incorreto. p ^ q so e V quando p E q sao V ao mesmo tempo.\n");
            } else {
                printf("Correto! A porta D foi DESTRANCADA.\n");
            }
            ui->mensagem = MSG_NENHUMA;   /* cada mensagem aparece uma unica vez */
        }

        /* ------------------------------------------------------------------
         * (C) LEITURA E VALIDACAO DA TECLA (sem ENTER)
         * O laco while so termina quando a tecla for valida para a tela
         * atual. Teclas erradas nunca travam nem encerram o programa.
         * ---------------------------------------------------------------- */
        printf("\n  Teclas aceitas: ");
        if (ui->telaAtual == TELA_MENU || ui->telaAtual == TELA_FIM_FASE) {
            printf("1, 2 ou 3\n");
        } else if (ui->telaAtual == TELA_INSTRUCOES) {
            printf("qualquer tecla\n");
        } else if (ui->telaAtual == TELA_MAPA) {
            printf("W, A, S, D, E, I, P ou Q\n");
        } else if (ui->telaAtual == TELA_PISTA || ui->telaAtual == TELA_CHAVE) {
            printf("E\n");
        } else if (ui->telaAtual == TELA_COMPUTADOR1) {
            printf("%s\n", partida->computador1Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (ui->telaAtual == TELA_COMPUTADOR2) {
            printf("%s\n", partida->computador2Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (ui->telaAtual == TELA_INVENTARIO) {
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
            } else if (ui->telaAtual == TELA_MENU || ui->telaAtual == TELA_FIM_FASE) {
                entradaValida = (tecla >= '1' && tecla <= '3');
            } else if (ui->telaAtual == TELA_INSTRUCOES) {
                entradaValida = 1;
            } else if (ui->telaAtual == TELA_MAPA) {
                entradaValida = (tecla == 'W' || tecla == 'A' || tecla == 'S' ||
                                 tecla == 'D' || tecla == 'E' || tecla == 'I' ||
                                 tecla == 'P' || tecla == 'Q');
            } else if (ui->telaAtual == TELA_PISTA || ui->telaAtual == TELA_CHAVE) {
                entradaValida = (tecla == 'E');
            } else if (ui->telaAtual == TELA_COMPUTADOR1) {
                if (partida->computador1Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (ui->telaAtual == TELA_COMPUTADOR2) {
                if (partida->computador2Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (ui->telaAtual == TELA_INVENTARIO) {
                entradaValida = (tecla == 'I' || tecla == 'Q');
            } else {
                entradaValida = (tecla == 'S' || tecla == 'N');
            }

            /* Aviso para teclas invalidas (espacos, ENTER e setas nao contam).
             * O '\r' reescreve sempre a mesma linha, sem empurrar o mapa, e
             * teclas de controle (ESC, Backspace...) aparecem como '?'. */
            if (!entradaValida && tecla != ' ' && tecla != '\n' &&
                tecla != '\r' && tecla != '\t') {
                tentativasInvalidas++;
                printf("\r  Tecla '%c' invalida! Tente novamente. (avisos: %d)   ",
                       (tecla >= ' ' && tecla <= '~') ? tecla : '?',
                       tentativasInvalidas);
            }
        }

        /* ------------------------------------------------------------------
         * (D) PROCESSAMENTO DA TECLA
         * Usamos if / else if: apenas o bloco da tela atual e executado.
         * ---------------------------------------------------------------- */
        if (ui->telaAtual == TELA_MENU) {
            /* 1 = iniciar, 2 = instrucoes, 3 = sair (com confirmacao) */
            if (tecla == '1') {
                ui->reiniciarJogo = 1;
                ui->telaAtual = TELA_MAPA;
            } else if (tecla == '2') {
                ui->telaAtual = TELA_INSTRUCOES;
            } else {
                ui->origemConfirmacao = TELA_MENU;
                ui->telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (ui->telaAtual == TELA_INSTRUCOES) {
            ui->telaAtual = TELA_MENU;               /* qualquer tecla volta */

        } else if (ui->telaAtual == TELA_MAPA) {
            if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
                /* Movimento: (tecla == 'S') vale 1 se verdadeiro e 0 se falso.
                 * A colisao e verificada no passo 0 do desenho do mapa. */
                partida->destinoLinha = partida->jogadorLinha + (tecla == 'S') - (tecla == 'W');
                partida->destinoColuna = partida->jogadorColuna + (tecla == 'D') - (tecla == 'A');
                partida->tentouMover = 1;

            } else if (tecla == 'E') {
                /* Interacao: procura um objeto ativo ao redor do jogador
                 * (ao lado tem prioridade sobre a diagonal - ver mapa.c). */
                objetoProximo = procurarObjetoProximo(partida);

                /* Reacao ao objeto encontrado, respeitando a ordem da fase */
                if (objetoProximo == OBJ_PISTA) {
                    partida->pistaEncontrada = 1;
                    partida->pontos += PONTOS_PISTA;
                    ui->telaAtual = TELA_PISTA;
                } else if (objetoProximo == OBJ_COMPUTADOR1) {
                    if (partida->pistaEncontrada) {
                        ui->telaAtual = TELA_COMPUTADOR1;
                    } else {
                        ui->mensagem = MSG_C1_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_COMPUTADOR2) {
                    if (partida->computador1Resolvido) {
                        ui->telaAtual = TELA_COMPUTADOR2;
                    } else {
                        ui->mensagem = MSG_C2_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_PORTA) {
                    ui->mensagem = MSG_PORTA_TRANCADA;
                } else if (objetoProximo == OBJ_CHAVE) {
                    partida->chaveDaVerdade = 1;
                    partida->pontos += PONTOS_CHAVE;
                    ui->telaAtual = TELA_CHAVE;
                } else {
                    ui->mensagem = MSG_NADA_PROXIMO;
                }

            } else if (tecla == 'I') {
                ui->telaAtual = TELA_INVENTARIO;
            } else if (tecla == 'P') {
                ui->mensagem = MSG_SALVAR;
            } else {                              /* Q */
                ui->origemConfirmacao = TELA_MAPA;
                ui->telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (ui->telaAtual == TELA_PISTA) {
            ui->telaAtual = TELA_MAPA;

        } else if (ui->telaAtual == TELA_COMPUTADOR1) {
            /* Julgar p (resposta F) e depois ~p (resposta V) */
            if (tecla == 'Q' || tecla == 'E') {
                ui->telaAtual = TELA_MAPA;
            } else {
                respostaEsperada = (partida->etapaComputador1 == 0) ? 'F' : 'V';
                if (tecla == respostaEsperada) {
                    partida->etapaComputador1++;
                    ui->mensagem = MSG_ACERTO;
                    if (partida->etapaComputador1 == ETAPAS_C1) {
                        partida->computador1Resolvido = 1;
                        partida->pontos += PONTOS_COMPUTADOR;
                    }
                } else {
                    partida->respostasIncorretas++;
                    ui->mensagem = (partida->etapaComputador1 == 0) ? MSG_ERRO_P : MSG_ERRO_NAO_P;
                }
            }

        } else if (ui->telaAtual == TELA_COMPUTADOR2) {
            /* Completar a tabela-verdade de p ^ q, uma linha por vez */
            if (tecla == 'Q' || tecla == 'E') {
                ui->telaAtual = TELA_MAPA;
            } else {
                valorP = (partida->linhaTabela < 2);
                valorQ = (partida->linhaTabela % 2 == 0);
                respostaEsperada = (valorP && valorQ) ? 'V' : 'F';
                if (tecla == respostaEsperada) {
                    partida->linhaTabela++;
                    ui->mensagem = MSG_ACERTO;
                    if (partida->linhaTabela == LINHAS_TABELA) {
                        partida->computador2Resolvido = 1;
                        partida->pontos += PONTOS_COMPUTADOR;
                        /* Regra da porta (conjuncao): abre se C1 E C2 corrigidos */
                        partida->portaAberta = partida->computador1Resolvido && partida->computador2Resolvido;
                        ui->mensagem = MSG_PORTA_ABERTA;
                    }
                } else {
                    partida->respostasIncorretas++;
                    ui->mensagem = MSG_ERRO_TABELA;
                }
            }

        } else if (ui->telaAtual == TELA_INVENTARIO) {
            ui->telaAtual = TELA_MAPA;

        } else if (ui->telaAtual == TELA_CHAVE) {
            ui->telaAtual = TELA_FIM_FASE;

        } else if (ui->telaAtual == TELA_FIM_FASE) {
            /* 1 = jogar novamente, 2 = menu, 3 = sair */
            if (tecla == '1') {
                ui->reiniciarJogo = 1;
                ui->telaAtual = TELA_MAPA;
            } else if (tecla == '2') {
                ui->telaAtual = TELA_MENU;
            } else {
                ui->telaAtual = TELA_ENCERRAR;
            }

        } else if (ui->telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* S confirma; N volta para a tela de origem */
            if (tecla == 'N') {
                ui->telaAtual = ui->origemConfirmacao;
            } else if (ui->origemConfirmacao == TELA_MENU) {
                ui->telaAtual = TELA_ENCERRAR;
            } else {
                ui->telaAtual = TELA_MENU;
            }
        }
    }

    printf("\n  Obrigado por jogar NEXUS! Ate a proxima.\n\n");
    return 0;
}
