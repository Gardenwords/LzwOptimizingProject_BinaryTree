//#include "stdxh.h"
///*************************************************************************/
//
////����
//
////���캯��
//EnCode::EnCode() {
//	//��ʼ������
//	this->code = 1;
//	this->result = "";
//
//	//��ʼ���ֵ䣺��text��һ���ַ������ֵ�
//	Dictionary sFirst;
//	sFirst.firstChild = -1;
//	sFirst.rWord = '#';
//	sFirst.rCode = 0;
//	hashmap.insert({ "#", 0 });
//
//	vector<Dictionary> init;
//	init.emplace_back(sFirst);
//	Dict.emplace_back(init);
//}
//
////�����ı�
//void EnCode::textLoad() {
//	ifstream is("test.txt", ios::binary);
//	Text.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());
//}
//
///***************
//�����ֵ�
//������ʽ��1 a -1
//***************/
//void EnCode::dictSave() {
//	ofstream os("dict.txt", ios::binary);
//	if (os)
//		for (int col = 0; col < Dict[0].size(); ++col)
//			os << Dict[0][col].rCode << ' ' << Dict[0][col].rWord << ' ' << Dict[0][col].firstChild << ' ' << endl;
//	else
//		cerr << "no such file!" << endl;
//}
//
////���ѹ�����
//void EnCode::compressResult() {
//	ofstream os("test.clzw", ios::binary);
//	if (os)
//		os << result;
//	else
//		cerr << "no such file!" << endl;
//}
//
///***************
//cLoc��	��ʾ��ǰ�ַ�λ��
//row��	��ʾ�ڶ�ά������prerow��firstChild���ӵ�0�п�ʼ����
//prerow����ʾ��һ���ַ��ڶ�ά�����е��к�
//precol����ʾ��һ���ַ��ڶ�ά�����е��к�
//code��	��ʾ��ǰ�ַ�/�ַ����ı���
//****************/
//void EnCode::textCompress(string& current, int row, int prerow, int precol, int eLoc) {
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
//		temp.emplace_back(t);
//		Dict.emplace_back(temp);
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
//			Dict[row].emplace_back(t);
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
////������һ��
//void EnCode::lastStep(string current) {
//	result = result + to_string(hashmap[current]);
//}
//
////��ӡ�ֵ�
//void EnCode::cPrint() {
//	for (int row = 0; row < Dict.size(); ++row) {
//		for (int col = 0; col < Dict[row].size(); ++col)
//			cout << "(" << Dict[row][col].rCode << "," << Dict[row][col].rWord << "," << Dict[row][col].firstChild << ")" << " ";
//		cout << endl;
//	}
//	cout << Dict.capacity() << endl;
//	for (int row = 0; row < Dict.size(); ++row)
//		cout << Dict[row].capacity() << endl;
//}
//
///*************************************************************************/
//
////����
//
//DeCode::DeCode() {
//	this->code = 1;
//	this->Text = "";
//}
//
////����ѹ�����
//void DeCode::readResult() {
//	ifstream is("test.clzw", ios::binary);
//	string line;
//	if (is)
//		while (getline(is, line, ','))
//			compresionresult.emplace_back(stoi(line));
//	else
//		cout << "no such file!" << endl;
//	is.close();
//}
//
////�����ֵ䣬��ʼ��
//void DeCode::readDict() {
//	ifstream is("dict.txt", ios::binary);
//	vector<Dictionary> tempvector;
//	while (!is.eof()) {
//		Dictionary tempstruct;
//		is >> tempstruct.rCode >> tempstruct.rWord >> tempstruct.firstChild;
//		tempvector.emplace_back(tempstruct);
//	}
//	Dict.emplace_back(tempvector);
//	is.close();
//
//	//��ʼ��
//	string current = "";
//	for (int index = 1; index < Dict[0].size() - 1; ++index)
//		hashmap.insert({ Dict[0][index].rCode, current + Dict[0][index].rWord });
//	for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++)
//		cout << iter->first << " " << iter->second << endl;
//}
//
///***************
//��ѹ
//��Ҫע��ĵ㣺
//1.	��һ�������ر�������Ҫ�������
//***************/
//void DeCode::deCompress() {
//	string prev = "", output = "";
//	output = hashmap[compresionresult[0]];
//	Text = Text + output;
//
//	for (int index = 1; index < compresionresult.size(); ++index) {
//		prev = output;
//		output = hashmap[compresionresult[index]];
//		prev = prev + output[0];
//		while (hashmap.find(code) != hashmap.end())
//			code++;
//		hashmap.insert({ code, prev });
//		Text = Text + output;
//	}
//}
//
////д���ļ�
//void DeCode::writeFile() {
//	ofstream os("decompression.txt", ios::out);
//	if (os)
//		os << Text;
//	else
//		cerr << "no such file!" << endl;
//}
//
////������
//void DeCode::reText() {
//	cout << Text << endl;
//}
//
////����
//void DeCode::length() {
//	cout << this->compresionresult.size() * 2 / 1024 << "KB" << endl;
//}
//
///*************************************************************************/
//
////�������
////class inProcess {
////private:
////	char* fileRoute;
////	char* fileOperation;
////public:
////	inProcess(char* route, char* operation);
////	void chooseRun();
////};
////
////inProcess::inProcess(char* route, char* operation) {
////	this->fileRoute = route;
////	this->fileOperation = operation;
////}
////
////void inProcess::chooseRun() {
////	cout << this->fileOperation << " " << this->fileOperation << endl;
////	if (this->fileOperation == "-e") {
////		string current = "";
////		EnCode* encode = new EnCode(this->fileRoute);
////		encode->textLoad();
////		encode->textCompress(current, 0, -1, -1, 0);
////		encode->lastStep(current);
////		encode->dictSave();
////		encode->compressResult();
////		delete encode;
////		cout << "EnCode Success!" << endl;
////	}
////	else if (this->fileOperation == "-d") {
////		DeCode* decode = new DeCode(this->fileRoute);
////		decode->readResult();
////		decode->readDict();
////		decode->deCompress();
////		decode->writeFile();
////		delete decode;
////		cout << "DeCode Success!" << endl;
////	}
////	else
////		cout << "Operation Sign Error!" << endl;
////}
//
//
//int main(int argc, char* argv[]) {
//	/***************
//	argv[1]Ϊ����
//	argv[2]Ϊ·��
//	***************/
//	//cout << argv[1] << " " << argv[2] << endl;
//	/*inProcess* process = new inProcess(argv[1], argv[2]);
//	delete process;*/
//	clock_t startTime, endTime;
//	
//	string current = "";
//	EnCode* encode = new EnCode();
//	encode->textLoad();
//	startTime = clock();
//	encode->textCompress(current, 0, -1, -1, 0);
//	endTime = clock();
//	encode->lastStep(current);
//	encode->dictSave();
//	encode->compressResult();
//	//encode->cPrint();
//	delete encode;
//	cout << "EnCode Success!" << endl;
//	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//
//	DeCode* decode = new DeCode();
//	decode->readResult();
//	//decode->readDict();
//	//decode->deCompress();
//	//decode->writeFile();
//	//decode->reText();
//	decode->length();
//	delete decode;
//	cout << "DeCode Success!" << endl;
//	
//	system("pause");
//
//	return 0;
//}