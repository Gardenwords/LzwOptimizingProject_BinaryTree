//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <map>
//using namespace std;
//
//typedef struct {
//	char	rWord;
//	int		rCode;		//表示字符/字符串在哈希表中对应的编码
//	int		firstChild;	//初始 -1，若存在孩子，则为下一个一维数组在二维数组中的序号
//}Dictionary;
//
//vector<vector<Dictionary>> Dict;	//以一位数组形式表示兄弟,以二维数组形式表示孩子
//int	code = 1;
//string Text;
//string	result = "";
//map<string, int> hashmap;
//
///***************
//cLoc：	表示当前字符位置
//row：	表示在二维数组中prerow的firstChild，从第0行开始查找
//prerow：表示上一个字符在二维数组中的行号
//precol：表示上一个字符在二维数组中的列号
//code：	表示当前字符/字符串的编码
//****************/
//
//void textCompress(string& current, int row, int prerow, int precol, int eLoc) {
//	//Text已读取完成	结束编码、压缩
//	if (eLoc == Text.size())
//		return;
//	
//	/***************
//	若不存在孩子	则创建vector
//	需要进行的操作：
//	1.创建新的一维数组vector，加入二维数组Dict的末尾
//	2.进行上一层和下一层的连接
//	3.将current的最后一个字符对应的code加入result
//	4.将current + Text.at(eLoc)加入哈希表（此处的current一定存在于hashmap中。因为，若不存在，row不会为-1）
//	5.将current清空
//	6.下一层递归
//	****************/
//	else if (row == -1) {
//		//1.创建新的一维数组vector，加入二维数组Dict的末尾
//		vector<Dictionary> temp;
//		Dictionary t;
//		t.rWord = Text.at(eLoc);
//		t.firstChild = -1;
//		t.rCode = code;
//		//2.进行上一层和下一层的连接
//		temp.push_back(t);
//		Dict.push_back(temp);
//		Dict[prerow][precol].firstChild = Dict.size() - 1;
//		//3.将current的最后一个字符对应的code加入result
//		result = result + to_string(hashmap[current]) + ',';
//		//4.将current + Text.at(eLoc)加入哈希表
//		hashmap.insert({ current + Text.at(eLoc), code });
//		code++;
//		//5.将current清空
//		current = "";
//		//6.下一层递归
//		textCompress(current, 0, -1, -1, eLoc);
//	}
//	//若存在孩子，顺序遍历
//	else {
//		int index = 0;
//		bool sign = false;
//		for (; index < Dict[row].size(); ++index) {
//			//若存在匹配的字符，加入current
//			if (Text.at(eLoc) == Dict[row][index].rWord) {
//				current += Text.at(eLoc);
//				sign = true;
//				textCompress(current, Dict[row][index].firstChild, row, index, eLoc + 1);
//			}
//		}
//
//		/***************
//		若当前字符不在字典中
//		由于在上一次递归中	先判断当前字符是否存在于字典中	再加入current	因此	此时的Text.at(eLoc)并没有加入current	故不需要回退一格
//		需要进行的操作：
//		1.将字符插入Dict[row]的末尾中，不用上下进行连接
//		2.将current的最后一个字对应的code加入result中（hashmap中可能并不存在current，此时row = 0，应添加判断）
//		3.将current + Text.at(eLoc)插入哈希表
//		4.将current清空
//		5.回到判断不存在字符的位置，即eLoc
//		6.下一层递归
//		***************/
//		if (!sign) {
//			//1.将字符插入二维数组中
//			Dictionary t;
//			t.rWord = Text.at(eLoc);
//			t.rCode = code;
//			t.firstChild = -1;
//			Dict[row].push_back(t);
//			/***************
//			2.将到当前字符的最后一个字对应的code加入result中（hashmap中可能并不存在current，此时row = 0，应添加判断）
//			  修正：为贴近lzw算法，不需要加入result
//			***************/
//			if (row == 0) {
//				//result = result + to_string(code) + ',';
//				//3.1.将current插入哈希表
//				hashmap.insert({ current + Text.at(eLoc), code });
//				//4.将current清空
//				current = "";
//				code++;
//				//5.回到判断不存在字符的位置，即eLoc	6.下一层递归
//				//textCompress(current, 0, -1, -1, eLoc + 1);
//				textCompress(current, 0, -1, -1, eLoc);
//			}
//			else {
//				result = result + to_string(hashmap[current]) + ',';
//				//3.2.将current插入哈希表
//				hashmap.insert({ current + Text.at(eLoc), code });
//				code++;
//				//4.将current清空
//				current = "";
//				//5.回到判断不存在字符的位置，即eLoc	6.下一层递归
//				textCompress(current, 0, -1, -1, eLoc);
//			}
//		}
//	}
//
//}
//
////初始化字典：把text第一个字符存入字典
//void initDict() {
//	Dictionary sFirst;
//	sFirst.firstChild = -1;
//	sFirst.rWord = '#';
//	sFirst.rCode = 0;
//	hashmap.insert({ "#", 0 });
//
//	vector<Dictionary> init;
//	init.push_back(sFirst);
//	Dict.push_back(init);
//}
//
////读入文本
//void textLoad() {
//	ifstream is("test.txt", ios::binary);
//	Text.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());	
//	
//}
//
////打印字典
//void cPrint() {
//	for (int row = 0; row < Dict.size(); ++row) {
//		for (int col = 0; col < Dict[row].size(); ++col)
//			cout << "(" << Dict[row][col].rCode << "," << Dict[row][col].rWord << "," << Dict[row][col].firstChild << ")" << " ";
//		cout << endl;
//	}
//}
//
///***************
//保存字典
//保存形式：（1，a，-1），以空格隔开
//***************/
//void dictSave() {
//	ofstream os("dict.txt", ios::binary);
//	if (os)
//		for (int col = 0; col < Dict[0].size(); ++col)
//			//os << '(' <<Dict[0][col].rCode << ',' << Dict[0][col].rWord << ',' << Dict[0][col].firstChild << ')';
//			os << Dict[0][col].rCode << ' ' << Dict[0][col].rWord << ' ' << Dict[0][col].firstChild << ' ' << endl;
//	else
//		cerr << "no such file!" << endl;
//}
//
////输出压缩结果
//void compressResult() {
//	ofstream os("test.clzw", ios::binary);
//	if(os)
//		os << result;
//	else
//		cerr << "no such file!" << endl;
//}
//
//
//int main() {
//	string	current = "";
//
//	initDict();
//	textLoad();
//	textCompress(current, 0, -1, -1, 0);
//
//	//添加最后一个
//	result = result + to_string(hashmap[current]);
//
//	dictSave();
//	//cPrint(Dict);
//	cout << result << endl;
//	for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++) 
//		cout << iter->first << " " << iter->second << endl;
//	compressResult();
//
//
//	system("pause");
//	return 0;
//}
