#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

typedef struct Node Node;
typedef struct Car Car;

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

struct Node {
	Car car;
	struct Node* next;
};


// nou-sem 4  -adaugare la inceput
void insertAtBeginning(Node** start, Car car)
{
	Node* newNode = malloc(sizeof(Node));////creeez nod
	newNode->car = car;// atribuit informatie
	newNode->next = *start;//, creez legatura

	*start = newNode;//update start

}

//adaugare la final
void insertAtEnd(Node** start, Car car)
{
	Node* newNode = malloc(sizeof(Node));//creez nod
	newNode->car = car;//creeez nod
	newNode->next = NULL;
	
	if (*start) {//daca exista start(informatiein in lista)

		Node* aux = *start; //start dereferentiat este *start
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = newNode;
	}
	else {//creez un start
		*start = newNode;//update start
	}
}




void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}

//stergere  de la inceput
Car deleteFromBeginning(Node** start)
{
	
	Node* deleted = *start;//copie a startului
	*start = (*start)->next;

	Car deletedCar = deleted->car;
	free(deleted);
	return deletedCar;
}



void parseListAndaPrint(Node* start)//nu am nevoie de adresa lui, ci doar de o copie (d aia pun doar un *)
{
	while (start)
	{
		printCar(start->car);
		start = start->next;
	}
}


Car readCarFromFile(FILE* f) {

	char buffer[LINESIZE];

	fgets(buffer, LINESIZE, f);

	Car car;

	char* carData = NULL;

	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData = strtok(NULL, ",");
	car.manufacturer = malloc((strlen(carData) + 1) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;

}

void readCarsFromFile(Node** start, int* noCars, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	*noCars = (int)strtol(buffer, NULL, 10);
	for (int i = 0; i < (*noCars); i++) {
		insertAtEnd(start, readCarFromFile(f));//nu am facut alocare de mem pt start pt ca am facut la insertAtEnd
	}

	fclose(f);

}



int main() {

	int noCars = 0;
	Node* list = NULL;



	readCarsFromFile(&list, &noCars, "cars.txt");

	parseListAndaPrint(list);

	printf("\n--------------------\n");
	//nou 
	Car deletedCar=deleteFromBeginning(&list);
	parseListAndaPrint(list);

	printf("\n--------------------\n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);

	return 0;
}


//liste simple inantuite-seminar 4
//inserare si stergere la mijloc- tema
//tema- stergere la final

//stiva
//adaugare si stergere la inceput  (push, pop)


//coada->adaugare final, remove inceput
