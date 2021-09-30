//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <map>
//using namespace std;
//
//typedef struct {
//	char	rword;
//	int		rcode;		//��ʾ�ַ�/�ַ����ڹ�ϣ���ж�Ӧ�ı���
//	int		firstchild;	//��ʼ -1�������ں��ӣ���Ϊ��һ��һά�����ڶ�ά�����е����
//}dictionary;
//
//vector<vector<dictionary>> dict;	//��һλ������ʽ��ʾ�ֵ�,�Զ�ά������ʽ��ʾ����
//int code = 1;
//string text = "";
//vector<int> compresionresult;
//map<int, string> hashmap;
//
//
//void print() {
//	for (int i = 0; i < compresionresult.size(); ++i)
//		std::cout << compresionresult[i] << ',';
//}
//
////����ѹ�����
//void readresult() {
//	ifstream is("test.clzw", ios::binary);
//	string line;
//	if (is)
//		while (getline(is, line, ','))
//			compresionresult.push_back(stoi(line));
//	else
//		cout << "no such file!" << endl;
//	is.close();
//}
//
////�����ֵ䣬��ʼ��
//void readdict() {
//	ifstream is("dict.txt", ios::binary);
//	vector<dictionary> tempvector;
//	while (!is.eof()) {
//		dictionary tempstruct;
//		is >> tempstruct.rcode >> tempstruct.rword >> tempstruct.firstchild;
//		tempvector.push_back(tempstruct);
//	}
//	dict.push_back(tempvector);
//	is.close();
//
//	//��ʼ��
//	string current = "";
//	for (int index = 1; index < dict[0].size() - 1; ++index)
//		hashmap.insert({ dict[0][index].rcode, current + dict[0][index].rword });
//	for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++)
//		cout << iter->first << " " << iter->second << endl;
//}
//
///***************
//��ѹ
//��Ҫע��ĵ㣺
//1.	��һ�������ر�������Ҫ�������
//***************/
//void decompress() {
//	string prev = "", output = "";
//	output = hashmap[ compresionresult[0] ];
//	text = text + output;
//
//	for (int index = 1; index < compresionresult.size(); ++index) {
//		prev = output;
//		output = hashmap[ compresionresult[index] ];
//		prev =  prev + output[0];
//		while (hashmap.find(code) != hashmap.end())
//			code++;
//		hashmap.insert({ code, prev });
//		text = text + output;
//	}
//}
//
//
////д���ļ�
//void writefile() {
//	ofstream os("decompression.txt", ios::out);
//	if(os)
//		os << text;
//	else
//		cerr << "no such file!" << endl;
//}
//
////��ӡ�ֵ�
//void cprint() {
//	for (int row = 0; row < dict.size(); ++row) {
//		for (int col = 0; col < dict[row].size(); ++col)
//			cout << "(" << dict[row][col].rcode << "," << dict[row][col].rword << "," << dict[row][col].firstchild << ")" << " ";
//		cout << endl;
//	}
//}
//
//int main() {
//	readresult();
//	readdict();
//	decompress();
//	//for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++)
//	//	cout << iter->first << " " << iter->second << endl;
//	
//	writefile();
//	cout << text << endl;
//	
//
//	system("pause");
//	return 0;
//}