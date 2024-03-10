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


Biblioteca* citesteBiblioteciDinFisier(const char* numeFisier, int* nrBiblioteci) {
	FILE* fisier = fopen(numeFisier, "r");
	if (!fisier) {
		return NULL;
	}

	fscanf(fisier, "%d\n", nrBiblioteci);
	Biblioteca* biblioteci = (Biblioteca*)malloc(sizeof(Biblioteca) * (*nrBiblioteci));

	for (int i = 0; i < *nrBiblioteci; i++) {
		biblioteci[i].denumire = (char*)malloc(256 * sizeof(char));
		biblioteci[i].locatie = (char*)malloc(256 * sizeof(char));

		fscanf(fisier, "%d,%255[^,],%255[^,],%d\n", &biblioteci[i].id, biblioteci[i].denumire, biblioteci[i].locatie, &biblioteci[i].nrCarti);
	}

	fclose(fisier);
	return biblioteci;
}

void salveazaBibliotecaInFisier(Biblioteca b, const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "w");
	if (fisier == NULL) {
		return;
	}
	fprintf(fisier, "ID: %d\nDenumire: %s\nLocatie: %s\nNumar carti: %d\n", b.id, b.denumire, b.locatie, b.nrCarti);

	fclose(fisier);
}

void salveazaVectorBiblioteciInFisier(Biblioteca* biblioteci, int nrBiblioteci, const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "w");
	if (!fisier) {
		return;
	}

	for (int i = 0; i < nrBiblioteci; i++) {
		fprintf(fisier, "%d,%s,%s,%d\n",
			biblioteci[i].id, biblioteci[i].denumire, biblioteci[i].locatie, biblioteci[i].nrCarti);
	}

	fclose(fisier);
}


double calculIncasariImprumuturi(Biblioteca b) {
	double costPerCarte = 10.2;
	return costPerCarte * b.nrCarti;
}

void modificaNrCarti(Biblioteca* b, int nouNrCarti) {
	b->nrCarti = nouNrCarti;

}


void sortareBiblioteci(Biblioteca* vector, int nrBiblioteci) {
	int i, j;
	for (i = 0; i < nrBiblioteci - 1; i++) {
		for (j = 0; j < nrBiblioteci - i - 1; j++) {
			if (vector[j].nrCarti < vector[j + 1].nrCarti) {
				Biblioteca temp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = temp;
			}
		}
	}
}

Biblioteca** copiazaInMatrice(Biblioteca* vector, int nrBiblioteci) {
	sortareBiblioteci(vector, nrBiblioteci);
	Biblioteca** matrice = (Biblioteca**)malloc(nrBiblioteci * sizeof(Biblioteca*));
	for (int i = 0; i < nrBiblioteci; i++) {
		matrice[i] = (Biblioteca*)malloc(sizeof(Biblioteca));
		matrice[i]->id = vector[i].id;
		matrice[i]->denumire = (char*)malloc((strlen(vector[i].denumire) + 1)*sizeof(char));
		strcpy(matrice[i]->denumire, vector[i].denumire);
		matrice[i]->locatie = (char*)malloc((strlen(vector[i].locatie) + 1) * sizeof(char));
		strcpy(matrice[i]->locatie, vector[i].locatie);
		matrice[i]->nrCarti = vector[i].nrCarti;
	}
	return matrice;

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

void afiseazaMatriceBiblioteci(Biblioteca** matrice, int nrBiblioteci) {
	for (int i = 0; i < nrBiblioteci; i++) {
		printf("Biblioteca %d: %s, %s, %d carti\n",
			matrice[i]->id,
			matrice[i]->denumire,
			matrice[i]->locatie,
			matrice[i]->nrCarti);
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

void dezalocaMatrice(Biblioteca** matrice, int nrBiblioteci) {
	for (int i = 0; i < nrBiblioteci; i++) {
		free(matrice[i]->denumire);
		free(matrice[i]->locatie);
		free(matrice[i]);
	}
	free(matrice);
}



void main() {

	const char* sursa = "biblioteci.txt";
	int nrBiblioteciFisier;
	Biblioteca* vector_biblioteci = citesteBiblioteciDinFisier(sursa, &nrBiblioteciFisier);
	if (vector_biblioteci) {
		printf("\nBiblioteci fisier:\n");
		afisareVectorBiblioteci(vector_biblioteci, nrBiblioteciFisier);
	}

	Biblioteca** matrice_biblioteci = copiazaInMatrice(vector_biblioteci, nrBiblioteciFisier);
	if (matrice_biblioteci) {
		printf("\nMatrice:\n");
		afiseazaMatriceBiblioteci(matrice_biblioteci, nrBiblioteciFisier);
	}
	
	dezalocare(&vector_biblioteci, &nrBiblioteciFisier);
	dezalocaMatrice(matrice_biblioteci, nrBiblioteciFisier);

}