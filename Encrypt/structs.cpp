#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createLetterTable(node_t*** array)
{
	node_t** arr = *array;

	for (int i = 0; i < 256; ++i)
	{
		arr[i] = (node_t*)malloc(sizeof(node_t));
		arr[i]->letter = i;
		arr[i]->priority = 0;
		arr[i]->left = NULL;
		arr[i]->right = NULL;
	}

	FILE* input;
	fopen_s(&input, "input.txt", "r");
	char* string = (char*)malloc(sizeof(char) * 256);
	int size = 0;

	while ((size = fread(string, sizeof(char), 256, input)))
	{
		for (int i = 0; i < size; ++i)
		{
			arr[string[i]]->priority++;
		
		}
	}

	int position = 0;
	for (int i = 0; i < 256; ++i)
	{
		if (arr[i]->priority == 0) {
			position++;
			continue;
		}

		arr[i - position] = arr[i];
	}

	fclose(input);
	return 256 - position;
}


void printTree(node_t* tree, int level)
{
	if (tree)
	{
		for (int i = 0; i < level; ++i) printf("__");
		printf("Level %d - %c\n", level, tree->letter);

		printTree(tree->left, level + 1);
		printTree(tree->right, level + 1);
	}
}


void treeSwap(node_t** tree1, node_t** tree2)
{
	node_t* buffer = (*tree1);
	(*tree1) = (*tree2);
	(*tree2) = buffer;
}

void listInit(list_t** list, char letter, char* string)
{
	(*list) = (list_t*)malloc(sizeof(list_t));
	(*list)->letter = letter;
	(*list)->code = (char*)calloc(sizeof(char)*(strlen(string) + 1), sizeof(char)*(strlen(string) + 1));
	strcpy((*list)->code, string);
	(*list)->next = NULL;
}

void treeFree(node_t** tree)
{
	if ((*tree))
	{
		treeFree(&((*tree)->left));
		free(((*tree)->left));
		treeFree(&((*tree)->right));
		free(((*tree)->right));
	}
}

void listFree(list_t** list)
{
	for (; (*list) != NULL;)
	{
		list_t* buffer = (*list);
		(*list) = (*list)->next;
		free(buffer);
	}
}