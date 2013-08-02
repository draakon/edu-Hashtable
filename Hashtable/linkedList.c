/* linkedList.c :: Lingitud list.
 * Autor: Kristjan Kaitsa
 * Programmeerimine C-keeles (MTAT.03.219) @ 2012 A.D. */
#include "linkedList.h"

// Kas antud indeks on legaalne.
__inline unsigned char isValidIndex(unsigned int index) {
	if ((index >= 0) && (index < UINT_MAX))
		return TRUE;
	else
		return FALSE;
}

// Uue listi loomine.
linkedList* linkedList_new(void) {
	linkedList* newList = (linkedList*) malloc(sizeof(linkedList));

	newList->size = 0;
	newList->first = NULL;
	newList->last = NULL;
	return newList;
}

// Listi lõppu lisamine.
void linkedList_append(linkedList *list, void *value) {
	node* newNode = (node*) malloc(sizeof(node));

	if (!isValidIndex(list->size)) return;

	newNode->value = value;
	newNode->next = NULL;

	if (list->size == 0)
		list->first = newNode;
	else
		list->last->next = newNode;

	list->last = newNode;
	list->size++;
}

// Indeksi järgi elemendi leidmine listist.
__inline node* findNode(linkedList *list, unsigned int index) {
	unsigned int i;
	node *p;

	if (!isValidIndex(index)) return NULL;
	
	if (index >= list->size)
		return NULL;
	else if (index == 0)
		return list->first;
	else if (index == list->size - 1)
		return list->last;
	else {
		p = list->first;
		for (i = 0; i < index; i++) {
			p = p->next;
		}
		return p;
	}
}

// Indeksi järgi elemendi tagastamine listist.
void* linkedList_get(linkedList *list, unsigned int index) {
	node *p;

	if ((!isValidIndex(index)) || (index >= list->size)) return NULL;

	p = findNode(list, index);
	return (p != NULL) ? p->value : NULL;
}

// Indeksi järgi listi elemendi väärtuse määramine.
void linkedList_set(linkedList *list, unsigned int index, void *value) {
	node *p;

	if ((!isValidIndex(index)) || (index >= list->size)) return;

	p = findNode(list, index);
	if (p != NULL)
		p->value = value;
}

// Indeksi järgi elemendi listist eemaldamine.
void linkedList_remove(linkedList *list, unsigned int index) {
	node *p;
	node *p_last;
	unsigned int i;

	if ((!isValidIndex(index)) || (index >= list->size)) return;

	p_last = NULL;
	p = list->first;
	for (i = 0; i < index; i++) {
		p_last = p;
		p = p->next;
	}
	
	if (p_last != NULL)				// node ei olnud esimene
		p_last->next = p->next;			// muudame eelneva järglase
	else							// node oli esimene
		list->first = p->next;			// muudame listi esimese elemendi viida

	if (list->last == p)			// node oli viimane
		list->last = p_last;			// muudame listi viimase elemendi viida

	list->size--;

	free(p);
}

// Listist sisendparameetriga võrdse elemendi otsimine.
unsigned int linkedList_search(linkedList *list, unsigned char (*compareFunction)(void*, void*), void *value) {
	node *p;
	unsigned int i;

	p = list->first;
	for (i = 0; i < list->size; i++) {
		if ((*compareFunction)(p->value, value))
			return i;
		p = p->next;
	}

	return UINT_MAX;
}

// Kontrollib, kas list on tühi.
unsigned char linkedList_isEmpty(linkedList *list) {
	if (list->size == 0) 
		return TRUE;
	else
		return FALSE;
}

/* Ettevaatust!
 * Kui viite mälu ei olnud dünaamiliselt eraldatud, siis tulemus on
 * etteaimamatu - crash? memory corruption? */
void linkedList_destroyWithContent(linkedList *list) {
	node *p;
	node *p_next;
	unsigned int i;

	p = list->first;
	for (i = 0; i < list->size; i++) {
		p_next = p->next;
		free(p->value);
		free(p);
		p = p_next;
	}
	free(list);
}
