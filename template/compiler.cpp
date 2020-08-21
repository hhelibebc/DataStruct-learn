// compiler.cpp : 此文件包含 词法分析器 第一部分
// 单行注释
#include "compiler.h"

CPCHAR keywords[] = {
	"asm","auto","bool","break","case","cast","catch","char","class","const",
	"const_cast","continue","default","delete","do","double","dynamic_cast","else",
	"enum","explicit","export","extern","false","float","for","friend","goto",
	"if","inline","int","long","mutable","namespace","new","operator","private",
	"protected","public","register","reinterpret_cast","return","short","signed",
	"sizeof","static","struct","switch","template","this","throw","true","try",
	"typedef","typeid","typename","union","unsigned","using","virtual","void",
	"volatile","wchar_t","while",
};
CPCHAR symbols = "+-*/!#%^&*_=()[]{}<>;:',.?|/\"\\";
static CPCHAR blanks = " \n\t";
static FILE* fi;
static CPCHAR tmpToken;
WordWrap ww;

inline static bool Exist(Record& src) {
	return !Compare(tmpToken, src.token.data());
}
static CHAR_TYPE GetCharType(int ch) {
	ch = ch & 0xff;
	if (ch == 0x00)
		return CHAR_EOF;
	else if(ch > '~')
		return CHAR_NULL;
	else if (isdigit(ch))
		return CHAR_DIGIT;
	else if (isalpha(ch))
		return CHAR_LETTER;
	else if (strchr(blanks, ch))
		return CHAR_BLANK;
	else if (strchr(symbols, ch))
		return CHAR_SYMBOL;
	else
		return CHAR_NULL;
}
static void JoinIn(CPCHAR token, TOKEN_TYPE type) {
	vector<Record>::iterator iter;
	tmpToken = token;
	iter = find_if(ww.tokens.begin(), ww.tokens.end(), Exist);
	if (iter == ww.tokens.end()) {
		Record tmp;
		tmp.token = token;
		tmp.type = type;
		ww.tokens.push_back(tmp);
		ww.idxs.push_back(ww.total++);
	}
	else
		ww.idxs.push_back(iter - ww.tokens.begin());
}

void WordWrap::Open(CPCHAR filename)
{
	fopen_s(&fi,filename, "r");
	fseek(fi, 0, SEEK_END);
	len = ftell(fi);
	buf = (char*)calloc(1, len);
	fseek(fi, 0, SEEK_SET);
	fread(buf, 1, len, fi);
	fclose(fi);
}
void WordWrap::GetToken()
{
	/* 多行注释
	多行注释
	多行注释 */
	CHAR_TYPE type1;
	TOKEN_TYPE type2 = TOKEN_NULL, type3 = TOKEN_NULL;
	char* p = buf;
	char tmp[128] = { 0 };
	char len = 0;
	while (true)
	{
		type1 = GetCharType(*p);
		if (type1 == CHAR_EOF) return;
		tmp[len++] = *p++;
		switch (type2) {
		case TOKEN_SYMBOL:
			if (p[-2] == '/') {
				if (p[-1] == '/')
					type2 = TOKEN_SINGLE_NOTE;
				else if(p[-1] == '*')
					type2 = TOKEN_MULTI_NOTE;
				else
					type2 = TOKEN_NULL;
			}
			else if (p[-2] == '\"')
				type2 = TOKEN_STRING;
			else if (p[-2] == '\'')
				type2 = TOKEN_CHAR;
			else
				type2 = TOKEN_NULL;
			break;
		case TOKEN_SINGLE_NOTE:
			if (p[-2] == '\n')
				type2 = TOKEN_NULL;
			break;
		case TOKEN_MULTI_NOTE:
			if(p[-2] == '*' && p[-1] == '/')
				type2 = TOKEN_NULL;
			break;
		case TOKEN_CHAR:
			if (p[-2] == '\\')
				tmp[len++] = *p++;
			else if(p[-2] == '\'')
				type2 = TOKEN_NULL;
			break;
		case TOKEN_STRING:
			if (p[-2] == '\\')
				tmp[len++] = *p++;
			else if (p[-2] == '\"')
				type2 = TOKEN_NULL;
			break;
		case TOKEN_VARNAME:
			if(type1 != CHAR_LETTER && type1 != CHAR_DIGIT && p[-1] != '_')
				type2 = TOKEN_NULL;
			break;
		case TOKEN_DIGIT:
			if (p[-1] == 'x' || p[-1] == 'X')
				type2 = TOKEN_HEX;
			else if (p[-1] == '.')
				type2 = TOKEN_FLOAT;
			else if (type1 != CHAR_DIGIT)
				type2 = TOKEN_NULL;
			break;
		case TOKEN_HEX:
			if (!isxdigit(p[-1]))
				type2 = TOKEN_NULL;
			break;
		case TOKEN_FLOAT:
			if (type1 != CHAR_DIGIT)
				type2 = TOKEN_NULL;
			break;
		}
		if (type2 == TOKEN_NULL) {
			if (len > 1) {
				tmp[len - 1] = 0;
				JoinIn(tmp, type3);
				memset(tmp, 0, len-1);
				len = 0;
				p--;
			}
			else {
				if (type1 == CHAR_DIGIT)
					type2 = TOKEN_DIGIT;
				else if (type1 == CHAR_LETTER || p[-1] == '_')
					type2 = TOKEN_VARNAME;
				else if (type1 == CHAR_SYMBOL)
					type2 = TOKEN_SYMBOL;
				else if (type1 == CHAR_BLANK) {
					len--;
					type2 = TOKEN_NULL;
				}
			}
		}
		type3 = type2;
	}
}
void WordWrap::Classify()
{
}
