#pragma once
#include "lexical_analyzer.h"


class Exist_Symbols {
public:
	Sym_type type;	//���ķ����ŵ�����
	std::set<int> First;	//�ķ����ŵ�first����
	std::set<int> Follow;	//�ķ����ŵ�follow����
	std::string word;	//�ķ����ŵ������ַ���

	Exist_Symbols(const Sym_type type_in, const std::string word_in);	//���캯��
};
//�ķ��е�ÿһ�����
class Grammar_rule {
public:
	int origin_item;	//����ʽ�����ķ�������symbol�����е��±�
	std::vector<int> derivation_item;	//����ʽ�Ҳ���ķ�������symbol�����е��±�
	Grammar_rule(const int origin_item_in,const std::vector<int>& derivation_item_in);
};

class Grammar {
public:
	std::vector<Exist_Symbols> symbols_all;	//�ķ��г��ֵ����з���
	std::set<int> terminals_all;	//�ս����symbols_all�е�index
	std::set<int> n_terminals_all;	//���ս����symbols_all�е�index
	std::vector<Grammar_rule> grammar_expressions;	//˳��洢ÿһ���ķ����ʽ�������Լʱ���±�Ѱ��
	int begin_expression;	//�ķ�����ʼ����ʽ��grammar_expressions�е�λ��
	Grammar(const std::string filepath);
	int symbol_index(const std::string token);	//ͨ��token�ҵ�����symbols_all�����е��±�
	std::set<int> getFirst(const std::vector<int>& str);	//�õ�һ�����Ŵ���first����

private:
	void file_grammar(const std::string filepath);	//���붨����ķ�
	void initialize_Firstset();	//��ʼ��first����
};