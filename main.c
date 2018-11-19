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
void ClearQueue(void);

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
	while (temp)
	{

		if(strcmp(temp->name,data->name)>0)//if (strcmp(temp->phoneNum, data->phoneNum) > 0) // root's phone number is bigger, data should go left.
		{
#ifdef __DEBUG__
			puts("DEBUG: Data is smaller.");
#endif
			if (temp->leftNode)
			{
#ifdef __DEBUG__
				printf("DEBUG: '%s''s left nodes is not empty.", temp->name);
#endif
				temp = temp->leftNode;
#ifdef __DEBUG__
				printf("DEBUG: now searching '%s'\n", temp->name);
#endif
			}
			else
			{
#ifdef __DEBUG__
				printf("DEBUG: '%s''s left node is empty\n", temp->name);
#endif
				temp->leftNode = data;
#ifdef __DEBUG__
				printf("DEBUG: now leftnode is '%s'\n", temp->leftNode->name);
#endif
				puts("New phone number is added.");
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
				printf("DEBUG: now searching '%s'\n", temp->name);
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
				puts("New phone number is added.");
				return;
			}
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
	ClearQueue();
	LevelOrder(gRoot);

	puts("End of list");
	
	return;

#ifdef INTERACTIVE
	getchar();
#endif
}


void SearchPhoneData()
{
	char searchName[NAME_LEN];
	phoneData* temp;
	front = 0;
	rear = 0;

	fputs("NAME: ", stdout);

	if (getString(searchName, NAME_LEN) == 1)//
	{
		return;
	}

	enqueue(gRoot);


	while(1)// (temp != NULL)
	{

		temp = dequeue();
		if (temp)
		{
			if (!strcmp(temp->name, searchName)) // strcmp returns 0 when two strings are same.
			{									 // so this line means if(strcmp(temp->name, searchName) == 0)
				ShowPhoneInfo(temp);
				return;
			}

			if (temp->leftNode)
			{
				enqueue(temp->leftNode);
			}
			if (temp->rightNode)
			{
				enqueue(temp->rightNode);
			}
		}
		else
		{
			break;
		}
	}

	printf("'%s'is not in the list.\n", searchName);
}


void ReplacePhoneData()
{
	char searchName[NAME_LEN];
	phoneData* temp;
	front = 0;
	rear = 0;

	fputs("Name: ", stdout);
	if (getString(searchName, NAME_LEN) == 1)//getString return 1 when it failed.
	{
		return;
	}

	enqueue(gRoot);

	while (1)
	{
		temp = dequeue();

		if (temp)
		{
			if (!strcmp(temp->name, searchName))
			{
				ShowPhoneInfo(temp);
				break;
			}
			
			if (temp->leftNode)
			{
				enqueue(temp->leftNode);
			}

			if (temp->rightNode)
			{
				enqueue(temp->rightNode);
			}
		}
		else
		{
			printf("'%s' is not in the list.\n", searchName);
			return;
		}

	}

	fputs("New phone number: ", stdout);
	if (getString(temp->phoneNum, NAME_LEN) == 1) {
		return;
	}

	puts("Phone number is replaced.");

	return;

}



void DeletePhoneData()
{

	char searchName[NAME_LEN];
	phoneData *pPre, *pLoc;
	phoneData *pPre2, *pLoc2;
	phoneData *child;

	pLoc = gRoot;
	pPre = NULL;

	fputs("Name: ", stdout);

	if (getString(searchName, NAME_LEN) == 1)
	{
		return;
	}
#ifdef __DEBUG__
		printf("DEBUG: searching from '%s'", pLoc);
#endif
	while (pLoc != NULL)
	{
		if (!strcmp(searchName, pLoc->name))
		{
			break;
		}
		pPre = pLoc;
		pLoc = (strcmp(searchName,pLoc->name) < 0) ? pLoc->leftNode : pLoc->rightNode;
#ifdef __DEBUG__
		printf("DEBUG: pPre->name : '%s'\n, pLoc->name : '%s'\n",pPre->name, pLoc->name);
#endif
	}

	if (pLoc == NULL)
	{
		printf("'%s' is not in the list.\n", searchName);
		return;
	}


	if ((pLoc->leftNode == NULL) && (pLoc->rightNode == NULL))
	{

#ifdef __DEBUG__
		puts("DEBUG: pLoc is a single node.");
#endif
		if (pPre != NULL)
		{
			if (pPre->leftNode == pLoc)
			{
				pPre->leftNode = NULL;
			}
			else
			{
				pPre->rightNode = NULL;
			}
		}
		else
		{
			gRoot = NULL;
		}
		puts("Phone number is deleted.");
		free(pLoc);
	}
	else if ((pLoc->leftNode == NULL) || (pLoc->rightNode == NULL))
	{
#ifdef __DEBUG__
		puts("DEBUG: pLoc has only one child.");
#endif
		child = (pLoc->leftNode != NULL) ? pLoc->leftNode : pLoc->rightNode;
#ifdef __DEBUG__
		printf("DEBUG: child is : '%s'\n",child);
#endif
		if (pPre != NULL)
		{
			if (pPre->leftNode == pLoc)
			{
#ifdef __DEBUG__
				printf("DEBUG: now pPre->leftNode is '%s'\n", child);
#endif

				pPre->leftNode = child;

			}
			else
			{
#ifdef __DEBUG__
				printf("DEBUG: now pPre->rightNode is '%s'\n", child);
#endif
				pPre->rightNode = child;
			}
		}
		else
		{
#ifdef __DEBUG__
			printf("DEBUG: now gRoot is '%s'\n", child);
#endif
			gRoot = child;
		}
#ifdef __DEBUG__
		printf("DEBUG: free('%s')\n", pLoc->name);
#endif
		puts("Phone number is deleted.");
		free(pLoc);
	}
	else
	{
#ifdef __DEBUG__
		puts("DEBUG: pLoc has two child.");
#endif
		pPre2 = pLoc;
		pLoc2 = pLoc->rightNode;
#ifdef __DEBUG__
		puts("DEBUG: searcing minum node of pLoc's tree.");
#endif
		while (pLoc2->leftNode != NULL)
		{
			pPre2 = pLoc2;
			pLoc2 = pLoc2->leftNode;
		}
		if (pPre2->leftNode == pLoc2)
		{
			pPre2->leftNode = pLoc2->rightNode;
		}
		else
		{
			pPre2->rightNode = pLoc2->rightNode;
		}

		strcpy(pLoc->name, pLoc2->name);
		strcpy(pLoc->phoneNum, pLoc2->phoneNum);
		puts("Phone number is deleted.");
		free(pLoc2);

	}
	
}

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

void ClearQueue(void)
{
	int i;
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		queue[i] = NULL;
	}

	return;
}