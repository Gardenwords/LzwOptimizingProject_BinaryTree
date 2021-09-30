#pragma once
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;


//�ֵ�ṹ
typedef struct {
	char	rWord;
	int		rCode;		//��ʾ�ַ�/�ַ����ڹ�ϣ���ж�Ӧ�ı���
	int		firstChild;	//��ʼ -1�������ں��ӣ���Ϊ��һ��һά�����ڶ�ά�����е����
}Dictionary;

class EnCode {
private:
	vector<vector<Dictionary>> Dict;	//��һλ������ʽ��ʾ�ֵ�,�Զ�ά������ʽ��ʾ����
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
	vector<vector<Dictionary>> Dict;	//��һλ������ʽ��ʾ�ֵ�,�Զ�ά������ʽ��ʾ����
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