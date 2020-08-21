#pragma once

#include "template.h"
using namespace std;

typedef enum {
	CHAR_NULL,
	CHAR_EOF,
	CHAR_DIGIT,
	CHAR_LETTER,
	CHAR_SYMBOL,
	CHAR_BLANK,
}CHAR_TYPE;
typedef enum {
	TOKEN_NULL,
	TOKEN_SINGLE_NOTE,
	TOKEN_MULTI_NOTE,
	TOKEN_CHAR,
	TOKEN_STRING,
	TOKEN_VARNAME,
	TOKEN_SYMBOL,
	TOKEN_DIGIT,
	TOKEN_HEX,
	TOKEN_FLOAT,
}TOKEN_TYPE;
typedef enum {

}EXP_TYPE;
typedef enum {

}BLOCK_TYPE;
typedef struct{
	TOKEN_TYPE type;
	string token;
} Record;
class Base {

};
class WordWrap {
public:
	void Open(CPCHAR filename);
	void GetToken();
	void Classify();
public:
	vector<Record> tokens;
	vector<int> idxs;
	int total;
private:
	char* buf;
	int len;
};
extern WordWrap ww;
extern CPCHAR keywords[];
extern CPCHAR symbols;
