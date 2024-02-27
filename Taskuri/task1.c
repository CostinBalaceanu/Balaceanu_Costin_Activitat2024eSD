#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Biblioteca Biblioteca;

struct Biblioteca {

	int id;
	char* denumire;
	char* locatie;
	int nrCarti;
	
	
};


Biblioteca citireBiblioteca() {
	Biblioteca b;
	printf("\nID:");
	scanf_s("%d", &b.id);
	getchar();
	printf("\nDenumire:");
	b.denumire= (char*)malloc(sizeof(char) * 256);
	fgets(b.denumire, 256, stdin);
	printf("\nLocatie:");
	b.locatie = (char*)malloc(sizeof(char) * 256);
	fgets(b.locatie, 256, stdin);
	printf("\nNumar carti:");
	scanf_s("%d", &b.nrCarti);

	return b;

}

float calculIncasariImprumuturi(Biblioteca b) {
	float costPerCarte = 10.2;
	return costPerCarte * b.nrCarti;
}

void modificaNrCarti(Biblioteca* b, int nouNrCarti) {
	b->nrCarti = nouNrCarti;
	
}

void afiseazaBiblioteca(Biblioteca b) {
	printf("\nID: %d", b.id);
	printf("\nDenumire: %s", b.denumire);
	printf("\nLocatie: %s", b.locatie);
	printf("\nNumar carti: %d", b.nrCarti);
}

void main() {
	Biblioteca biblioteca1 = citireBiblioteca();
	printf("\nIncasari imprumuturi %s: %5.2f", biblioteca1.denumire, calculIncasariImprumuturi(biblioteca1));
	afiseazaBiblioteca(biblioteca1);
	modificaNrCarti(&biblioteca1, 122);
	afiseazaBiblioteca(biblioteca1);
}