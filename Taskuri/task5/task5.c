#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Biblioteca Biblioteca;

struct Biblioteca {
    int id;
    char* denumire;
    char* locatie;
    int nrCarti;
};

struct Nod {
    Biblioteca info;
    struct Nod* next;
};

Biblioteca initializareBiblioteca(int id, const char* denumire, const char* locatie, int nrCarti) {
    Biblioteca b;
    b.id = id;
    b.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(b.denumire, denumire);
    b.locatie = (char*)malloc(strlen(locatie) + 1);
    strcpy(b.locatie, locatie);
    b.nrCarti = nrCarti;
    return b;
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

struct Nod* inserareSortata(struct Nod* cap, Biblioteca b) {
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->info = b;
    nou->next = NULL;

    if (cap == NULL || cap->info.nrCarti > b.nrCarti) {
        nou->next = cap;
        cap = nou;
    }
    else {
        struct Nod* temp = cap;
        while (temp->next != NULL && temp->next->info.nrCarti <= b.nrCarti) {
            temp = temp->next;
        }
        nou->next = temp->next;
        temp->next = nou;
    }
    return cap;
}

struct Nod* stergeNod(struct Nod* cap, int pozitie) {
    if (cap == NULL) return NULL;
    struct Nod* temp = cap;

    if (pozitie == 0) {
        cap = cap->next;
        free(temp->info.denumire);
        free(temp->info.locatie);
        free(temp);
        return cap;
    }

    for (int i = 0; temp != NULL && i < pozitie - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return cap;

    struct Nod* urm = temp->next->next;
    free(temp->next->info.denumire);
    free(temp->next->info.locatie);
    free(temp->next);
    temp->next = urm;

    return cap;
}

void afisareBiblioteca(Biblioteca b) {
    printf("Biblioteca %s din %s are %d carti.\n", b.denumire, b.locatie, b.nrCarti);
}

void afisareLista(struct Nod* cap) {
    while (cap != NULL) {
        afisareBiblioteca(cap->info);
        cap = cap->next;
    }
}

void dezalocareLista(struct Nod** cap) {
    while (*cap != NULL) {
        struct Nod* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.denumire);
        free(temp->info.locatie);
        free(temp);
    }
}




void main() {
    struct Nod* lista = NULL;
    int nrBiblioteci = 0;
    Biblioteca* biblioteci = citesteBiblioteciDinFisier("biblioteci.txt", &nrBiblioteci);

    for (int i = 0; i < nrBiblioteci; i++) {
        lista = inserareSortata(lista, biblioteci[i]);
    }

    afisareLista(lista);
    dezalocareLista(&lista);
   

    return 0;

}
