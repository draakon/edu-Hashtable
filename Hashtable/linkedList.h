/* linkedList.h :: Lingitud list.
 * Autor: Kristjan Kaitsa
 * Programmeerimine C-keeles (MTAT.03.219) @ 2012 A.D. */
#pragma once
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0

typedef struct tagLinkedList {
	unsigned int size;
	struct tagNode *first;
	struct tagNode *last;
} linkedList;

typedef struct tagNode {
	void *value;
	struct tagNode *next;
} node;

linkedList* linkedList_new(void);
void linkedList_append(linkedList *list, void *value);
void* linkedList_get(linkedList *list, unsigned int index);
void linkedList_set(linkedList *list, unsigned int index, void *value);
void linkedList_remove(linkedList *list, unsigned int index);
unsigned int linkedList_search(linkedList *list, unsigned char (*compareFunction)(void*, void*), void *value);
unsigned char linkedList_isEmpty(linkedList *list);
void linkedList_destroyWithContent(linkedList *list);
