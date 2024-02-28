#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	b.denumire = (char*)malloc(sizeof(char) * 256);
	fgets(b.denumire, 256, stdin);
	printf("\nLocatie:");
	b.locatie = (char*)malloc(sizeof(char) * 256);
	fgets(b.locatie, 256, stdin);
	printf("\nNumar carti:");
	scanf_s("%d", &b.nrCarti);

	return b;

}

Biblioteca initializareBiblioteca(int id, const char* denumire, const char* locatie, int nrCarti) {
	Biblioteca b;
	b.id = id;
	b.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(b.denumire, denumire);
	b.locatie = (char*)malloc(sizeof(char) * (strlen(locatie) + 1));
	strcpy(b.locatie, locatie);
	b.nrCarti = nrCarti;
	return b;
}

Biblioteca* copiazaBiblioteci(Biblioteca* biblioteci, int nrBiblioteci) {
	Biblioteca* copie = (Biblioteca*)malloc(sizeof(Biblioteca) * nrBiblioteci);
	if (!copie) {
			return NULL;
		}
	for (int i = 0; i < nrBiblioteci; i++) {

		copie[i].id = biblioteci[i].id;
		copie[i].nrCarti = biblioteci[i].nrCarti;
		copie[i].denumire = (char*)malloc(sizeof(char) * (strlen(biblioteci[i].denumire) + 1));
		strcpy(copie[i].denumire, biblioteci[i].denumire);
		copie[i].locatie = (char*)malloc(sizeof(char) * (strlen(biblioteci[i].locatie) + 1));
		strcpy(copie[i].locatie, biblioteci[i].locatie);
	}
	return copie;
}

Biblioteca* copiazaBiblioteciPestePrag(Biblioteca* biblioteci,
	int nrBiblioteci, int pragCarti, int* nrBiblioteciPrag) {

	*nrBiblioteciPrag = 0;
	for (int i = 0; i < nrBiblioteci; i++) {
		if (biblioteci[i].nrCarti > pragCarti) {
			(*nrBiblioteciPrag)++;
		}
	}
	Biblioteca* b = (Biblioteca*)malloc(sizeof(Biblioteca) * (*nrBiblioteciPrag));
	int k = 0;
	for (int i = 0; i < nrBiblioteci; i++) {
		if (biblioteci[i].nrCarti > pragCarti) {
			b[k++] = initializareBiblioteca(biblioteci[i].id, biblioteci[i].denumire, biblioteci[i].locatie,
				biblioteci[i].nrCarti);
		}
	}
	return b;
}

Biblioteca* concateneazaVectori(Biblioteca* vector1, int nrBiblioteci1, Biblioteca* vector2, int nrBiblioteci2) {
	int nrTotalBiblioteci = nrBiblioteci1 + nrBiblioteci2;
	Biblioteca* vectorConcatenat = (Biblioteca*)malloc(sizeof(Biblioteca) * nrTotalBiblioteci);
	if (!vectorConcatenat) {
		return NULL;
	}
	for (int i = 0; i < nrBiblioteci1; i++) {
		vectorConcatenat[i] = initializareBiblioteca(vector1[i].id, vector1[i].denumire, vector1[i].locatie, vector1[i].nrCarti);
	}
	for (int i = 0; i < nrBiblioteci2; i++) {
		vectorConcatenat[nrBiblioteci1 + i] = initializareBiblioteca(vector2[i].id, vector2[i].denumire, vector2[i].locatie, vector2[i].nrCarti);
	}

	return vectorConcatenat;
}




double calculIncasariImprumuturi(Biblioteca b) {
	double costPerCarte = 10.2;
	return costPerCarte * b.nrCarti;
}

void modificaNrCarti(Biblioteca* b, int nouNrCarti) {
	b->nrCarti = nouNrCarti;

}

void afiseazaBiblioteca(Biblioteca b) {
	printf("\nID: %d", b.id);
	printf("\nDenumire: %s", b.denumire);
	printf("\nLocatie: %s", b.locatie);
	printf("\nNumar carti: %d\n", b.nrCarti);
}
void afisareVectorBiblioteci(Biblioteca* vector, int nrBiblioteci) {
	if (nrBiblioteci > 0 && vector != NULL) {
		for (int i = 0; i < nrBiblioteci; i++) {
			afiseazaBiblioteca(vector[i]);
		}
	}
	
}
void dezalocare(Biblioteca** vector, int* dim) {
	for (int i = 0; i < *dim; i++) {
		free((*vector)[i].denumire);
		free((*vector)[i].locatie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}



void main() {
	//Biblioteca biblioteca1 = citireBiblioteca();
	//printf("\nIncasari imprumuturi %s: %5.2f", biblioteca1.denumire, calculIncasariImprumuturi(biblioteca1));
	//afiseazaBiblioteca(biblioteca1);
	//modificaNrCarti(&biblioteca1, 122);
	//afiseazaBiblioteca(biblioteca1);

	int nrBiblioteci = 5;
	Biblioteca* vectorBiblioteci = (Biblioteca*)malloc(sizeof(Biblioteca) * nrBiblioteci);
	for (int i = 0; i < nrBiblioteci; i++) {
		vectorBiblioteci[i] = initializareBiblioteca(i+1, "Biblioteca", "Bucuresti", 100 + i * 2);
	}
	afisareVectorBiblioteci(vectorBiblioteci, nrBiblioteci);

	Biblioteca* copii = copiazaBiblioteci(vectorBiblioteci, nrBiblioteci);
	printf("\nVector biblioteci copiate:\n");
	afisareVectorBiblioteci(copii, nrBiblioteci);

	printf("\nVector copii care indeplinesc conditie:\n");
	int nrBiblioteciPrag = 0;
	Biblioteca* biblioteciPrag = copiazaBiblioteciPestePrag(vectorBiblioteci, nrBiblioteci, 105, &nrBiblioteciPrag);
	afisareVectorBiblioteci(biblioteciPrag, nrBiblioteciPrag);

	printf("\nVector concatenat:\n");
	int dimVectorConcatenat = nrBiblioteci + nrBiblioteciPrag;
	Biblioteca* vectorConcatenat = concateneazaVectori(biblioteciPrag, nrBiblioteciPrag, vectorBiblioteci, nrBiblioteci);
	afisareVectorBiblioteci(vectorConcatenat, dimVectorConcatenat);
	
	dezalocare(&vectorBiblioteci, &nrBiblioteci);
	dezalocare(&copii, &nrBiblioteci);
	dezalocare(&biblioteciPrag, &nrBiblioteciPrag);
	dezalocare(&vectorConcatenat, &dimVectorConcatenat);
	
}