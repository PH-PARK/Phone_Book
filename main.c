//********************
//PhoneBook Version 1.6
//Using Binary Search Tree
//*******************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define INTERACTIVE
//#define __DEBUG__
#define NAME_LEN 20
#define PHONE_LEN 20
#define LIST_NUM 100

enum { QUIT = 0, INPUT, SHOWALL,SEARCH, REPLACE, DELETE };

typedef struct phoneData
{
	char name[NAME_LEN];
	char phoneNum[PHONE_LEN];
	struct phoneData* leftNode, *rightNode;

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

phoneData* gRoot = NULL;

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
	return;
}



void InputPhoneData()
{
	phoneData* data = (phoneData*)malloc(sizeof(phoneData));
	phoneData* pLoc = NULL;
	phoneData* pPre = NULL;

#ifdef __DEBUG__
	int i = 0;
	//phoneData* temp;
#endif

	fputs("Name: ", stdout);

	if(getString(data->name,NAME_LEN) == 1)
	{
#ifdef INTERACTIVE
		getchar();
#endif
		return;
	}

	fputs("Phone number: ", stdout);

	if(getString(data->phoneNum,PHONE_LEN) == 1)
	{
#ifdef INTERACTIVE
		getchar();
#endif
		return;
	}

	if (!gRoot)
	{
		gRoot = data;
	}
	puts("New phone number is added.");



#ifdef INTERACTIVE

	getchar();

#endif

}



int getString(char *buf, int maxLen)
{
	int i;
	char ch;
#ifdef __DEBUG__
//	printf("We are here.");
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
	phoneData* temp = FirstAddres;


	puts("End of list");

	return;

#ifdef INTERACTIVE
	getchar();
#endif
}

void SearchPhoneData()
{
	char searchName[NAME_LEN];
	phoneData* temp = FirstAddress;

	fputs("NAME: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//
	{
		return;
	}

	while(temp)// (temp != NULL)
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
	char searchName[NAME_LEN];
	phoneData* data = NULL;
	phoneData* temp = FirstAddress;


	fputs("Name: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//getString return 1 when it failed.
	{
		return;
	}

	if(!FirstAddress)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}
	
	while (temp)
	{
		if (!strcmp(temp->name, searchName))
		{
			ShowPhoneInfo(temp);
			break;
		}
		temp = temp->NextAddress;
	}

	if (!temp)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}
	
	fputs("New phone number: ", stdout);
	if (getString(temp->phoneNum, NAME_LEN) == 1) {
		return;
	}

	//temp = data;
	puts("Phone number is replaced.");

	return;

}



void DeletePhoneData()
{

	char searchName[NAME_LEN];
	phoneData* temp = FirstAddress;
	phoneData* pLoc;
	phoneData* pPre = NULL;

	fputs("Name: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)
	{
		return;
	}
	if (!FirstAddress)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}

	while (temp)
	{
		if (!strcmp(temp->name, searchName))
		{
			if (pPre)
			{
				pPre->NextAddress = temp->NextAddress;
			}
			else
			{
				FirstAddress = temp->NextAddress;
			}
			free(temp);
			puts("Phone number is deleted.");
			break;
		}
		pPre = temp;
		temp = temp->NextAddress;
	}

	if (!temp)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}

}

void ShowPhoneInfo(phoneData* phone)
{
	puts("---------------------------");
	printf("| Name: %s\n", phone->name);
	printf("| Phone number: %s\n", phone->phoneNum);
	puts("---------------------------");

}

phoneData* MakeBTNode(char* name, int phoneNumber)
{
	phoneData* temp;

	temp->name = name;
	temp->phoneNum = phoneNumber;
	temp->leftNode = NULL;
	temp->rightNode = NULL;

	return temp;
}