/*
 * ============================================================================
 *  NEXUS - Interface e entrada do terminal (Windows)
 * ============================================================================
 *
 *  Tudo o que aparece na tela e a leitura das teclas ficam aqui.
 *  As funcoes so LEEM o estado do jogo (const): quem altera o progresso
 *  e o game loop em nexus.c.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>   /* system("cls"): limpa a tela do terminal do Windows */
#include <conio.h>    /* _getch(): le uma tecla na hora, sem precisar de ENTER */
#include "terminal.h"
#include "mapa.h"

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

/* Aparencia */
#define SEPARADOR   " ==================================================\n"
#define LINHA_FINA  " --------------------------------------------------\n"

/* ----------------------------------------------------------------------------
 * DESENHO DA TELA ATUAL
 * Limpa o terminal e mostra a tela, a mensagem do rodape e as teclas aceitas.
 * -------------------------------------------------------------------------- */
void desenharTela(const Jogo *jogo) {
    const EstadoJogo *partida = &jogo->partida;
    const EstadoInterface *ui = &jogo->ui;
    int linha, coluna;
    char celula;                         /* simbolo calculado da posicao    */
    int linhaExibida, valorP, valorQ;    /* linhas da tabela-verdade        */

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

        /* Desenha o mapa com as regras de mapa.c
         * (o movimento pendente ja foi aplicado pelo game loop). */
        for (linha = 0; linha < ALTURA_MAPA; linha++) {
            printf("   ");
            for (coluna = 0; coluna < LARGURA_MAPA; coluna++) {
                /* Regras do mapa: qual simbolo existe nesta posicao? */
                celula = celulaDoMapa(partida, linha, coluna);

                /* desenha (o jogador aparece por cima do chao) */
                if (linha == partida->jogadorLinha && coluna == partida->jogadorColuna) {
                    printf("%c ", JOGADOR);
                } else {
                    printf("%c ", celula);
                }
            }
            printf("\n");
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
        printf("       Valor logico: %c\n", partida->etapaComputador1 > 0 ? (VALOR_P_C1 ? 'V' : 'F') : '?');
        printf("   ~p: \"Nao e verdade que o servidor principal\n");
        printf("        esta ligado.\"\n");
        printf("       Valor logico: %c\n\n", partida->etapaComputador1 > 1 ? (!VALOR_P_C1 ? 'V' : 'F') : '?');

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
            printf("\n  FILTRO CORRIGIDO!%s\n\n", partida->portaAberta ? " A porta D foi destrancada." : "");
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
    }

    /* Teclas aceitas na tela atual */
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
}

/* ----------------------------------------------------------------------------
 * LEITURA E VALIDACAO DA TECLA (sem ENTER)
 * O laco while so termina quando a tecla for valida para a tela atual.
 * Teclas erradas nunca travam nem encerram o programa, e a tela nao e
 * redesenhada: o aviso reescreve sempre a mesma linha.
 * Devolve a tecla valida, ja em maiuscula.
 * -------------------------------------------------------------------------- */
char lerTecla(const Jogo *jogo) {
    const EstadoJogo *partida = &jogo->partida;
    const EstadoInterface *ui = &jogo->ui;
    int teclaLida;                       /* codigo lido por _getch()        */
    char tecla = ' ';                    /* tecla ja convertida p/ maiuscula */
    int entradaValida;
    int tentativasInvalidas;

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

    return tecla;
}

/* Mensagem exibida ao encerrar o jogo */
void mostrarDespedida(void) {
    printf("\n  Obrigado por jogar NEXUS! Ate a proxima.\n\n");
}
