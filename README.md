<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/1108ca33-4437-470d-86ca-d7bef468be8a" />

## 📑 Sumário

- [📖 Sobre o jogo](#-sobre-o-jogo)
- [🎯 Objetivo](#-objetivo)
- [⭐ Principais características](#-principais-características)
- [🕹️ Controles](#️-controles)
- [🗺️ Como funciona a aventura](#️-como-funciona-a-aventura)
- [🧩 Sistema de jogo](#-sistema-de-jogo)
- [🛠️ Tecnologias](#️-tecnologias)
- [📦 Status do desenvolvimento](#-status-do-desenvolvimento)
- [▶️ Como compilar e executar no VS Code](#️-como-compilar-e-executar-no-vs-code)
- [💻 Detalhes técnicos da Etapa 1 (PIF)](#-detalhes-técnicos-da-etapa-1-pif)
- [👥 Integrantes](#-integrantes)
- [🚀 Proposta do projeto](#-proposta-do-projeto)
- [📎 Anexos](#-anexos)

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
| Próximas etapas | Fase 2, Fase 3, Fase Final, salvamento em arquivo e regras/pontuação em Haskell | 🔜 Em desenvolvimento |

Nesta etapa, todo o código está no arquivo `nexus.c`, na raiz do repositório.

---

## ▶️ Como compilar e executar no VS Code

### 1. Abrir o projeto no VS Code

Clone o repositório:

```bash
git clone <https://github.com/joaollima7/projeto-integrador-Nexus.git>
```

No VS Code, vá em **Arquivo > Abrir Pasta...** (*File > Open Folder...*) e selecione a pasta do repositório.

### 2. Abrir o terminal integrado

Vá em **Terminal > Novo Terminal** (*Terminal > New Terminal*) ou use o atalho **Ctrl + '**. O terminal abre na parte de baixo da janela, já dentro da pasta do projeto.

### 3. Compilar

No terminal, digite:

```bash
gcc -Wall -Wextra -std=c99 nexus.c -o nexus.exe
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

## 👥 Integrantes  

| Rodrigo Alves |  
| João Victor Queiroz |  
| João Victor Nicacio |  
| João Guilherme Queiroz |  
| Danilo Barros |  
| Gustavo Cassemiro |  
| Daniel Luiz |  
| Fernando Araújo |  
| Lucas Collier |  
  
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
