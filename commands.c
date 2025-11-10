#include "commands.h"


void initRoot(void) {
	ROOT = (node*)malloc(sizeof(node));
	ROOT->child = NULL;
	ROOT->parent = NULL;
	ROOT->sibling = NULL;
	ROOT->name = "/";
	CWD = ROOT;
}

void addSibling(node* sibling, const char* name) {
	if (sibling == NULL) {
		fprintf(stderr, "sibling is NULL\n");
		exit(-1);
	}
	if (sibling->sibling != NULL) {
		fprintf(stderr, "sibling is not NULL -> so I can't add you right now as sibling\n");
		exit(-1);
	}
	sibling->sibling = (node*)malloc(sizeof(node));
	sibling->sibling->name = name;
	sibling->sibling->parent = sibling->parent;
	sibling->sibling->sibling = NULL;
	sibling->sibling->child = NULL;
	sibling->sibling->fileType = 'D'; // temporary solution
}

void giveBirth(node* parent, const char* name) {
	if (parent == NULL) {
		fprintf(stderr, "giveBirth: parent is NULL\n");
		exit(-1);
	}
	if (parent->child != NULL) {
		fprintf(stderr, "giveBirth: child is not NULL\n");
		exit(-1);
	}

	parent->child = (node*)malloc(sizeof(node));
	parent->child->name = name;
	parent->child->parent = parent;
	parent->child->sibling = NULL;
	parent->child->child = NULL;
	parent->child->fileType = 'D'; // temporary solution
}

static linkedElement* dirname(const char* pathname){
	return fromStrToList(pathname);
}

int mkdir(const char* pathname) {
	if (pathname[0] == '/') {
		linkedElement* path = dirname(pathname);
		//printf(" path to create : %s\n", pathname);
		if (ROOT->child == NULL) {
			if (path->next != NULL) {
				fprintf(stderr, "no directory name : %s\n", path->next->content);
				destroy(path);
				return -1;
			}
			giveBirth(ROOT, path->content);
			//printf("a new directory whose name is %s has been created \n", path->content);
			destroy(path);
			return 0; // success
		}

		node* currentDir = ROOT->child;
		node* lastDir = currentDir;
		linkedElement* currentLinkedListEl = path;
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
					addSibling(lastDir, currentLinkedListEl->content);
					//puts("sibling has been created");
					return 1;
				}
				if (currentSibling == NULL) { // case where the file doesnt exist
					fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
					destroy(path);
					return -1;
				}
				lastDir = currentSibling;
				currentDir = currentSibling->child;
				//printf("a sibling : %s has been found in depth : %d  \n", currentLinkedListEl->content, currentLinkedListEl->depth);
				currentLinkedListEl = currentLinkedListEl->next;
				if (currentLinkedListEl == NULL) { // case when the file already exist
					fprintf(stderr, " %s already exists \n", pathname);
					return 2;
				}
			}
			else {
					lastDir = currentDir;
					currentDir = currentDir->child;
					currentLinkedListEl = currentLinkedListEl->next;
					//puts("the file is down below in the child");
					if (currentLinkedListEl == NULL) {
						fprintf(stderr, " %s already exists \n", pathname);
						return 2;
					}
					//printf("current depth : %d \n", lastLinkedListEl->depth);
			}
		}
		//puts("end of loop");
		if (currentLinkedListEl->depth != last(path)->depth) {
			fprintf(stderr, "no directory name : %s\n", currentLinkedListEl->content);
			destroy(path);
			return -1;
		}
		giveBirth(lastDir, currentLinkedListEl->content);
		destroy(path);
		//puts("child has been created");
		return 0;
	}

	return 0;
}

int rmdir(const char* pathname){
	if (pathname[0] == '/') {
		linkedElement* path = dirname(pathname);
		node* currentDir = ROOT->child;
		node* lastDir = currentDir;
		linkedElement* currentLinkedListEl = path;
		while (currentDir != NULL) {
			if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
				lastDir = currentDir;
				node* currentSibling = currentDir->sibling;
				while (currentSibling != NULL && strcmp(currentSibling->name, currentLinkedListEl->content) != 0) {
					lastDir = currentSibling;
					currentSibling = currentSibling->sibling;
				}
				if (currentSibling == NULL) { // case where the file doesnt exist
					fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
					destroy(path);
					return -1;
				}
				if (last(path)->depth == currentLinkedListEl->depth && strcmp(currentSibling->name, currentLinkedListEl->content) == 0) { // case where the file needs to be destroyed
					node* next = currentSibling->sibling;
					if (currentSibling->child != NULL) {
						fprintf(stderr, "%s is not empty \n", currentSibling->name);
						destroy(path);
						return -1;
					}
					free(currentSibling);
					lastDir->sibling = next;
					puts("sibling has been deleted");
					return 1;
				}
				lastDir = currentSibling;
				currentDir = currentSibling->child;
				//printf("a sibling : %s has been found in depth : %d  \n", currentLinkedListEl->content, currentLinkedListEl->depth);
				currentLinkedListEl = currentLinkedListEl->next;
			}
			else {
				lastDir = currentDir;
				currentDir = currentDir->child;
				currentLinkedListEl = currentLinkedListEl->next;
				//puts("the file is down below in the child");
				if (currentLinkedListEl == NULL) {
					if (currentDir != NULL) {
						fprintf(stderr, "%s is not empty \n", lastDir->name);
						destroy(path);
						return -1;
					}
					node* next = lastDir->sibling;
					lastDir->parent->child = next;
					free(lastDir);
					puts("child has been deleted");
					return 0;
				}
			}
		}
			fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
			destroy(path);
			return -1;
	}
	return 0;
}


int cd(const char* pathname) {
	if (pathname[0] == '/') {
		linkedElement* path = dirname(pathname);
		node* currentDir = ROOT->child;
		node* lastDir = currentDir;
		linkedElement* currentLinkedListEl = path;
		linkedElement* lastLinkedListEl = currentLinkedListEl;
		while (currentDir != NULL) {
			if (strcmp(currentLinkedListEl->content, currentDir->name) != 0) {
				lastDir = currentDir;
				node* currentSibling = currentDir->sibling;
				while (currentSibling != NULL && strcmp(currentSibling->name, currentLinkedListEl->content) != 0) {
					lastDir = currentSibling;
					currentSibling = currentSibling->sibling;
				}
				if (currentSibling == NULL) { // case where the file doesnt exist
					fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
					destroy(path);
					return -1;
				}
				if (last(path)->depth == currentLinkedListEl->depth && strcmp(currentSibling->name, currentLinkedListEl->content) == 0) {
					CWD = currentSibling;
					destroy(path);
					return 1;
				}
				lastDir = currentSibling;
				currentDir = currentSibling->child;
				//printf("a sibling : %s has been found in depth : %d  \n", currentLinkedListEl->content, currentLinkedListEl->depth);
				lastLinkedListEl = currentLinkedListEl;
				currentLinkedListEl = currentLinkedListEl->next;
			}
			else {
				lastDir = currentDir;
				currentDir = currentDir->child;
				lastLinkedListEl = currentLinkedListEl;
				currentLinkedListEl = currentLinkedListEl->next;
				//puts("the file is down below in the child");
				if (currentLinkedListEl == NULL) {
					if (last(path)->depth == lastLinkedListEl->depth) {
						CWD = lastDir;
						destroy(path);
						return 0;
					}
					else {
						fprintf(stderr, "no directory name : %s \n", lastLinkedListEl->content);
						destroy(path);
						return -1;
					}
				}
			}
		}
		fprintf(stderr, "no sibling directory name : %s, last known : %s \n", currentLinkedListEl->content, lastDir->name);
		destroy(path);
		return -1;

	}
	return 0;
}

int ls(const char* pathname){
	return 0;
}

int pwd(void){
	linkedElement* myList = init(CWD->name);
	for ( node* current = CWD->parent; current != NULL; current = current->parent) {
		addEl(myList, current->name);
	}

	for ( int i = last(myList)->depth; 0 <= i; i--) {

	}
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
