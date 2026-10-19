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
 *
 *  Modulos: jogo.h (estado e constantes), mapa.c (mapa e objetos) e
 *           terminal.c (desenho das telas e leitura das teclas).
 * ============================================================================
 */

#include "jogo.h"     /* structs e constantes de telas, mensagens e regras */
#include "mapa.h"     /* mapa da Fase 1 e objetos interativos */
#include "terminal.h" /* desenho das telas e leitura das teclas */

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
    char tecla;                          /* tecla valida, em maiuscula      */

    /* ---------------- Movimento ---------------- */
    char celulaDestino;                  /* simbolo na casa de destino      */

    /* ---------------- Interacao e computadores ---------------- */
    int objetoProximo;                   /* objeto alcancado com a tecla E  */
    char respostaEsperada;
    int valorP, valorQ;                  /* linha atual da tabela-verdade   */

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
         * Antes de desenhar o mapa, aplica o movimento pendente (W/A/S/D):
         * o jogador nao atravessa obstaculos. Depois do desenho, a mensagem
         * do rodape e apagada (cada mensagem aparece uma unica vez).
         * ---------------------------------------------------------------- */
        if (ui->telaAtual == TELA_MAPA && partida->tentouMover) {
            celulaDestino = celulaDoMapa(partida, partida->destinoLinha, partida->destinoColuna);
            if (celulaDestino == CHAO || celulaDestino == PORTA_ABERTA) {
                partida->jogadorLinha = partida->destinoLinha;
                partida->jogadorColuna = partida->destinoColuna;
            } else {
                ui->mensagem = MSG_PAREDE;
            }
            partida->tentouMover = 0;
        }

        desenharTela(&jogo);
        ui->mensagem = MSG_NENHUMA;

        /* ------------------------------------------------------------------
         * (C) LEITURA E VALIDACAO DA TECLA (sem ENTER)
         * So retorna quando a tecla for valida para a tela atual. Teclas
         * erradas nunca travam nem encerram o programa.
         * ---------------------------------------------------------------- */
        tecla = lerTecla(&jogo);

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

    mostrarDespedida();
    return 0;
}
