#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128


struct Car {
	int year;
	char* manufacturer;
	float cc;
};

typedef struct Car Car;

struct Node {
	Car car;
	struct Node* next;// pointer catre urm nod din lista
};

typedef struct Node Node;


//adaugare la inceput
void insertAtBeginning(Node** start, Car car)
{
	   /*Fără Node** start(pointer la pointer) : Dacă ai doar un Node* start, atunci funcția
		poate doar să citească valoarea lui start, dar nu poate să o modifice(nu poate 
			schimba adresa start din funcție).

		Cu Node** start(pointer la pointer) : Permite funcției să modifice adică să schimbe
		ce indică pointerul start din afacerea funcției, astfel încât să adauge un nou nod
		la începutul listei.*/
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = *start;
	*start = newNode;

}

//adaugare la final 

void insertAtEnd(Node** start, Car car)
{

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;

	if (*start)//daca exista informatie in lista
	{
		Node* aux = *start;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = newNode;

	}
	else
	{
		*start=newNode ;
	}

}


void printCar(Car car)
{
	printf("%s din anul %d are %.2f \n", car.manufacturer, car.year, car.cc);
}


//stergere la inceput
Car deleteFromBeginning(Node** start)
{
	Node* deleted = *start;
	*start = (*start)->next;

	Car deletedCar = deleted->car;
	free(deleted);
	return deletedCar;

}


// TEMA -> STERGERE DE LA FINAL
Car deleteFromEnd(Node** start)
{
	if (*start == NULL)
	{
		printf("Lista este goala!");
	}
	else {
		Node* temp = *start;
		Node* prev = NULL;
		while (temp->next)
		{
			prev = temp;
			temp = temp->next;
		}

		Car deletedCar = temp->car;

		if (prev)
		{
			prev->next = NULL;
		}
		else {
			*start = NULL;
		}

		free(temp);
		return deletedCar;

	}
}

void parseListAndPrint(Node* start)
{
	/*Diferența între Node* start și Node** start
	
		Node* start → Ai o copie a pointerului către primul nod.

		Poți să modifici start local(să - l faci start = start->next), dar asta nu 
		afectează lista originală.
		Practic, te plimbi prin listă fără să o modifici.
		Node** start → Ai un pointer la pointer.

		Folosești Node** start când vrei să modifici efectiv pointerul original

		(de exemplu, să elimini primul element al listei, așa cum făceai în
			deleteFromBeginning).
		Dacă aici ai folosi Node** start, ar însemna că funcția poate schimba direct
		adresa lui start în apelant.*/
	while (start)
	{
		printCar(start->car);
		start = start->next;
	}

}



//TEMA -> INSERARE LA MIJLOC
// ??????????????????????????????????????????????????
// Functie pentru inserare la mijloc (dupa un anumit nod dat ca parametru)
void insertAtMiddle(Node** start, Car car, Node* afterNode) {
	if (afterNode == NULL) {
		printf("Nodul dat pentru inserare este NULL!\n");
	
	}
	else {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->car = car;
		newNode->next = afterNode->next;
		afterNode->next = newNode;
	}
}




//TEMA -> STERGERE LA MIJLOC



Car readCarFromFile(FILE* f)
{

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


void readCarsFromFile(Node** start, int* noCars, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	*noCars = (int)strtol(buffer, NULL, 10);
	

	for (int i = 0; i < (*noCars); i++)
	{
		insertAtEnd(start, readCarFromFile(f));
	}
	fclose(f);

}




int main()
{
	int nr = 0;
	Node* list = NULL;

	readCarsFromFile(&list, &nr, "cars.txt");

	parseListAndPrint(list);
	printf("\n----------------stergere de la inceput----------------------------------\n");


	Car deletedCar = deleteFromBeginning(&list); // Avem nevoie de &list, ca să modificăm list în funcția apelată.
	parseListAndPrint(list); //nu avem nevoie de &: functia nu modifica nmc, doar o parcurge fara modificare

	printf("\n----------------a fost setrs de la inceput---------------------------------\n");
	printCar(deletedCar);
	free(deletedCar.manufacturer);// deoarece manufacturer e alocat dinamic (char*) si tb eliberata memoria


	printf("\n----------------------stergere de la final------------------------------\n");
	Car delete = deleteFromEnd(&list);
	parseListAndPrint(list);

	printf("\n---------------------a fost sters de la final-------------------------------\n");
	printCar(delete);
	free(delete.manufacturer);


	printf("\n----------------------inserare la mijloc------------------------------\n");
	// ???????





}



