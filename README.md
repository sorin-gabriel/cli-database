Implementarea urmareste modularizarea componentelor, astfel incat fiecare
functie sa indeplineasca o singura sarcina, de exemplu:
- o functie care gaseste un tabel in baza de date, pe baza unui nume
- o functie care genereaza (sterge) coloanele (liniile, celulele) unui tabel
- o functie care seteaza tipul de date al tabelului
- o functie care ofera indexul unei coloane, utilizat pentru a verifica
valorile celulelor din acea coloana (la comenzile delete, search)
- o functie care compara un int (float, string) cu o valoare de referinta,
folosind operatorul precizat

Modularizarea si tratarea in mod separat a diferitelor tipuri de date (int,
float, string) permite scrierea unor functii mai scurte, cu precizarea ca
numarul functiilor este mai mare decat daca as fi folosit o implementare
generica, care, pe alocuri, nu ar fi tinut seama de tipul de date prelucrat.
