#include <stdio.h>
#include <fstream>
#include <stdarg.h>
#include "tree.h"

FILE* treeCreate(node_t** main_tree)
{
	node_t* tree = *main_tree;

	FILE* input;
	fopen_s(&input, "encrypted.compressed", "rb");
	if (input == NULL) return NULL;

	char* symbols = (char*)calloc(256, 256 * sizeof(char)); //������ ��� ����������.

	while (true) //���� �� ������ �� �����.
	{
		fgets(symbols, 256, input);
		if (symbols[0] == '\n') break; //���� ��� ������ �� ����, �� ����� �����.
		if (feof(input)) return NULL;
		nodeCreate(&tree, symbols); //������� ���� � ���� ���������� � ��������.
	}

	return input;
}

void nodeCreate(node_t** main_tree, char* code) //������ ���� ������.
{
	node_t* tree = *main_tree;
	char letter = code[0]; //�������������� ����� ��� ������� � ����.

	for (int i = 1; i < strlen(code)-1; ++i) {
		if (code[i] == '1') { //���� � ���� ����, �� ���� ������.
			if (tree->right == NULL) {
				tree->right = (node_t*)malloc(sizeof(node_t));
				tree->right->right = NULL;
				tree->right->left = NULL;

				tree->right->letter = STOPELEMENT;
			}

			tree = tree->right;
		}
		else { //���� ����, �� �����.
			if (tree->left == NULL) {
				tree->left = (node_t*)malloc(sizeof(node_t));
				tree->left->right = NULL;
				tree->left->left = NULL;

				tree->left->letter = STOPELEMENT;
			}

			tree = tree->left;
		}
	}
	if (letter == STOPELEMENT) tree->letter = '\n'; //�������� ������� ������, ���� ��.
	else tree->letter = letter; //��������� ������ � ����.
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