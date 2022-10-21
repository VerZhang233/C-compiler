#pragma once
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>

#define SPACE_OR_TAB 1 //�ո�"\t"
#define NUMBER 2 //����
#define LETTER 3 //��ĸ
#define OPERATOR 4 //�����
#define OTHER 5 //����

enum class WordKind;

struct Word {
	WordKind wk;//����
	std::string val;//����
};

//���ܣ�����ʷ���������ǰ֧�ֵ����е����ֱ�
enum class WordKind : int {
	undefined,
	//�ؼ���
	kw_Int,
	kw_Void,
	kw_If,
	kw_Else,
	kw_While,
	kw_Return,
	//��ʶ��
	identifier,
	//��ֵ
	num,
	//��ֵ
	op_Assign,
	//���
	op_Add, op_Sub, op_Mul, op_Div, op_Mod, // �Ӽ��˳�+ȡģ
	op_Gt, op_Lt, op_Ngt, op_Nlt, op_Eq, op_Neq, //��ϵ
	//������ֺ�
	op_Delim,
	//�ָ���������
	op_Separ,
	//ע��
	lComm, rComm, dComm,
	//������
	lPara,
	//������
	rPara,
	//�������
	lBrace,
	//�Ҵ�����
	rBrace,
	//������
	eof,
	//����
	Max
};

//��������������DFA����ʱ��Ҫ����Ϣ
const static struct {
	const std::string key; WordKind kind;
} build_keyWord[] = {
	{ "int", WordKind::kw_Int },
	{ "void", WordKind::kw_Void },
	{ "if", WordKind::kw_If },
	{ "else", WordKind::kw_Else },
	{ "while", WordKind::kw_While },
	{ "return", WordKind::kw_Return },
	{ NULL, WordKind::Max }
};

const static struct {
	WordKind kind; const std::string key;
} build_Operator[] = {
	{ WordKind::op_Add, "+"},
	{ WordKind::op_Assign, "="},
	{ WordKind::op_Separ, ","},
	{ WordKind::op_Delim, ";"},
	{ WordKind::op_Div, "/"},
	{ WordKind::op_Eq, "=="},
	{ WordKind::op_Gt, ">"},
	{ WordKind::op_Lt, "<"},
	{ WordKind::op_Mod, "%"},
	{ WordKind::op_Mul, "*"},
	{ WordKind::op_Neq, "!="},
	{ WordKind::op_Ngt, "<="},
	{ WordKind::op_Nlt, ">="},
	{ WordKind::op_Sub, "-"},
	{ WordKind::lComm, "/*"},
	{ WordKind::rComm, "*/"},
	{ WordKind::rComm, "//"},
	{ WordKind::lPara, "("},
	{ WordKind::rPara, ")"},
	{ WordKind::lBrace, "{"},
	{ WordKind::rBrace, "}"},
	{ WordKind::Max, NULL }
};

struct Node {
	int flag;//�Ƿ��ǵ��ʽ���
	Node* next[128];//��̽��
	WordKind wordKind;//��������
	Node() {//��ʼ��
		memset(next, NULL, sizeof(next));
		wordKind = WordKind::undefined;
		flag = false;
	}
};
struct Trie {
	Node* root;
	Trie() {
		root = new Node();
	}
	//����һ���ַ���������
	void Insert(const std::string& S, WordKind wk) {
		int len = int(S.length());
		Node* p = root;
		for (int i = 0; i < len; i++) {
			if (p->next[S[i]] == NULL) {
				p->next[S[i]] = new Node();
			}
			p = p->next[S[i]];
		}
		//�����ַ�
		p->flag = true;
		p->wordKind = wk;
	}
	//�����Ƿ����
	bool Search(std::string& S) {
		Node* p = root;
		for (int i = 0; i < S.length(); i++) {
			p = p->next[S[i]];
			if (p == NULL) {//������
				return false;
			}
		}
		return true;
	}
};

class LexicalAnalyzer {
protected:
	std::ifstream& infile; //�ļ���������Ϊ�ʷ�������������
	std::unique_ptr<Trie> trie; //����ָ��
	std::vector<Word> words;
public:
	LexicalAnalyzer(std::ifstream& infile);
	void Analyse();
	std::vector<Word> GetWords();
	void printWords();
};

