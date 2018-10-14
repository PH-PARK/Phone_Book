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

	if (!FirstAddress)// if(First == NULL)
	{
		FirstAddress = data;
		data->NextAddress = NULL;
#ifdef __DEBUG__
//	puts("if(FirstAddress)");
//	temp=FirstAddress;
//	printf("FirstAddress : %d, &data: %d, temp: %d \n", FirstAddress, &data, temp);
//	printf("data.name : %s\n data.phonenum : %s\n", data.name, data.phoneNum);
//	printf("temp->name : %s\n temp->phoneNum : %s\n", temp->name, temp->phoneNum);
#endif
	}
	else
	{
#ifdef __DEBUG__
		//puts("else");
#endif

		pLoc = FirstAddress;
		
#ifdef __DEBUG__
//		printf("FistAddress : %d, pLoc : %d\n",FirstAddress, pLoc);
		//printf("name : %s, phonenum: %s, nextAddress : %d\n", pLoc->name, pLoc->phoneNum, pLoc->NextAddress);
		printf("r_v : %d, i : %d\n", strcmp(pLoc->name,data->name), i);
#endif
		while (strcmp(pLoc->name, data->name) < 0) // new string should be go to rear.
		{
#ifdef __DEBUG__
			
			i++;
			if (i == 100)
			{
				puts("stop infinite loop");
				system("pause");
			}
#endif
		
			if (pLoc->NextAddress) //if pLoc is not Last
			{	
				pPre = pLoc;
				pLoc = pLoc->NextAddress; //keep Searching
#ifdef __DEBUG__
				puts("here 1");
				//ShowAllData();
#endif
			}
			else//if pLoc is Last : pLoc->NextAddress is NULL; Can't Keep Searcing.
			{
#ifdef __DEBUG__
				puts("here 2");
#endif
				if (pPre)//pPre is not NULL : If there are only two items including pLoc
				{
#ifdef __DEBUG__
					puts("here 3");
#endif
		
					pPre->NextAddress = pLoc;
					
				}

					pLoc->NextAddress = data;
					data->NextAddress = NULL;
					puts("New phone number is added.");
#ifdef __DEBUG__
					puts("here 5");
#endif
					return;
				
			}

#ifdef __DEBUG__
			puts("here 4");
#endif


		}

		//when it found something.

		if (pPre)
		{//pPre != NULL : Data is not in the first.
#ifdef __DEBUG__
			puts("here !");
#endif
			pPre->NextAddress = data;
		/*	if(!data->NextAddress)
			{
#ifdef __DEBUG__
				puts("here #");
				printf("data->NextAddress : %d", data->NextAddress);
#endif
				data->NextAddress = pLoc;
				pLoc->NextAddress = NULL;
			}
			else*/
			//{
#ifdef __DEBUG__
				puts("here $");
				printf("data->NextAddress : %d", data->NextAddress);
#endif
				data->NextAddress = pLoc;
			//}
		}
		else//pPre == NULL : Data is in the first.
		{
#ifdef __DEBUG__
			puts("here @");
#endif

			FirstAddress = data;

			if (pLoc)
			{
				data->NextAddress = pLoc;//->NextAddress;
#ifdef __DEBUG__
				puts("here#");
#endif
			}
			else
			{
#ifdef __DEBUG__
				puts("here%");
#endif
				data->NextAddress = NULL;
			}
			data = pLoc;
			/*
			if (pLoc->NextAddress) //this is not last
			{
				pLoc->NextAddress = data;
				if (data->NextAddress)
				{
					data->NextAddress = data->NextAddress;
				}
				else
				{
					data->NextAddress = NULL;
				}
				
			}*/
			/*else//
			{
				pLoc->NextAddress = NULL;
			}*/
			
		}

	}//not First Data

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
	phoneData* temp = FirstAddress;

#ifdef __DEBUG__
//	printf("temp : %d\n",temp);
//	printf("| Name: %s\n", temp->name);
//	printf("| Phone number: %s\n", temp->phoneNum);
#endif
	while (temp) //  (temp != NULL)
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