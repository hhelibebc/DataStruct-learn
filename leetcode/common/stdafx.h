// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

class BaseData{
public:
	BaseData():var(0),str(NULL){}
	BaseData(int v,char* s):var(v),str(s){}
	~BaseData(){}
	void Print(){
		printf("%d ",var);
	}
public:
	int var;
	char* str;
};

#define CLEAROBJ(p) memset((p),0,sizeof(*(p)))
