#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int N, M, K, T;
char grila[MAXN][MAXN + 1];
int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

void regula_B(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int vecini = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && sursa[ni][nj] == 'X') {
                    vecini++;
                }
            }
            if (sursa[i][j] == 'X') {
                rezultat[i][j] = 'X';  // rămâne vie
            } else {
                rezultat[i][j] = (vecini == 2) ? 'X' : '+';  // doar cele moarte cu 2 vecini devin vii
            }
        }
        rezultat[i][M] = '\\0';
    }
}

void regula_clasica(char rezultat[MAXN][MAXN + 1], char sursa[MAXN][MAXN + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cnt = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && sursa[ni][nj] == 'X') {
                    cnt++;
                }
            }
            if (sursa[i][j] == 'X')
                rezultat[i][j] = (cnt == 2 || cnt == 3) ? 'X' : '+';
            else
                rezultat[i][j] = (cnt == 3) ? 'X' : '+';
        }
        rezultat[i][M] = '\0';
    }
}

typedef struct {
    Punct drum[MAXN * MAXN];
    int lungime;
} Solutie;

int este_vecin(Punct a, Punct b) {
    for (int d = 0; d < 8; d++)
        if (a.linie + dx[d] == b.linie && a.coloana + dy[d] == b.coloana)
            return 1;
    return 0;
}

int lex_mai_mic(Solutie a, Solutie b) {
    for (int i = 0; i <= a.lungime; i++) {
        if (a.drum[i].linie != b.drum[i].linie)
            return a.drum[i].linie < b.drum[i].linie;
        if (a.drum[i].coloana != b.drum[i].coloana)
            return a.drum[i].coloana < b.drum[i].coloana;
    }
    return 0;
}

void backtrack(Punct *v, int n, Punct *drum, int pas, int *max_len, Solutie *best, int target_len) {
    if (pas == target_len) {
        Solutie curent = {.lungime = pas};
        memcpy(curent.drum, drum, (pas + 1) * sizeof(Punct));
        if (best->lungime == -1 || lex_mai_mic(curent, *best)) {
            *best = curent;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        int valid = 1;
        for (int j = 0; j <= pas; j++) {
            if (drum[j].linie == v[i].linie && drum[j].coloana == v[i].coloana) {
                valid = 0; break;
            }
        }
        if (valid && este_vecin(drum[pas], v[i])) {
            drum[pas + 1] = v[i];
            backtrack(v, n, drum, pas + 1, max_len, best, target_len);
        }
    }
}

int viz[MAXN][MAXN];

void dfs(int i, int j, char g[MAXN][MAXN + 1], Punct *componenta, int *cnt) {
    viz[i][j] = 1;
    componenta[(*cnt)++] = (Punct){i, j};
    for (int d = 0; d < 8; d++) {
        int ni = i + dx[d], nj = j + dy[d];
        if (ni >= 0 && ni < N && nj >= 0 && nj < M &&
            g[ni][nj] == 'X' && !viz[ni][nj]) {
            dfs(ni, nj, g, componenta, cnt);
        }
    }
}

void proceseaza_si_afiseaza(char grila_proc[MAXN][MAXN + 1], FILE *fout) {
    memset(viz, 0, sizeof(viz));
    Solutie best = {.lungime = -1};

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (grila_proc[i][j] == 'X' && !viz[i][j]) {
                Punct componenta[MAXN * MAXN];
                int cnt = 0;
                dfs(i, j, grila_proc, componenta, &cnt);

                Solutie curent = {.lungime = -1};
                Punct drum[MAXN * MAXN];
                for (int x = 0; x < cnt; x++) {
                    drum[0] = componenta[x];
                    int len = -1;
                    backtrack(componenta, cnt, drum, 0, &len, &curent, cnt - 1);
                }

                if (curent.lungime == cnt - 1 &&
                    (best.lungime == -1 || curent.lungime > best.lungime || 
                    (curent.lungime == best.lungime && lex_mai_mic(curent, best)))) {
                    best = curent;
                }
            }

    if (best.lungime == -1) {
        fprintf(fout, "-1\n");
    } else {
        fprintf(fout, "%d\n", best.lungime);
        for (int i = 0; i <= best.lungime; i++) {
            fprintf(fout, "(%d ,%d)%s", best.drum[i].linie, best.drum[i].coloana,
                    i == best.lungime ? "\n" : " ");
        }
    }
}

Node* creeaza_nod(char g[MAXN][MAXN + 1]) {
    Node *nod = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < N; i++)
        strcpy(nod->grila[i], g[i]);
    nod->stanga = nod->dreapta = NULL;
    return nod;
}

void construieste_arbore(Node *nod, int nivel) {
    if (nivel == 0) return;
    char st[MAXN][MAXN + 1], dr[MAXN][MAXN + 1];
    regula_B(st, nod->grila);
    regula_clasica(dr, nod->grila);
    nod->stanga = creeaza_nod(st);
    nod->dreapta = creeaza_nod(dr);
    construieste_arbore(nod->stanga, nivel - 1);
    construieste_arbore(nod->dreapta, nivel - 1);
}

void proceseaza_frunze(Node *nod, int nivel, int cur, FILE *fout) {
    if (!nod) return;
    if (cur == nivel) {
        proceseaza_si_afiseaza(nod->grila, fout);
        return;
    }
    proceseaza_frunze(nod->stanga, nivel, cur + 1, fout);
    proceseaza_frunze(nod->dreapta, nivel, cur + 1, fout);
}

void elibereaza_arbore(Node *nod) {
    if (!nod) return;
    elibereaza_arbore(nod->stanga);
    elibereaza_arbore(nod->dreapta);
    free(nod);
}