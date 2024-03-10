#include <stdio.h>
#include <malloc.h>
#include<string.h>

typedef struct Aeroport Aeroport;

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

Aeroport* adaugaAeroport(Aeroport* vector, Aeroport aeroport, int* dimensiune) {
	Aeroport* copie = (Aeroport*)malloc(sizeof(Aeroport) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = aeroport; // pe ultima pozitie, facem shallow copy si nu facem stergerea
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	//stregem vectorul primit fara sa-l parcugem deoarece am facut shallow copy
	if (vector!=NULL) {
		free(vector);
	}

	(*dimensiune)++;
	return copie;
}

Aeroport* citire_Fisier(const char* numeFisier, int* nrAeroporturi) {
	
	Aeroport* vectorAeroporturi=NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		char buffer[100];
		(*nrAeroporturi) = 0;
		while (fgets(buffer, 100, f)!=NULL) {
			Aeroport aeroport;
			char delimitator[] = ",\n"; //initializare direct pe stiva
			char* token=strtok(buffer, delimitator); 
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator); // isi cauta apelul anterior
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi); //nu punem &nrAeroporturi deoarece deja este pointer in ambele functii

		}
		fclose(f);
		
	}
	return vectorAeroporturi;
}

Aeroport* cautareAeroportDupaID(Aeroport* aeroporturi, int dimensiune, int idCautat) {
	for (int i = 0; i < dimensiune; i++) {
		if (aeroporturi[i].id == idCautat) {
			return &aeroporturi[i]; 
		}
	}
	return NULL; 
}

void afisareAeroport(Aeroport* aeroport) {
	printf("Aeroportul cu id-ul: %d , nume: %s, numar terminale: %d\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}
void afisareVectorAeroporturi(Aeroport* aeroporturi, int dim) {
	printf("Afisare vector:\n");
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}


void dezalocareVector(Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
		free(aeroporturi[i]);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void main() {
	
	int dimensiune=3;
	Aeroport* aeroporturi = NULL;
	aeroporturi=citire_Fisier("aeroporturi.txt", &dimensiune);

	afisareVectorAeroporturi(aeroporturi, dimensiune);

	dezalocareVector(&aeroporturi, &dimensiune);
}