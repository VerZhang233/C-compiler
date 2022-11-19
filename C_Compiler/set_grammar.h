#pragma once
#include "lexical_analyzer.h"


class Exist_Symbols {
public:
	Sym_type type;	//该文法符号的种类
	std::set<int> First;	//文法符号的first集合
	std::set<int> Follow;	//文法符号的follow集合
	std::string word;	//文法符号的内容字符串

	Exist_Symbols(const Sym_type type_in, const std::string word_in);	//构造函数
};
//文法中的每一句规则
class Grammar_rule {
public:
	int origin_item;	//产生式左侧的文法符号在symbol数组中的下标
	std::vector<int> derivation_item;	//产生式右侧的文法符号在symbol数组中的下标
	Grammar_rule(const int origin_item_in,const std::vector<int>& derivation_item_in);
};

class Grammar {
public:
	std::vector<Exist_Symbols> symbols_all;	//文法中出现的所有符号
	std::set<int> terminals_all;	//终结符在symbols_all中的index
	std::set<int> n_terminals_all;	//非终结符在symbols_all中的index
	std::vector<Grammar_rule> grammar_expressions;	//顺序存储每一句文法表达式，方便规约时用下标寻找
	int begin_expression;	//文法的起始产生式在grammar_expressions中的位置
	Grammar(const std::string filepath);
	int symbol_index(const std::string token);	//通过token找到其在symbols_all数组中的下标
	std::set<int> getFirst(const std::vector<int>& str);	//得到一个符号串的first集合

private:
	void file_grammar(const std::string filepath);	//读入定义的文法
	void initialize_Firstset();	//初始化first集合
};