#include "structs.h"
#include "textcompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t* setEncoding(node_t* tree, list_t** list, char* string)
{
	static list_t* temp = *list;

	if (tree)
	{
		if (tree->letter != STOPELEMENT)
		{
			if ((*list) == NULL)
			{
				listInit(list, tree->letter, string);
				temp = (*list);
				
			}
			else
			{
				listInit(&((*list)->next), tree->letter, string);
				(*list) = (*list)->next;
			}
		}

		char* stringLeft = (char*)calloc(strlen(string) + 2, strlen(string) + 2);
		char* stringRight = (char*)calloc(strlen(string) + 2, strlen(string) + 2);
		strcpy(stringLeft, string);
		strcpy(stringRight, string);
		stringLeft[strlen(string)] = '0';
		stringRight[strlen(string)] = '1';

		setEncoding(tree->left, list, stringLeft);
		free(stringLeft);
		setEncoding(tree->right, list, stringRight);
		free(stringRight);

		return temp;
	}
}

int textCompress(list_t* encoding)
{
	FILE *input, *output;
	fopen_s(&input, "input.txt", "r");
	fopen_s(&output, "encrypted.compressed", "wb");
	if (input == NULL) return 1;
	list_t* list = encoding;
	char symbol = '\n';

	for (; list != NULL; list = list->next)
	{
		char letter = list->letter;
		if (list->letter == '\n') letter = STOPELEMENT;
		fwrite(&letter, sizeof(char), sizeof(char), output);
		fwrite(list->code, sizeof(char), strlen(list->code), output);
		fwrite(&symbol, sizeof(char), sizeof(char), output);
	}
	fwrite(&symbol, sizeof(char), sizeof(char), output);

	int size = 0;
	int bit = 0;
	int index = 0;
	symbol = '\0';
	char* string = (char*)calloc(256, 256 * sizeof(char));
	char* string_to_file = (char*)calloc(256, 256 * sizeof(char));

	while ((size = fread(string, sizeof(char), 256, input)))
	{
		for (int i = 0; i < size; ++i)
		{
			list = encoding;
			for (; list->letter != string[i]; list = list->next);

			for (int j = 0; j < strlen(list->code); ++j)
			{
				if (list->code[j] == '1')
				{
					symbol <<= 1;
					symbol += 1;
				}
				else
				{
					symbol <<= 1;
				}

				++bit;

				if (bit == 8)
				{
					string_to_file[index++] = symbol;
					bit = 0;
					symbol = '\0';
				}

				if (index == 256)
				{
					fwrite(string_to_file, sizeof(char), index, output);
					memset(string_to_file, '\0', index);
					index = 0;
				}
			}
		}
		memset(string, '\0', size);
	}

	if (bit!=0)
	{
		char number = 8 - bit + '0';
		string_to_file[index++] = number;
		string_to_file[index++] = symbol;
		fwrite(string_to_file, sizeof(char), index, output);
	}

	fclose(input);
	fclose(output);
	return 0;
}