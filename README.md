# NEXUS — PIF Unidade 2
Jogo educativo em C para terminal Windows, squad NEXUS, Projeto Integrador CESAR School.

## Versão jogável
1. **Central da Verdade:** explorar, ler a pista, corrigir negação no C1 e conjunção no C2, abrir a porta e coletar a Chave da Verdade (80 pontos). C1 e C2 são etapas de uma missão.
2. **Setor de Privacidade:** após a chave, pressionar E e corrigir três decisões da IA sobre minimização de dados, autorização e anonimização. A terceira resposta correta entrega a Chave da Privacidade (+60 pontos).

Erros não retiram pontos nem avançam perguntas; ficam registrados no resumo. Total: 140 pontos. Ao concluir, 1 reinicia, 2 volta ao menu, 3 sai.

## Compilar e executar
Requer GCC/MinGW no Windows:
```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror src/nexus.c src/jogo.c src/mapa.c src/terminal.c src/missoes.c -o nexus.exe
.\nexus.exe
```
Controles sem Enter: WASD move, E interage, I inventário, Q retorna/sai com confirmação. V/F responde na missão 1; 1/2/3 na missão 2. P apenas informa que salvamento não está disponível.

## Novidades e conteúdos U2
Segunda missão, perguntas em estruturas, vetor de perguntas, matrizes de alternativas e tabela lógica, enum de resultado, switch no menu e string.h (strchr sobre string constante terminada em NUL, sem cópias). Permanecem if/else, ternário, funções com parâmetros/retorno, protótipos, typedef struct e modularização.

## Arquivos
- src/nexus.c: laço principal.
- src/jogo.c e .h: estado, progressão e pontuação.
- src/mapa.c e .h: colisões e interação.
- src/terminal.c e .h: telas e validação de teclas.
- src/missoes.c e .h: dados dos desafios e correção da missão 2.
- tests/regras.c: testes automatizados de regras e percurso completo.
- [Pacote PI2-33 e PI2-36](docs/pif-u2/entrega.md): matriz antes/depois, evidências, roteiro e pendências.

## Testar
```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic -Werror tests/regras.c src/jogo.c src/mapa.c src/missoes.c -o testes.exe
.\testes.exe
```

## Limitações e demonstração
Somente Windows (conio.h). Não há salvamento, Haskell, terceira missão nem escape final nesta entrega. O inventário ainda reserva uma chave da Justiça futura. Testes automatizados não comprovam desenho nem captura real de teclado; fazer a demonstração conforme roteiro do pacote. Os links históricos abaixo foram preservados, mas acesso/permissões precisam de conferência da equipe. Vídeo específico de PIF U2: **PENDENTE**.

[Repositório da squad](https://github.com/joaollima7/projeto-integrador-Nexus)

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/1108ca33-4437-470d-86ca-d7bef468be8a" />

## 📑 Sumário

- [🧭 Guia rápido do repositório](#-guia-rápido-do-repositório)
- [📖 Sobre o jogo](#-sobre-o-jogo)
- [🎯 Objetivo](#-objetivo)
- [⭐ Principais características](#-principais-características)
- [🕹️ Controles](#️-controles)
- [🗺️ Como funciona a aventura](#️-como-funciona-a-aventura)
- [🧩 Sistema de jogo](#-sistema-de-jogo)
- [🛠️ Tecnologias](#️-tecnologias)
- [📦 Status do desenvolvimento](#-status-do-desenvolvimento)
- [▶️ Como compilar e executar no VS Code](#️-como-compilar-e-executar-no-vs-code)
- [📁 Estrutura do código](#-estrutura-do-código)
- [🔗 Rastreabilidade das histórias de usuário](#-rastreabilidade-das-histórias-de-usuário)
- [🧪 Testes de sistema](#-testes-de-sistema)
- [🐞 Issues e correções](#-issues-e-correções)
- [📈 Evolução do projeto](#-evolução-do-projeto)
- [💻 Detalhes técnicos da Etapa 1 (PIF)](#-detalhes-técnicos-da-etapa-1-pif)
- [📚 Documentação de FDS](#-documentação-de-fds)
- [🤝 Como contribuir](#-como-contribuir)
- [👥 Integrantes](#-integrantes)
- [🚀 Proposta do projeto](#-proposta-do-projeto)
- [📎 Anexos](#-anexos)

---

## 🧭 Guia rápido do repositório

| Pergunta | Onde encontrar |
|---|---|
| Quem é o time? | [👥 Integrantes](#-integrantes) |
| Qual problema está sendo resolvido? | [📖 Sobre o jogo](#-sobre-o-jogo) e [🚀 Proposta do projeto](#-proposta-do-projeto) |
| Como executar o projeto? | [▶️ Como compilar e executar no VS Code](#️-como-compilar-e-executar-no-vs-code) |
| Quais funcionalidades existem? | [📦 Status do desenvolvimento](#-status-do-desenvolvimento) e [🔗 Rastreabilidade](#-rastreabilidade-das-histórias-de-usuário) |
| Como o software evoluiu? | [📈 Evolução do projeto](#-evolução-do-projeto) |
| Quais issues foram tratadas? | [🐞 Issues e correções](#-issues-e-correções) |
| Quais evidências foram produzidas? | [🧪 Testes de sistema](#-testes-de-sistema) e [📚 Documentação de FDS](#-documentação-de-fds) (screencasts, sprint e backlog) |
| Como contribuir? | [🤝 Como contribuir](#-como-contribuir) |
| Onde estão protótipos, diagramas e screencasts? | [📎 Anexos](#-anexos) e [📚 Documentação de FDS](#-documentação-de-fds) |

---

## 📖 Sobre o jogo

**NEXUS** é um jogo educativo de aventura e exploração desenvolvido para ser executado diretamente no terminal.

O jogador fica preso dentro de um sistema controlado por uma Inteligência Artificial chamada **NEXUS**. Para conseguir escapar, será necessário explorar os mapas, encontrar pistas, investigar computadores, resolver problemas e coletar três chaves de segurança.

Durante a aventura, o jogador entra em contato com conceitos importantes relacionados ao uso da Inteligência Artificial, como:

- 🧠 Informações falsas e alucinações;
- 🔐 Privacidade e proteção de dados;
- ⚖️ Viés e decisões injustas;
- 🤖 Decisões automatizadas.

A proposta é transformar esses assuntos em uma experiência simples e interativa, utilizando exploração e resolução de situações dentro do próprio jogo.

---

## 🎯 Objetivo

O objetivo principal é conseguir as três chaves de segurança:

- 🔑 Chave da Verdade
- 🔑 Chave da Privacidade
- 🔑 Chave da Justiça

Depois de conseguir todas elas, o jogador precisa chegar até a porta de saída para escapar do sistema NEXUS.

---

## ⭐ Principais características

- 🎮 Aventura e exploração em modo terminal;
- 🗺️ Mapas diferentes em cada fase;
- 🚶 Movimentação pelo mapa;
- 🔎 Exploração e descoberta de pistas;
- 💻 Interação com computadores e objetos;
- 🔑 Sistema de itens e chaves;
- 📊 Sistema de pontuação;
- 💾 Salvamento do progresso;
- 🧠 Conteúdo educativo sobre Inteligência Artificial;
- 🏆 Fase final com objetivo de escapar do sistema.

---

## 🕹️ Controles

O jogo utiliza comandos simples para facilitar a navegação. **Não é preciso apertar ENTER:** o jogo reage assim que você aperta a tecla. Letras maiúsculas e minúsculas funcionam.

| Tecla | Função |
|:---:|---|
| `W` | Mover para cima |
| `S` | Mover para baixo |
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `E` | Interagir com objetos e computadores (ao lado do jogador) |
| `I` | Abrir o inventário |
| `P` | Salvar o jogo (o salvamento em arquivo será implementado em uma próxima etapa) |
| `Q` | Sair do jogo (pede confirmação) |

**Símbolos do mapa:**

| Símbolo | Significado |
|:---:|---|
| `P` | Jogador |
| `#` | Parede |
| `.` | Chão |
| `?` | Pista |
| `C` | Computador |
| `D` | Porta |
| `/` | Porta aberta |
| `K` | Chave |

> 💡 **Dica:** explore o mapa com atenção. Algumas informações importantes estão espalhadas pelo cenário.

---

## 🗺️ Como funciona a aventura

A aventura é dividida em três fases principais e uma etapa final.

### 🧠 Fase 1 — Central da Verdade

O sistema NEXUS apresenta informações incorretas em um de seus computadores.

O jogador deve:

1. Explorar o mapa;
2. Encontrar uma pista;
3. Investigar os computadores;
4. Descobrir qual deles apresenta o erro;
5. Corrigir o sistema;
6. Coletar a Chave da Verdade.

**Tema:** informações falsas e confiabilidade das informações geradas por IA.

#### ✅ Roteiro implementado (Etapa 1)

1. **Explore** o mapa e encontre a **pista `?`**: *"O servidor principal foi desligado às 22h."* (+10 pontos)
2. No **computador C1**, julgue as afirmações da IA: **p** ("o servidor está ligado") e **~p**. A afirmação p é uma **alucinação**. (+20 pontos)
3. No **computador C2**, complete a **tabela-verdade da conjunção (p ∧ q)** do filtro de confiança. (+20 pontos)
4. A **porta D** abre somente se **C1 E C2** estiverem corrigidos (`portaAberta = computador1Resolvido && computador2Resolvido`).
5. Atrás da porta, pegue a **Chave da Verdade `K`**. (+30 pontos)
6. Ao final, o jogo mostra a pontuação e pergunta se você quer **jogar novamente, voltar ao menu ou sair**.

### 🔐 Fase 2 — Setor de Privacidade

O sistema está armazenando informações pessoais que não são necessárias para realizar suas tarefas.

O jogador deve explorar o setor, encontrar os arquivos necessários e descobrir um código para desbloquear o sistema.

Ao concluir a missão, recebe a Chave da Privacidade.

**Tema:** privacidade e uso responsável de dados.

### ⚖️ Fase 3 — Núcleo da Justiça

O sistema de decisões da NEXUS está utilizando uma informação inadequada para tomar uma decisão.

O jogador deve:

1. Encontrar uma pista;
2. Investigar os computadores;
3. Identificar a informação que está causando o problema;
4. Corrigir o sistema;
5. Coletar a Chave da Justiça.

**Tema:** viés e decisões automatizadas.

### 🚪 Fase Final — Escape

Depois de conseguir as três chaves, o jogador finalmente pode chegar à porta de saída.

```
[ Chave da Verdade ]       ✓
[ Chave da Privacidade ]   ✓
[ Chave da Justiça ]       ✓

          ↓

      PORTA FINAL

          ↓

       ESCAPE!
```

Se todas as chaves tiverem sido encontradas, a porta é desbloqueada e o jogador consegue escapar do sistema.

---

## 🧩 Sistema de jogo

O NEXUS foi pensado para utilizar mecânicas simples e reaproveitáveis.

### 🔎 Exploração

O jogador percorre os mapas procurando objetos, pistas e computadores. Paredes e objetos bloqueiam a passagem: o personagem não atravessa obstáculos.

### 💻 Interação

Ao encontrar um objeto importante, o jogador pode utilizar a tecla `E` para interagir com ele.

### 🎒 Inventário

As chaves e outros itens encontrados ficam registrados no inventário do jogador.

### 📊 Pontuação

O jogador recebe pontos ao completar determinadas tarefas e resolver os problemas encontrados nas fases:

| Ação | Pontos |
|---|:---:|
| Encontrar uma pista | +10 |
| Corrigir um computador | +20 |
| Coletar uma chave | +30 |

Pontuação máxima da Fase 1: **80 pontos**.

### 💾 Salvamento

O progresso pode ser salvo para que o jogador continue a aventura posteriormente. *(O salvamento em arquivo será implementado em uma próxima etapa.)*

---

## 🛠️ Tecnologias

- **C** — desenvolvimento principal do jogo, menus, movimentação, mapas e fluxo das fases;
- **Haskell** — regras e pontuação;
- **Arquivos** — armazenamento do progresso e informações do jogo;
- **Terminal** — interface principal da experiência.

> 🪟 **Plataforma:** o jogo foi feito para **Windows**. Ele usa a biblioteca `conio.h`, que só existe no Windows, para ler as teclas sem precisar apertar ENTER.

---

## 📦 Status do desenvolvimento

| Etapa | Conteúdo | Status |
|---|---|:---:|
| **Etapa 1 – PIF** | Núcleo imperativo em C: menu principal e Fase 1 (Central da Verdade) jogáveis do início ao fim | ✅ Concluída |
| **Modularização** | Código dividido em módulos (`jogo`, `mapa`, `terminal`) com structs e funções | ✅ Concluída |
| **Correções e melhorias** | Defeitos D1 e D2 corrigidos e lógica proposicional mais clara na interface | ✅ Concluída |
| Próximas etapas | Fase 2, Fase 3, Fase Final, salvamento em arquivo e regras/pontuação em Haskell | 🔜 Em desenvolvimento |

**Histórias de usuário implementadas no código atual:** US01 a US07 (veja a [🔗 Rastreabilidade](#-rastreabilidade-das-histórias-de-usuário)).

O código-fonte fica na pasta [`src/`](src/) (veja a [📁 Estrutura do código](#-estrutura-do-código)).

---

## ▶️ Como compilar e executar no VS Code

### 1. Abrir o projeto no VS Code

Clone o repositório:

```bash
git clone https://github.com/joaollima7/projeto-integrador-Nexus.git
```

No VS Code, vá em **Arquivo > Abrir Pasta...** (*File > Open Folder...*) e selecione a pasta do repositório.

### 2. Abrir o terminal integrado

Vá em **Terminal > Novo Terminal** (*Terminal > New Terminal*) ou use o atalho **Ctrl + '**. O terminal abre na parte de baixo da janela, já dentro da pasta do projeto.

### 3. Compilar

No terminal, digite:

```bash
gcc -Wall -Wextra -std=c99 src/nexus.c src/jogo.c src/mapa.c src/terminal.c -o nexus.exe
```

O código compila **sem erros e sem avisos (warnings)**, mesmo com as opções `-Wall -Wextra`. Depois da compilação, o arquivo `nexus.exe` aparece na pasta do projeto.

### 4. Executar

No mesmo terminal, digite:

```bash
.\nexus.exe
```

> 💡 **Dicas:**
> - Use o **terminal integrado** (passo 2) para executar o jogo. A aba *Output* (usada por extensões como o botão "Run Code") não consegue ler as teclas do jogo.
> - **Clique dentro do terminal** antes de começar a jogar, para que as teclas sejam enviadas ao jogo.
> - Para ver melhor o mapa, aumente a área do terminal arrastando a borda dele para cima.

---

## 📁 Estrutura do código

```
projeto-integrador-Nexus/
├── src/
│   ├── nexus.c       → função main e game loop
│   ├── jogo.h / jogo.c       → estado da partida (structs), fluxo das telas e regras
│   ├── mapa.h / mapa.c       → mapa da Fase 1 e busca de objetos próximos
│   └── terminal.h / terminal.c → desenho das telas e leitura das teclas
├── .gitignore        → ignora os arquivos .exe gerados na compilação
└── README.md
```

| Arquivo | Principais funções | Responsabilidade |
|---|---|---|
| `src/nexus.c` | `main` | Inicia o jogo e repete o game loop até o jogador sair |
| `src/jogo.c` | `iniciarJogo`, `reiniciarSePedido`, `aplicarMovimento`, `processarTecla` | Estado da partida, regras e troca de telas |
| `src/mapa.c` | `celulaDoMapa`, `procurarObjetoProximo` | Símbolo de cada posição do mapa, colisão e objetos ao alcance da tecla `E` |
| `src/terminal.c` | `desenharTela`, `lerTecla`, `mostrarDespedida` | Interface no terminal e validação das teclas |

---

## 🔗 Rastreabilidade das histórias de usuário

Cada história pode ser seguida da necessidade até a entrega: **história → board → commit → código → teste → evidência**.

| História | Funcionalidade | Status | Código | Commits | Testes | Screencasts |
|---|---|:---:|---|---|---|---|
| **US01** | Iniciar o jogo pelo menu | ✅ | `terminal.c` (`desenharTela`, `lerTecla`), `jogo.c` (`processarTecla`) | [6522bce](https://github.com/joaollima7/projeto-integrador-Nexus/commit/6522bce), [2cbfe0e](https://github.com/joaollima7/projeto-integrador-Nexus/commit/2cbfe0e) | TS01, TS02, TS14, TS15 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US02** | Ver as instruções | ✅ | `terminal.c` (`desenharTela`) | [6522bce](https://github.com/joaollima7/projeto-integrador-Nexus/commit/6522bce) | TS03 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US03** | Movimentar o personagem sem atravessar paredes | ✅ | `mapa.c` (`celulaDoMapa`), `jogo.c` (`aplicarMovimento`) | [6522bce](https://github.com/joaollima7/projeto-integrador-Nexus/commit/6522bce), [9f8a95d](https://github.com/joaollima7/projeto-integrador-Nexus/commit/9f8a95d) | TS04, TS05 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US04** | Interagir com objetos (tecla `E`) | ✅ | `mapa.c` (`procurarObjetoProximo`), `jogo.c` (`processarTecla`) | [2570399](https://github.com/joaollima7/projeto-integrador-Nexus/commit/2570399), [47c50aa](https://github.com/joaollima7/projeto-integrador-Nexus/commit/47c50aa) | TS06 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US05** | Encontrar a pista da Fase 1 | ✅ | `jogo.c` (`processarTecla`), `terminal.c` (`desenharTela`) | [2570399](https://github.com/joaollima7/projeto-integrador-Nexus/commit/2570399) | TS07 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US06** | Investigar os computadores e identificar o erro | ✅ | `jogo.c` (`processarTecla`), `terminal.c` (`desenharTela`) | [2570399](https://github.com/joaollima7/projeto-integrador-Nexus/commit/2570399), [bf3efbf](https://github.com/joaollima7/projeto-integrador-Nexus/commit/bf3efbf), [9288416](https://github.com/joaollima7/projeto-integrador-Nexus/commit/9288416) | TS08, TS09, TS10 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| **US07** | Corrigir o sistema e liberar a Chave da Verdade | ✅ | `jogo.c` (`processarTecla`), `mapa.c` (`celulaDoMapa`) | [1256ab7](https://github.com/joaollima7/projeto-integrador-Nexus/commit/1256ab7), [b616b93](https://github.com/joaollima7/projeto-integrador-Nexus/commit/b616b93) | TS11, TS12, TS13 | [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing) |
| US08 | Encontrar arquivos na Fase 2 | 🔜 | — | — | — | — |
| US09 | Evitar dados pessoais desnecessários | 🔜 | — | — | — | — |
| US10 | Encontrar o código de acesso | 🔜 | — | — | — | — |
| US11 | Receber a Chave da Privacidade | 🔜 | — | — | — | — |
| US12 | Encontrar a pista da Fase 3 | 🔜 | — | — | — | — |
| US13 | Investigar os computadores da Fase 3 | 🔜 | — | — | — | — |
| US14 | Corrigir a decisão injusta e receber a Chave da Justiça | 🔜 | — | — | — | — |
| US15 | Usar as três chaves para abrir a saída | 🔜 | — | — | — | — |

**Legenda:** ✅ implementada · 🔜 planejada

As tarefas de cada história ficam no board do projeto (cards `PI2-xx`). Veja os prints na seção [📚 Documentação de FDS](#-documentação-de-fds).

---

## 🧪 Testes de sistema

Os testes foram feitos jogando o NEXUS como um usuário faria, apertando as teclas e conferindo o que aparece na tela.

| ID | História | Passos | Resultado esperado | Resultado |
|---|:---:|---|---|:---:|
| TS01 | US01 | No menu, apertar `1` | O mapa da Fase 1 aparece | ✅ Passou |
| TS02 | US01 | No menu, apertar `9` | Aviso "Tecla '9' invalida" e o jogo continua no menu | ✅ Passou |
| TS03 | US02 | No menu, apertar `2` | Instruções com os comandos W, A, S, D, E, I e P | ✅ Passou |
| TS04 | US03 | Iniciar o jogo e apertar `D` | O jogador anda uma casa para a direita | ✅ Passou |
| TS05 | US03 | Iniciar o jogo e apertar `W` (parede acima) | Mensagem "Caminho bloqueado" e o jogador não se move | ✅ Passou |
| TS06 | US04 | Iniciar o jogo e apertar `E` longe de objetos | Mensagem "Nada para interagir aqui" | ✅ Passou |
| TS07 | US05 | Andar até a pista `?` e apertar `E` | Tela "PISTA ENCONTRADA" com a explicação de alucinação e +10 pontos | ✅ Passou |
| TS08 | US06 | Ir ao C1 sem ter lido a pista e apertar `E` | Mensagem "O computador C1 esta bloqueado" | ✅ Passou |
| TS09 | US06 | No C1, responder `V` para p | Mensagem explicando que p é falsa | ✅ Passou |
| TS10 | US06 | No C1, responder `F` para p e `V` para ~p | Tela "SISTEMA CORRIGIDO" | ✅ Passou |
| TS11 | US07 | Apertar `E` na porta D antes de corrigir C1 e C2 | Mensagem "Porta D trancada" | ✅ Passou |
| TS12 | US07 | Ir ao C2 antes de corrigir o C1 | Mensagem "Acesso negado ao C2" | ✅ Passou |
| TS13 | US07 | Completar C1 e C2, passar pela porta e pegar a chave `K` | Porta destrancada, "CHAVE DA VERDADE OBTIDA" e "FASE 1 CONCLUIDA" com 80 de 80 pontos | ✅ Passou |
| TS14 | US01 | No fim da fase, apertar `1` (jogar novamente) | O jogo recomeça com 0 pontos | ✅ Passou |
| TS15 | US01 | No menu, apertar `3` e depois `S` | Pede confirmação e encerra com "Obrigado por jogar NEXUS!" | ✅ Passou |

---

## 🐞 Issues e correções

Cada correção foi feita em uma branch própria e entrou no código por Pull Request. Novos bugs devem ser registrados na aba [Issues](https://github.com/joaollima7/projeto-integrador-Nexus/issues).

| Problema | Correção | Card | Commit | Pull Request |
|---|---|:---:|---|:---:|
| Avisos de teclas inválidas instáveis na tela | Estabiliza a exibição dos avisos | PI2-28 | [e0aeb02](https://github.com/joaollima7/projeto-integrador-Nexus/commit/e0aeb02) | [#1](https://github.com/joaollima7/projeto-integrador-Nexus/pull/1) |
| Interação errada quando o jogador estava perto do C1 e do C2 ao mesmo tempo | Corrige a prioridade de interação entre C1 e C2 | PI2-28 | [47c50aa](https://github.com/joaollima7/projeto-integrador-Nexus/commit/47c50aa) | [#1](https://github.com/joaollima7/projeto-integrador-Nexus/pull/1) |
| **D1:** a porta não era reavaliada ao concluir C1 e C2 | Reavalia a porta ao concluir os dois computadores | PI2-31 | [b616b93](https://github.com/joaollima7/projeto-integrador-Nexus/commit/b616b93) | [#2](https://github.com/joaollima7/projeto-integrador-Nexus/pull/2) |
| **D2:** a negação no C1 não era calculada a partir do valor de p | Calcula ~p a partir do valor de p | PI2-31 | [bf3efbf](https://github.com/joaollima7/projeto-integrador-Nexus/commit/bf3efbf) | [#2](https://github.com/joaollima7/projeto-integrador-Nexus/pull/2) |
| A lógica proposicional ficava pouco clara para o jogador | Mostra legenda e raciocínio na interface dos computadores | PI2-38 | [9288416](https://github.com/joaollima7/projeto-integrador-Nexus/commit/9288416) | [#4](https://github.com/joaollima7/projeto-integrador-Nexus/pull/4) |

---

## 📈 Evolução do projeto

| Data | Marco | Commits / PRs |
|---|---|---|
| 03/09/2026 | Criação do repositório, README inicial e primeiros arquivos de estrutura | [466f524](https://github.com/joaollima7/projeto-integrador-Nexus/commit/466f524) |
| 08 a 10/09/2026 | README revisado com a ideia, as regras e os objetivos do jogo | [108c594](https://github.com/joaollima7/projeto-integrador-Nexus/commit/108c594), [bb6e567](https://github.com/joaollima7/projeto-integrador-Nexus/commit/bb6e567) |
| 08/10/2026 | Links do protótipo, do diagrama de atividades e do Trello | [0a64852](https://github.com/joaollima7/projeto-integrador-Nexus/commit/0a64852) |
| 12/10/2026 | **Etapa 1 (PIF):** menu e Fase 1 implementados em três passos | [6522bce](https://github.com/joaollima7/projeto-integrador-Nexus/commit/6522bce) → [2570399](https://github.com/joaollima7/projeto-integrador-Nexus/commit/2570399) → [1256ab7](https://github.com/joaollima7/projeto-integrador-Nexus/commit/1256ab7) |
| 15/10/2026 | Correção de bugs da Fase 1 | [e0aeb02](https://github.com/joaollima7/projeto-integrador-Nexus/commit/e0aeb02), [47c50aa](https://github.com/joaollima7/projeto-integrador-Nexus/commit/47c50aa) |
| 19/10/2026 | **Modularização:** código dividido em `jogo`, `mapa` e `terminal` | [PR #1](https://github.com/joaollima7/projeto-integrador-Nexus/pull/1) |
| 20/10/2026 | Correção dos defeitos D1 e D2 | [PR #2](https://github.com/joaollima7/projeto-integrador-Nexus/pull/2) |
| 22/10/2026 | README com a Entrega 3 de FDS (programação em pares, sprint e backlog) | [afa8620](https://github.com/joaollima7/projeto-integrador-Nexus/commit/afa8620) |
| 29/10 a 06/11/2026 | README com a Entrega 4 de FDS (sprint, backlog e screencasts) | [42f567c](https://github.com/joaollima7/projeto-integrador-Nexus/commit/42f567c) |
| 09/11/2026 | Lógica proposicional mais clara na interface | [PR #4](https://github.com/joaollima7/projeto-integrador-Nexus/pull/4) |

O histórico completo está em [Commits](https://github.com/joaollima7/projeto-integrador-Nexus/commits).

---

## 💻 Detalhes técnicos da Etapa 1 (PIF)

### Conteúdos de C utilizados

| Conteúdo | Onde aparece no código |
|---|---|
| Entrada e saída formatada | `printf` em todas as telas e leitura de teclas com `_getch()` |
| Variáveis e tipos de dados | `int` (posição, pontos, fase, chaves, estados) e `char` (tecla, símbolos do mapa) |
| Constantes | `#define` para telas, símbolos do mapa, posições dos objetos e pontuação |
| Operadores | `=` `+` `-` `*` `%` `+=` `++` `==` `!=` `<` `>` `<=` `>=` `&&` `\|\|` `!` `? :` |
| `if` / `else` | Escolha da tela a desenhar, regras do mapa, colisão, interação e respostas dos computadores |
| `while` | Game loop principal e validação de teclas inválidas |
| `for` | Desenho do mapa (linhas × colunas), tabela-verdade e busca de objetos próximos |

### Leitura de teclas sem ENTER

Com `scanf` ou `getchar`, o terminal só entrega o que foi digitado depois do ENTER. Para o jogo reagir na hora, o código usa duas bibliotecas do Windows:

| Recurso | Biblioteca | Para que serve |
|---|---|---|
| `_getch()` | `conio.h` | Lê a tecla assim que ela é apertada, sem mostrá-la na tela |
| `system("cls")` | `stdlib.h` | Limpa a tela antes de desenhar a próxima |

### Tratamento de entradas inválidas

Toda leitura de tecla fica dentro de um laço `while`, que só termina quando a tecla é válida para a tela atual. Se a tecla for inválida, o jogo mostra um aviso e espera outra, sem travar nem encerrar. Espaço, ENTER e as setas do teclado são ignorados.

---

## 📚 Documentação de FDS

> 📌 Os itens desta seção fazem parte das entregas da disciplina de **FDS (Fundamentos de Desenvolvimento de Software)**.

### 👥 Programação em pares (FDS)

| Integrantes | Implementação |
|---|---|
| João Victor Queiroz e Rodrigo Alves | Códigos dos arquivos `jogo.c` e `jogo.h` |
| João Guilherme Queiroz, Danilo Barros e João Victor Nicacio | Códigos dos arquivos `mapa.c`, `mapa.h`, `terminal.c` e `terminal.h` |

### 🏃 Sprint atual (FDS)

**Week 13e14 (26/10 a 06/11):** Entrega 4 de FDS

<img width="1569" height="707" alt="image" src="https://github.com/user-attachments/assets/a2a100a5-e08c-4412-881a-dbd75c8e626e" />

### 📋 Backlog (FDS)

<img width="1527" height="618" alt="image" src="https://github.com/user-attachments/assets/5a438a57-4d87-4bc6-ba3e-df2e03ccd2fb" />

### Screencast (FDS) - Entrega 3

https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk

### Screencast (FDS) - Entrega 4

https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing

---

## 🤝 Como contribuir

1. **Escolha uma tarefa no board** e mova o card para "Em andamento".
2. **Crie uma branch** a partir da `main`, com o código do card no nome:
   ```bash
   git checkout -b feat/pi2-XX-descricao-curta
   ```
   Use `feat/` para funcionalidades novas, `fix/` para correções e `docs/` para documentação.
3. **Faça commits pequenos**, com mensagens que expliquem o que mudou e citem o card:
   ```bash
   git commit -m "feat: adiciona arquivos da Fase 2 (PI2-XX)"
   ```
4. **Compile e teste** antes de enviar: o código deve compilar sem avisos com `-Wall -Wextra`, e os [testes de sistema](#-testes-de-sistema) devem continuar passando.
5. **Abra um Pull Request** para a `main`, descrevendo o que foi feito e qual história ou issue ele resolve.
6. **Atualize o board e o README** (status, rastreabilidade e testes) quando a tarefa for concluída.

Encontrou um bug? Abra uma [Issue](https://github.com/joaollima7/projeto-integrador-Nexus/issues) dizendo os passos para reproduzir, o resultado esperado e o resultado obtido.

---

## 👥 Integrantes

| Integrante | Função |
|---|---|
| Rodrigo Alves | Desenvolvimento principal em C e integração do jogo |
| João Victor Queiroz ([@jvqmg](https://github.com/jvqmg)) | Desenvolvimento dos mapas e movimentação |
| João Victor Nicacio | Sistema de interação e itens |
| João Guilherme Queiroz ([@joaoguilhermeqmg](https://github.com/joaoguilhermeqmg)) | Desenvolvimento das fases e missões |
| Danilo Barros | Sistema de pontuação e regras |
| Gustavo Cassemiro | Testes e correção de erros |
| Daniel Luiz | Sistema de salvamento e arquivos |
| Fernando Araújo | Apoio no desenvolvimento e organização do projeto |
| Lucas Collier ([@LucasCollier](https://github.com/LucasCollier)) | Modularização do código e correção de bugs |

---

## 🚀 Proposta do projeto

O NEXUS busca unir programação e aprendizado sobre Inteligência Artificial em uma experiência simples de jogar e desenvolver.

Em vez de apresentar os conceitos apenas como perguntas, o jogador aprende enquanto explora, investiga e resolve problemas dentro do sistema.

A missão é simples: encontrar as três chaves, corrigir os erros do sistema e escapar.

<p align="center">
  <b>🎮 NEXUS</b><br>
  <i>Explore o sistema. Descubra os erros. Recupere as chaves.<br>
  Escape do NEXUS</i>
</p>

---

## 📎 Anexos

- **Link do Trello:** https://trello.com/invite/b/6a99efa1bc0ba7766566dcf9/ATTI9fdd42898827a53c75effbdee9083b71BA91C41C/projeto-integrador-entregas-fds
- **Link do Protótipo Navegável Lo-Fi:** https://www.figma.com/design/KaKeypsS67eQHAWmZoUpev/NEXUS-—-Fluxo-de-Telas?node-id=0-1&t=RsjCwZyaYFWcjrjL-1
- **Link do Diagrama de Atividades:** https://www.figma.com/board/ECGOhLU5rYH2vMqNarHMec/Diagramas-de-atividades---FDS?node-id=0-1&t=GH0cTbkJmIx6VAhe-1
- **Screencasts:** [Entrega 3](https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk) · [Entrega 4](https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing)

## Fechamento técnico PIF U2
As perguntas das duas missões usam a estrutura Pergunta em src/missoes.c. C1/C2 agora consomem os enunciados, alternativas, respostas e pontos dessa estrutura, mantendo a saída textual e as recompensas originais. A correção é compartilhada com a Missão 2.

Regressões: compilação C99 sem avisos; duas missões, 140 pontos, erros, reinício, saída e regras de LMC aprovados. As oito telas de C1/C2 tiveram saída textual comparada com a versão anterior, sem diferenças. A execução interativa humana ainda está pendente.

Conferência de links: o pacote local existe; GitHub confirmado pela API: repositório público e PR #5 integrada. Os dois vídeos Drive não puderam ser confirmados pela ferramenta web. Figma/Trello e demais links históricos não verificados. Conferir permissões com a equipe. Vídeo específico PIF U2 e confirmação dos integrantes continuam pendentes. As seções históricas da Etapa 1 acima descrevem a versão anterior; o resumo U2 e este fechamento descrevem a versão atual.

## Evidências finais da PI2-36
Versão integrada pela [PR #5](https://github.com/joaollima7/projeto-integrador-Nexus/pull/5), commit 4cf4496bb3e066e6aa5e45c24cb336bd522853b3. Veja a [validação final](docs/pif-u2/validacao-final.md): compilação estrita, testes e simulação completa executados; execução interativa bloqueada pela política do Windows. Vídeo e conferências externas seguem pendentes. Esta atualização documental ainda é local.
