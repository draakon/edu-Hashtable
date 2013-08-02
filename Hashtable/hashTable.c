/* hashTable.c :: Avatud addresseerimisega paisktabel.
 * Autor: Kristjan Kaitsa
 * Programmeerimine C-keeles (MTAT.03.219) @ 2012 A.D. */
#include "hashTable.h"

// Uue paisktabeli loomine.
hashtable* hashtable_new(PROTO_HASHFUNC, unsigned int bucketsCount, PROTO_COMPAREFUNC) {
	int i;
	hashtable *newTable = (hashtable*) malloc(sizeof(hashtable));

	newTable->hashFunction = hashFunction;
	newTable->compareFunction = compareFunction;
	newTable->bucketsCount = bucketsCount;
	newTable->buckets = (linkedList**) malloc(sizeof(linkedList*)*bucketsCount);
	for (i = 0; i < bucketsCount; i++)
		newTable->buckets[i] = linkedList_new();

	return newTable;
}

// Kontrollib võrdlusfunktsiooniga, kas paistabelis antud element juba eksisteerib.
unsigned char hashtable_contains(hashtable *table, void *data) {
	unsigned int index;

	index = linkedList_search(
		table->buckets[(*table->hashFunction)(data)],
		table->compareFunction,
		data
	);
	if (index != UINT_MAX)
		return TRUE;
	else
		return FALSE;
}

// Tagastab paisktabelist sisendparameetriga võrdse elemendi.
void* hashtable_get(hashtable *table, void *data) {
	unsigned int index;
	linkedList *bucket;

	bucket = table->buckets[(*table->hashFunction)(data)];
	index = linkedList_search(bucket, table->compareFunction, data);

	return linkedList_get(bucket, index);
}

void hashtable_remove(hashtable *table, void *data) {
	unsigned int index;
	linkedList *bucket;

	bucket = table->buckets[(*table->hashFunction)(data)];
	index = linkedList_search(bucket, table->compareFunction, data);
	linkedList_remove(bucket, index);
}

/* Vabastab kõik paisktabeli poolt kasutatud mälu:
 * ka. listide ning viidete (paisktabeli sisu) mälu.*/
void hashtable_destroyWithContent(hashtable *table) {
	int i;

	for (i = 0; i < table->bucketsCount; i++)
		linkedList_destroyWithContent(table->buckets[i]);

	free(table->buckets);
	free(table);
}