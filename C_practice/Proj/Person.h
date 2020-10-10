#ifndef __PERSON_H__
#define __PERSON_H__
#define STR_LEN 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _person
{
	int ssn;
	char name[STR_LEN];
	char addr[STR_LEN];
}Person;

int GetSSN(Person* p)
{
	return p->ssn;
}
void ShowPerInfo(Person* p)
{
	printf("주민등록번호: %d\n", p->ssn);
	printf("이름: %s\n", p->name);
	printf("주소: %s\n", p->addr);
}

Person* MakePersonData(int ssn, char* name, char* addr)
{
	Person* newP = (Person*)malloc(sizeof(Person));
	newP->ssn = ssn;
	strcpy(newP->name, name);
	strcpy(newP->addr, addr);
	return newP;
}
#endif // !__PERSON_H__
