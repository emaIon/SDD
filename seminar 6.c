#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

typedef struct Car Car;
typedef struct Node Node;
typedef struct HashTable HT;


//tabele de dispersie- seminar 6 - hashtable  (chaining)
//conversii
// 
//din listat in vector sa salvam pt test
//coada-adaugare la inceput scoatere la inceput pt tesct, si stiva


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

void printCar(Car car) {
	printf("%s from %d has %5.2f\n", car.manufacturer, car.year, car.cc);
}


//returneaza un int
int hash(int htSize, char* manufacturer)// char* manufacturer ->este cheia; int htSize- marimea tabelului
{
	int sum = 0;
	for (int i = 0; i < strlen(manufacturer); i++)
	{
		sum += manufacturer[i];//nu fac cunversie pt ca char e val numerica imi aduna cod ascii
	}
	return sum % htSize;
}


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

void parseListAndPrint(Node* start) {
	while (start) {
		printf("\n");
		printCar(start->car);
		start = start->next;
	}
}

void printHT(HT hashTable)
{
	for (int i = 0; i < hashTable.size; i++)
	{
		printf("Bucket %d:\n", i);
		parseListAndPrint(hashTable.array[i]);
	}
}


//era delete From end- codul e la fel
void insertToList(Node** start, Car car) {

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;

	if (*start) {

		Node* aux = *start;

		while (aux->next) {
			aux = aux->next;
		}

		aux->next = newNode;

	}
	else {
		*start = newNode;
	}
}




void insertToHT(HT hashTable, Car car)//chaining
{
	int position = hash(hashTable.size, car.manufacturer);

	insertToList(&(hashTable.array[position]), car);

	//doar exemplificam ca exista coliziune
	//if (hashTable.array[position])
	//{ //lista e ocupata, deci inserez in lista (mai departe)
	//	insertToList(&(hashTable.array[position]), car);
	//}
	//else
	//{ //lista e goala, deci inserez in lista
	//	insertToList(&(hashTable.array[position]), car);
	//}
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

HT readCarsFromFile(const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");
	
	char buffer[LINESIZE];
	 fgets(buffer, LINESIZE, f);
	int size = (int)strtol(buffer, NULL, 10);

	HT hashTable = initHashTable(size);

	while (!feof(f)) {
		insertToHT(hashTable, readCarFromFile(f));
	}

	fclose(f);
	return hashTable;

}
//Car searchHT(HT hashTable, char* key)
//{
//	int position = hash(hashTable.size, key);
//	Node* aux = hashTable.array[position];
//
//	while (aux)
//	{
//		if (aux && strcmp(aux->car.manufacturer, key))
//		{
//			return aux->car;
//		}
//		aux = aux->next;
//	}
//	else
//	{
//		Car c = { .year = 0, .manufacturer = "-", .cc = 0 };
//	}
//}
int main() {

	

	HT hashTable=readCarsFromFile( "cars.txt");

	printHT(hashTable);

	return 0;
}



