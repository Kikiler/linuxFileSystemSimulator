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
			//printf("a new directory whose name is %s has been created \n", path->content);
			destroy(path);
			return 0; // success
		}

		node* currentDir = ROOT->child;
		node* lastDir = currentDir;
		linkedElement* currentLinkedListEl = path;
		linkedElement* lastLinkedListEl = currentLinkedListEl;
		//puts("beginning of the loop");
		while(currentDir != NULL) {
			if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
				lastDir = currentDir;
				node* currentSibling = currentDir->sibling;
				while (currentSibling != NULL && strcmp(currentSibling->name, currentLinkedListEl->content) != 0) {
					lastDir = currentSibling;
					currentSibling = currentSibling->sibling;
				}
				if (last(path)->depth == currentLinkedListEl->depth && currentSibling == NULL) { // case where the file needs to be created
					lastDir->sibling = malloc(sizeof(node));
					lastDir->sibling->name = currentLinkedListEl->content;
					lastDir->sibling->sibling = NULL;
					lastDir->sibling->parent = lastDir->parent;
					lastDir->sibling->child = NULL;
					lastDir->fileType = 'D';
					puts("sibling has been created");
					return 1;
				}
				else if (currentSibling == NULL) { // case where the file doesnt exist
					fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
					destroy(path);
					return -1;
				}
				lastDir = currentSibling;
				currentDir = currentSibling->child;
				//printf("a sibling : %s has been found in depth : %d  \n", currentLinkedListEl->content, currentLinkedListEl->depth);
				lastLinkedListEl = currentLinkedListEl;
				currentLinkedListEl = currentLinkedListEl->next;
				if (currentLinkedListEl == NULL) { // case when the file already exist
					fprintf(stderr, " %s already exists \n", pathname);
					return 2;
				}
			}
			else {
					lastDir = currentDir;
					currentDir = currentDir->child;
					lastLinkedListEl = currentLinkedListEl;
					currentLinkedListEl = currentLinkedListEl->next;
					//puts("the file is down below in the child");
					if (currentLinkedListEl == NULL) {
						fprintf(stderr, " %s already exists \n", pathname);
						return 2;
					}
					printf("current depth : %d \n", lastLinkedListEl->depth);

			}
			lastLinkedListEl = currentLinkedListEl;
		}
		puts("end of loop");
		if (lastLinkedListEl->depth != last(path)->depth) {
			fprintf(stderr, "no directory name : %s\n", lastLinkedListEl->content);
			destroy(path);
			return -1;
		}
		lastDir->child = malloc(sizeof(node));
		lastDir->child->name = currentLinkedListEl->content;
		lastDir->child->sibling = NULL;
		lastDir->child->child = NULL;
		lastDir->child->parent = lastDir;
		lastDir->child->fileType = 'D';
		destroy(path);
		puts("child has been created");
		return 0;
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
