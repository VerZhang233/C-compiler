#pragma once
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>

#define SPACE_OR_TAB 1 //空格、"\t"
#define NUMBER 2 //数字
#define LETTER 3 //字母
#define OPERATOR 4 //运算符
#define OTHER 5 //其他

enum class WordKind;

struct Word {
	WordKind wk;//种类
	std::string val;//内容
};

//功能：定义词法分析器当前支持的所有单词种别
enum class WordKind : int {
	undefined,
	//关键字
	kw_Int,
	kw_Void,
	kw_If,
	kw_Else,
	kw_While,
	kw_Return,
	//标识符
	identifier,
	//数值
	num,
	//赋值
	op_Assign,
	//算符
	op_Add, op_Sub, op_Mul, op_Div, op_Mod, // 加减乘除+取模
	op_Gt, op_Lt, op_Ngt, op_Nlt, op_Eq, op_Neq, //关系
	//界符：分号
	op_Delim,
	//分隔符：逗号
	op_Separ,
	//注释
	lComm, rComm, dComm,
	//左括号
	lPara,
	//右括号
	rPara,
	//左大括号
	lBrace,
	//右大括号
	rBrace,
	//结束符
	eof,
	//特殊
	Max
};

//以下两个表，储存DFA建立时需要的信息
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
	int flag;//是否是单词结束
	Node* next[128];//后继结点
	WordKind wordKind;//单词种类
	Node() {//初始化
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
	//插入一个字符串到树中
	void Insert(const std::string& S, WordKind wk) {
		int len = int(S.length());
		Node* p = root;
		for (int i = 0; i < len; i++) {
			if (p->next[S[i]] == NULL) {
				p->next[S[i]] = new Node();
			}
			p = p->next[S[i]];
		}
		//结束字符
		p->flag = true;
		p->wordKind = wk;
	}
	//查找是否存在
	bool Search(std::string& S) {
		Node* p = root;
		for (int i = 0; i < S.length(); i++) {
			p = p->next[S[i]];
			if (p == NULL) {//不存在
				return false;
			}
		}
		return true;
	}
};

class LexicalAnalyzer {
protected:
	std::ifstream& infile; //文件输入流作为词法分析器的输入
	std::unique_ptr<Trie> trie; //智能指针
	std::vector<Word> words;
public:
	LexicalAnalyzer(std::ifstream& infile);
	void Analyse();
	std::vector<Word> GetWords();
	void printWords();
};

