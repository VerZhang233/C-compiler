#pragma once
#include<set>
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include"iomanip"
#include<map>


#define SPACE_OR_TAB 1 //�ո�"\t"
#define NUMBER 2 //����
#define LETTER 3 //��ĸ
#define OPERATOR 4 //�����
#define OTHER 5 //����

//�ķ������г��ֵ����ַ���
enum Sym_type {
	NULL_type = 0,	//�մ�
	T_type,			//�ս��
	NT_type,		//���ս��
	END_type		//��ֹ����
};

//LR1����������action
enum Action {
	Shift, // ����
	Reduce,  // ��Լ
	Accept,  // ����
	Err	// ����
};

struct ActionDetail {
	Action action;	//����
	int detail;	//��Լ����ʽ��ת��״̬
};


//�ķ������г��ֵ���Ҫ����
const std::string NullItem = "@";// Epsilon
const std::string SepItem = " | ";// ����ʽ�Ҳ��ָ���
const std::string DeriveItem = "::=";// ����ʽ���Ҳ��ָ���
const std::string BeginItem = "Program";// �ķ���ʼ����
const std::string ExtendStartItem = "S";// ��չ�ķ���ʼ����
const std::string TerminalDefineItem = "%terminals";//���е��ս��