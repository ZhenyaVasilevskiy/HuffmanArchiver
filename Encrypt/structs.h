#pragma once
#define STOPELEMENT '~'

typedef struct node {
	unsigned char letter;
	int priority;
	node *right, *left;
}node_t;

typedef struct list {
	unsigned char letter;
	char* code;
	list* next;
}list_t;

int createLetterTable(node_t***);
void treeSwap(node_t**, node_t**);
void printTree(node_t*, int);
void listInit(list_t**, char, char*);
void listFree(list_t**);
void treeFree(node_t**);