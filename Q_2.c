#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int code_for_word(int opt, char* file_name){
    int numOfLines = 0;
    int numOfWords = 0;
    int word_flag = 0;
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Wrong argument\n");
        return -1;
    }
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), file)){
        for (int i = 0; ; i++) {

            if(buffer[i] == '\r' && i==0){
                numOfLines++;
                break;
            }
            else if(buffer[i] == '\r' && buffer[i-1] == ' '){
                numOfLines++;
                break;
            }
            else if(buffer[i] == '\0'){
                break;
            }
            if(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
                if(word_flag == 0){
                    word_flag = 1;
                    numOfWords++;
                }
            } 
            else {
                word_flag = 0;
            }
        }
    }
    fclose(file);
    // printf("Number of words: %d\n", numOfWords);
    // printf("Number of lines: %d\n", numOfLines);
    if(opt == 0){
        return numOfWords+numOfLines;
    }
    else{
        return numOfWords;
    }
}

void word(int argc, char*argv[]){
    if(argc == 3){
        printf("%d\n", code_for_word(0, argv[2]));
    }

    else if(strcmp(argv[2], "-n") == 0){
        printf("%d\n", code_for_word(1, argv[3]));
    }

    else if((strcmp(argv[2],"-d") == 0) && (argc == 5)){
        printf("%d\n", code_for_word(0, argv[3]) - code_for_word(0, argv[4]));
    }

    else if((strcmp(argv[2],"-d") == 0) && (argc != 5)){
        perror("Wrong argument\n");
        return;
    }

    else{
        perror("wrong option\n");
    }
}

int main() {
    char cwd[1024];
	strcpy(cwd, getcwd(cwd, sizeof(cwd)));
    while(1){
		if(cwd != NULL){
			printf("%s $  ", cwd);

            //-----------CODE FOR INPUT
            char* argv[10];
            for(int i = 0; i<9; i++){
                argv[i] ="placeholder";
            }
            argv[9] = NULL;
            char inputSentence[100];  
            fgets(inputSentence, sizeof(inputSentence), stdin);

            char* token = strtok(inputSentence, " \n");
            int argc = 1;
            int inputs_num = 0;

            while (token != NULL) {
                argv[argc] = token;
                inputs_num++;
                argc++;
                token = strtok(NULL, " \n");
            }

            if(inputs_num > 4){
                printf("Error");
            }
            //-------CODE FOR INPUT ENDS            
            if(!strcmp(argv[1], "exit")){
                break;
            }
            if(strcmp(argv[1], "word")&&strcmp(argv[1], "dir")&&strcmp(argv[1], "date")){
                perror("Wrong command\n");
            }
            if(!strcmp(argv[1], "word")){
                word(argc, argv);
            }

            else{
                int flag_dir = 0;
                if(!strcmp(argv[1], "dir")){
                    flag_dir = 1;
                }
                int rc = fork();
                
                if (rc<0){
                    printf("fork failed\n");
                    exit(1);
                }
                else if (rc == 0){
                    if(!strcmp(argv[1], "date")){
                        execvp("./date", argv);
                    }
                    else if(!strcmp(argv[1], "dir")){
                        execvp("./dir", argv);
                    }
                }
                else{
                    wait(NULL);
                }

                if(flag_dir == 1){
                    int arg_counter = 1;
                    for(int i = 0; i<argc; i++){
                        if(strcmp(argv[i], "placeholder")){
                            arg_counter++;
                        }
                    }
                    if(arg_counter == 3){
                        strcat(cwd, "/");               
                        strcat(cwd, argv[2]);               
                    }
                    else{
                        strcat(cwd, "/");               
                        strcat(cwd, argv[3]);
                    }
                }
            }
        }

        else{
			perror("getcwd");
		}
    }
    return 0;
}