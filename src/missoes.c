#include "missoes.h"
#include <string.h>
const int tabelaConjuncao[4][2] = {{1,1},{1,0},{0,1},{0,0}};
const Pergunta verdade[6] = {
 {"  Qual o valor logico de p?\n", {"Verdadeiro", "Falso", ""}, 'F', 0},
 {"  Qual o valor logico de ~p (negacao de p)?\n", {"Verdadeiro", "Falso", ""}, 'V', 20},
 {"\n  Qual o valor de p ^ q nessa linha?\n", {"Verdadeiro", "Falso", ""}, 'V', 0},
 {"\n  Qual o valor de p ^ q nessa linha?\n", {"Verdadeiro", "Falso", ""}, 'F', 0},
 {"\n  Qual o valor de p ^ q nessa linha?\n", {"Verdadeiro", "Falso", ""}, 'F', 0},
 {"\n  Qual o valor de p ^ q nessa linha?\n", {"Verdadeiro", "Falso", ""}, 'F', 20}
};
const Pergunta privacidade[3] = {
 {"A IA recomenda livros. Quais dados minimos conservar?", {"Preferencias de leitura", "Senha bancaria", "Todos os dados pessoais"}, '1', 20},
 {"Acesso = autorizacao E necessidade. V E F permite acesso?", {"Sim", "Nao", "Sempre"}, '2', 20},
 {"Como divulgar resultados sem identificar leitores?", {"Publicar nomes", "Publicar senhas", "Usar estatisticas anonimas"}, '3', 20}
};
Resultado corrigir(const Pergunta *p, char tecla) {
 /* Consulta limitada a string constante terminada em NUL. */
 if (tecla == '\0' || strchr((p->resposta == 'V' || p->resposta == 'F') ? "VF" : "123", tecla) == NULL) return INVALIDA;
 return tecla == p->resposta ? CORRETA : INCORRETA;
}
