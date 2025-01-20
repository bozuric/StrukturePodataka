/*
Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.
	a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
	sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraca
	pokazivac na korijen stabla.
	b) Napisati funkciju replace koja ce svaki element stabla zamijeniti sumom elemenata u
	njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
	vrijednosti u tim potomcima).
	c) Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja koristenjem
	funkcije rand() generira slucajne brojeve u rasponu <10, 90>.Takoder, potrebno je
	upisati u datoteku sve brojeve u inorder prolasku nakon koristenja funkcije iz a), zatim b)
	dijela zadatka.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct nebitno {
	int number;
	struct nebitno* left;
	struct nebitno* right;
}node_;

typedef node_* node;

node inserthub(node root);
node insert(node root, int x);
node createnode(int x);
int inorderprint(node root);
node replace(node root);
int change(node root);
int finorderprint(node root, FILE* fptr);
int deleteall(node root);

int main()
{
	node root = NULL;

	FILE* fptr = NULL;
	fptr = fopen("C:\\Users\\Ivan\\Desktop\\datoteka.txt", "w");
	if (fptr == NULL)
	{
		printf("Neuspjesno otvaranje datoteke");
		return -1;
	}

	root = inserthub(root);

	inorderprint(root);
	finorderprint(root, fptr);

	replace(root);

	printf("\n");
	fprintf(fptr, "\n");
	inorderprint(root);
	finorderprint(root, fptr);

	fclose(fptr);
	deleteall(root);
}

node inserthub(node root)
{
	for (int i = 0; i < 10; i++)
	{
		root = insert(root, i);
	}
	return root;
}

node insert(node root, int x)
{
	if (root == NULL)
	{
		return createnode(x);
	}

	if (root->number <= x)
	{
		root->left = insert(root->left, x);
	}
	else if (root->number > x)
	{
		root->right = insert(root->right, x);
	}

	return root;
}

node createnode(int x)
{
	node ptr = NULL;
	ptr = malloc(sizeof(node_));
	if (ptr == NULL)
	{
		printf("Neuspjesno alociranje memorije");
		return NULL;
	}
	ptr->number = x;
	ptr->right = NULL;
	ptr->left = NULL;

	return ptr;
}

int inorderprint(node root)
{
	if (root == NULL)
	{
		return 0;
	}

	inorderprint(root->left);
	printf("%d ", root->number);
	inorderprint(root->right);
}

node replace(node root)
{
	if (root == NULL)
	{
		return NULL;
	}

	root->number = change(root) - root->number;
	replace(root->left);
	replace(root->right);

	return root;
}

int change(node root)
{
	if (root == NULL)
	{
		return 0;
	}

	int leftSum = change(root->left);
	int rightSum = change(root->right);

	return leftSum + rightSum + root->number;
}

int finorderprint(node root, FILE* fptr)
{
	if (root == NULL)
	{
		return 0;
	}

	finorderprint(root->left, fptr);
	fprintf(fptr, "%d ", root->number);
	finorderprint(root->right, fptr);
}

int deleteall(node root)
{
	if (root == NULL)
	{
		return 1;
	}
	deleteall(root->left);
	deleteall(root->right);
	free(root);
	return 1;
}