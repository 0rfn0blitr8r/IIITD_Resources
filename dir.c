#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int arg_counter = 1;
	for(int i = 0; i<argc; i++){
		if(strcmp(argv[i], "placeholder")){
			arg_counter++;
		}
	}


	struct stat st;
	
	if(arg_counter == 3){
		char *newDirName = argv[2];
		if(stat(newDirName, &st) == 0){
			printf("ERROR: Directory %s already present here\n", newDirName);
			return 1;
		}
		else{
			if(mkdir(newDirName, S_IRWXU) == 0){
				if(chdir(newDirName) == 0){
					printf("Path has been changed to the given newly made directory %s\n", newDirName);
				}
				else{
					printf("ERROR: changing of path could not be executed\n");
				}
			}
			else{
				printf("ERROR: in making of a new directory\n");
			}
		}
	}

	else if(strcmp(argv[2], "-v") == 0){
		char *newDirName = argv[3];
		if (stat(newDirName, &st) == 0) {
			printf("Error: Directory '%s' already exists\n", newDirName);
			return 1;
		}
		else{
			printf("A new directory is to be made with the name %s\n", newDirName);
			if(mkdir(newDirName, S_IRWXU) == 0){
				printf("A new directory %s has been made successfully\n", newDirName);
				if(chdir(newDirName) == 0){
					printf("Path has been successfully changed to %s\n", newDirName);
				}
				else{
					printf("ERROR: changing of path could not be executed\n");
				}
			}
			else{
				printf("ERROR: in making of a new directory\n");
			}
		}
	}

	else if(strcmp(argv[2], "-r") == 0){
		char *newDirName = argv[3];
		if (stat(newDirName, &st) != 0) {
			//code for a new dir and changing path into it
			if(mkdir(newDirName, S_IRWXU) == 0){
				if(chdir(newDirName) == 0){
						printf("%s has been made and\nPath has been changed to it\n", newDirName);
				}
				else{
						printf("ERROR: path couldn't be changed to new directory\n");
				}
			}	
			else{
					printf("ERROR: new directory couldn't be formed\n");
			}
		}
		else{
			fprintf(stderr,"Given directory %s exists\n", newDirName);

			//removing the existing EMPTY directory with rmdir
			if(rmdir(newDirName) == 0){
				// printf("present Dir has been deleted\n");
				if(mkdir(newDirName, S_IRWXU) == 0){
					if(chdir(newDirName) == 0){
						printf("%s has been deleted and made again and\nPath has been changed to it\n", newDirName);
					}
					else{
						printf("ERROR: path couldn't be changed to new directory\n");
					}
				}	
				else{
					printf("ERROR: new directory couldn't be formed\n");
				}
			}
			else{
				printf("ERROR: directory couldn't be deleted\n");
			}
		}
	}
	else{
		//error handling
		printf("Wrong argument\n");
	}
}