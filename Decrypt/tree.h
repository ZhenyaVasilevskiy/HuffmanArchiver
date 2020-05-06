#pragma once
#include <stdio.h>
#define STOPELEMENT '~'

typedef struct node {
	char letter;
	node* right = NULL, *left = NULL;
}node_t;

FILE* treeCreate(node_t**);
void nodeCreate(node_t**, char*);
void treeFree(node_t**);