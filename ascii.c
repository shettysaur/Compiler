#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc,char* argv[]){
        char* f = argv[1];
        FILE* fp = fopen(f,"r");
        if(fp == NULL){
                printf("File could not be opened");
                exit(0);
        }
	while(!feof(fp)){
		printf("%d\t",fgetc(fp));
	}
}
		
		
