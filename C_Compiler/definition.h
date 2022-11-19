#pragma once
#include<set>
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include"iomanip"
#include<map>


#define SPACE_OR_TAB 1 //空格、"\t"
#define NUMBER 2 //数字
#define LETTER 3 //字母
#define OPERATOR 4 //运算符
#define OTHER 5 //其他

//文法定义中出现的四种符号
enum Sym_type {
	NULL_type = 0,	//空串
	T_type,			//终结符
	NT_type,		//非终结符
	END_type		//终止符号
};

//LR1分析中四种action
enum Action {
	Shift, // 移入
	Reduce,  // 归约
	Accept,  // 接受
	Err	// 错误
};

struct ActionDetail {
	Action action;	//动作
	int detail;	//归约产生式或转移状态
};


//文法定制中出现的重要符号
const std::string NullItem = "@";// Epsilon
const std::string SepItem = " | ";// 产生式右部分隔符
const std::string DeriveItem = "::=";// 产生式左右部分隔符
const std::string BeginItem = "Program";// 文法起始符号
const std::string ExtendStartItem = "S";// 扩展文法起始符号
const std::string TerminalDefineItem = "%terminals";//所有的终结符