#include "commands.h"

char* basename(char* pathname){
	char* name = strdup(pathname);
	char* result = NULL;
	char* str = name;
	char* sep = strdup("/");
	if(pathname[0] =='/'){
		name++;
		//printf("name after the / %s \n", name);
	}
	char* token = strsep(&name, sep);
	while(token != NULL && token[0] != '\0'){
		//printf("a token : %s\n", token);
		result = strdup(token);
		token = strsep(&name, sep);
	}
	if(result == NULL){
		fprintf(stderr, "error in parsing \n");
		exit(-1);
	}
	free(str);
	free(sep);
	//printf("the found base is %s \n", result);
	return result;
}

char* dirname(char* pathname){
	char* name = strdup(pathname);
	char* result = strdup("");
	char* str = name;
	char* sep = strdup("/");
	if(pathname[0]=='/'){
		result = strdup("/");
		name++;
		//printf("name after the / %s \n", name);
	}
	char* token = strsep(&name, sep);
	while(token != NULL && strcmp(token, basename(pathname)) != 0){
		if(token[0] != '\0'){
			//printf("actually found a token : %s\n", token);
			strlcat(result, token, strlen(token)+strlen(result)+1);
			strlcat(result, sep, strlen(result) + 2);
			//printf("current path: %s\n", result);
		}
		token = strsep(&name, sep);
	}
	free(str);
	free(sep);
	return result;
}

int mkdir(char* pathname) {
	//	puts("Mkdir actually launched");
	if(pathname != NULL && pathname[0] != '/'){
		char* dir = strdup(dirname(pathname));
		char* str1 = strdup(dir);
		char* name = strdup(basename(pathname));
		char* str2= name;
		printf("found a base %s and dir %s \n", name, dir);
		node* current = CWD;
		for(char* currentDir = strsep(&dir, "/"); currentDir != NULL; currentDir = strsep(&dir, "/")){
			current = current->child;
			if(current == NULL){
				fprintf(stderr, "no directory named %s\n", currentDir);
				free(str1);
				free(str2);
				return -1;
			}
			if(strcmp(current->name, currentDir) != 0){
				while(current != NULL && strcmp(current->name, currentDir) != 0)
					current->sibling = current;
				if(strcmp(current->name, currentDir) != 0){
					fprintf(stderr, "no directory named %s\n", currentDir);
					free(str1);
					free(str2);
					return -1;
				}
			}
			if(current->fileType != 'D'){
				fprintf(stderr, " %s not a directory \n", currentDir);
				free(str1);
				free(str2);
				return -1;
			}
		}

		while(current->sibling != NULL){
			current = current->sibling;
		}
		current->sibling = malloc(sizeof(node));
		current->sibling->name = name;
		current->sibling->sibling = NULL;
		current->sibling->child = NULL;
		current->sibling->parent = current->parent;
		current->sibling->fileType = 'D';
		printf("created a new directory : %s at %s starting from the current working directory \n", current->sibling->name, str1);
		free(str1);
		free(str2);
		return 0; // success
	}
	else if(pathname != NULL){
		char* dir = dirname(pathname);
		char* name = basename(pathname);
		char* str1 = dir;
		char* str2 = name;
		char* sep = strdup("/");
		node* current = malloc(sizeof(node));	
		char* dirCopy = strdup(dir);
		printf("found a base :%s and dir :%s \n", name, dir);
		dir++;
		//printf("incremented dir pointer :%s \n", dir);
		current = ROOT;
		if(current->child == NULL){
			current->child = malloc(sizeof(node));
			current->child->parent = current;
			current->child->name = strdup(name);
			current->child->sibling = NULL; 
			current->child->child = NULL;
			current->child->fileType = 'D';
			printf("the first directory : %s has been created starting from root \n", current->child->name);
			free(str1);
			free(str2);
			free(sep);
			return 0;
		}
		for(char* currentDir = strsep(&dir, sep); currentDir != NULL && currentDir[0] != '\0'; currentDir = strsep(&dir, sep)){
			current = current->child;
			puts("in loop (root)");
			if(current == NULL){
				fprintf(stderr, "no directory named 1st %s\n", currentDir);
				free(str1);
				free(str2);
				free(sep);
				return -1;
			}
			if(strcmp(current->name, currentDir) != 0){
				//	printf("found name : %s and current directory : %s \n", current->name, currentDir);
				while(current != NULL && strcmp(current->name, currentDir) != 0){
					current = current->sibling;
				}
				if(current == NULL){
					fprintf(stderr, "no directory named 2nd %s\n", currentDir);
					free(str1);
					free(str2);
					free(sep);
					return -1;
				}
				if(current->fileType != 'D'){
					fprintf(stderr, " %s not a directory \n", currentDir);
					free(str1);
					free(str2);
					return -1;
				}
			}
			if(current->child == NULL){
				current->child = malloc(sizeof(node));
				current->child->name = strdup(name);
				current->child->child = NULL;
				current->child->sibling = NULL;
				current->child->parent = current;
				current->child->fileType = 'D';
				printf("a new directory : %s has been created at %s starting from root\n", current->child->name, str1);
				free(str1);
				free(str2);
				free(sep);
				return 0;//success
			}
			if(current->fileType != 'D'){
				fprintf(stderr, " %s not a directory \n", currentDir);
				free(str1);
				free(str2);
				return -1;
			}
		}
		while(current->sibling != NULL){
			current = current->sibling;
		}
		current->sibling = malloc(sizeof(node));
		current->sibling-> name = strdup(name);
		current->sibling->child = NULL;
		current->sibling->parent = current->parent;
		current->sibling->fileType = 'D';
		printf("a new directory : %s has been created at %s starting from root\n", current->sibling->name, str1);
		free(str1);
		free(str2);
		free(sep);
		return 0; // success
	}
	fprintf(stderr, "should never get there \n");
	return -1;
}
int rmdir(char* pathname){
	if(pathname != NULL && pathname[0] != '/'){
		char* dir = strdup(dirname(pathname));
		char* name = strdup(basename(pathname));
		node* current = ROOT;
		node* previous = ROOT;
		for(char* currentDir = strsep(&pathname, "/"); currentDir != NULL; currentDir = strsep(&pathname, "/")){
			current = current->child;
			if(current == NULL){
				fprintf(stderr, "no directory name %s\n", currentDir);
				free(name);
				free(dir);
				return -1;
			}
			if(strcmp(current->name, currentDir) != 1){
				while(current != NULL && strcmp(current->name, currentDir) != 1)
					current->sibling = current;
			}

			if(strcmp(current->name, currentDir) != 1){
				fprintf(stderr, "no directory named %s\n", currentDir);
				free(name);
				free(dir);
				return -1;
			}
			if(current->fileType != 'D'){
				fprintf(stderr, " %s not a directory \n", currentDir);
				free(name);
				free(dir);
				return -1;
			}
		}

		while(current->sibling != NULL){
			current = current->sibling;
		}
		current->sibling = malloc(sizeof(node));
		current->sibling->name = name;
		current->sibling->sibling = NULL;
		current->sibling->child = NULL;
		current->sibling->parent = current->parent;
		current->sibling->fileType = 'D';
		free(name);
		free(dir);
		return 0; // success
	}
	else if(pathname != NULL){
		char* dir = strdup(dirname(pathname));
		char* name = strdup(basename(pathname));
		node* current = malloc(sizeof(node));	
		current = CWD;
		for(char* currentDir = strsep(&dir, "/"); currentDir != NULL; currentDir = strsep(&dir, "/")){
			current = current->child;
			if(current == NULL){
				fprintf(stderr, "no directory name %s\n", currentDir);
				free(name);
				free(dir);
				return -1;
			}
			if(strcmp(current->name, currentDir) != 1){
				while(current != NULL && strcmp(current->name, currentDir) != 1)
					current->sibling = current;
				if(current == NULL){
					fprintf(stderr, "no directory named %s\n", currentDir);
					free(name);
					free(dir);
					return -1;
				}
				if(current->fileType != 'D'){
					fprintf(stderr, " %s not a file \n", currentDir);
					free(name);
					free(dir);
					return -1;
				}
			}
		}
		while(current->sibling != NULL){
			current = current->sibling;
		}
		current->sibling = malloc(sizeof(node));
		current->sibling->name = name;
		current->sibling->sibling = NULL;
		current->sibling->child = NULL;
		current->sibling->parent = current->parent;
		current->sibling->fileType = 'D';
		free(name);
		free(dir);
		return 0; // success
	}
	return -1;
}


int cd(char* pathname){
	return 0;
}

int ls(char* pathname){
	return 0;
}

int pwd(void){
	return 0;
}

int creat(char* pathname){
	return 0;
}

int rm(char* pathname){
	return 4;
}

int save(char* filename){
	return 1 ;
}

int reload(char* pathname){
	return 1;
}
