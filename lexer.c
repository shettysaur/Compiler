// 2014B3A70718P
// Saurabh Shankar Shetty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexerDef.h"
#include "lexer.h"

#define BUFFER_SIZE 4096

char lex_buffer1[BUFFER_SIZE];
char lex_buffer2[BUFFER_SIZE];
char* lexBegin = lex_buffer1;
char* forward;
int line_no = 1;

FILE* getStream(FILE *fp,int x){
	if(x == 0){
		if(feof(fp))
			return NULL;
		else if(fread(lex_buffer1,sizeof(char),BUFFER_SIZE,fp) > 0){
			forward = lex_buffer1;
			return fp;
		}
		else{
			printf("Error in reading file");
			return NULL;
		}
	}
	else if(x == 1){
		if(feof(fp))
			return NULL;
		else if(fread(lex_buffer2,sizeof(char),BUFFER_SIZE,fp) > 0){
			forward = lex_buffer2;
			return fp;
		}
		else{
			printf("Error in reading file");
			return NULL;
		}
	}
}

tokenInfo getNextToken(FILE* fp){
	if(1){
		tokenInfo token;
//		printf("lexBegin value = %c\n",*(lexBegin));
		if(forward == lex_buffer1+BUFFER_SIZE){
			printf("First buffer full\n");
			if(lexBegin == forward){
				fp = getStream(fp,1);
				lexBegin = forward;
			}
			else
				fp = getStream(fp,1);
			
		}	
		if(forward == lex_buffer2+BUFFER_SIZE){
			printf("Second buffer full\n");
			if(lexBegin == forward){
				fp = getStream(fp,0);
				lexBegin = forward;
			}
			else
				fp = getStream(fp,0);
		}
		printf("lexBegin value = %d\n",*(lexBegin));
		if(*(lexBegin) == 13){
			lexBegin = ++forward;
			if(*(lexBegin) == '\n')	{
				printf("New linefound \n");
				line_no++;
				lexBegin = ++forward;
			}
		}
		if(*lexBegin == '['){
			token.type = SQO;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == ']'){
			token.type = SQC;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '('){
			token.type = OP;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == ')'){
			token.type = CL;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == ';'){
			token.type = SEMICOLON;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == ','){
			token.type = COMMA;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '+'){
			token.type = PLUS;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '-'){
			token.type = MINUS;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '*'){
			token.type = MUL;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '/'){
			token.type = DIV;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '@'){
			token.type = SIZE;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '#'){
			token.type = COMMENT;
			token.val_type = 4;
			token.line_no = line_no;
			while(*forward != '\n')
				forward++;
			line_no++;
			lexBegin = ++forward;
			return token; 		
		}
		else if(isalpha(*lexBegin)){
			char temp[20] = "";
			int p = 0;
			temp[p++] = *lexBegin;
			while(1){
				while(++forward != lex_buffer1+BUFFER_SIZE && (isalpha(*forward) || isdigit(*forward))){
					if(isdigit(*forward)){
						temp[p++] = *forward;
						temp[p++] = '\0'; 
						token.type = ID;
						token.val_type = 3;
						strcpy(token.lex.name,temp);
						lexBegin = ++forward;
						return token;
					}
				}
			}
		}
		
	}	
}


main(int argc,char* argv[]){
	char* f = argv[1];
	FILE* fp = fopen(f,"r");
	if(fp == NULL){
		printf("File could not be opened");
		exit(0);
	}
	fp = getStream(fp,0);
	int n = 4;
	/*
	while((lexBegin) != lex_buffer1+5){
	printf("%c line_no = %d\n",line_no,*(lexBegin++));
	}
	*/
	tokenInfo test;
//	printf("%c line_no = %d\n",line_no,*(lexBegin++));
	while(n--){
		test = getNextToken(fp);
		switch(test.type){
			case COMMENT : printf("COMMENT line_no = %d\n",line_no-1);
				       break;
			case ASSIGNOP : printf("ASSIGNOP line_no = %d\n",line_no);
				       break;
			case FUNID : printf("FUNID line_no = %d\n",line_no);
				       break;
			case ID : printf("ID line_no = %d , value = %s\n",line_no,test.lex.name);
				       break;
			case NUM : printf("NUM line_no = %d\n",line_no);
				       break;
			case RNUM : printf("RNUM line_no = %d\n",line_no);
				       break;
			case STR : printf("STR line_no = %d\n",line_no);
				       break;
			case END : printf("END line_no = %d\n",line_no);
				       break;
			case INT : printf("INT line_no = %d\n",line_no);
				       break;
			case REAL : printf("REAL line_no = %d\n",line_no);
				       break;
			case STRING : printf("STRING line_no = %d\n",line_no);
				       break;
			case MATRIX : printf("MATRIX line_no = %d\n",line_no);
				       break;
			case MAIN : printf("MAIN line_no = %d\n",line_no);
				       break;
			case SQO : printf("SQO line_no = %d\n",line_no);
				       break;
			case SQC : printf("SQC line_no = %d\n",line_no);
				       break;
			case OP : printf("OP line_no = %d\n",line_no);
				       break;
			case CL : printf("CL line_no = %d\n",line_no);
				       break;
			case SEMICOLON : printf("SEMICOLON line_no = %d\n",line_no);
				       break;
			case COMMA : printf("COMMA line_no = %d\n",line_no);
				       break;
			case IF : printf("IF line_no = %d\n",line_no);
				       break;
			case ELSE : printf("ELSE line_no = %d\n",line_no);
				       break;
			case ENDIF : printf("ENDIF line_no = %d\n",line_no);
				       break;
			case READ : printf("READ line_no = %d\n",line_no);
				       break;
			case PRINT : printf("PRINT line_no = %d\n",line_no);
				       break;
			case FUNCTION : printf("FUNCTION line_no = %d\n",line_no);
				       break;
			case PLUS : printf("PLUS line_no = %d\n",line_no);
				       break;
			case MINUS : printf("MINUS line_no = %d\n",line_no);
				       break;
			case MUL : printf("MUL line_no = %d\n",line_no);
				       break;
			case DIV : printf("DIV line_no = %d\n",line_no);
				       break;
			case SIZE : printf("SIZE line_no = %d\n",line_no);
				       break;
			case AND : printf("AND line_no = %d\n",line_no);
				       break;
			case OR : printf("OR line_no = %d\n",line_no);
				       break;
			case NOT : printf("NOT line_no = %d\n",line_no);
				       break;
			case LT : printf("LT line_no = %d\n",line_no);
				       break;
			case LE : printf("LE line_no = %d\n",line_no);
				       break;
			case EQ : printf("EQ line_no = %d\n",line_no);
				       break;
			case GT : printf("GT line_no = %d\n",line_no);
				       break;
			case GE : printf("GE line_no = %d\n",line_no);
				       break;
			case NE : printf("NE line_no = %d\n",line_no);
				       break;
			default : printf("Error");
				       break;
		}
	}
}


