//********************
//PhoneBook Version 1.6
//Using Binary Search Tree
//*******************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define INTERACTIVE
#define __DEBUG__
#define NAME_LEN 20
#define PHONE_LEN 20
#define LIST_NUM 100
#define MAX_QUEUE_SIZE 1000
//#define TEST

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
phoneData* MakeBTNode(void);
phoneData* dequeue(void);
void enqueue(phoneData*);
void LevelOrder(phoneData*);

phoneData* gRoot = NULL;
int front = 0;
int rear = 0;
phoneData* queue[MAX_QUEUE_SIZE];

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
#ifdef TEST
		case SEARCH:
			SearchPhoneData();
			break;

		case REPLACE:
			ReplacePhoneData();
			break;

		case DELETE:
			DeletePhoneData();
			break;
#endif
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
	phoneData* data = MakeBTNode();
	phoneData* temp;



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
#ifdef __DEBUG__
		puts("DEBUG: First Data Added.");
#endif
		puts("New phone number is added.");
		return;
	}
	
	temp = gRoot;
#ifdef __DEBUG__
	puts("DEBUG: Not a First Data.");
#endif
	if (strcmp(temp->phoneNum, data->phoneNum) > 0) // root's phone number is bigger, data should go left.
	{
#ifdef __DEBUG__
		puts("DEBUG: Data is smaller.");
#endif
		if (temp->leftNode)
		{
#ifdef __DEBUG__
			printf("DEBUG: '%s''s left nodes is not empty.",temp->name);
#endif
			temp = temp->leftNode;
#ifdef __DEBUG__
			printf("DEBUG: now searching '%s'\n",temp->leftNode->name);
#endif
		}
		else
		{
#ifdef __DEBUG__
			printf("DEBUG: '%s''s left node is empty\n",temp->name);
#endif
			temp->leftNode = data;
#ifdef __DEBUG__
			printf("DEBUG: now leftnode is '%s'\n",temp->leftNode->name);
#endif
			return;
		}
	}
	else
	{
#ifdef __DEBUG__
		puts("DEBUG: Data is bigger.");
#endif
		if (temp->rightNode)
		{
#ifdef __DEBUG__
			printf("DEBUG: '%s''s right nodes is not empty.\n", temp->name);
#endif
			temp = temp->rightNode;
#ifdef __DEBUG__
			printf("DEBUG: now searching '%s'\n", temp->rightNode->name);
#endif
		}
		else
		{
#ifdef __DEBUG__
			printf("DEBUG: '%s''s right node is empty\n", temp->name);
#endif
			temp->rightNode = data;
#ifdef __DEBUG__
			printf("DEBUG: now rightnode is '%s'\n", temp->rightNode->name);
#endif
			return;
		}
	}

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
	LevelOrder(gRoot);

	puts("End of list");
	
	return;

#ifdef INTERACTIVE
	getchar();
#endif
}

#ifdef TEST
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

}//not yet



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

}//should change this
#endif
void ShowPhoneInfo(phoneData* phone)
{
	puts("---------------------------");
	printf("| Name: %s\n", phone->name);
	printf("| Phone number: %s\n", phone->phoneNum);
	puts("---------------------------");

}

phoneData* MakeBTNode(void)
{
	phoneData* temp = (phoneData*)malloc(sizeof(phoneData));

	temp->leftNode = NULL;
	temp->rightNode = NULL;

	return temp;
}

void LevelOrder(phoneData* root)
{
	front = 0;
	rear = 0;
	if (!root)
	{
#ifdef __DEBUG__
		puts("DEBUG: root is 'NULL'" );
#endif
		return;
	}

	enqueue(root);
#ifdef __DEBUG__
	printf("DEBUG: enqueue a root : '%s'\n",root->name);
#endif

	while(1)
	{
		root = dequeue();
#ifdef __DEBUG__
		printf("DEBUG: dequeue root '%s'\n",root->name);
#endif
		if (root)
		{
#ifdef __DEBUG__
			puts("DEBUG: root is not 'NULL'");
			puts("DEBUG: showing root's name");
#endif
			ShowPhoneInfo(root);
			if (root->leftNode)
			{
				enqueue(root->leftNode);
#ifdef __DEBUG__
				printf("DEBUG: enqueue root->leftNode : '%s'\n",root->leftNode);
#endif

			}
			else
			{
#ifdef __DEBUG__
				puts("DEBUG: root->leftnode is NULL");
#endif
			}
			if (root->rightNode)
			{
				enqueue(root->rightNode);
#ifdef __DEBUG__
				printf("DEBUG: enqueue root->rightNode : '%s'\n",root->rightNode);
#endif
			}
			else
			{
#ifdef __DEBUG__
				puts("DEBUG: root->rightnode is NULL");
#endif
			}
		}
		else
		{
#ifdef __DEBUG__
			puts("DEBUG: root is NULL");
			puts("DEBUG: break");
#endif
			break;
		}
	}

}

void enqueue(phoneData* item)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = item;
	return;
}

phoneData* dequeue(void)
{
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}