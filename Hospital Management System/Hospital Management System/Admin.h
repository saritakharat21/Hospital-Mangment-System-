#pragma once
#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

//FILE* FP; /* global pointer to file */
/* global pointer to beginning of list */
typedef struct Admin
{
	char login_id[10];
	char password[10];
}admin;

typedef struct Patient
{
	int pId;
	char pName[10];
	int pAge;
	char pGender;
	long int p_phoneNo;
	char* pSymptoms;
	struct Patient *next;
}patient;

//patient *list;

void menu();

//Admin modules
admin defaultAdmin();
void acceptAdmin();

patient* getnode();
patient* getrecord();
patient* search(int,int*,patient*);
int insert(patient*,patient*);
void displayall(patient*);
int del(int,patient*);
void BackToFile(patient*);