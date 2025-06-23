#include "commands.h"

int findCMD(char* cmdName){
	if(strcmp(cmdName, "mkdir") == 0){
		return 0;
	}
	else if(strcmp(cmdName, "rmdir") == 0){
		return 1;
	}
	else if(strcmp(cmdName, "cd") == 0){
		return 2;
	}
	else if(strcmp(cmdName, "ls") == 0){
		return 3;
	}
	else if(strcmp(cmdName, "creat") == 0){
		return 4;
	}
	else if(strcmp(cmdName, "rm") == 0){
		return 5;
	}
	else if(strcmp(cmdName, "save")== 0){
		return 6;
	}
	else if(strcmp(cmdName, "reload") == 0){
		return 7;
	}
	else{
		return -1;
	}
}
command functionTable[] = {mkdir, rmdir, cd, ls, creat, rm, save, reload};
void quit(void){
	puts("You quit the simulator");
	exit(0);
}

int main(void) {
	puts("\t\t\t\t\t Welcome to the linux file system simulator ");
	puts("\t\t\t\t\t You'll find all the typical commands you'd find in a unix-like terminal which means :");
	ROOT = malloc(sizeof(node));
	ROOT->child = NULL;
	ROOT->sibling = NULL;
	ROOT->fileType = 'D';
	ROOT->name = "/";
	ROOT->parent = NULL;
	CWD = ROOT;
	puts("mkdir, rmdir, cd, ls, rm, save and reload all working with a directory name and pwd without ");
	while(1){
		char buffer[128];
		puts("Type a command among the aforementionned");
		fgets(buffer, 128, stdin);
		buffer[strcspn(buffer, "\n")]='\0';
		char commandName[20];
		char pathname[108];
		sscanf(buffer, "%s %s", commandName, pathname);
		printf("the prompted command is %s and the prompted path is %s \n", commandName, pathname);
		if(strcmp(commandName, "pwd") == 0)
			pwd();

		else if(strcmp(commandName, "quit") == 0)
			quit();

		else {
			int index = findCMD(commandName);
			if(index == -1){
				puts("unknown command, try again");
			}
			else{
				functionTable[index](pathname);
			}
		}
		memset(buffer, 0, 128);
	}
}
