# PI2-36 — Evidências da validação final

Base executada: `4cf4496bb3e066e6aa5e45c24cb336bd522853b3` (main, PR #5 integrada). Esta revisão documental não altera código nem jogabilidade.

## Resultados executados

| Verificação | Resultado |
|---|---|
| Jogo e testes em C99, -Wall -Wextra -Wpedantic -Werror | APROVADO, sem diagnósticos |
| tests/regras.c | APROVADO, código de saída 0 |
| Negação F/V, conjunção V/F/F/F, porta e pontos por pergunta | APROVADO nos testes existentes |
| Percurso desde menu, movimentação, colisão e interação | APROVADO na simulação do programa completo |
| Teclas minúsculas, inválidas X, acertos e erros | APROVADO na leitura/validação real de terminal.c com fonte de teclas adaptada |
| Duas chaves e 140 pontos, com três erros | APROVADO na transcrição |
| Inventário, cancelamento de saída, reinício e encerramento | APROVADO; saída 0, reinício com 0 pontos/0 chaves |
| Caracteres na saída capturada | Sem U+FFFD; textos ASCII legíveis na captura textual |
| Teclado físico, _getch real, limpeza de tela, fonte e layout visual | NÃO VERIFICADO |
| Gravação real do terminal | NÃO DISPONÍVEL nesta execução; nenhum vídeo produzido |

A tentativa de executar nexus.exe em pseudoterminal Windows falhou com “Uma política de Controle de Aplicativo bloqueou este arquivo”, inclusive fora do sandbox. Não foram alteradas políticas de segurança. Isso é um impedimento do ambiente, não prova de defeito do jogo.

## Método e limites da simulação

Foram compilados os arquivos originais nexus.c, jogo.c, mapa.c, terminal.c e missoes.c. Somente duas dependências foram substituídas por adaptadores de teste: _getch lê stdin; system não limpa a tela, permitindo capturar todas as telas. main, lerTecla, desenharTela e regras foram executados sem edição. Arquivos auxiliares e transcrição ficaram em `%TEMP%/nexus-pi236-validation`, fora do repositório.

Adaptador usado:
```c
#include <stdio.h>
#include <stdlib.h>
int nexusTestGetch(void) {
    int c = getchar();
    if (c == EOF) { fputs("FALHA: entrada esgotada antes da saida\n", stderr); exit(2); }
    return c;
}
int nexusTestSystem(const char *command) { (void)command; return 0; }
```
O cabeçalho conio.h exclusivo do diretório temporário declara `int nexusTestGetch(void);`. Flags adicionais: `-I <diretorio-temporario> -D_getch=nexusTestGetch -Dsystem=nexusTestSystem`, com o adaptador incluído na compilação. A primeira tentativa de ligação, sem esse cabeçalho, falhou por dllimport de conio.h; corrigido somente no harness temporário.

Entrada exata concatenada, sem espaços:
```
x1a + dddddee + ssevfvE + ddssefvfffe + wwdddddddddde + ex2123 + 1iqqnqs3n3s
```
Os sinais `+` acima indicam concatenação e não são enviados. Inclui um erro em C1, um em C2 e um na Privacidade. Não há emulação de teclado físico nem avaliação de latência.

Trechos observados:
```text
PASS: percurso completo desde o menu, duas chaves, 140 pontos.
PASS: regras C1/C2, porta, missao 2, erros, pontos, reinicio e saida.
Tecla 'X' invalida! Tente novamente.
Caminho bloqueado! Voce nao pode atravessar obstaculos.
*** CHAVE DA VERDADE OBTIDA! ***  (+30 pontos)
DUAS MISSOES CONCLUIDAS! Chave da Privacidade obtida.
Pontuacao:            140 de 140 pontos
Respostas incorretas: 3
Pontos: 0 | Chaves: 0/3
Obrigado por jogar NEXUS! Ate a proxima.
```

## Compilação e execução Windows

No PowerShell, na raiz do projeto, com GCC/MinGW no PATH:
```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror src/nexus.c src/jogo.c src/mapa.c src/terminal.c src/missoes.c -o nexus.exe
if ($LASTEXITCODE -ne 0) { throw 'Compilacao falhou' }
.\nexus.exe
```
Testes:
```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror tests/regras.c src/jogo.c src/mapa.c src/missoes.c -o testes.exe
if ($LASTEXITCODE -ne 0) { throw 'Compilacao dos testes falhou' }
.\testes.exe
```

## Roteiro definitivo — 2min50s

Pressionar teclas separadamente, sem Enter; × indica repetição. Não colar sequências no jogo. Preparar o terminal antes de iniciar a gravação.

| Tempo | Ação | Fala |
|---|---|---|
| 0:00–0:15 | Mostrar repositório, PR e identificação confirmada | “Somos a squad NEXUS. A versão U2 integrada pela PR 5 apresenta duas missões sobre lógica e ética em IA.” |
| 0:15–0:35 | Compilar com as flags acima e executar | “Compilamos em C99, com avisos tratados como erros.” |
| 0:35–0:45 | X, pausa, 1, A | “Uma tecla inválida é rejeitada. Paredes impedem o movimento.” |
| 0:45–1:00 | D × 5, E, pausa, E | “A pista informa que o servidor foi desligado e vale dez pontos.” |
| 1:00–1:20 | S × 2, E, V errado, F, V, E | “A afirmação é falsa e sua negação verdadeira. Erros não avançam a pergunta. Corrigir o computador vale vinte pontos.” |
| 1:20–1:40 | D × 2, S × 2, E, F errado, V, F, F, F, E | “A conjunção é verdadeira somente com duas entradas verdadeiras. Corrigir ambos os computadores abre a porta.” |
| 1:40–1:55 | W × 2, D × 10, E, pausa, E | “Coletamos a Chave da Verdade: oitenta pontos e primeira missão concluída.” |
| 1:55–2:20 | X, pausa, 2 errado, 1, 2, 3 | “A Privacidade aborda minimização de dados, autorização e anonimização. Os três acertos entregam a segunda chave.” |
| 2:20–2:35 | Mostrar resumo; 1; I; Q | “Concluímos com cento e quarenta pontos e três erros registrados. Reiniciar zera os pontos e as chaves.” |
| 2:35–2:50 | Q, S, 3, S | “Voltamos ao menu e encerramos. Código, testes e documentação estão no repositório.” |

Este roteiro coincide com o percurso simulado; não é evidência de gravação já realizada.

## Links, equipe e pendências

GitHub API confirmou repositório público, PR #5 MERGED e existência do pacote no commit integrado. As consultas web aos dois screencasts Drive, protótipo Figma, diagrama Figma e Trello retornaram inacessibilidade pela ferramenta: NÃO VERIFICADOS, sem classificá-los como quebrados ou afirmar autenticação sem evidência. URLs históricas preservadas no README. Link específico de LMC ainda não identificado.

Nomes documentados: Rodrigo Alves, João Victor Queiroz, João Victor Nicacio, João Guilherme Queiroz, Danilo Barros, Gustavo Cassemiro, Daniel Luiz, Fernando Araújo e Lucas Collier. A equipe deve confirmar a composição e as contribuições; nomes não foram inferidos nem alterados.

## Texto para PI2-36 (preparado, não enviado)

Versão técnica de PIF U2 integrada ao main pela [PR #5](https://github.com/joaollima7/projeto-integrador-Nexus/pull/5), commit `4cf4496bb3e066e6aa5e45c24cb336bd522853b3`. Duas missões completas, dados estruturados, validação, reinício e máximo de 140 pontos.

Compilação estrita C99 e testes existentes aprovados. Simulação adicional executou o laço principal e a interface textual originais com entrada adaptada, confirmando movimentação, colisão, interação, entradas inválidas, erros/acertos, duas chaves, reinício e saída. Execução interativa foi bloqueada pela política Windows; teclado físico e renderização visual não estão aprovados.

Evidências publicadas:
- [README](https://github.com/joaollima7/projeto-integrador-Nexus/blob/4cf4496bb3e066e6aa5e45c24cb336bd522853b3/README.md)
- [Testes](https://github.com/joaollima7/projeto-integrador-Nexus/blob/4cf4496bb3e066e6aa5e45c24cb336bd522853b3/tests/regras.c)
- [Pacote original](https://github.com/joaollima7/projeto-integrador-Nexus/blob/4cf4496bb3e066e6aa5e45c24cb336bd522853b3/docs/pif-u2/entrega.md)

Atualização destas evidências documentais: commit local nesta branch, ainda NÃO publicado. O pacote original vinculado acima contém registros anteriores ao merge, corrigidos apenas nesta atualização local.

Pendentes: [URL DO VÍDEO 2–3 MIN], [CONFIRMAÇÃO DOS INTEGRANTES], [LINK LMC/PERMISSÕES FDS], [VALIDAÇÃO VISUAL/TECLADO REAL]. Sprint sob responsabilidade do Tech Lead, sem alteração ou confirmação por esta validação. Não marcar o ticket como concluído.

## Checklist e veredito

- Resolvido: compilação, testes existentes, simulação completa, links GitHub, atualização documental local, roteiro e texto Jira.
- Confirmação externa: equipe/contribuições, links FDS/LMC, renderização e teclado real em ambiente que permita executar o jogo.
- Vídeo: gravação real, publicação e URL obrigatórias; não produzido nem simulado como vídeo real.
- Autorização: publicação das correções documentais locais ainda não autorizada.

**NO-GO para entrega acadêmica integral neste momento:** falta vídeo obrigatório e validação externa. Código sem defeito concreto identificado nos cenários executados. Jira não modificado; sprint permanece responsabilidade do Tech Lead.
