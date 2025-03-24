#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

//LISTA DUBLA INLANTUITA

#define LINESIZE 128

struct Car
{
	int year;
	char* manufacturer;
	float cc;
};

typedef struct Car Car;
typedef struct Node Node;
typedef struct DoublyLinkedList DLList;

struct Node {
	Car car;
	Node* next;
	Node* prev;
};

struct DoublyLinkedList {
	Node* start;
	Node* end;
};


void printCar(Car car)
{
	printf("%s din anul %d are %.2f\n", car.manufacturer, car.year, car.cc);
}

//adaugare a inceput
void insertAtBeginning(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = list->start;
	newNode->prev = NULL;

	if (list->start)
	{
		list->start->prev = newNode;
	}
	else
	{
		list->end = newNode;
	}

	list->start = newNode;


}

//adaugare a final
void insertAtEnd(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = NULL;
	newNode->prev = list->end;

	if (list->end)//=! 0
	{
		list->end->next = newNode;
	}
	else
	{
		list->start = newNode;
	}
	list->end = newNode;

}

//afisare insert
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
		printf("lista e goala");
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
		printf("lista e goala");
	}
}


//stergere de la inceput
Car deleteFromBeginning(DLList* list)
{
	if (list->start)
	{
		Node* deleted = list->start;
		Car deletedCar = deleted->car;//=list->start->car


		if (list->start->next)
		{
			list->start = list->start->next;
			list->start->prev = NULL;
			free(deleted);
			return deletedCar;
		}
		else
		{
			list->start = NULL;
			list->end = NULL;

			free(deleted);
			return deletedCar;
		}
	}
	else
	{
		Car empty = { .manufacturer = "-", .year = 0, .cc = 0 };
		return empty;
	}
}

//stergere de la final
Car deleteAtEnd(DLList* list)
{

	if (list->end)
	{
		Node* deleted = list->end;
		Car deletedCar = deleted->car;

		if (list->end->prev)
		{
			list->end = list->end->prev;
			list->end->next = NULL;

			free(deleted);
			return deletedCar;
		}
		else
		{
			list->end = NULL;
			list->start = NULL;
			free(deleted);
			return deletedCar;
		}
	}
	else
	{
		Car empty = { .manufacturer = "-", .year = 0, .cc = 0 };
		return empty;
	}

}



//citire din fisier
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

void readCarsFromFile(DLList* list, int* noCars, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	int nrCars = 0;
	while (!feof(f))
	{
		insertAtBeginning(list, readCarFromFile(f));
		nrCars++;
	}
	*noCars = nrCars;
	fclose(f);

}



int main()
{
	int nr = 0;
	DLList list;
	list.start = NULL;
	list.end = NULL;

	printf("\n--------inserare de la inceput la final----------------\n");
	readCarsFromFile(&list, &nr, "cars.txt");
	parseBtoE(list);

	printf("\n-------inserare de la final la inceput-----------------\n");
	parseEtoB(list);

	printf("\n-------stergere de la inceput-----------------\n");
	Car delete = deleteFromBeginning(&list);
	parseBtoE(list);
	printf("\n-------elementul sters este: ");
	printCar(delete);

	printf("\n-------stergere de la final-----------------\n");
	Car deleteCar = deleteAtEnd(&list);
	parseBtoE(list);
	printf("\n-------elementul sters este: ");
	printCar(deleteCar);
}
