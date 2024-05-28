
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Metrou Metrou;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Metrou {
	int serie;
	int nrStatie;
	char* magistrala;
};

struct NodPrincipal {
	Metrou info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie initializare Metrou
Metrou creareMetrou(int serie, int nrStatii, const char* magistrala) {
	Metrou m;
	m.serie = serie;
	m.nrStatie = nrStatii;
	m.magistrala = (char*)malloc(sizeof(char) * (strlen(magistrala) + 1));
	strcpy_s(m.magistrala, strlen(magistrala) + 1, magistrala);
	return m;
}

//inserare la inceput in lista principala

void inserarePrincipala(NodPrincipal** cap, Metrou m) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}

//functie de cautare Nod dupa serie
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}


//inserare la final in lista secundara
NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = nod;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

//functie de inserare muchie
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
	}
}

#pragma region Coada

typedef struct NodCoada NodCoada;
struct NodCoada {
	int serie;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int serie) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->serie = serie;
	nou->next = NULL;

	if ((*cap)) {
		NodCoada* aux = (*cap);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*cap) = nou;
	}
}

int extragereCoada(NodCoada** cap) {
	if ((*cap)) {
		int rezutat = (*cap)->serie;
		NodCoada* aux = (*cap);
		(*cap) = aux->next;
		free(aux);
		return rezutat;
		
	}
	else {
		return -1;
	}
}

#pragma endregion

void afisareMetrou(Metrou m) {
	printf("%d, nr statii: %d, magistrala: %s\n", m.serie, m.nrStatie, m.magistrala);
}

int getNrNoduri(NodPrincipal* graf) {
	int rezultat = 0;
	while (graf) {
		rezultat++;
		graf = graf->next;
	}
	return rezultat;
}

void afisarePrinParcugereInLatime(NodPrincipal* graf, int serie) {
	NodCoada* coada = NULL;
	int nrNoduri = getNrNoduri(graf);
	
	char* vizitate = (char*)malloc(nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	inserareCoada(&coada, serie);
	vizitate[serie] = 1;

	while (coada) {
		int serieExtrasa= extragereCoada(&coada);
		NodPrincipal* nou = cautaNodDupaSerie(graf, serieExtrasa);
		afisareMetrou(nou->info);

		NodSecundar* temp = nou->vecini;
		while (temp) {
			if (vizitate[temp->nod->info.serie] == 0) {
				vizitate[temp->nod->info.serie] = 1;
				inserareCoada(&coada, vizitate[temp->nod->info.serie]);
			}
			temp = temp->next;
		}
	}
	if (vizitate) {
		free(vizitate);
	}

}

//functia de dezalocare
void dezalocareGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* aux = *graf;
		free(aux->info.magistrala);
		while (aux->vecini) {
			NodSecundar* temp = aux->vecini;
			aux->vecini = temp->next;
			free(temp);
		}
		(*graf) = aux->next;
		free(aux);
	}
}

void main() {

	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, creareMetrou(4, 6, "M2"));
	inserarePrincipala(&graf, creareMetrou(3, 7, "M1"));
	inserarePrincipala(&graf, creareMetrou(2, 8, "M4"));
	inserarePrincipala(&graf, creareMetrou(1, 12, "M5"));
	inserarePrincipala(&graf, creareMetrou(0, 4, "M6"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);

	afisarePrinParcugereInLatime(graf, 0);
	dezalocareGraf(&graf);

}
