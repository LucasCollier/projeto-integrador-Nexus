#ifndef MISSOES_H
#define MISSOES_H
typedef enum { INVALIDA, INCORRETA, CORRETA } Resultado;
typedef struct { char texto[200]; char alternativas[3][100]; char resposta; int pontos; } Pergunta;
extern const Pergunta verdade[6];
extern const int tabelaConjuncao[4][2];
extern const Pergunta privacidade[3];
Resultado corrigir(const Pergunta *p, char tecla);
#endif
