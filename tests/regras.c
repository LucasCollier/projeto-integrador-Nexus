#include <assert.h>
#include <stdio.h>
#include "../src/jogo.h"
#include "../src/missoes.h"
static void passos(Jogo *j, const char *s) { for (; *s; s++) { processarTecla(j, *s); aplicarMovimento(j); } }
int main(void) {
 Jogo j; iniciarJogo(&j);
 processarTecla(&j,'x'); assert(j.ui.telaAtual == TELA_MENU);
 processarTecla(&j,'1'); reiniciarSePedido(&j);
 /* Teste de regras; posicionamento e terminal real nao simulados. */
 j.ui.telaAtual = TELA_COMPUTADOR1;
 processarTecla(&j,'V'); assert(j.partida.respostasIncorretas == 1);
 processarTecla(&j,'F'); processarTecla(&j,'V');
 assert(j.partida.computador1Resolvido && j.partida.pontos == 20);
 j.ui.telaAtual = TELA_COMPUTADOR2;
 processarTecla(&j,'F'); processarTecla(&j,'V');
 processarTecla(&j,'F'); processarTecla(&j,'F'); processarTecla(&j,'F');
 assert(j.partida.portaAberta && j.partida.pontos == 40);
 j.ui.telaAtual = TELA_CHAVE; processarTecla(&j,'E');
 assert(j.ui.telaAtual == TELA_PRIVACIDADE);
 processarTecla(&j,'x'); assert(j.partida.perguntaPrivacidade == 0);
 processarTecla(&j,'2'); assert(j.partida.respostasIncorretas == 3);
 processarTecla(&j,'1'); processarTecla(&j,'2'); processarTecla(&j,'3');
 assert(j.partida.chaveDaPrivacidade && j.partida.pontos == 100);
 assert(j.ui.telaAtual == TELA_FIM_FASE);
 processarTecla(&j,'1'); reiniciarSePedido(&j);
 assert(j.partida.pontos == 0 && j.partida.perguntaPrivacidade == 0 && !j.partida.chaveDaPrivacidade);
 j.ui.telaAtual = TELA_FIM_FASE; processarTecla(&j,'3');
 assert(j.ui.telaAtual == TELA_ENCERRAR);
 assert(corrigir(&privacidade[0], '\0') == INVALIDA);
 iniciarJogo(&j); processarTecla(&j,'1'); reiniciarSePedido(&j);
 passos(&j,"DDDDDEE");
 assert(j.partida.pistaEncontrada && j.partida.pontos == 10);
 passos(&j,"SSEFVE");
 assert(j.partida.computador1Resolvido);
 passos(&j,"DDSSEVFFFE");
 assert(j.partida.computador2Resolvido && j.partida.portaAberta);
 passos(&j,"WWDDDDDDDDDDE");
 assert(j.partida.chaveDaVerdade && j.partida.pontos == 80);
 passos(&j,"E123");
 assert(j.ui.telaAtual == TELA_FIM_FASE && j.partida.pontos == 140);
 puts("PASS: percurso completo desde o menu, duas chaves, 140 pontos.");
 puts("PASS: regras C1/C2, porta, missao 2, erros, pontos, reinicio e saida.");
 return 0;
}
