#include <fstream>
# include <iostream>
# include <map>
# include <vector>
# include <string>
# include <queue>

using namespace std;
class BorNode;
typedef map<const char, BorNode*> LinksMap;


class BorNode {
public:
	LinksMap links;
	BorNode* fail;  // Предыдущее состояние для функции отката. Только для root равно NULL.
	BorNode* term; // Ближайшее терминальное состояние. Если отстутствует - NULL
	int out;


public:
	BorNode(BorNode* fail_node = NULL)
		: fail(fail_node)
		, term(NULL)
		, out(-1)
	{ }

	BorNode* getLink(const char c) const
	{
		LinksMap::const_iterator iter = links.find(c);
		if (iter != links.cend())
			return iter->second;
		else
			return NULL;

	}

	bool isTerminal() const
	{
		return (out >= 0);
	}
};


class AhoCorasick
{
public:
	typedef void(*Callback) (const char* substr, vector<string>* rez);
	BorNode root;
	vector<string> words;
	BorNode* current_state;


public:

	void addString(const char* const str)
	{
		BorNode* current_node = &root;
		for (const char* cp = str; *cp; ++cp) {
			BorNode* child_node = current_node->getLink(*cp);
			if (!child_node) {
				child_node = new BorNode(&root);
				current_node->links[*cp] = child_node;
			}
			current_node = child_node;
		}
		current_node->out = words.size();
		words.push_back(str);
	}

	void init()
	{

		queue<BorNode*> q;
		q.push(&root);
		while (!q.empty()) {
			BorNode* current_node = q.front();
			q.pop();
			for (LinksMap::const_iterator iter = current_node->links.cbegin();
				iter != current_node->links.cend(); ++iter)
			{
				const char symbol = iter->first;
				BorNode* child = iter->second;


				BorNode* temp_node = current_node->fail;
				while (temp_node) {
					BorNode* fail_candidate = temp_node->getLink(symbol);
					if (fail_candidate) {
						child->fail = fail_candidate;
						break;
					}
					temp_node = temp_node->fail;
				}


				if (child->fail->isTerminal()) {
					child->term = child->fail;
				}
				else {
					child->term = child->fail->term;
				}
				q.push(child);
			}
		}
	}

	void step(const char c)
	{
		while (current_state) {
			BorNode* candidate = current_state->getLink(c);
			if (candidate) {
				current_state = candidate;
				return;
			}
			current_state = current_state->fail;
		}
		current_state = &root;
	}

	void printTermsForCurrentState(Callback callback, vector<string>* rez) const
	{
		if (current_state->isTerminal()) {
			callback(words[current_state->out].c_str(), rez);
		}
		BorNode* temp_node = current_state->term;
		while (temp_node) {
			callback(words[temp_node->out].c_str(), rez);
			temp_node = temp_node->term;
		}
	}

	void search(const char* str, Callback callback, vector<string>* rez)
	{
		current_state = &root;
		for (; *str; ++str) {
			//cout << *str << ':' << endl;
			step(*str);
			printTermsForCurrentState(callback, rez);
		}
	}
};


void ResultSearch(const char* str, vector<string>* rez)
{
	string str_bag = str;
	//string str1 = "ab";
	//str_bag = str_bag + str1;
	rez->push_back(str_bag);
}

void WriteInFile()
{
	ofstream wr("C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR4\\LR4\\str.txt");
	wr << "test rok roka strok ";
	wr.close();
}

int ReadFile(AhoCorasick& ak, string FileName)
{
	string line;
	//C:\\Users\\user\\Desktop\\Учеба\\3 курс\\Управление качеством ПО\\ЛР2\\LR2\\LR2\\str.txt
	ifstream in(FileName.c_str());
	if (in.is_open())
	{
		if (in.peek() == EOF) { return 2; }
		while (getline(in, line, ' '))
		{
			cout << line << endl;
			ak.addString(line.c_str());
		}
	}
	else
	{
		cout << "Erorr open file" << endl;
		return 3;
	}
	in.close();
	return 1;
}

int TestAho(string str, vector<string>& REZULT, string fileName)
{
	//int chek1 = 12;

	AhoCorasick ak;
	if (!REZULT.empty()) 
		return 4; //4;
	int check = ReadFile(ak, fileName);
	if (check == 1)
	{
		ak.init();
		ak.search(str.c_str(), ResultSearch, &REZULT);
	}
	return check;
}

int main()
{


	return 0;
}
