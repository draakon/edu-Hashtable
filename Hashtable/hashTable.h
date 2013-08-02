/* hashTable.h :: Avatud addresseerimisega paisktabel.
 * Autor: Kristjan Kaitsa
 * Programmeerimine C-keeles (MTAT.03.219) @ 2012 A.D. */
#pragma once
#include "linkedList.h"
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define PROTO_HASHFUNC unsigned int (*hashFunction)(void*)
#define PROTO_COMPAREFUNC unsigned char (*compareFunction)(void*, void*)

typedef struct tagHashtable {
	PROTO_HASHFUNC;
	PROTO_COMPAREFUNC;
	unsigned int bucketsCount;
	linkedList **buckets;
} hashtable;

hashtable* hashtable_new(PROTO_HASHFUNC, unsigned int buckets, PROTO_COMPAREFUNC);
__inline void hashtable_put(hashtable *table, void *data);
unsigned char hashtable_contains(hashtable *table, void *data);
void hashtable_remove(hashtable *table, void *data);
void* hashtable_get(hashtable *table, void *data);
void hashtable_destroyWithContent(hashtable *table);

__inline void hashtable_put(hashtable *table, void *data) {
	linkedList_append(
		table->buckets[(*table->hashFunction)(data)], 
		data
	);
}
