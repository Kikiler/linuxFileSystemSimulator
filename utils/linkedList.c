#include "linkedList.h"

linkedElement* init(const char* content){
	if(content == NULL)
		fprintf(stderr, "given string is null\n");
	linkedElement* result = malloc(sizeof(linkedElement));
	result->next = NULL;
    result->content = strdup(content);
	result->depth = 0;
	return result;
}

void addEl(linkedElement* list, const char* content){
	if(list == NULL || content == NULL){
		fprintf(stderr, "given list or string is null\n");
		exit(-1);
	}
	else if(list->next == NULL){
		list->next = malloc(sizeof(linkedElement));
		list->next->next = NULL;
		list->next->content = strdup(content);
		list->next->depth = list->depth + 1;
		return;	
	}
	for(linkedElement* current = list->next; current != NULL; current= current->next){
		if(current->next == NULL){
			current->next = malloc(sizeof(linkedElement));
			current->next->next = NULL;
			current->next->content = strdup(content);
			current->next->depth = current->depth + 1;
			return;
		}
	}
}

linkedElement* last(const linkedElement* list){
	if(list == NULL){
		fprintf(stderr, "given list is null\n");
		exit(-1);
	}
	else if(list->next == NULL){
		return list;
	}
	else {
		for(linkedElement* current = list->next; current != NULL; current = current-> next){
			if(current->next == NULL){
				return current;
			}
		}
		fprintf(stderr, "Should never get there \n");
		exit(-1);
	}
}

void destroy(linkedElement* list){
	if(list == NULL){
		fprintf(stderr, "Can't destroy null list");
		exit(-1);
	}
	else if(list->next == NULL){
		free(list);
	}
	else {
		linkedElement* current = list->next;
		linkedElement* previous = list->next;
		free(list);
		do {
			current = current->next;
			free(previous);
			previous = current;
		}while(current != NULL);
	}

}

linkedElement* fromStrToList(const char* pathname){
	if(pathname == NULL){
		fprintf(stderr, "given string is null \n");
		exit(-1);
	}
	char* path = strdup(pathname);
	if(path[0] == '/')
		path++;
	linkedElement* result = init(strsep(&path, "/"));
	for(const char* str = strsep(&path, "/"); str != NULL && *str != '\0'; str = strsep(&path, "/"))
		addEl(result, str);
free(path);
return result;
}

void printList(linkedElement* list){
	if(list == NULL){
		fprintf(stderr, "list is null");
		exit(-1);
	}
	printf("[ %s", list->content);
	for(const linkedElement* current = list->next; current != NULL; current = current->next){
		printf(", %s", current->content);
	}
	puts(" ]");
}
