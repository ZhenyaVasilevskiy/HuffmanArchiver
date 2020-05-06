#include "tree.h"
#include "tofile.h"
#include <stdio.h>
#include <stdlib.h>

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

int main()
{
	int result = -1;
	node_t* dictionary = new node_t; //Корень.
	dictionary->letter = STOPELEMENT;
	FILE* input	= treeCreate(&dictionary); //Иницилаизация дерева.
	if(input != NULL) result = decryptMe(dictionary, &input); //Дешифровка.
	treeFree(&dictionary);
	free(dictionary);

	if(result == 0) printf("Successfully decrypted!\n");
	else if (result == 1) printf("Empty tree!\n");
	else printf("Check your file, bro!\n");

	system("pause");
}