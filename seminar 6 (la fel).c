#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>

#define LINESIZE 128

typedef struct Car Car;
typedef struct Node Node;
typedef struct HashTable HT;

struct Car {
	int year;
	char* manufacturer;
	float cc;
};

struct Node {
	Car car;
	Node* next;
};

struct HashTable {
	int size;
	Node** array;
};

//lista simpla
void printCar(Car car)
{
	printf("%s din anul %d are %.2f\n", car.manufacturer, car.year, car.cc);
}

//lista simpla
void parseListAndPrint(Node* start)
{
	while (start)
	{
		printCar(start->car);
		start = start->next;
	}
}

//lista simpla
void insertAtList(Node** start, Car car)//insert at end lista simpla
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;

	if (*start)
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
		(*start) = newNode;
	}
}


//sem 6 -> indexuri
int hash(int htSize, char* manufacturer)
{
	int sum = 0;
	for (int i = 0; i < strlen(manufacturer); i++)
	{
		sum += manufacturer[i];
	}
	return sum % htSize;
}

//sem 6 ->initializare hashtable
HT initHashTable(int size)
{
	HT hashTable;
	hashTable.size = size;
	hashTable.array = malloc(hashTable.size * sizeof(Node*));
	for (int i = 0; i < hashTable.size; i++)
	{
		hashTable.array[i] = NULL;
	}
	return hashTable;
}

//sem 6- inserare in hashtable
void insertToHT(HT hashtable, Car car)
{
	int position = hash(hashtable.size, car.manufacturer);
	insertAtList(&(hashtable.array[position]), car);
}

//sem6 ->printare hashtable
void printHT(HT hashTable)
{
	for (int i = 0; i < hashTable.size; i++)
	{
		printf("\nBucket %d:\n", i);
		parseListAndPrint(hashTable.array[i]);
	}
}


//sem 6- SEARCH HASHCODE 






//lista simpla
Car readCar(FILE* f)
{
	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	Car car;
	char* carData=NULL;

	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData = strtok(NULL, ",");
	car.manufacturer = malloc(strlen(carData) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;
}

HT readCars(const char* fileName)
{

	FILE* f;
	f = fopen(fileName, "r");

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	int size = (int)strtol(buffer, NULL, 10);
	HT hashTable=initHashTable(size);

	while (!feof(f))
	{
		insertToHT(hashTable, readCar(f));
	}
	fclose(f);
	return hashTable;

}



int main()
{
	HT hashTable = readCars("cars.txt");
	printHT(hashTable);
}
