/*
Napisati program koji pomocu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod - direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 30

typedef struct nebitno {
	char name[MAX_LINE];
	struct nebitno* down;
	struct nebitno* next;
}node_;

typedef node_* node;

int menu(node current);
int makedir(node root);
node changedir(node current);
node goback(node root, node current);
int preorderprint(node root);

int main()
{
	int x = 1, r;
	char buffer[MAX_LINE];

	node root;
	root = malloc(sizeof(node_));

	strcpy(root->name, "C:");
	root->down = NULL;
	root->next = NULL;

	node current = root;

	do {
		r = menu(current);

		switch (r)
		{
		case 1:
			makedir(current);
			break;
		case 2:
			current = changedir(root);
			break;
		case 3:
			current = goback(root, current);
			break;
		case 4:
			preorderprint(root);
			break;
		case 0:
			return 0;
			break;
		}

	} while (x);
}

int menu(node current)
{
	int g;
	char c;

	do {
		printf("Nalazite se u \"%s\" direktoriju\n", current->name);
		printf("Pritisnite \"1\" za pravljenje direktorija\n");
		printf("Pritisnite \"2\" za promjenu direktorija\n");
		printf("Pritisnite \"3\" za vracanje na prethodni direktorij\n");
		printf("Pritisnite \"4\" za ispis direktorija(preorder)\n");
		printf("Pritisnite \"0\" za izlaz iz programa\n");
		printf("\033[0;34mUnos: \033[0m");

		scanf("%d", &g);

		if (g > -1 || g < 5)
		{
			return g;
		}

	} while (1);
}

int makedir(node root)
{
	node ptr = malloc(sizeof(node_));

	printf("Nalazite se u \"%s\" direktoriju\n", root->name);
	printf("\033[0;34mUnesite ime datoteke koju zelite napraviti:\033[0m\n");
	scanf("%s", ptr->name);

	ptr->next = root->down;
	ptr->down = NULL;
	root->down = ptr;
}

node changedir(node current)
{
	node temp = current;
	char buffer[MAX_LINE];

	printf("\033[0;34mUnesite ime direktorija u koji se zelite prebaciti:\033[0m\n");
	scanf("%s", buffer);

	current = current->down;

	while (current != NULL && strcmp(current->name, buffer) != 0)
	{
		current = current->next;
	}
	if (current == NULL)
	{
		printf("\033[0;31mU direktoriju %s ne postoji takav file\033[0m\n", temp->name);
		return temp;
	}
	return current;
}

node goback(node root, node current)
{
	if (root == current)
	{
		printf("\033[0;31mVec ste u %s direktoriju\033[0m\n", root->name);
	}

	node temp = root;

	while (root->next != NULL)
	{
		if (root->next == NULL)
		{
			if (root == current)
			{
				return current;
			}
			temp = root;
			root = root->down;
		}
		else
		{
			if (root == current)
			{
				return current;
			}
			root = root->next;
		}
	}
}

int preorderprint(node root)
{
	if (root == NULL)
	{
		return 0;
	}

	printf("%s\n", root->name);

	preorderprint(root->down);
	preorderprint(root->next);
}