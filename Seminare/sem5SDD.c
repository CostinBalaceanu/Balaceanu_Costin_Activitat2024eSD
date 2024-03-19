#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod {
	Biblioteca info;
	Nod* next;
};

Biblioteca initializareBiblioteca(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca biblioteca;
	biblioteca.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(biblioteca.nume, nume);
	biblioteca.nrCarti = nrCarti;
	biblioteca.nrCititori = nrCititori;
	return biblioteca;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareBiblioteca(b.nume, b.nrCarti, b.nrCititori);
	nou->next = cap;
	return nou;
}

void inserareFinal(Nod** cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareBiblioteca(b.nume, b.nrCarti, b.nrCititori); //deepcopy
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = (*cap);
		while (aux->next != NULL) {
			aux = aux->next;//deplasare pana la ultimul nod
		}
		aux->next = nou;
	}
	else {
		(*cap) = nou;
	}

}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		printf("Biblioteca %s are %d carti si %d cititori\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		//procesare
		cap = cap->next;
	}
	printf("\n");
}

char* getBibliotecaNrCartiPerCititor(Nod* cap) {
	float max = 0;
	char* nume_aux = NULL;

	while (cap) {
		if (cap->info.nrCarti / cap->info.nrCititori > max) {
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}

		cap = cap->next;
	}
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);
	return nume;
}

void stergeLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void main() {
	Nod* cap = NULL;
	Biblioteca b1 = initializareBiblioteca("Mihai Eminescu", 150, 20);
	Biblioteca b2 = initializareBiblioteca("Ion Creanga", 200, 30);
	Biblioteca b3 = initializareBiblioteca("Tudor Arghezi", 100, 30);
	cap = inserareInceput(cap, b1);
	cap = inserareInceput(cap, b2);
	cap = inserareInceput(cap, b3);
	//cap = inserareInceput(cap, initializareBiblioteca("Ion Creanga", 200, 30));//alocam de 2 ori spatiu pentru biblioteca asa
	afisareLista(cap);
	char* numeAfisat = getBibliotecaNrCartiPerCititor(cap);
	printf("Biblioteca cu media maxima: %s\n", numeAfisat);

	Biblioteca b4 = initializareBiblioteca("Mihail Sadoveanu", 400, 50);
	inserareFinal(&cap, b4);
	afisareLista(cap);

	stergeLista(&cap);
	afisareLista(cap);
	free(b1.nume);
	free(b2.nume);
	free(b3.nume);
	free(b4.nume);
	free(numeAfisat);
}