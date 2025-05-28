#ifndef FUNCTII_H
#define FUNCTII_H

#define MAXN 100

typedef struct {
    int linie, coloana;
} Punct;

typedef struct Node {
    char grila[MAXN][MAXN + 1];
    struct Node *stanga;
    struct Node *dreapta;
} Node;

extern int N, M, K, T;
extern char grila[MAXN][MAXN + 1];

void regula_B(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]);
void regula_clasica(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]);
void proceseaza_si_afiseaza(char grila[MAXN][MAXN + 1], FILE *fout);

Node* creeaza_nod(char grila[MAXN][MAXN + 1]);
void construieste_arbore(Node *nod, int nivel);
void proceseaza_frunze(Node *nod, int nivel, int cur, FILE *fout);
void elibereaza_arbore(Node *nod);

#endif
