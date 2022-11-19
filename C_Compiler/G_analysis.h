#pragma once
#include"set_grammar.h"

class LR1_content {
public:
	int origin_symbol;	//文法表达式左边的表示符(index)
	std::vector<int> derive_symbol;	//文法表达式右边的表示符(index)
	int index_in_expressions;	//lr1项对应的产生式在expressions中的下标
	int dot;	//点的位置
	int next_symbol;	//展望符在symbols_all中的下标

	LR1_content(const int origin_symbol_, const std::vector<int>& derive_symbol_,
		const int index_in_expressions_,const int dot_,const int next_symbol_);
	bool operator==(const LR1_content& content);
};

//一个closure集合
class Closure_Set {
public:
	std::vector<LR1_content> closure;
	bool operator==(const Closure_Set& closure_);
};

class LR1 :public Grammar {
public:
	std::vector<Closure_Set> clusters;	//所有的cluster，DFA用
	//第一个int为当前closure在cluster中的下标，第二个为当前符号的下标，第三个为转移到的closure在cluster中的下标
	std::map<std::pair<int, int>, int> closure_goto_con;	//closure之间的转移信息表
	std::map<std::pair<int, int>, int>goto_table;	//GOTO[i,A]=j
	std::map<std::pair<int, int>, int>action_table;	//Action[i,A]=...

	LR1(const std::string filepath);
	void get_cluster();	//计算生成cluster
	Closure_Set& getClosure(Closure_Set& ori_closure);	//生成ori_closure的闭包
	Closure_Set& getGOTO_result(const Closure_Set& ori_closure, int in_symbol);//计算进行GOTO运算得到的新闭包

	void LR1_grammatical_analysis(std::vector<Word>, const std::string filepath);	//对词法分析得到的内容进行语法分析,filepath是语法分析输出路径

	void cal_LR1_Table(const std::string file_path);//计算LR1分析表

	void tree_file(std::vector<Word>, const std::string file_path);
};