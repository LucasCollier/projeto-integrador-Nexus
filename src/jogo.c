/*
 * ============================================================================
 *  NEXUS - Fluxo e regras do jogo
 * ============================================================================
 *
 *  Tudo o que altera o estado da partida e das telas fica aqui:
 *  inicializacao, reinicio, movimento, interacao com objetos, desafios dos
 *  computadores C1 e C2, recompensas e transicoes entre telas.
 *  Este modulo nao le teclas nem escreve na tela (isso e o terminal.c).
 * ============================================================================
 */

#include "jogo.h"
#include "mapa.h"

/* ----------------------------------------------------------------------------
 * INICIALIZACAO: estado do jogo ao abrir o programa
 * -------------------------------------------------------------------------- */
void iniciarJogo(Jogo *jogo) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;

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
}

/* ----------------------------------------------------------------------------
 * REINICIO DA FASE
 * Um unico bloco zera o progresso. E usado tanto por "Iniciar jogo"
 * quanto por "Jogar novamente" (evita repetir codigo - DRY).
 * -------------------------------------------------------------------------- */
void reiniciarSePedido(Jogo *jogo) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;

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
}

/* ----------------------------------------------------------------------------
 * MOVIMENTO PENDENTE (W/A/S/D)
 * Aplicado antes de desenhar o mapa: o jogador nao atravessa obstaculos.
 * -------------------------------------------------------------------------- */
void aplicarMovimento(Jogo *jogo) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;
    char celulaDestino;                  /* simbolo na casa de destino      */

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
}

/* ----------------------------------------------------------------------------
 * TELA DO MAPA: movimento, interacao (E), inventario, salvar e sair
 * -------------------------------------------------------------------------- */
static void processarMapa(Jogo *jogo, char tecla) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;
    int objetoProximo;                   /* objeto alcancado com a tecla E  */

    if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
        /* Movimento: (tecla == 'S') vale 1 se verdadeiro e 0 se falso.
         * A colisao e verificada em aplicarMovimento, antes do desenho. */
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
}

/* ----------------------------------------------------------------------------
 * REGRA DA PORTA (conjuncao): a porta D fica aberta se C1 E C2 corrigidos.
 * Reavaliada sempre que C1 ou C2 e concluido: portaAberta = c1 ^ c2.
 * -------------------------------------------------------------------------- */
static void atualizarPorta(EstadoJogo *partida) {
    partida->portaAberta = partida->computador1Resolvido && partida->computador2Resolvido;
}

/* ----------------------------------------------------------------------------
 * COMPUTADOR C1: julgar p (VALOR_P_C1 = F) e depois ~p (!VALOR_P_C1 = V)
 * -------------------------------------------------------------------------- */
static void responderComputador1(Jogo *jogo, char tecla) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;
    char respostaEsperada;
    int valorEsperado;                   /* valor logico de p ou de ~p      */

    if (tecla == 'Q' || tecla == 'E') {
        ui->telaAtual = TELA_MAPA;
    } else {
        /* etapa 0: julgar p ; etapa 1: julgar ~p (negacao do mesmo p) */
        valorEsperado = (partida->etapaComputador1 == 0) ? VALOR_P_C1 : !VALOR_P_C1;
        respostaEsperada = valorEsperado ? 'V' : 'F';
        if (tecla == respostaEsperada) {
            partida->etapaComputador1++;
            ui->mensagem = MSG_ACERTO;
            if (partida->etapaComputador1 == ETAPAS_C1) {
                partida->computador1Resolvido = 1;
                partida->pontos += PONTOS_COMPUTADOR;
                atualizarPorta(partida);
            }
        } else {
            partida->respostasIncorretas++;
            ui->mensagem = (partida->etapaComputador1 == 0) ? MSG_ERRO_P : MSG_ERRO_NAO_P;
        }
    }
}

/* ----------------------------------------------------------------------------
 * COMPUTADOR C2: completar a tabela-verdade de p ^ q, uma linha por vez
 * -------------------------------------------------------------------------- */
static void responderComputador2(Jogo *jogo, char tecla) {
    EstadoJogo *partida = &jogo->partida;
    EstadoInterface *ui = &jogo->ui;
    char respostaEsperada;
    int valorP, valorQ;                  /* linha atual da tabela-verdade   */

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
                atualizarPorta(partida);
                /* a mensagem de abertura so aparece se a porta abriu */
                ui->mensagem = partida->portaAberta ? MSG_PORTA_ABERTA : MSG_ACERTO;
            }
        } else {
            partida->respostasIncorretas++;
            ui->mensagem = MSG_ERRO_TABELA;
        }
    }
}

/* ----------------------------------------------------------------------------
 * PROCESSAMENTO DA TECLA
 * Usamos if / else if: apenas o bloco da tela atual e executado.
 * -------------------------------------------------------------------------- */
void processarTecla(Jogo *jogo, char tecla) {
    EstadoInterface *ui = &jogo->ui;

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
        processarMapa(jogo, tecla);

    } else if (ui->telaAtual == TELA_PISTA) {
        ui->telaAtual = TELA_MAPA;

    } else if (ui->telaAtual == TELA_COMPUTADOR1) {
        responderComputador1(jogo, tecla);

    } else if (ui->telaAtual == TELA_COMPUTADOR2) {
        responderComputador2(jogo, tecla);

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
