#pragma once
#include"set_grammar.h"

class LR1_content {
public:
	int origin_symbol;	//�ķ����ʽ��ߵı�ʾ��(index)
	std::vector<int> derive_symbol;	//�ķ����ʽ�ұߵı�ʾ��(index)
	int index_in_expressions;	//lr1���Ӧ�Ĳ���ʽ��expressions�е��±�
	int dot;	//���λ��
	int next_symbol;	//չ������symbols_all�е��±�

	LR1_content(const int origin_symbol_, const std::vector<int>& derive_symbol_,
		const int index_in_expressions_,const int dot_,const int next_symbol_);
	bool operator==(const LR1_content& content);
};

//һ��closure����
class Closure_Set {
public:
	std::vector<LR1_content> closure;
	bool operator==(const Closure_Set& closure_);
};

class LR1 :public Grammar {
public:
	std::vector<Closure_Set> clusters;	//���е�cluster��DFA��
	//��һ��intΪ��ǰclosure��cluster�е��±꣬�ڶ���Ϊ��ǰ���ŵ��±꣬������Ϊת�Ƶ���closure��cluster�е��±�
	std::map<std::pair<int, int>, int> closure_goto_con;	//closure֮���ת����Ϣ��
	std::map<std::pair<int, int>, int>goto_table;	//GOTO[i,A]=j
	std::map<std::pair<int, int>, int>action_table;	//Action[i,A]=...

	LR1(const std::string filepath);
	void get_cluster();	//��������cluster
	Closure_Set& getClosure(Closure_Set& ori_closure);	//����ori_closure�ıհ�
	Closure_Set& getGOTO_result(const Closure_Set& ori_closure, int in_symbol);//�������GOTO����õ����±հ�

	void LR1_grammatical_analysis(std::vector<Word>, const std::string filepath);	//�Դʷ������õ������ݽ����﷨����,filepath���﷨�������·��

	void cal_LR1_Table(const std::string file_path);//����LR1������

	void tree_file(std::vector<Word>, const std::string file_path);
};