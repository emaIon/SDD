#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

typedef struct Car Car;
typedef struct Node Node;
typedef struct  DoublyLinkedList DLList;
//lista dubla inlantuita

//PT TEST: liste simple,duble,vector,matrice,hashtabe, stiva,coada
//tema: apelat fct in main,  in fct de an <2020 sa stergrem nod( care poate fi la mijloc), stergerea de la mijloc in fct de an

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

struct Node {
	Car car;
	Node* next;
	Node* prev;
};

struct DoublyLinkedList{
	Node* start;
	Node* end;
};

void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}

void insertAtBeginning(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = list->start;//setez vecinii noului nod
	newNode->prev = NULL;//setez vecinii noului nod

	if (list->start)//daca avem elemente in lista
	{
		list->start->prev = newNode;
	}
	else//daca lista e goala
	{
		list->end = newNode;
	}
	list->start = newNode;

}

void insertAtEnd(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->prev = list->end;
	newNode->next = NULL;

	if (list->end)
	{
		list->end->next = newNode;
	}
	else
	{
		list->start = newNode;
	}
	list->end = newNode;
}

void parseBtoE(DLList list)
{
	if (list.start)
	{
		while (list.start)
		{
			printCar(list.start->car);
			list.start = list.start->next;
		}
	}
	else
	{
		printf("Lista e goala\n");
	}
}

void parseEtoB(DLList list)
{
	if (list.end)
	{
		while (list.end)
		{
			printCar(list.end->car);
			list.end = list.end->prev;
		}
	}
	else
	{
		printf("Lista e goala\n");
	
	}
}

//stergere
Car deleteFromBeginning(DLList* list)
{
	if (list->start)
	{
		Node* nodeToBeDeleted = list->start;
		Car carToBeDeleted = list->start->car;//=nodeToBeDelete.start;   acelaci lucru

		if (list->start->next)
		{
			list->start = list->start->next;
			list->start->prev = NULL;
			free(nodeToBeDeleted);

			return carToBeDeleted;
		}
		else
		{
			list->start = NULL;
			list->end = NULL;
			free(nodeToBeDeleted);
			return carToBeDeleted;
		}

	}
	else
	{
		Car empty = { .year = 0, .manufacturer = "empty", .cc = 0 };
		return empty;
	}
}


Car deleteFromEnd(DLList* list)
{
	if (list->end)
	{
		Node* nodeToBeDeleted = list->end;
		Car carToBeDeleted = list->end->car;//=nodeToBeDelete.start;   acelaci lucru

		if (list->end->prev)
		{
			list->end= list->end->prev;
			list->end->next = NULL;
			free(nodeToBeDeleted);

			return carToBeDeleted;
		}
		else
		{
			list->start = NULL;
			list->end = NULL;
			free(nodeToBeDeleted);
			return carToBeDeleted;
		}

	}
	else
	{
		Car empty = { .year = 0, .manufacturer = "empty", .cc = 0 };
		return empty;
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

void readCarsFromFile(DLList* list,int*noCars, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	/*char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	*noCars = (int)strtol(buffer, NULL, 10);*/
	//daca nu stim cate masini avem
	int carsRead = 0;
	while (!feof(f)) {
		insertAtEnd(list, readCarFromFile(f));
		carsRead++;
	}
	*noCars = carsRead;
	fclose(f);

}

int main() {

	int noCars = 0;
	DLList list;

	list.start = NULL;
	list.end = NULL;

	readCarsFromFile(&list, &noCars, "cars.txt");

	parseBtoE(list);

	printf("\n----------------\n");
	parseEtoB(list);

	return 0;
}

