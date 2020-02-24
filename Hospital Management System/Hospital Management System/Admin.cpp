#include"pch.h"
#include"Admin.h"

void menu()
{
	printf("\n\t\t\t\tMenu\n\n");
	printf("\t\t\t\t1.Insert\n");
	printf("\t\t\t\t2.Delete\n");
	printf("\t\t\t\t3.Display list\n");
	printf("\t\t\t\t0.Exit\n");
}


//Login details of default admin
admin defaultAdmin()
{
	admin da;
	strcpy(da.login_id, "admin");
	strcpy(da.password, "admin123");
	return da;
}


//Login details of admin
void acceptAdmin()
{
	admin a, da;
	int compid, comppass;
	printf("\nEnter username:");
	scanf("%s", &a.login_id);
	printf("\nEnter password:");
	scanf("%s", &a.password);
	da = defaultAdmin();                            //to take default admin details
	compid = strcmp(da.login_id, a.login_id);
	comppass = strcmp(da.password, a.password);
	if (compid == 0 && comppass == 0)               //compare userid & password
		printf("\nWelcome to Suvidha Hospital");
	else
	{
		printf("Invalid login or password");
		acceptAdmin();
	}


}



patient *getnode() /*creates a node and accepts data from user*/
{
	char buffer[20];
	patient *temp;
	temp = (patient*)malloc(sizeof(patient));
	/*printf("Enter the employee id:");
	scanf("%d", &temp->empid);
	fflush(stdin);
	printf("Enter the name:");
	scanf("%s", temp->name);
	fflush(stdin);
	printf("Enter salary:");
	scanf("%f", &temp->sal);
	fflush(stdin);*/
	printf("\nEnter patient details: ");
	printf("\nEnter name: ");
	scanf("%s", &temp->pName);
	printf("\nEnter age: ");
	scanf("%d", &temp->pAge);
	printf("\nEnter gender: ");
	while (getchar() != '\n');
	scanf("%c", &temp->pGender);
	printf("\nEnter phone no.: ");
	scanf("%ld", &temp->p_phoneNo);
	printf("\nEnter symptoms: ");
	while (getchar() != '\n');
	gets_s(buffer, 20);  //DMA for symptoms
	temp->pSymptoms = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(temp->pSymptoms, buffer);
	fflush(stdin);
	temp->next = NULL;
	return temp;
}
patient* getrecord() /*creates a node and reads a record from file */
{
	patient* temp;
	FILE *FP= fopen("patient_data.txt", "r");
	temp = (patient*)malloc(sizeof(patient));
	fscanf(FP, "%d %s %d %c %ld %s", &temp->pId, &temp->pName, &temp->pAge, &temp->pGender,&temp->p_phoneNo,&temp->pSymptoms);
	temp->next = NULL;
	return temp;
}
/* Search returns address of previous node; current node is */
patient* search(int cd, int *flag,patient* list)
{
	patient *prev, *cur;
	*flag = 0;
	if (list == NULL) /* list empty */
		return NULL;
	for (prev = NULL, cur = list; (cur) && ((cur->pId) < cd);
		prev = cur, cur = cur->next);
	if ((cur) && (cur->pId == cd)) /* Node with given empid exists */
		*flag = 1;
	else
		*flag = 0;
	return prev;
}
int insert(patient* new1,patient* list)
{
	patient *prev;
	int flag;
	if (list == NULL) /* list empty */
	{
		list = new1;
		return 0;
	}
	prev = search(new1->pId, &flag,list);
	if (flag == 1) /* duplicate empid */
		return -1;
	if (prev == NULL) /*insert at beginning */
	{
		new1->next = list;
		list = new1;
	}
	else /* insert at middle or end */
	{
		new1->next = prev->next;
		prev->next = new1;
	}
	return 0;
}
void displayall(patient* list)
{
	patient *cur;
	if (list == NULL)
	{
		printf("The list is empty\n");
		return;
	}
	printf("\nPatient details: ");
	
	for (cur = list; cur; cur = cur->next)
		printf("\n%d %s %d %c %ld %s", cur->pId, cur->pName, cur->pAge, cur->pGender, cur->p_phoneNo, cur->pSymptoms);
}
int del(int cd,patient* list)
{
	patient *prev, *temp;
	int flag;
	if (list == NULL) /* list empty */
		return -1;
	prev = search(cd, &flag,list);
	if (flag == 0) /* pid not found */
		return -1;
	if (prev == NULL) /* node to delete is first node (as flag is 1) */
	{
		temp = list;
		list = list->next;
		free(temp);
	}
	else
	{
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
	return 0;
}
void BackToFile(patient* list) /*save entire list to the file*/
{
	patient* cur = list;
	FILE* FP = fopen("patient_data.txt", "w");
	if (FP == NULL)
		printf("Unable to open patient_data.txt\n");
	else
	{
		while (cur != NULL)
		{
			fprintf(FP,"\n%d %s %d %c %ld %s", cur->pId, cur->pName, cur->pAge, cur->pGender, cur->p_phoneNo, cur->pSymptoms);
			cur = cur->next;
		}
	}
	fclose(FP);
}