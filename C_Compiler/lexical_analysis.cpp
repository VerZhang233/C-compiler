#include<iostream>
#include"lexical_analyzer.h"

int main()
{
	std::ifstream infile;
	infile.open("test.c", std::ios::in );
	if (!infile.is_open()) {
		std::cout << "�ļ���ʧ�ܣ�" << std::endl;
	}
	LexicalAnalyzer analyzer(infile);
	analyzer.Analyse();
	

	return 0;
}