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

int getKeyword(char str[20]){
	if(!strcmp(str,"string"))
		return STRING;
	else if(!strcmp(str,"end"))
		return END;
	else if(!strcmp(str,"int"))
		return INT;
	else if(!strcmp(str,"real"))
		return REAL;
	else if(!strcmp(str,"matrix"))
		return MATRIX;
	else if(!strcmp(str,"if"))
		return IF;
	else if(!strcmp(str,"else"))
		return ELSE;
	else if(!strcmp(str,"endif"))
		return ENDIF;
	else if(!strcmp(str,"read"))
		return READ;
	else if(!strcmp(str,"print"))
		return PRINT;
	else if(!strcmp(str,"function"))
		return FUNCTION;
	else 
		return 0;
}

tokenInfo getNextToken(FILE* fp){
	while(1){
		tokenInfo token;
//		printf("lexBegin value = %d\n",*(lexBegin));
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
//		printf("lexBegin value = %d\n",*(lexBegin));
		if(*(lexBegin) == 13){
			lexBegin = ++forward;
			if(*(lexBegin) == '\n')	{
//				printf("New linefound \n");
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
		else if(*lexBegin == ' ' || *lexBegin == '\t'){
			lexBegin = ++forward;
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
		else if(*lexBegin == 0){
//			printf("ENDOFFILE\n");
			token.type = ENDOFFILE;
			token.val_type = 4;
			token.line_no = line_no;
			lexBegin = ++forward;
			return token; 		
		}
		else if(*lexBegin == '.'){
			if(*(forward +1) == 'a' && *(forward +2) == 'n' && *(forward +3) == 'd' && *(forward +4) == '.'){
				token.type = AND;
				token.val_type = 4;
				token.line_no = line_no;
				forward = forward + 5;
				lexBegin = forward;
				return token; 			
			}
			else if(*(forward +1) == 'o' && *(forward +2) == 'r' && *(forward +3) == '.'){
				token.type = OR;
				token.val_type = 4;
				token.line_no = line_no;
				forward = forward + 4;
				lexBegin = forward;
				return token; 			
			}
			else if(*(forward +1) == 'n' && *(forward +2) == 'o' && *(forward +3) == 't' && *(forward +4) == '.'){
				token.type = NOT;
				token.val_type = 4;
				token.line_no = line_no;
				forward = forward + 5;
				lexBegin = forward;
				return token; 			
			}
			else{
				printf("Error in line no %d",line_no);
				return;
			}
			
		}
		else if(*lexBegin == '='){
			if(*(++forward) == '='){
				token.type = EQ;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = ++forward;
				return token; 			
			}
			else if(*forward == '/'){
				if(*(++forward) == '='){
					token.type = NE;
					token.val_type = 4;
					token.line_no = line_no;
					lexBegin = ++forward;
					return token; 			
				}	
			}
			else{
				token.type = ASSIGNOP;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = forward;
				return token; 			
				
			}			
		}
		else if(*lexBegin == '<'){
			if(*(++forward) == '='){
				token.type = LE;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = ++forward;
				return token; 			
			}
			else{
				token.type = LT;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = forward;
				return token; 			
				
			}			
		}
		else if(*lexBegin == '>'){
			if(*(++forward) == '='){
				token.type = GE;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = ++forward;
				return token; 			
			}
			else{
				token.type = GT;
				token.val_type = 4;
				token.line_no = line_no;
				lexBegin = forward;
				return token; 			
				
			}			
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
		else if(isdigit(*(lexBegin))){
			int num = 0;
			double rnum = 0;
			num = *forward - '0';
			rnum = *forward - '0';
			while(isdigit(*++forward)){
				num = num*10 + (*forward-'0');
				rnum = rnum*10 + (*forward-'0');
			}
			if(*forward == '.'){
				if(isdigit(*(forward+1)) && isdigit(*(forward+2))){
					rnum = (rnum*100+(*(forward+1)-'0')*10 + (*(forward+2)-'0'))/100;
					token.type = RNUM;
					token.val_type = 2;
					token.lex.rnum = rnum;
					token.line_no = line_no;
					forward = forward+3;
					lexBegin = forward;
					return token; 			
					
				}
				else{
					token.type = NUM;
					token.val_type = 1;
					token.lex.num = num;
					token.line_no = line_no;
					lexBegin = forward;
					return token; 			
					
				}
			}
			else{
					token.type = NUM;
					token.val_type = 1;
					token.lex.num = num;
					token.line_no = line_no;
					lexBegin = forward;
					return token; 			
				
			}
		}
		else if(*lexBegin == '_'){
			forward++;
			char temp[20] = "";
			int p = 0;
			if(isalpha(*forward)){
				temp[p++] = *forward++;
				while(1){
					while(isalpha(*forward) || isdigit(*forward)){
						temp[p++] = *forward++;
					}
					temp[p++] = '\0';
					if(!strcmp(temp,"main")){
						token.type = MAIN;
						token.val_type = 4;
						lexBegin = forward;
						return token;
					}
					else{ 
						token.type = FUNID;
						token.val_type = 3;
						strcpy(token.lex.name,temp);
						lexBegin = forward;
						return token;
					}
				}
			}
			else{
				printf("Function name must start with alphabet");
				return;
			}
		}
		else if(*lexBegin == '"'){
			forward++;
			char temp[20] = "";
			int p = 0;
			while(isalpha(*forward) || *forward == ' '){
				temp[p++] = *forward++;	
			}
			if(*forward == '"'){
				temp[p++] = '\0';
				token.type = STR;
				token.val_type = 3;
				strcpy(token.lex.name,temp);
				lexBegin = ++forward;
				return token;
			}
			else{
				printf("Error at line %d",line_no);
				return;
			}
		}
		else if(isalpha(*lexBegin)){
			char temp[20] = "";
			int p = 0;
			temp[p++] = *lexBegin;
			while(1){
				while(++forward != lex_buffer1+BUFFER_SIZE && (isalpha(*forward) || isdigit(*forward)) || p>19){
					if(isdigit(*forward)){
						if(isalpha(*(forward+1)) || isdigit(*(forward+1))){
							printf("Lexical error at line %d",line_no);
							return;
						}
						else{
							temp[p++] = *forward;
							temp[p++] = '\0'; 
							token.type = ID;
							token.val_type = 3;
							strcpy(token.lex.name,temp);
							lexBegin = ++forward;
							return token;
						}
					}
					else if(isalpha(*forward)){
						if(!isalpha(*(forward+1)) && !isdigit(*(forward+1))){
//							Check hashtable for keywords
							temp[p++] = *forward;
							temp[p++] = '\0'; 
							int key = getKeyword(temp);
							if(key > 0){
								token.type = key;
								token.val_type = 4;
								lexBegin = ++forward;
								return token;
							}	
							else{
								token.type = ID;
								token.val_type = 3;
								strcpy(token.lex.name,temp);
								lexBegin = ++forward;
								return token;
							}
						}else{
							temp[p++] = *forward;
						}
					}
				}
				if(p>19){
					printf("ID size exceeded");
					return;
				}
				temp[p++] = '\0';
				token.type = ID;
				token.val_type = 3;
				strcpy(token.lex.name,temp);
				lexBegin = forward;
				return token;
			}
			
		}
//		printf("LexBegin value = %d\n",*lexBegin);
	}	
}
void removeComments(char *testcaseFile,char* cleanFile){
	printf("Remove Comments\n");
	FILE* fpr = fopen(testcaseFile,"r");
	printf("Readfile opened\n");
	FILE* fpw = fopen(cleanFile,"w");
	printf("Write file opened\n");
	char c = fgetc(fpr);
	while(c != EOF){
		if(c != '#')
			fputc(c,fpw);
		else{
			while(c != '\n')
				c = fgetc(fpr);
		}
		c = fgetc(fpr);
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
	int n = 125;
	/*
	while((lexBegin) != lex_buffer1+5){
	printf("%c line_no = %d\n",line_no,*(lexBegin++));
	}
	*/
	tokenInfo test;
//	printf("%c line_no = %d\n",line_no,*(lexBegin++));
	while(*lexBegin != '\0'){
		test = getNextToken(fp);
		switch(test.type){
			case COMMENT : printf("COMMENT line_no = %d\n",line_no-1);
				       break;
			case ASSIGNOP : printf("ASSIGNOP line_no = %d\n",line_no);
				       break;
			case FUNID : printf("FUNID line_no = %d,value = %s\n",line_no,test.lex.name);
				       break;
			case ID : printf("ID line_no = %d , value = %s\n",line_no,test.lex.name);
				       break;
			case NUM : printf("NUM line_no = %d,value = %d\n",line_no,test.lex.num);
				       break;
			case RNUM : printf("RNUM line_no = %d,value = %f\n",line_no,test.lex.rnum);
				       break;
			case STR : printf("STR line_no = %d,value = %s\n",line_no,test.lex.name);
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
			case ENDOFFILE :  //printf("End of file");
					  break;
			default : printf("Error");
				       break;
		}
	}
//	removeComments("testcase5.txt","test1");
}


