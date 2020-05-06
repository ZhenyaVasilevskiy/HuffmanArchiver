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

	char* symbols = (char*)calloc(256, 256 * sizeof(char)); //Строка для считывания.

	while (true) //Пока не выйдет из шапки.
	{
		fgets(symbols, 256, input);
		if (symbols[0] == '\n') break; //Если вся строка из него, то конец шапки.
		if (feof(input)) return NULL;
		nodeCreate(&tree, symbols); //Содание узла с этой кодировкой и символом.
	}

	return input;
}

void nodeCreate(node_t** main_tree, char* code) //Строим узел дерева.
{
	node_t* tree = *main_tree;
	char letter = code[0]; //Инициализируем букву для вставки в узел.

	for (int i = 1; i < strlen(code)-1; ++i) {
		if (code[i] == '1') { //Если в коде один, то идем вправо.
			if (tree->right == NULL) {
				tree->right = (node_t*)malloc(sizeof(node_t));
				tree->right->right = NULL;
				tree->right->left = NULL;

				tree->right->letter = STOPELEMENT;
			}

			tree = tree->right;
		}
		else { //Если ноль, то влево.
			if (tree->left == NULL) {
				tree->left = (node_t*)malloc(sizeof(node_t));
				tree->left->right = NULL;
				tree->left->left = NULL;

				tree->left->letter = STOPELEMENT;
			}

			tree = tree->left;
		}
	}
	if (letter == STOPELEMENT) tree->letter = '\n'; //Дешифрую перенос строки, если он.
	else tree->letter = letter; //Записываю символ в узел.
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