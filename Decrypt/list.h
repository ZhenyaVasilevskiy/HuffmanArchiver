#pragma once
#include <stdio.h>
#define STOPELEMENT '~'

typedef struct node {
	char letter;
	node* right = NULL, *left = NULL;
}node_t;

FILE* treeCreate(node_t**);
void nodeCreate(node_t**, char*);
void letsWork(node_t*, FILE**);
void helperFunction(unsigned char, int, char*, int*, node_t**, node_t*, FILE**);
