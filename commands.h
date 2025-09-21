#pragma once
#include "utils/linkedList.h"
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

typedef int (*command)(const char* pathname);

int mkdir(const char* pathname);

int rmdir(const char* pathname);

int cd(const char* pathname);

int ls(const char* pathname);

int pwd(void);

int creat(const char* pathname);

int rm(const char* pathname);

int save(const char* filename);

int reload(const char* pathname);
