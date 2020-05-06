#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "buildaheap.h"
#include "textcompress.h"

int main()
{
	node_t** chars = (node_t**)malloc(sizeof(node_t*)*256);
	int size = createLetterTable(&chars);
	node_t* tree = treeBuild(chars, size);

	//printTree(tree, 0);
	//system("pause");

	list_t* encoding = NULL;
	char* string = (char*)calloc(sizeof(char), sizeof(char));
	encoding = setEncoding(tree, &encoding, string);

	int result = textCompress(encoding); 

	listFree(&encoding);
	treeFree(&tree);
	free(tree);

	if (result == 0) printf("Successfully encrypted!\n");
	else printf("Error was occured!\n");

	system("pause");
	return 0;
}