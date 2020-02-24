#include "pch.h"
#include "Admin.h"

//Developed by Sarita Kharat


int main()
{
	patient* list;
	patient *new1;
	int choice = 1, cd;
	list = NULL;
	acceptAdmin();
	FILE* FP;
	FP = fopen("patient_data.txt", "r");
	if (FP == NULL)
		printf("Unable to open file patient_data.txt\n");
	else
	{
		/* populate the list from file records*/
		while (!feof(FP))
		{
			new1 = getrecord();
			if (insert(new1,list) == -1)
				printf("error:cannot insert\n");
			else
				printf("File Record inserted as node\n");
		}
		fclose(FP);
	}
	
	do
	{
		menu();
		printf("\n\t\t\t\t...... choice:");
		scanf("%d", &choice);
		fflush(stdin);
		switch (choice)
		{
		case 1:
			new1 = getnode();
			if (insert(new1,list) == -1)
				printf("error:cannot insert\n");
			else
				printf("node inserted\n");
			break;
		case 2:
			printf("Enter the employee id of the record to delete:");
			scanf("%d", &cd);
			fflush(stdin);
			if (del(cd,list) == -1)
				printf("deletion failed\n");
			else
				printf("node deleted\n");
			break;
		case 3:
			displayall(list);
			break;
		case 0:
			BackToFile(list); /* save the list back to the file*/
			exit(0);
		}
	} while (choice != 0);
	return 0;
}
