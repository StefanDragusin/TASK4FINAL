# Pentru mai multe detalii accesati: https://site-pa.netlify.app/proiecte/game_of_life/#task1

`Asigurati-va ca aveti instalata comanda 'gcc'`

regula_B()/regula_clasica() - in functie de nod, se aplica una dintre reguli construieste
creeaza_nod(), construieste_arbore(), elibereaza_arbore() - sunt functii pentru arborele de generatii(creare nod, constructie arbore si eliberare memorie)
este_vecin() - verifica daca 2 celule sunt vecine
lex_mai_mic() - compara 2 solutii lexicografic
dfs() - gasire componente conexe
backtrack() - cauta toate drumurile, retine cel mai lung drum
proceseaza_si_afiseaza() - pentru o generatie cauta lantul Hamiltonian optim, daca nu gaseste afiseaza -1
proceseaza_frunze() - proceseaza fiecare generatie finala, apel direct la proceseaza_si_afiseaza() pentru frunze
