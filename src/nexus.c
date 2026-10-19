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
 *    - Funcoes e modularizacao (arquivos .h e .c)
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
 *  Modulos: jogo.c (estado, fluxo e regras), mapa.c (mapa e objetos) e
 *           terminal.c (desenho das telas e leitura das teclas).
 * ============================================================================
 */

#include "jogo.h"     /* estado do jogo, fluxo e regras */
#include "terminal.h" /* desenho das telas e leitura das teclas */

int main(void) {
    Jogo jogo;
    char tecla;                          /* tecla valida, em maiuscula      */

    iniciarJogo(&jogo);

    /* ========================================================================
     * GAME LOOP: repete ate o jogador escolher sair
     * ====================================================================== */
    while (jogo.ui.telaAtual != TELA_ENCERRAR) {
        /* (A) reinicio da fase, se pedido */
        reiniciarSePedido(&jogo);

        /* (B) aplica o movimento pendente e desenha a tela atual;
         *     depois do desenho a mensagem do rodape e apagada
         *     (cada mensagem aparece uma unica vez) */
        aplicarMovimento(&jogo);
        desenharTela(&jogo);
        jogo.ui.mensagem = MSG_NENHUMA;

        /* (C) le e valida a tecla (sem ENTER) */
        tecla = lerTecla(&jogo);

        /* (D) processa a tecla e decide a proxima tela */
        processarTecla(&jogo, tecla);
    }

    mostrarDespedida();
    return 0;
}
