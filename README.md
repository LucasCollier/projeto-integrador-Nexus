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

O NEXUS foi pensado para utilizar mecânicas simples e
