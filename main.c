#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main() {
    FILE *fin = fopen("tn.in", "r");
    if (!fin) {
        perror("Eroare la deschiderea input.txt");
        return 1;
    }

    fscanf(fin, "%d", &T);
    fscanf(fin, "%d %d", &N, &M);
    fscanf(fin, "%d", &K);
    for (int i = 0; i < N; i++)
        fscanf(fin, "%s", grila[i]);
    fclose(fin);
    
    FILE *fout = fopen("resn.out", "w");
    if (!fout) {
        perror("Eroare la deschiderea output.txt");
        return 1;
    }

    if (K == 1) {
        Node *rad = creeaza_nod(grila);
        char b[MAXN][MAXN + 1], c[MAXN][MAXN + 1];

        regula_B(b, grila);
        rad->stanga = creeaza_nod(b);

        regula_clasica(c, grila);
        rad->dreapta = creeaza_nod(c);

        proceseaza_si_afiseaza(rad->grila, fout);
        proceseaza_si_afiseaza(rad->stanga->grila, fout);
        proceseaza_si_afiseaza(rad->dreapta->grila, fout);

        elibereaza_arbore(rad);
    } else {
        proceseaza_si_afiseaza(grila, fout);
    }

    fclose(fout);
    return 0;
}
