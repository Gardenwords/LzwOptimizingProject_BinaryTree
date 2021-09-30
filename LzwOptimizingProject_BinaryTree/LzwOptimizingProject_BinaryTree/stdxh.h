#pragma once
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;


//字典结构
typedef struct {
	char	rWord;
	int		rCode;		//表示字符/字符串在哈希表中对应的编码
	int		firstChild;	//初始 -1，若存在孩子，则为下一个一维数组在二维数组中的序号
}Dictionary;

class EnCode {
private:
	vector<vector<Dictionary>> Dict;	//以一位数组形式表示兄弟,以二维数组形式表示孩子
	int	code;
	string Text;
	string	result;
	map<string, int> hashmap;

public:
	EnCode();
	void textLoad();
	void dictSave();
	void compressResult();
	void lastStep(string current);
	void textCompress(string& current, int row, int prerow, int precol, int eLoc);
	void cPrint();
};

class DeCode {
private:
	vector<vector<Dictionary>> Dict;	//以一位数组形式表示兄弟,以二维数组形式表示孩子
	int code;
	string Text;
	vector<int> compresionresult;
	map<int, string> hashmap;

public:
	DeCode();
	void readResult();
	void readDict();
	void deCompress();
	void writeFile();
	void reText();
	void length();
};