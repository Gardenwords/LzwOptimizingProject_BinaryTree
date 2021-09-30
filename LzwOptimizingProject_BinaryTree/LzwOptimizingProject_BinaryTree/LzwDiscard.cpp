//#include "stdxh.h"
///*************************************************************************/
//
////编码
//
////构造函数
//EnCode::EnCode() {
//	//初始化变量
//	this->code = 1;
//	this->result = "";
//
//	//初始化字典：把text第一个字符存入字典
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
////读入文本
//void EnCode::textLoad() {
//	ifstream is("test.txt", ios::binary);
//	Text.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());
//}
//
///***************
//保存字典
//保存形式：1 a -1
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
////输出压缩结果
//void EnCode::compressResult() {
//	ofstream os("test.clzw", ios::binary);
//	if (os)
//		os << result;
//	else
//		cerr << "no such file!" << endl;
//}
//
///***************
//cLoc：	表示当前字符位置
//row：	表示在二维数组中prerow的firstChild，从第0行开始查找
//prerow：表示上一个字符在二维数组中的行号
//precol：表示上一个字符在二维数组中的列号
//code：	表示当前字符/字符串的编码
//****************/
//void EnCode::textCompress(string& current, int row, int prerow, int precol, int eLoc) {
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
//		temp.emplace_back(t);
//		Dict.emplace_back(temp);
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
//			Dict[row].emplace_back(t);
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
////添加最后一个
//void EnCode::lastStep(string current) {
//	result = result + to_string(hashmap[current]);
//}
//
////打印字典
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
////解码
//
//DeCode::DeCode() {
//	this->code = 1;
//	this->Text = "";
//}
//
////读入压缩结果
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
////读入字典，初始化
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
//	//初始化
//	string current = "";
//	for (int index = 1; index < Dict[0].size() - 1; ++index)
//		hashmap.insert({ Dict[0][index].rCode, current + Dict[0][index].rWord });
//	for (auto iter = hashmap.begin(); iter != hashmap.end(); iter++)
//		cout << iter->first << " " << iter->second << endl;
//}
//
///***************
//解压
//需要注意的点：
//1.	第一个进行特别处理，不需要进行组词
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
////写回文件
//void DeCode::writeFile() {
//	ofstream os("decompression.txt", ios::out);
//	if (os)
//		os << Text;
//	else
//		cerr << "no such file!" << endl;
//}
//
////输出结果
//void DeCode::reText() {
//	cout << Text << endl;
//}
//
////长度
//void DeCode::length() {
//	cout << this->compresionresult.size() * 2 / 1024 << "KB" << endl;
//}
//
///*************************************************************************/
//
////命令解析
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
//	argv[1]为操作
//	argv[2]为路径
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