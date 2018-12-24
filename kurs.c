#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100
#define MAXLEN 1000
#define YES 1
#define NO 0
#define GANRES 9
typedef struct sNode
{
	int id;
	char name[LEN];
	char author[LEN];
	char ganre[LEN];
	struct sNode *next;
}Node;
int showMenu()
{
	int choice;
	printf("    1 - Add song\n");
	printf("    2 - Editing song \n");
	printf("    3 - Delete song\n");
	printf("    4 - Display the database on the screen in alphabetical order by song ganre or song name or song author\n");
	printf("    5 - Selection of tracks for one, two or three keywords\n");
	printf("\n              Press 0 and Enter if you want to quit.\n");
	scanf("%d", &choice);
	return choice;
}
Node* init(int a)
{
	Node *lst;
	lst = (Node*)malloc(sizeof(Node));
	lst->id = a;
	lst->next = NULL;
	return(lst);
}
Node * deleteHead(Node *head)
{
	Node *temp;
	temp = head->next;
	free(head);
	return(temp);
}
void deleteNode(Node *lst, Node *head)
{
	Node *temp;
	temp = head;
	while (temp->next != lst)
	{
		temp = temp->next;
	}
	temp->next = lst->next;
	free(lst);
}
void freeStruct(Node ** head)
{
	Node * current = *head;
	Node * next = NULL;
	do
	{
		next = current->next;
		free(current);
		current = next;
	} while (current != NULL);
	free(current);
}
Node* Appendlist(Node** headRef)
{
	Node* current = *headRef;
	Node* lst;
	lst = (Node*)malloc(sizeof(Node));
	lst->next = NULL;
	if (current == NULL) {
		*headRef = lst;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = lst;
	}
	return(lst);
}
void structFor(Node** headRef, int structType, int count)
{
	Node* current;
	Node* next;
	int noSwap;
	int iBuf;
	char cBuf[MAXLEN];
	switch (structType)
	{
	case 1:
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->name, next->name) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(cBuf, current->name);
					strcpy(current->name, next->name);
					strcpy(next->name, cBuf);
					strcpy(cBuf, current->author);
					strcpy(current->author, next->author);
					strcpy(next->author, cBuf);
					strcpy(cBuf, current->ganre);
					strcpy(current->ganre, next->ganre);
					strcpy(next->ganre, cBuf);
					noSwap = 0;
				}
				current = current->next;
				next = current->next;
			}
			if (noSwap == 1)
				break;
		}
		break;
	case 2:
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->author, next->author) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(cBuf, current->name);
					strcpy(current->name, next->name);
					strcpy(next->name, cBuf);
					strcpy(cBuf, current->author);
					strcpy(current->author, next->author);
					strcpy(next->author, cBuf);
					strcpy(cBuf, current->ganre);
					strcpy(current->ganre, next->ganre);
					strcpy(next->ganre, cBuf);
					noSwap = 0;
				}
				current = current->next;
				next = current->next;
			}
			if (noSwap == 1)
				break;
		}
		break;
	case 3:
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->ganre, next->ganre) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(cBuf, current->name);
					strcpy(current->name, next->name);
					strcpy(next->name, cBuf);
					strcpy(cBuf, current->author);
					strcpy(current->author, next->author);
					strcpy(next->author, cBuf);
					strcpy(cBuf, current->ganre);
					strcpy(current->ganre, next->ganre);
					strcpy(next->ganre, cBuf);
					noSwap = 0;
				}
				current = current->next;
				next = current->next;
			}
			if (noSwap == 1)
				break;
		}
		break;
	default:
		break;
	}
}
void inputData(Node** headRef, int *countsongsRet, int *songNumRet)
{
	FILE *fpin;
	FILE *finit;
	int dataNum;
	int songNum = 0;
	int insong = NO;
	int countsongs = 0;
	int i = 0;
	char line[MAXLEN];
	Node* song_ptr = NULL;
	fpin = fopen("base.txt", "r");
	if (fpin == NULL)
	{
		finit = fopen("base.txt", "w");
		fclose(finit);
		fpin = fopen("base.txt", "r");
	}
	fscanf(fpin, "%d\n", &countsongs);
	while (!feof(fpin))
	{
		fscanf(fpin,"%s\n",line);
		if (line == NULL)
			break;
		if (*line == '(')
		{
			insong = YES;
			songNum++;
			if (songNum == 1)
			{
				song_ptr = *headRef;
			}
			else
			{
				song_ptr = Appendlist(&(*headRef));
			}
			dataNum = 0;
			continue;
		}
		if (*line == ')')
		{
			insong = NO;
			continue;
		}
		if (insong)
		{
			i = -1;
			++dataNum;
			switch (dataNum)
			{
			case 1:
				song_ptr->id = atoi(line);
				break;
			case 2:
				do
				{
					i++;
					song_ptr->ganre[i] = line[i];
				} while (line[i] != '\0');
				break;
			case 3:
				do
				{
					i++;
					song_ptr->name[i] = line[i];
				} while (line[i] != '\0');
				break;
			case 4:
				do
				{
					i++;
					song_ptr->author[i] = line[i];
				} while (line[i] != '\0');
				break;
			}
		}
	}
	fclose(fpin);
	*songNumRet = songNum;
	*countsongsRet = countsongs;
}
void recordData(Node** headRef, int songNum)
{
	FILE *fpin;
	Node* current = *headRef;
	fpin = fopen("base.txt", "w");
	fprintf(fpin, "%d\n", songNum);
	while (current != NULL)
	{
		fprintf(fpin, "(\n");
		fprintf(fpin, "%d\n", current->id);
		fprintf(fpin, "%s\n", current->ganre);
		fprintf(fpin, "%s\n", current->name);
		fprintf(fpin, "%s\n", current->author);
		fprintf(fpin, ")\n");
		current = current->next;
	}
	fclose(fpin);
}
int main()
{
	Node* HeadPointer = init(0);
	Node* songPointer = NULL;
	char WantedName[LEN];
	char WantedAuthor[LEN];
	int songNum;
	int countsongs;
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 0;
	int need_menu;
	int need_song;
	int need_ganre;
	int cnt = 0;
	int need_showGanre;
	char ganres[GANRES][100] = { "folk","country", "latin", "blues", "jazz", "chanson", "electronic", "rock", "rap" };
	inputData(&HeadPointer, &countsongs, &songNum);

	do
	{
		need_menu = showMenu();
		switch (need_menu)
		{
		case 1:
			printf("1 - folk\n");
			printf("2 - country\n");
			printf("3 - latin\n");
			printf("4 - blues\n");
			printf("5 - jazz\n");
			printf("6 - chanson\n");
			printf("7 - electronic\n");
			printf("8 - rock\n");
			printf("9 - rap\n");
			printf("Select song ganre : ");
			scanf("%d", &need_ganre);
			getchar();
			printf("Enter the song name:");
			fgets(WantedName, LEN, stdin);
			getchar();
			printf("Enter the song author: ");
			scanf("%d", &WantedAuthor);
			fgets(WantedAuthor, LEN, stdin);
			getchar();
			countsongs++;
			if (songNum == 0)
			{
				songPointer = HeadPointer;
			}
			else
			{
				songPointer = Appendlist(&HeadPointer);
			}
			songPointer->id = countsongs;
			i = -1;
			do
			{
				i++;
				songPointer->name[i] = WantedName[i];
			} while (WantedName[i] != '\0');
			i = -1;
			do
			{
				i++;
				songPointer->author[i] = WantedAuthor[i];
			} while (WantedAuthor[i] != '\0');
			i = -1;
			do
			{
				i++;
				songPointer->ganre[i] = ganres[need_ganre - 1][i];
			} while (ganres[need_ganre - 1][i] != '\0');
			songNum++;
			break;
		case 2:

			if (!songNum)
			{
				printf("There is no songs here\n");

				break;
			}
			printf("Select the song you want to change : \n");
			songPointer = HeadPointer;
			i = 1;
			while (songPointer != NULL)
			{
				printf("%d - %s\n", i, songPointer->name);
				i++;
				songPointer = songPointer->next;
			}
			songPointer = HeadPointer;
			scanf("%d", &need_song);
			for (i = 0; i < need_song - 1; i++)
			{
				songPointer = songPointer->next;
			}
			printf("Old song type : %s\n||||||||||\n", songPointer->ganre);
			for (i = 0; i < GANRES; i++)
			{
				printf("%d %s\n", i + 1, &ganres[i]);
			}
			printf("Enter a new ganre of song : ");
			scanf("%d", &need_ganre);
			printf("Old song name : %s\nEnter new song name : ", songPointer->name);
			getchar();
			fgets(WantedName, LEN, stdin);
			getchar();
			printf("Old song author : %s\nEnter new song author : ", songPointer->author);
			scanf("%d", &WantedAuthor);
			fgets(WantedAuthor, LEN, stdin);
			getchar();
			i = -1;
			do
			{
				i++;
				songPointer->name[i] = WantedName[i];
			} while (WantedName[i] != '\0');
			i = -1;
			i = -1;
			do
			{
				i++;
				songPointer->author[i] = WantedAuthor[i];
			} while (WantedAuthor[i] != '\0');
			i = -1;
			i = -1;
			do
			{
				i++;
				songPointer->ganre[i] = ganres[need_ganre - 1][i];
			} while (ganres[need_ganre - 1][i] != '\0');

			break;
		case 3:
			if (!songNum)
			{
				printf("There is no songs here\n");

				break;
			}
			printf("Select the song you want to remove : \n");
			songPointer = HeadPointer;
			i = 1;
			while (songPointer != NULL)
			{
				printf("%d %s\n", i, songPointer->name);
				i++;
				songPointer = songPointer->next;
			}
			scanf("%d", &need_song);
			songPointer = HeadPointer;
			for (i = 0; i < need_song - 1; i++)
			{
				songPointer = songPointer->next;
			}
			if (need_song == 1)
			{
				HeadPointer = deleteHead(songPointer);
			}
			else
			{
				deleteNode(songPointer, HeadPointer);
			}
			songNum--;
			if (!songNum)
			{
				HeadPointer = init(0);
			}
			break;
		case 4:

			if (!songNum)
			{
				printf("There is no songs here\n");
				break;
			}
			printf("Choose sorting method: \n");
			printf("1 - Name\n2 - Author\n3 - Ganre\n");
			scanf("%d", &need_showGanre);

			structFor(&HeadPointer, need_showGanre, songNum);
			songPointer = HeadPointer;
			i = 1;
			while (songPointer != NULL)
			{
				printf("      <%d>      \n", i);
				printf("ID: %d\n", songPointer->id);
				printf("Ganre: %s\n", songPointer->ganre);
				printf("Name: %s\n", songPointer->name);
				printf("Author: %s\n", songPointer->author);
				i++;
				songPointer = songPointer->next;
			}
			break;
		case 5:
		{
			Node *pNode;
			int choice_num = 0;
			char line_ingr[100][100];
			char line_mas[100][100];
			int i = 0, j = 0, k = 0, flag = 0;
			int count_ingr = 0, count_mas = 0;

			printf("Enter [1], if you want to find with first keyword, else press [0]\n");
			scanf("%d", &choice_num);
			if (choice_num == 1)
			{
				getchar();
				printf("enter\n");
				gets(*(line_mas + i));
				getchar();
				count_mas++;
				i++;
			}
			printf("Enter [1], if you want to find with second keyword, else press [0]\n");
			scanf("%d", &choice_num);
			if (choice_num == 1)
			{
				getchar();
				printf("enter\n");
				gets(*(line_mas + i));
				getchar();
				count_mas++;
				i++;
			}
			printf("Enter [1], if you want to find with third keyword, else press [0]\n");
			scanf("%d", &choice_num);
			if (choice_num == 1)
			{
				getchar();
				printf("enter\n");
				gets(*(line_mas + i));
				getchar();
				count_mas++;
				i++;
			}

			printf("Letters found:\n");
			pNode = HeadPointer;
			while (pNode != NULL)
			{
				//получение из pNode->ingr всех ингридиентов 
				j = i = k = 0;

				do // обрабатываем строку ингридиентов данного узла и записываем ингридиенты по отдельности 
				// в массив line_ingr 
				{

					do
					{
						*(*(line_ingr + i) + j) = *(pNode->name + k);
						j++;
						k++;
						char c = *(pNode->name + k);
						if (*(pNode->name + k) == ' ' || *(pNode->name + k) == ',' || *(pNode->name + k) == '\0') break; // kostyl' 
					} while (*(pNode->name + k) != ' ' || *(pNode->name + k) != ',' || *(pNode->name + k) != '\0'); // тут прикол 
					*(*(line_ingr + i) + j) = '\0';
					i++;
					count_ingr++;
					j = 0;
					while ((*(pNode->name + k) == ' ' || *(pNode->name + k) == ',') && *(pNode->name + k) != '\0')
						k++;

				} while (*(pNode->name + k) != '\0');
				j = k = 0;
				i = 1;
				do 
				{

					do
					{
						*(*(line_ingr + i) + j) = *(pNode->author + k);
						j++;
						k++;
						char c = *(pNode->author + k);
						if (*(pNode->author + k) == ' ' || *(pNode->author + k) == ',' || *(pNode->author + k) == '\0') break; // kostyl' 
					} while (*(pNode->author + k) != ' ' || *(pNode->author + k) != ',' || *(pNode->author + k) != '\0'); // тут прикол 
					*(*(line_ingr + i) + j) = '\0';
					i++;
					count_ingr++;
					j = 0;
					while ((*(pNode->author + k) == ' ' || *(pNode->author + k) == ',') && *(pNode->author + k) != '\0')
						k++;

				} while (*(pNode->author + k) != '\0');
				j = k = 0;
				i = 2;
				do 
				{

					do
					{
						*(*(line_ingr + i) + j) = *(pNode->ganre + k);
						j++;
						k++;
						char c = *(pNode->ganre + k);
						if (*(pNode->ganre + k) == ' ' || *(pNode->ganre + k) == ',' || *(pNode->ganre + k) == '\0') break; // kostyl' 
					} while (*(pNode->ganre + k) != ' ' || *(pNode->ganre + k) != ',' || *(pNode->ganre + k) != '\0'); // тут прикол 
					*(*(line_ingr + i) + j) = '\0';
					i++;
					count_ingr++;
					j = 0;
					while ((*(pNode->ganre + k) == ' ' || *(pNode->ganre + k) == ',') && *(pNode->ganre + k) != '\0')
						k++;

				} while (*(pNode->ganre + k) != '\0');

				flag = 0;
				//считаем сколько должно быть совпадений 


				for (i = 0; i < count_ingr; i++)
				{
					for (j = 0; j < count_mas; j++)
					{
						if (strcmp(*(line_ingr + i), *(line_mas + j)) == 0)
						{
							flag++;
						}

					}
				}

				if (flag >= count_mas)
				{
					printf("|id %-20d|",pNode->id);
					printf("|a: %-20s|", pNode->author);
					printf("|n: %-30s|", pNode->name);
					printf("|g: %s \n", pNode->ganre);
				}
				pNode = pNode->next;

			}
			system("pause");
		}
		}
	} while (need_menu);

	if (songNum)
	{
		recordData(&HeadPointer, countsongs);
	}
	freeStruct(&HeadPointer);
	return 0;
}
			