#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define INTERACTIVE
#define NAME_LEN 20
#define PHONE_LEN 20
#define LIST_NUM 100
enum { QUIT = 0, INPUT, SHOWALL,SEARCH, REPLACE, DELETE };

typedef struct phoneData
{
	char name[NAME_LEN];
	char phoneNum[PHONE_LEN];
} phoneData;

int numOfData = 0;

phoneData phoneList[LIST_NUM];

void ShowMenu();
void clear_inputBuffer();
void InputPhoneData();
int getString(char *buf, int maxLen);
void ShowAllData();
void ShowPhoneInfo(phoneData phone);
void SearchPhoneData();
void ReplacePhoneData();
void DeletePhoneData();


int main()
{
	int inputMenu = 0;
	while(1)
	{
		ShowMenu();
		fputs("Select a number: ", stdout);
		scanf_s("%d",&inputMenu);
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
	while(getchar() != '\n');     //clear buffer

}



void InputPhoneData()
{
	phoneData data; 

	if (numOfData >= LIST_NUM)
	{
		puts("Out of memory");

		return;
	}
	fputs("Name: ", stdout);
	if(getString(data.name,NAME_LEN) == 1) //write string to data.name and check error
	{

#ifdef INTERACTIVE

		getchar();

#endif

		return;

	}

	fputs("Phone number: ", stdout);


	if(getString(data.phoneNum,PHONE_LEN) == 1)//write string to data.phoneNum and check error
	{
#ifdef INTERACTIVE
		getchar();

#endif

		return;

	}
	
	phoneList[numOfData] = data; //add data to phonList from temporary data. 
	numOfData++;
	puts("New phone number is added.");

#ifdef INTERACTIVE

	getchar();

#endif

}



int getString(char *buf, int maxLen)
{
	int i;
	char ch;

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
	int i;
	for(i = 0;i <numOfData; i++)
	{
		ShowPhoneInfo(phoneList[i]);
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

	fputs("NAME: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//getString return 1 when it failed.
	{
		return;
	}

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i].name, searchName))
		{
			ShowPhoneInfo(phoneList[i]);
			return;
		}
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

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i].name, searchName))
		{
			ShowPhoneInfo(phoneList[i]);
			data = phoneList[i];
			break;
		}
	}
	fputs("New phone number: ",stdout);
	if (getString(data.phoneNum, NAME_LEN) == 1) {
		return;
	}

	phoneList[i] = data;
	puts("Phone number is replaced.", stdout);

	return 0;

}

void DeletePhoneData()
{

}
void ShowPhoneInfo(phoneData phone)
{
	puts("---------------------------");
	printf("| Name: %s\n", phone.name);
	printf("| Phone number: %s\n", phone.phoneNum);
	puts("---------------------------");

}