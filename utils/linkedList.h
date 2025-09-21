#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LISTELEMENT {
	struct LISTELEMENT* next;
	char* content;
	int depth;
} linkedElement;

linkedElement* init(const char* content);

void addEl(linkedElement* list, const char* content);

void removeEl(linkedElement* list, const char* content);

linkedElement* last(const linkedElement* list);

void destroy(linkedElement* list);

void printList(linkedElement* list);

linkedElement* fromStrToList(const char* pathname);
