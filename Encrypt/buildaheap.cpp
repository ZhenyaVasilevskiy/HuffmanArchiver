#include "buildaheap.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void heapify(node_t** array, int size, int index)
{
	int best = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < size && array[l]->priority < array[best]->priority)
		best = l;

	if (r < size && array[r]->priority < array[best]->priority)
		best = r;

	if (best != index)
	{
		treeSwap(&array[index], &array[best]);
		heapify(array, size, best);
	}
}

void merge(node_t** array, int size)
{
	while (size > 1)
	{
		size--;
		node_t* a = array[0];
		treeSwap(&array[0], &array[size]);
		heapify(array, size, 0);
		node_t* b = array[0];


		node_t* c = (node_t*)malloc(sizeof(node_t));
		c->left = (node_t*)malloc(sizeof(node_t));
		c->left = a;

		c->right = (node_t*)malloc(sizeof(node_t));
		c->right = b;
		c->priority = a->priority + b->priority;
		c->letter = STOPELEMENT;

		array[0] = c;
		heapify(array, size, 0);
	}
}

node_t* treeBuild(node_t** array, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(array, size, i);

	merge(array, size);

	return array[0];
}