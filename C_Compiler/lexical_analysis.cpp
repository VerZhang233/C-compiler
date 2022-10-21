#include<iostream>
#include"lexical_analyzer.h"

int main()
{
	std::ifstream infile;
	infile.open("test.c", std::ios::in );
	if (!infile.is_open()) {
		std::cout << "文件打开失败！" << std::endl;
	}
	LexicalAnalyzer analyzer(infile);
	analyzer.Analyse();
	

	return 0;
}