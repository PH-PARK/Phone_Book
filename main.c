#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define INTERACTIVE
#define __DEBUG__
#define NAME_LEN 20
#define PHONE_LEN 20
#define LIST_NUM 100

enum { QUIT = 0, INPUT, SHOWALL,SEARCH, REPLACE, DELETE };

typedef struct phoneData
{
	char name[NAME_LEN];
	char phoneNum[PHONE_LEN];
	struct phoneData* NextAddress;

} phoneData;

//int numOfData = 0;

//phoneData phoneList[LIST_NUM];

void ShowMenu();
void clear_inputBuffer();
void InputPhoneData();
int getString(char *buf, int maxLen);
void ShowAllData();
void ShowPhoneInfo(phoneData* phone);
void SearchPhoneData();
void ReplacePhoneData();
void DeletePhoneData();
phoneData* FirstAddress = NULL;

int main()
{
	
	int inputMenu = 0;
	while(1)
	{
		ShowMenu();
		fputs("Select a number: ", stdout);
		scanf("%d",&inputMenu);
		clear_inputBuffer();  // 입력버퍼 비우기
		switch (inputMenu)
		{
		case INPUT:
			InputPhoneData();		   			 
			break;

		case SHOWALL:
			ShowAllData();
			break;

		case SEARCH:
			SearchPhoneData();
			break;

		case REPLACE:
			ReplacePhoneData();
			break;

		case DELETE:
			DeletePhoneData();
			break;
		}

		if(inputMenu == QUIT)
		{
			puts("Bye~");
			break;
		}

	}

	return	0;

}



void ShowMenu()
{

#ifdef INTERACTIVE

#ifdef __linux__

	system("clear");  // stdlib.h

#else

	system("cls");  // stdlib.h

#endif

#endif

	puts("--------Menu----------");
	puts(" 0. Quit");
	puts(" 1. New phone number");
	puts(" 2. Display all");
	puts(" 3. Search");
	puts(" 4. Replace");
	puts(" 5. Delete");
	puts("----------------------");
	fputs("Menu>> ", stdout);
}



void clear_inputBuffer()
{
	//  fflush(stdin);
	while(getchar() != '\n');     // 입력버퍼 비우기

}



void InputPhoneData()
{
	phoneData data;
#ifdef __DEBUG__
	phoneData* temp;
#endif

	fputs("Name: ", stdout);

	if(getString(data.name,NAME_LEN) == 1)
	{
#ifdef INTERACTIVE
		getchar();
#endif
		return;
	}

	fputs("Phone number: ", stdout);

	if(getString(data.phoneNum,PHONE_LEN) == 1)
	{
#ifdef INTERACTIVE
		getchar();
#endif
		return;
	}

	if (FirstAddress == NULL) 
	{
		FirstAddress = &data;
		data.NextAddress = NULL;
#ifdef __DEBUG__
	//puts("In the if(FirstAddress == NULL)");
	temp=FirstAddress;
	printf("FirstAddress : %d, &data: %d, temp: %d \n", FirstAddress, &data, temp);
	printf("data.name : %s\n data.phonenum : %s\n", data.name, data.phoneNum);
	printf("temp->name : %s\n temp->phoneNum : %s\n", temp->name, temp->phoneNum);
#endif
	}
	else
	{
#ifdef __DEBUG__
		puts("else");
#endif
	}

	puts("New phone number is added.");

#ifdef __DEBUG__
//	printf("NAME : %s\n", data.name);
//	printf("PhoneNum : %s\n", data.phoneNum);
#endif

#ifdef INTERACTIVE

	getchar();

#endif

}



int getString(char *buf, int maxLen)
{
	int i;
	char ch;
#ifdef __DEBUG__
	printf("We are here.");
#endif 

	for	(i = 0;	i <	maxLen; i++)
	{
		ch = getchar();
		if(ch =='\n')
		{
			buf[i] = '\0';
			return 0;
		}
		buf[i] = ch;
	}
	puts("Too long string");
	printf("Maximum	input length is %d bytes.", maxLen - 1);
	clear_inputBuffer();
	return	1;
}


void ShowAllData()
{
	phoneData* temp = FirstAddress;

#ifdef __DEBUG__
	printf("temp : %d\n",temp);
	printf("| Name: %s\n", temp->name);
	printf("| Phone number: %s\n", temp->phoneNum);
#endif
	if (temp) //  (temp != NULL)
	{
		ShowPhoneInfo(temp);
		temp = temp->NextAddress;
	}

	puts("End of list");

#ifdef INTERACTIVE
	getchar();
#endif
}

void SearchPhoneData()
{
	int i;
	char searchName[NAME_LEN];
	phoneData* temp = FirstAddress;

	fputs("NAME: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//
	{
		return;
	}

	/*for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i].name, searchName))
		{
			ShowPhoneInfo(phoneList[i]);
			return;
		}
	}*/

	while (temp != NULL)
	{
		if (!strcmp(temp->name, searchName)) // strcmp returns 0 when two strings are same.
		{									 // so this line means if it is same
			ShowPhoneInfo(temp);
			return;
		}

		temp = temp->NextAddress;
	}

	printf("'%s'is not in the list.\n", searchName);
}

void ReplacePhoneData()
{
	int i;
	char searchName[NAME_LEN];
	phoneData data;

	fputs("NAME: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//getString return 1 when it failed.
	{
		return;
	}

	/*if (numOfData == 0)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i].name, searchName))
		{
			ShowPhoneInfo(phoneList[i]);
			data = phoneList[i];
			break;
		}

		if (i + 1 == numOfData)
		{
			printf("'%s' is not in the list.\n", searchName);
			return;
		}
	}*/
	fputs("New phone number: ", stdout);
	if (getString(data.phoneNum, NAME_LEN) == 1) {
		return;
	}

	//phoneList[i] = data;
	puts("Phone number is replaced.");

	return 0;

}



void DeletePhoneData()
{
	int i, j;
	char searchName[NAME_LEN];

	fputs("Name: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)
	{
		return;
	}
	/*if (numOfData == 0)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}
	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i].name, searchName))
		{
			for (j = i; j + 1 < numOfData; j++)
			{
				phoneList[j] = phoneList[j + 1];
			}
			//phoneList[numOfData]
			numOfData--;
			puts("Phone number is deleted.");

			break;
		}

		if (i + 1 == numOfData)
		{
			printf("'%s' is not in the list.\n", searchName);
			return;
		}
		
	}*/
}

void ShowPhoneInfo(phoneData* phone)
{
	puts("---------------------------");
	printf("| Name: %s\n", phone->name);
	printf("| Phone number: %s\n", phone->phoneNum);
	puts("---------------------------");

}