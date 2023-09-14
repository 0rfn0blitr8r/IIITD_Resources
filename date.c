#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
    int arg_counter = 1;
	for(int i = 0; i<argc; i++){
		if(strcmp(argv[i], "placeholder")){
			arg_counter++;
		}
	}
    const char *filename;
    if(arg_counter!=3 && arg_counter!=4){
        printf("Wrong argument\n");
        exit(1);
    }
    else if(arg_counter == 3){
        filename = argv[2];
    }
    else{
        filename = argv[3];
        struct stat fileStat;
    }

    struct stat fileStat;

    if(stat(filename, &fileStat) == -1){
        perror("Wrong argument\n");
        return 1;
    }

	char temp[33];
    char temp2[33];

	strcpy(temp, ctime(&fileStat.st_mtime));
    strcpy(temp2, temp);

    for(int i = 25; i<=32; i++){
        if (temp[i] == '\0'){
            temp[i] = ' ';
        }
    }
    for(int i = 24; i>19; i--){
        temp[i+7] = temp[i];
        temp[i] = ' ';
    }
    temp[23] = 'I'; temp[24] = 'S'; temp[25] = 'T'; temp[26] = ' ';

    char hour[3]; hour[0] = temp[11]; hour[1]= temp[12]; hour[3] = '\0';
    int hour_num = atoi(hour);
    if(hour_num>=12){
        temp[20] = 'P'; temp[21] = 'M';
        hour_num -= 12;
        char hour_str[3];
        sprintf(hour_str, "%02d", hour_num);
        temp[11] = hour_str[0]; temp[12] = hour_str[1];
    }

    else{
        temp[20] = 'A'; temp[21] = 'M';
        if(hour_num == 0){
            temp[11] = '1'; temp[12] = '2';
        }
    }
    temp[32] = '\0';

    if(arg_counter == 3){
        printf("%s", temp);
    }

    else if(arg_counter == 4){
        if(!strcmp(argv[2], "-R")){
            char* Token_time[6]; 
            for(int i = 0; i<6; i++){
                Token_time[i] ="placeholder";
            }

            char* token = strtok(temp2, " \n");
            int inputs_num = 0;
            while (token != NULL) {
                Token_time[inputs_num] = token;
                inputs_num++;
                token = strtok(NULL, " \n");
            }

            char holder0[5];
            strcpy(holder0, Token_time[0]);
            holder0[3] = ',';
            holder0[4] = '\0';
            Token_time[0] = holder0;

            char* holder1;
            holder1 = Token_time[1];
            Token_time[1] = Token_time[2];
            Token_time[2] = holder1;

            char* holder2;
            holder2 = Token_time[3];
            Token_time[3] = Token_time[4];
            Token_time[4] = holder2;

            Token_time[5] = "+0530";

            for(int i = 0; i<=5; i++){
                printf("%s ", Token_time[i]);
            }printf("\n");
        }

        else if(!strcmp(argv[2], "yesterday")||!strcmp(argv[2], "tomorrow")){
            char day[3];
            day[0] = temp[8]; day[1] = temp[9]; day[2] = '\0';
            int day_num = atoi(day);
            if(!strcmp(argv[2], "yesterday")){
                day_num -= 1;
            }
            else{
                day_num += 1;
            }
            sprintf(day, "%02d", day_num);
            temp[8] = day[0]; temp[9] = day[1];
            printf("%s", temp);
        }

        else{
            printf("wrong option\n");
        }
    }
    return 0;
}