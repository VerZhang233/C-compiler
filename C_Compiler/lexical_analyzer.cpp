#include"lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer(std::ifstream& infile):infile(infile) {
	words.clear();

	//初始化字典树
	trie = std::make_unique<Trie>();
	//建立DFA
	// 关键字
	for (int i = 0; build_keyWord[i].kind != WordKind::Max; i++) {
		trie->Insert(build_keyWord[i].key, build_keyWord[i].kind);
	}
	//所有操作符
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
	bool in_comm = false; //用于标识当前内容是否在多行注释中
	while (!infile.eof()) {
		infile.getline(line, 1024); //每次读入1024个字符
		
		int ch_type; //读到字符的类型
		int len = strlen(line);
		int word_length = 0; //记录每一次识别到的词的长度
		WordKind Kind = WordKind::undefined; //每一次识别出来的词的类型
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
				bool is_key_word = true;
				Node* cur_node = trie->root;
				for (int j = i; j < len; j++) {
					if (CharType(line[j]) == NUMBER || LETTER) {
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
				Node* cur_node = trie->root;
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
				break; //如果是行注释则直接忽略当前行剩下的所有内容
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
				for (int j = i; j < i + word_length - 1; i++) {
					word += line[j];
				}

				words.emplace_back(Word{ Kind,word });
			}

			i += (word_length - 1);
		}//end of for	
	}
}

std::vector<Word> LexicalAnalyzer::GetWords()
{
	return words;
}