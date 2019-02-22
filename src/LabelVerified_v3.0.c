/*
 ============================================================================
 Name        : LabelVerified.c
 Author      : Kris
 Version     : 3.0
 Description : The data is composed by Begin time, End time and Label.
               To examine the data, it is necessary to modify your data path in this code.
 ============================================================================
 */

#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

int main(void){

	int BeginTime[10000] = {0};
	int EndTime[10000] = {0};
	char Label[10];
	int i, j; //For-Loop
    int c = 0; //Begin Array
    int d = 0; //End Array
    int count = 0; //File count
    int errorBegin = 0; //Begin error count
    int errorEnd = 0; //End error count
    DIR *dir;
    FILE *file;
    struct dirent *entry_file;
    char inputPath[300];
    char tempPath[300];
    char tempsymbol[] = "\\";
    FILE *file2;
    FILE *file3;

    printf("Please enter the file path: ");
    scanf("%s", inputPath);
    strcat(inputPath, tempsymbol);
    if((dir = opendir(inputPath)) == NULL){ //*Must change the path
    	perror("opendir() error");
    	system("pause");
    	exit(0);
    }
    while((entry_file = readdir(dir)) != NULL){
    	//char globalPath[] = "C:\\Users\\P18353\\Desktop\\mono2\\"; //*Must change the path
	    c = 0; //Initial Begin Array
	    d = 0; //Initial End Array
	    if((!strcmp(entry_file->d_name, ".")) || (!strcmp(entry_file->d_name, ".."))){
	    	continue;
	    }
	    strncpy(tempPath, inputPath, 300);
	    char *datapath = strcat(tempPath, entry_file->d_name);
	    //printf("data path = %s\n", datapath);
	    file = fopen(datapath, "r");
	    if(file == NULL){
	    	    	printf("Missing the \\ in the last character. Error!\n");
	    	    	system("pause");
	    	    	exit(0);
	    	    }
	    while(fscanf(file, "%d %d %s", &BeginTime[c], &EndTime[d], Label) == 3){
	    	c++;
	    	d++;
	    }
	    remove("BeginError.txt");
	    for(i=0; i< (c-1); i++){
	    	file2 = fopen("BeginError.txt", "a+");
	    	if(BeginTime[i] >= BeginTime[i+1]){

	    		printf("********************\n");
                printf("%s\n", entry_file->d_name);
                printf("Begin\n");
                printf("No.%d is >= No.%d Error!\n", (i+1), (i+2));
                printf("No.%d = %d, No.%d = %d\n", i+1, BeginTime[i], i+2, BeginTime[i+1]);
                printf("\n");

	    		fprintf(file2, "********************\n");
                fprintf(file2, "%s\n", entry_file->d_name);
                fprintf(file2, "Begin\n");
                fprintf(file2, "No.%d is >= No.%d Error!\n", (i+1), (i+2));
                fprintf(file2, "No.%d = %d, No.%d = %d\n", i+1, BeginTime[i], i+2, BeginTime[i+1]);
                fprintf(file2, "\n");

                errorBegin++;
                break;
	    	}
	    	if(BeginTime[i] < 0){
	    		printf("********************\n");
                printf("%s\n", entry_file->d_name);
                printf("Begin\n");
                printf("No.%d is < 0 Error!\n", (i+1));
                printf("No.%d = %d\n", i+1, BeginTime[i]);
                printf("\n");

	    		fprintf(file2, "********************\n");
                fprintf(file2, "%s\n", entry_file->d_name);
                fprintf(file2, "Begin\n");
                fprintf(file2, "No.%d is < 0 Error!\n", (i+1));
                fprintf(file2, "No.%d = %d\n", i+1, BeginTime[i]);
                fprintf(file2, "\n");

                errorBegin++;
                break;
	    	}
	    	fclose(file2);
	    }
	    memset(BeginTime, 0, sizeof(BeginTime));

	    remove("EndError.txt");
	    for(j=0; j< (d-1); j++){
	    	file3 = fopen("EndError.txt", "a+");
	    	if(EndTime[j] >= EndTime[j+1]){
	    		printf("********************\n");
                printf("%s\n", entry_file->d_name);
                printf("End\n");
                printf("No.%d is >= No.%d Error!\n", (j+1), (j+2));
                printf("No.%d = %d, No.%d = %d\n", j+1, EndTime[j], j+2, EndTime[j+1]);
                printf("\n");

	    		fprintf(file3, "********************\n");
                fprintf(file3, "%s\n", entry_file->d_name);
                fprintf(file3, "End\n");
                fprintf(file3, "No.%d is >= No.%d Error!\n", (j+1), (j+2));
                fprintf(file3, "No.%d = %d, No.%d = %d\n", j+1, EndTime[j], j+2, EndTime[j+1]);
                fprintf(file3, "\n");
                errorEnd++;
                break;
	    	}
	    	if(EndTime[j] < 0){
	    		printf("********************\n");
                printf("%s\n", entry_file->d_name);
                printf("End\n");
                printf("No. %d is < 0 \n", (j+1));
                printf("No.%d = %d\n", j+1, EndTime[j]);
                printf("\n");

	    		fprintf(file3, "********************\n");
                fprintf(file3, "%s\n", entry_file->d_name);
                fprintf(file3, "End\n");
                fprintf(file3, "No. %d is < 0 \n", (j+1));
                fprintf(file3, "No.%d = %d\n", j+1, EndTime[j]);
                fprintf(file3, "\n");
                errorEnd++;
                break;
	    	}
	    	fclose(file3);
	    }
	    memset(EndTime, 0, sizeof(EndTime));
	    fclose(file);
	    count++;
    }
    closedir(dir);
    printf("Data path: %s\n", inputPath);
    printf("Total File = %d\n", count);

	file2 = fopen("BeginError.txt", "a+");
    printf("Begin岿粇计 : %d\n", errorBegin);
    fprintf(file2, "Data path: %s\n", inputPath);
    fprintf(file2, "Begin岿粇计 : %d\n", errorBegin);
	fclose(file2);

	file3 = fopen("EndError.txt", "a+");
    printf("End岿粇计 : %d\n", errorEnd);
    fprintf(file3, "Data path: %s\n", inputPath);
    fprintf(file3, "End岿粇计 : %d\n", errorEnd);
	fclose(file3);

    if((errorBegin == 0) && (errorEnd == 0)){
    	printf("****************\n");
    	printf("\n");
    	printf("Successful! No error!\n");
    	printf("\n");
    	printf("****************\n");
    }
    printf("Please enter any key to exit!\n");
    system("pause");
    return 0;
}
