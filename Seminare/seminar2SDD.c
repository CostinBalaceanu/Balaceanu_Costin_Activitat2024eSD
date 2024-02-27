//seminar 2 Balaceanu Costin
#include <stdio.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Calculator Calculator;

struct Calculator {
	char* serie;
	float pret;
	int numarPorturi;
};

Calculator initializare(const char* serie, float pret, int nrPorturi) {
	Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);//strlen(serie) + 1
	c.numarPorturi = nrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(Calculator c) {
	printf("Calculatorul cu serie %s, cost %5.2f si are %d porturi\n", c.serie, c.pret, c.numarPorturi);
}

void afisareVectorCalculatoare(Calculator* vector, int nrCalculatoare) {
	if (nrCalculatoare > 0 && vector != NULL) {
		for (int i = 0; i < nrCalculatoare; i++) {
			afisareCalculator(vector[i]);
		}
	}
}

Calculator* copiazaCalculatoare(Calculator* calculatoare, int nrCalculatoareCopiate) {
	Calculator* copiate = (Calculator*)malloc(sizeof(Calculator) * (strlen(nrCalculatoareCopiate) + 1));
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (strlen(calculatoare[i].serie) + 1));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
}

Calculator* copiazaCalculatoareCuMultePorturi(Calculator* calculatoare,
	int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi) {

	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].numarPorturi > pragNrPorturi) {
			(*nrCalculatoarePorturi)++;
		}
	}
	Calculator* v = (Calculator*)malloc(sizeof(Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].numarPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret,
				calculatoare[i].numarPorturi);
		}
	}
	return v;
}

Calculator calculatorPretDat(Calculator* c, int nrCalculatoare, float pretDorit) {
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (c[i].pret == pretDorit) {
			k++;
			if (k = 1) {
				return c[i];
			}
		}
	}
}

void dezalocare(Calculator** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].serie);

	}
	free(*vector);
	*vector = NULL;
	dim = 0;

}

void main() {
	//int v[10]; //alocat pe stack, static
	//int* v1;  // pointer catre adresa primului elemt, 8/64 biti

	int nrCalculatoare = 5;
	Calculator* calculatoare = (Calculator*)malloc(sizeof(Calculator) * (strlen(nrCalculatoare) + 1));
	for (int i = 0; i < nrCalculatoare; i++) {
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);

	int nrCalculatoareCopiate = 3;
	Calculator* calculatoareCopiate = copiazaCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);
	printf("\n\n");
	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoareCopiate);

	printf("\n\n");
	int nrCalculatoarePorturi = 0;
	Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);

	dezalocare(&calculatoare, &nrCalculatoare);
	dezalocare(&calculatoareCopiate, nrCalculatoareCopiate);
	dezalocare(&calculatoarePorturi, &nrCalculatoarePorturi);
}