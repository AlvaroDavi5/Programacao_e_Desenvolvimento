/*

	no lugar de classes com atributos e metodos teremos structs com membros e ponteiros para funções
		~Alvaro Davi

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define Class struct

typedef Class Person Class Person;
Class Person
{
	char name[10];
	int age;
	int height;
	void(*show)(Class Person *);
};

void personPrint(Class Person *person)
{
	printf("Name: %s \nAge: %d \nHeight: %d \n", person->name, person->age, person->height);
}

Class Person * newPerson(char name[], int age, int height)
{
	Class Person *person = (Class Person *) malloc(sizeof(Class Person));

	strcpy(person->name, name); // atributos
	person->age = age;
	person->height = height;
	person->show = &personPrint; // metodo

	return person;
}

int main()
{
	Class Person *self = newPerson("Alvaro", 18, 170); // isso seria um objeto, a instancia de uma classe

	self->show(self); // isso seria o metodo com self ou this

	return 0;
}
