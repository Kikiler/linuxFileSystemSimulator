#include "commands.h"

linkedElement* dirname(const char* pathname){
	return fromStrToList(pathname);
}

int mkdir(const char* pathname) {
	if (pathname[0] == '/') {
		linkedElement* path = dirname(pathname);
		printf(" path to create : %s\n", pathname);
		if (ROOT->child == NULL) {
			if (path->next != NULL) {
				fprintf(stderr, "no directory name : %s\n", path->next->content);
				destroy(path);
				return -1;
			}
			ROOT->child = malloc(sizeof(node));
			ROOT->child->name = path->content;
			ROOT->child->child = NULL;
			ROOT->child->parent = ROOT;
			ROOT->child->sibling = NULL;
			ROOT->child->fileType = 'D';
			printf("a new directory whose name is %s has been created \n", path->content);
			destroy(path);
			return 0; // success
		}

		node* currentDir = ROOT->child;
		puts("beginning of the loop");
		for (linkedElement* currentLinkedListEl = path; currentLinkedListEl != NULL; currentLinkedListEl = currentLinkedListEl->next) {
			if (strcmp(last(currentLinkedListEl)->content, currentLinkedListEl->content) == 0 && last(currentLinkedListEl)->depth == currentLinkedListEl->depth) { // the path exists
				if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
					puts("reached the end");
					while (currentDir->sibling != NULL)
						currentDir = currentDir->sibling;
					currentDir->sibling = malloc(sizeof(node));
					currentDir->sibling->name = currentLinkedListEl->content;
					currentDir->sibling->sibling = NULL;
					currentDir->sibling->parent = currentDir->parent;
					currentDir->sibling->child = NULL;
					currentDir->sibling->fileType = 'D';
					printf("a new directory whose name is %s has been created \n", currentLinkedListEl->content);
					destroy(path);
					return 0; // success
				}
				currentLinkedListEl = currentLinkedListEl->next;
				printf(" %s already exists \n", currentLinkedListEl->content);
			}
			else if (strcmp(last(currentLinkedListEl)->content, currentLinkedListEl->content) == 0 && last(currentLinkedListEl)->depth != currentLinkedListEl->depth) {
				if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
					node* currentSibling = currentDir->sibling;
					while (currentSibling != NULL && strcmp(currentSibling->name, currentLinkedListEl->content) != 0)
						currentSibling = currentSibling->sibling;
					if (currentSibling == NULL) {
						fprintf(stderr, "no directory name : %s\n", currentLinkedListEl->content);
						destroy(path);
						return -1;
					}
					printf("current depth : %d \n", currentLinkedListEl->depth);
					currentDir = currentSibling;
					printf("a sibling has been found: %s \n", currentLinkedListEl->content);
				}
			}
			else if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
				node* currentSibling = currentDir->sibling;
				while (currentSibling != NULL && strcmp(currentSibling->name, currentLinkedListEl->content) != 0)
					currentSibling = currentSibling->sibling;
				if (currentSibling == NULL) {
					fprintf(stderr, "no directory name : %s\n", currentLinkedListEl->content);
					destroy(path);
					return -1;
				}
				printf("current depth : %d \n", currentLinkedListEl->depth);
				currentDir = currentSibling;
				printf("a sibling has been found: %s \n", currentLinkedListEl->content);
			}
			else {
				if (currentDir->child == NULL && currentLinkedListEl->next->depth != last(currentLinkedListEl)->depth) {
					fprintf(stderr, "no directory name : %s\n", currentLinkedListEl->content);
					destroy(path);
					return -1;
				}
				else if (currentDir->child == NULL && currentLinkedListEl->next->depth == last(currentLinkedListEl)->depth) {
					currentDir->child = malloc(sizeof(node));
					currentDir->child->name = currentLinkedListEl->next->content;
					currentDir->child->sibling = NULL;
					currentDir->child->child = NULL;
					currentDir->child->parent = currentDir;
					currentDir->fileType = 'D';
					printf("a new child has been created : %s \n", currentLinkedListEl->next->content);
					destroy(path);
					return 0;
				}
				else {
						currentDir = currentDir->child;
						puts("the file is down below in the child");
						printf("current depth : %d \n", currentLinkedListEl->depth);
					}

			}
		}
		puts("end of loop");
		destroy(path);
		return -1;
	}

	return 0;
}
int rmdir(const char* pathname){
	return 0;
}


int cd(const char* pathname){
	return 0;
}

int ls(const char* pathname){
	return 0;
}

int pwd(void){
	return 0;
}

int creat(const char* pathname){
	return 0;
}

int rm(const char* pathname){
	return 4;
}

int save(const char* filename){
	return 1 ;
}

int reload(const char* pathname){
	return 1;
}
