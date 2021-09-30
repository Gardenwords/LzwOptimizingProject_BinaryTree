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
//	int		rcode;		//表示字符/字符串在哈希表中对应的编码
//	int		firstchild;	//初始 -1，若存在孩子，则为下一个一维数组在二维数组中的序号
//}dictionary;
//
//vector<vector<dictionary>> dict;	//以一位数组形式表示兄弟,以二维数组形式表示孩子
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
////读入压缩结果
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
////读入字典，初始化
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
//	//初始化
//	string current = "";
//	for (int index = 1; index < dict[0].size() - 1; ++index)
//		hashmap.insert({ dict[0][index].rcode, current + dict[0][index].rword });
//	for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++)
//		cout << iter->first << " " << iter->second << endl;
//}
//
///***************
//解压
//需要注意的点：
//1.	第一个进行特别处理，不需要进行组词
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
////写回文件
//void writefile() {
//	ofstream os("decompression.txt", ios::out);
//	if(os)
//		os << text;
//	else
//		cerr << "no such file!" << endl;
//}
//
////打印字典
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