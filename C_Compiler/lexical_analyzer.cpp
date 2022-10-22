#include"lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::ifstream& infile):infile(infile) {
	words.clear();

	//��ʼ���ֵ���
	trie = std::make_unique<Trie>();
	// �ؼ���
	for (int i = 0; build_keyWord[i].kind != WordKind::Max; i++) {
		trie->Insert(build_keyWord[i].key, build_keyWord[i].kind);
	}
	//���в�����
	for (int i = 0; build_Operator[i].kind != WordKind::Max; i++) {
		trie->Insert(build_Operator[i].key, build_Operator[i].kind);
	}
}

int CharType(char ch) {
	if (ch == ' ' || ch == '\t')
		return SPACE_OR_TAB;
	else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return LETTER;
	else if (ch >= '0' && ch <= '9') {
		return NUMBER;
	}
	else {
		switch (ch) {
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '>':
		case '<':
		case '!':
		case ';':
		case ',':
		case '#':
		case '(':
		case ')':
		case '{':
		case '}':
			return OPERATOR;
			break;
		default:
			return OTHER;
			break;
		}
	}
}

void LexicalAnalyzer::Analyse() {
	char line[1025] = {};
	bool in_comm = false; //���ڱ�ʶ��ǰ�����Ƿ��ڶ���ע����
	while (!infile.eof()) {
		infile.getline(line, 1024); //ÿ�ζ���1024���ַ�
		
		int ch_type; //�����ַ�������
		int len = int(strlen(line));
		int word_length = 0; //��¼ÿһ��ʶ�𵽵Ĵʵĳ���
		bool is_key_word = true;
		WordKind Kind = WordKind::undefined; //ÿһ��ʶ������Ĵʵ�����
		Node* cur_node = trie->root;
		for (int i = 0; i < len; i++) {
			word_length = 0;
			Kind = WordKind::undefined;

			ch_type = CharType(line[i]);
			switch (ch_type) {
			case SPACE_OR_TAB:
				break;
			case NUMBER:
				for (int j = i; j < len; j++) {
					if (CharType(line[j]) == NUMBER) {
						word_length++;
					}
					else
						break;
				}
				Kind = WordKind::num;
				break;
			case LETTER:
				is_key_word = true;
				cur_node = trie->root;
				for (int j = i; j < len; j++) {
					if (CharType(line[j]) == NUMBER || CharType(line[j]) == LETTER) {
						word_length++;
						if (is_key_word && cur_node->next[line[j]] != NULL) {
							cur_node = cur_node->next[line[j]];
						}
						else
							is_key_word = false;
					}
					else
						break;
				}
				Kind = (cur_node->wordKind != WordKind::undefined && is_key_word) ? cur_node->wordKind : WordKind::identifier;
				break;
			case OPERATOR:
				cur_node = trie->root;
				for (int j = i; j < len; j++) {
					if (CharType(line[j]) == OPERATOR) {
						if (cur_node->next[line[j]] != NULL) {
							word_length++;
							cur_node = cur_node->next[line[j]];
						}
						else
							break;
					}
					else
						break;
				}
				Kind = cur_node->wordKind;
				break;
			case OTHER:
				break;
			}

			if (Kind == WordKind::undefined)
				continue;
			else if (Kind == WordKind::dComm)
				break; //�������ע����ֱ�Ӻ��Ե�ǰ��ʣ�µ���������
			else if (Kind == WordKind::lComm)
				in_comm = true;
			else if (Kind == WordKind::rComm)
				in_comm = false;
			else {
				if (in_comm) {
					i += (word_length - 1);
					continue;
				}

				std::string word;
				for (int j = i; j < i + word_length; j++) {
					word += line[j];
				}

				words.emplace_back(Word{ Kind, word });
			}

			i += (word_length - 1);
		}//end of for	
	}
}

std::vector<Word> LexicalAnalyzer::GetWords()
{
	return words;
}

//���������������ı�
const static struct {
	WordKind kind;  const std::string output_info;
} info[] = {
	{ WordKind::undefined,"undefined"},
	{ WordKind::kw_Int,"kw_Int"},
	{ WordKind::kw_Void,"kw_Void" },
	{ WordKind::kw_If,"kw_If" },
	{ WordKind::kw_Else,"kw_Else" },
	{ WordKind::kw_While,"kw_While" },
	{ WordKind::kw_Return,"kw_Return" },
	{ WordKind::identifier,"identifier" },
	{ WordKind::num,"num" },
	{ WordKind::op_Add, "op_Add"},
	{ WordKind::op_Assign, "op_Assign"},
	{ WordKind::op_Separ, "op_Separ"},
	{ WordKind::op_Delim, "op_Delim"},
	{ WordKind::op_Div, "op_Div"},
	{ WordKind::op_Eq, "op_Eq"},
	{ WordKind::op_Gt, "op_Gt"},
	{ WordKind::op_Lt, "op_Lt"},
	{ WordKind::op_Mod, "op_Mod"},
	{ WordKind::op_Mul, "op_Mul"},
	{ WordKind::op_Neq, "op_Neq"},
	{ WordKind::op_Ngt, "op_Ngt"},
	{ WordKind::op_Nlt, "op_Nlt"},
	{ WordKind::op_Sub, "op_Sub"},
	{ WordKind::lPara, "lPara"},
	{ WordKind::rPara, "rPara"},
	{ WordKind::lBrace, "lBrace"},
	{ WordKind::rBrace, "rBrace"},
	{ WordKind::Max, "" }
};

std::ostream& operator<<(std::ostream& os, const WordKind myEnum)
{
	std::string s;
	for (auto item : info) {
		if (item.kind == myEnum) {
			os << std::setiosflags(std::ios::left) << std::setw(12) << item.output_info;
			break;
		}
	}
	return os;
}

void LexicalAnalyzer::printWords() {
	for (auto word : words) {
		std::cout << word.wk << "  " << word.val << std::endl;
	}
}
