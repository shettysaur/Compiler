// 2014B3A70718P
// Saurabh Shankar Shetty

#include <stdio.h>

#define LEX_SIZE 20

typedef enum{ASSIGNOP,COMMENT,FUNID,ID,NUM,RNUM,STR,END,INT,REAL,STRING,MATRIX,MAIN,SQO,SQC,OP,CL,SEMICOLON,COMMA,IF,ELSE,ENDIF,READ,PRINT,FUNCTION,PLUS,MINUS,MUL,DIV,SIZE,AND,OR,NOT,LT,LE,EQ,GT,GE,NE,ENDOFFILE}Token;

typedef union{
	char name[LEX_SIZE];
	int num;
	double rnum;
}lexVal;

typedef struct{
	Token type;
	lexVal lex;
	int val_type;
	int line_no;
}tokenInfo;
