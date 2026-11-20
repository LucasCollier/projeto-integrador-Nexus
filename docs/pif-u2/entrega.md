# PIF U2 — PI2-33 e PI2-36
Base: origin/main bd91b92, atualizada em 20/11/2026. Prazo: 25/11/2026.

## Matriz antes/depois
| Critério | Antes | Depois | Evidência |
|---|---|---|---|
| if/else e ternário | ATENDIDO | ATENDIDO | jogo.c/mapa.c |
| switch no menu | NÃO ATENDIDO | ATENDIDO | processarTecla |
| Funções, protótipos, parâmetros, retorno e módulos | ATENDIDO | ATENDIDO | src/*.h e src/*.c |
| Vetores, matrizes, strings | PARCIAL | ATENDIDO | missoes.c, alternativas, tabelaConjuncao |
| string.h com limites | NÃO ATENDIDO | ATENDIDO | corrigir: strchr em constante terminada em NUL |
| typedef struct | ATENDIDO | ATENDIDO | Jogo e Pergunta |
| enum | NÃO ATENDIDO | ATENDIDO | Resultado |
| Nomes, comentários, conteúdos U1 | ATENDIDO | ATENDIDO | módulos e laços existentes |
| Recursão/union/ponteiros adicionais | ATENDIDO | ATENDIDO | opcionais, não introduzidos |
| Compilar C99 | PARCIAL | ATENDIDO | GCC sem diagnósticos |
| Terminal interativo real | PARCIAL | PARCIAL | captura _getch e visual não verificados |
| Duas missões completas | NÃO ATENDIDO | ATENDIDO | Verdade e Privacidade; percurso automatizado |
| Dados de perguntas/respostas/pontos | NÃO ATENDIDO | ATENDIDO | verdade[]: enunciados, alternativas, respostas e pontos consumidos por terminal.c e jogo.c |
| Validação | ATENDIDO | ATENDIDO | lerTecla e corrigir |
| Reiniciar/sair | ATENDIDO | ATENDIDO | teste de estado |
| Modularizar menu/perguntas/correção/pontos | PARCIAL | ATENDIDO | terminal/jogo/missoes |
| Evitar duplicação | PARCIAL | ATENDIDO | corrigir compartilhada; textos de perguntas e pontos centralizados |
| Código U2 no GitHub | NÃO ATENDIDO | DEPENDE DA EQUIPE | apenas local, push não autorizado |
| README compilação/execução/novidades | PARCIAL | ATENDIDO | README |
| Links das demais disciplinas | PARCIAL | DEPENDE DA EQUIPE | FDS preservados, acesso não verificado; confirmar LMC |
| Vídeo 2–3 minutos e link | DEPENDE DA EQUIPE | DEPENDE DA EQUIPE | PENDENTE |
| Link repositório | ATENDIDO | ATENDIDO | link abaixo |
| Squad/integrantes | ATENDIDO | DEPENDE DA EQUIPE | nomes históricos no README, confirmar lista final |
| Commits distribuídos | PARCIAL | DEPENDE DA EQUIPE | múltiplos autores históricos; validar participação |

C1 e C2 são etapas de uma única missão. Haskell e persistência não são obrigatórios.

## PI2-33 — versão técnica e evidências
Segunda missão com três decisões de privacidade, 60 pontos e segunda chave; progressão após a primeira chave, reinício limpa ambos os estados. Menu switch, struct de perguntas, enum e matriz de alternativas.
APROVADO: compilação C99 com -Wall -Wextra -Wpedantic, sem diagnósticos.
APROVADO: tests/regras.c percorre desde menu por movimentos, pista, C1, C2, porta, chave, missão 2 e resumo com 140 pontos.
APROVADO: acertos/erros, entrada inválida no menu e missão 2, pontos, reinício, saída; regressão negação F/V e conjunção V/F/F/F.
NÃO VERIFICADO: execução visual/manual e captura de teclado real. Os testes chamam as funções de estado, não _getch.
Comandos reproduzíveis no README. Referências: git log --oneline origin/main..HEAD na branch feat/pif-u2-finalizacao.

## PI2-36 — texto de submissão
A squad NEXUS apresenta duas missões educativas em C: Central da Verdade e Setor de Privacidade. A versão inclui estruturas de dados, modularização, validação e reinício. Evidências reproduzíveis no README.
Repositório: https://github.com/joaollima7/projeto-integrador-Nexus
Commit publicado: PENDENTE DE APROVAÇÃO/PUBLICAÇÃO.
Vídeo PIF U2: PENDENTE.
Integrantes: confirmar lista histórica do README.

## Roteiro de vídeo — 2min40s
- 0:00–0:15: squad, integrantes, repositório e commit.
- 0:15–0:35: compilar com flags oficiais e mostrar entrada inválida no menu.
- 0:35–1:25: pista, erro no C1, correção F/V, C2 V/F/F/F, porta e chave.
- 1:25–2:05: objetivo da Privacidade, um erro, correção 1/2/3, segunda chave e 140 pontos.
- 2:05–2:25: reiniciar, mostrar estado zerado e sair.
- 2:25–2:40: módulos, enum, matriz e links.

## Checklist
- [x] Atualizar base, branch exclusiva, segunda missão, compilação e testes automatizados.
- [x] README, matriz, roteiro e texto de submissão.
- [x] Centralizar perguntas, alternativas, respostas e pontos da missão 1 em Pergunta.
- [ ] Validar terminal interativo real.
- [ ] Conferir links FDS/LMC, integrantes e histórico de participação.
- [ ] Gravar vídeo e inserir link.
- [ ] Aprovar/publicar commits e submeter até 25/11/2026.

## Veredito
GO CONDICIONAL para revisão da equipe. Não é entrega integral concluída: os critérios de implementação estão atendidos; permanecem validação interativa humana e entregáveis externos. Nenhum push, PR, merge, Jira ou publicação executado.

## Fechamento técnico complementar
Commits anteriores preservados: cabfa5a e d029013. Correção complementar registrada no commit mais recente desta branch (consultar git log -1).
- responderComputador1 e responderComputador2 usam corrigir e somam Pergunta.pontos antes de avançar. Mantidos 0/20 pontos em C1 e 0/0/0/20 em C2; pista 10 e chave 30 permanecem recompensas de exploração, não perguntas.
- desenharTela usa Pergunta.texto/alternativas/resposta. Explicações pedagógicas e regras da porta foram preservadas.
- APROVADO: C99 com -Wall -Wextra -Wpedantic e também -Werror, sem avisos.
- APROVADO: testes/regras.c ampliado verifica erro/acerto em cada uma das seis perguntas, ausência de pontos no erro, negação, quatro linhas da conjunção e porta. Percurso das duas missões confirma 140 pontos, reinício e saída.
- APROVADO: comparação automatizada da saída textual das oito telas C1/C2 (três estados do C1 e cinco do C2) contra HEAD anterior: saída idêntica. Harness temporário removido; isso não é inspeção visual/manual.
- Houve bloqueio inicial do executável pela política Windows, inclusive fora do sandbox; após recompilar os testes ampliados, a execução passou normalmente.

### Conferência dos links
O link relativo README -> docs/pif-u2/entrega.md existe. Consulta web ao repositório retornou Cache miss; ambos os screencasts Drive retornaram inacessível pela ferramenta. Esses resultados não comprovam links quebrados: acesso público não confirmado. Figma/Trello e demais links históricos não verificados. Nenhum endereço inventado ou substituído. Confirmar também artefato de LMC com a equipe.

### Pendências humanas e publicação
Vídeo PIF U2 de 2–3 minutos e URL; confirmação de integrantes/participação; execução interativa real no Windows; conferência de acesso aos artefatos FDS/LMC. Publicação depende da autorização do responsável. GO para revisão/publicação do código após autorização; GO CONDICIONAL para submissão acadêmica. Nenhum push, PR, merge ou Jira realizado.
