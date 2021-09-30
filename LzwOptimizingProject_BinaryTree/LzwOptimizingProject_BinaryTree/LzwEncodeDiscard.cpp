//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <map>
//using namespace std;
//
//typedef struct {
//	char	rWord;
//	int		rCode;		//��ʾ�ַ�/�ַ����ڹ�ϣ���ж�Ӧ�ı���
//	int		firstChild;	//��ʼ -1�������ں��ӣ���Ϊ��һ��һά�����ڶ�ά�����е����
//}Dictionary;
//
//vector<vector<Dictionary>> Dict;	//��һλ������ʽ��ʾ�ֵ�,�Զ�ά������ʽ��ʾ����
//int	code = 1;
//string Text;
//string	result = "";
//map<string, int> hashmap;
//
///***************
//cLoc��	��ʾ��ǰ�ַ�λ��
//row��	��ʾ�ڶ�ά������prerow��firstChild���ӵ�0�п�ʼ����
//prerow����ʾ��һ���ַ��ڶ�ά�����е��к�
//precol����ʾ��һ���ַ��ڶ�ά�����е��к�
//code��	��ʾ��ǰ�ַ�/�ַ����ı���
//****************/
//
//void textCompress(string& current, int row, int prerow, int precol, int eLoc) {
//	//Text�Ѷ�ȡ���	�������롢ѹ��
//	if (eLoc == Text.size())
//		return;
//	
//	/***************
//	�������ں���	�򴴽�vector
//	��Ҫ���еĲ�����
//	1.�����µ�һά����vector�������ά����Dict��ĩβ
//	2.������һ�����һ�������
//	3.��current�����һ���ַ���Ӧ��code����result
//	4.��current + Text.at(eLoc)�����ϣ���˴���currentһ��������hashmap�С���Ϊ���������ڣ�row����Ϊ-1��
//	5.��current���
//	6.��һ��ݹ�
//	****************/
//	else if (row == -1) {
//		//1.�����µ�һά����vector�������ά����Dict��ĩβ
//		vector<Dictionary> temp;
//		Dictionary t;
//		t.rWord = Text.at(eLoc);
//		t.firstChild = -1;
//		t.rCode = code;
//		//2.������һ�����һ�������
//		temp.push_back(t);
//		Dict.push_back(temp);
//		Dict[prerow][precol].firstChild = Dict.size() - 1;
//		//3.��current�����һ���ַ���Ӧ��code����result
//		result = result + to_string(hashmap[current]) + ',';
//		//4.��current + Text.at(eLoc)�����ϣ��
//		hashmap.insert({ current + Text.at(eLoc), code });
//		code++;
//		//5.��current���
//		current = "";
//		//6.��һ��ݹ�
//		textCompress(current, 0, -1, -1, eLoc);
//	}
//	//�����ں��ӣ�˳�����
//	else {
//		int index = 0;
//		bool sign = false;
//		for (; index < Dict[row].size(); ++index) {
//			//������ƥ����ַ�������current
//			if (Text.at(eLoc) == Dict[row][index].rWord) {
//				current += Text.at(eLoc);
//				sign = true;
//				textCompress(current, Dict[row][index].firstChild, row, index, eLoc + 1);
//			}
//		}
//
//		/***************
//		����ǰ�ַ������ֵ���
//		��������һ�εݹ���	���жϵ�ǰ�ַ��Ƿ�������ֵ���	�ټ���current	���	��ʱ��Text.at(eLoc)��û�м���current	�ʲ���Ҫ����һ��
//		��Ҫ���еĲ�����
//		1.���ַ�����Dict[row]��ĩβ�У��������½�������
//		2.��current�����һ���ֶ�Ӧ��code����result�У�hashmap�п��ܲ�������current����ʱrow = 0��Ӧ����жϣ�
//		3.��current + Text.at(eLoc)�����ϣ��
//		4.��current���
//		5.�ص��жϲ������ַ���λ�ã���eLoc
//		6.��һ��ݹ�
//		***************/
//		if (!sign) {
//			//1.���ַ������ά������
//			Dictionary t;
//			t.rWord = Text.at(eLoc);
//			t.rCode = code;
//			t.firstChild = -1;
//			Dict[row].push_back(t);
//			/***************
//			2.������ǰ�ַ������һ���ֶ�Ӧ��code����result�У�hashmap�п��ܲ�������current����ʱrow = 0��Ӧ����жϣ�
//			  ������Ϊ����lzw�㷨������Ҫ����result
//			***************/
//			if (row == 0) {
//				//result = result + to_string(code) + ',';
//				//3.1.��current�����ϣ��
//				hashmap.insert({ current + Text.at(eLoc), code });
//				//4.��current���
//				current = "";
//				code++;
//				//5.�ص��жϲ������ַ���λ�ã���eLoc	6.��һ��ݹ�
//				//textCompress(current, 0, -1, -1, eLoc + 1);
//				textCompress(current, 0, -1, -1, eLoc);
//			}
//			else {
//				result = result + to_string(hashmap[current]) + ',';
//				//3.2.��current�����ϣ��
//				hashmap.insert({ current + Text.at(eLoc), code });
//				code++;
//				//4.��current���
//				current = "";
//				//5.�ص��жϲ������ַ���λ�ã���eLoc	6.��һ��ݹ�
//				textCompress(current, 0, -1, -1, eLoc);
//			}
//		}
//	}
//
//}
//
////��ʼ���ֵ䣺��text��һ���ַ������ֵ�
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
////�����ı�
//void textLoad() {
//	ifstream is("test.txt", ios::binary);
//	Text.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());	
//	
//}
//
////��ӡ�ֵ�
//void cPrint() {
//	for (int row = 0; row < Dict.size(); ++row) {
//		for (int col = 0; col < Dict[row].size(); ++col)
//			cout << "(" << Dict[row][col].rCode << "," << Dict[row][col].rWord << "," << Dict[row][col].firstChild << ")" << " ";
//		cout << endl;
//	}
//}
//
///***************
//�����ֵ�
//������ʽ����1��a��-1�����Կո����
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
////���ѹ�����
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
//	//������һ��
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
