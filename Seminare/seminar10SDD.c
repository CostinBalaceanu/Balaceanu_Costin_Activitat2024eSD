#include <stdio.h>
#include <malloc.h>
#include <string.h>

//arbore=graf conex aciclic
//arbore binar=.. fiecare parinte are 2 noduri copii

typedef struct Elev Elev;
typedef struct Nod Nod;

struct Elev {
	int id;
	int nrMedii;
	float* medii;
};

struct Nod {
	Elev info;
	Nod* stanga;
	Nod* dreapta;
};

void inserareInArbore(Nod** radacina, Elev e) {
	if ((*radacina)!=NULL) {
		if ((*radacina)->info.id > e.id) {
			inserareInArbore((&(*radacina)->stanga), e);
		}
		else {
			inserareInArbore((&(*radacina)->dreapta), e);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod)); //frunza
		nou->info = e;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		*radacina = nou;
	}
}

Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = (float*)malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &(e.medii[i]));
	}
	return e;
}

Nod* citireFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	if (f == NULL) {
		exit(1);
	}
	
	Nod* arbore = NULL;
	int nrElevi;
	fscanf(f, "%d", &nrElevi);
	
	for (int i = 0; i < nrElevi; i++) {
		Elev e = citireElev(f);
		inserareInArbore((&arbore), e); //fara dereferentiere(*) fiindca trebuie sa obtinem adresa, nu valoarea
	}
	fclose(f);
	return arbore;
}

float calculMedieElev(Elev e) {
	if (e.nrMedii > 0) {
		float suma = 0.0;
		for (int i = 0; i < e.nrMedii; i++) {
			suma += e.medii[i];
		}
		return (float)(suma / e.nrMedii);
	}
	else {
		printf("\nElevul nu are medii");
		exit(1);
	}
}

float calculSumaMedii(Nod* radacina, int* nrMediiTotale) {
	if (radacina != NULL) {
		float suma = 0.0;

		//R
		for (int i = 0; i < radacina->info.nrMedii; i++) {
			suma += radacina->info.medii[i];
		}
		(*nrMediiTotale) += radacina->info.nrMedii;

		//S
		float sumaStanga=calculSumaMedii(radacina->stanga, nrMediiTotale);

		//D
		float sumaDreapta = calculSumaMedii(radacina->dreapta, nrMediiTotale);
		
		return suma + sumaStanga + sumaDreapta;
	}
	return 0;
}

float calculMedieGenerala(Nod* radacina) {
	int nrNote = 0;
	float suma=calculSumaMedii(radacina, &nrNote);
	if (nrNote > 0) {
		return suma / nrNote;
	}
	else {
		return 0;
	}
}


void afisareElev(Elev e) {
	printf("Elevul %d, nr medii %d, cu mediile: ", e.id, e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%5.2f ", e.medii[i]);
	}
	printf("\n");
}

//SRD
void afisareInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInOrdine(radacina->stanga);
		afisareElev(radacina->info);
		afisareInOrdine(radacina->dreapta);
	}
}

//SDR
void afisarePreOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInOrdine(radacina->stanga);
		afisareInOrdine(radacina->dreapta);
		afisareElev(radacina->info);
	}
}

//DSR
void afisarePostOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInOrdine(radacina->dreapta);
		afisareInOrdine(radacina->stanga);
		afisareElev(radacina->info);
	}
}

//cautare dupa id, ca la inserare

void main() {
	Nod* radacina=NULL;
	radacina=citireFisier("elevi.txt");
	afisareInOrdine(radacina);

	printf("Media generala este: %5.2f", calculMedieGenerala(radacina));
}