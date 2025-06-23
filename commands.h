#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
	char* name;
	char fileType;
	struct NODE* child;
	struct NODE* parent;
	struct NODE* sibling;	
} node;

node* ROOT;
node* CWD; 

typedef int (*command)(char* pathname);

int mkdir(char* pathname); 

int rmdir(char* pathname);

int cd(char* pathname);

int ls(char* pathname);

int pwd(void);

int creat(char* pathname);

int rm(char* pathname);

int save(char* filename);

int reload(char* pathname);
