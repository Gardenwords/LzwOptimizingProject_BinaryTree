//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<vector>
//#include<algorithm>
//#include<queue>
//#include<time.h>
//#include<map>
//using namespace std;
//class LZW
//{
//private:
//	double B_bit = 0;
//	double C_bit = 0;
//	string filename;//文件名
//	map<unsigned short, string>form;//压缩表
//	map<string, unsigned short>find_string;
//public:
//	LZW();
//	void initialize_form_findP();
//	void compress();//压缩
//	void decompress();//解压
//	void action();//外部接口
//};
//LZW::LZW()
//{
//	cout << "LZW压缩" << endl;
//	cout << "请输入要压缩的文件名：";
//	getline(cin, filename);
//}
//void LZW::initialize_form_findP()
//{
//	string P;
//	for (int i = -128; i < 128; i++)
//	{
//		P.push_back(i);
//		form.insert(pair<unsigned short, string>(i, P));
//		find_string.insert(pair<string, unsigned short>(P, i));
//		P.clear();
//	}
//}
//void LZW::compress()
//{
//	ofstream fin("LZW.bin", ios::binary);
//	if (fin.is_open() == false)
//	{
//		cout << "不能打开LZW.bin" << endl;
//		return;
//	}
//	FILE *f = fopen(filename.c_str(), "rb+");
//	if (f == NULL)
//	{
//		cout << "不能打开" << filename << endl;
//		return;
//	}
//	char nextChar;
//	string test, P;
//	int count = 128;
//	while (fread(&nextChar, sizeof(char), 1, f))//LZW压缩算法
//	{
//		B_bit++;
//		test = P + nextChar;
//		map<string, unsigned short>::iterator it1;
//		it1 = find_string.find(test);
//		if (it1 == find_string.end())
//		{
//			map<string, unsigned short>::iterator it2;
//			it2 = find_string.find(P);
//			fin.write((char*)&it2->second, sizeof(unsigned short));
//			form.insert(pair<unsigned short, string>(count, test));
//			find_string.insert(pair<string, unsigned short>(test, count));
//			P = nextChar;
//			count++;
//		}
//		else
//		{
//			P += nextChar;
//		}
//	}
//	B_bit *= 8;
//	map<string, unsigned short>::iterator it;
//	it = find_string.find(P);
//	fin.write((char*)&it->second, sizeof(unsigned short));
//	fclose(f);
//	fin.close();
//}
//void LZW::decompress()//解压
//{
//	ifstream fin("LZW.bin", ios::binary);
//	if (!fin.is_open())
//	{
//		cout << "不能打开LZW.bin" << endl;
//		return;
//	}
//	ofstream fout("LZW decompress.txt");
//	if (!fout.is_open())
//	{
//		cout << "不能打开LZW decompress.txt" << endl;
//		return;
//	}
//	string P;
//	map<unsigned short, string>dictionary;//解压字典
//	for (int i = -128; i < 128; i++)
//	{
//		P.push_back(i);
//		dictionary.insert(pair<unsigned short, string>(i, P));
//		P.clear();
//	}
//	unsigned short cW, pW;//解压算法
//	fin.read((char*)&cW, sizeof(unsigned short));
//	C_bit++;
//	map<unsigned short, string>::iterator it;
//	it = dictionary.find(cW);
//	P = it->second;
//	fout << P;
//	pW = cW;
//	int count = 128;
//	char C;
//	while (fin.read((char*)&cW, sizeof(unsigned short)))
//	{
//		C_bit++;
//		it = dictionary.find(cW);
//		if (it == dictionary.end())
//		{
//			it = dictionary.find(pW);
//			P = it->second;
//			C = P[0];
//			dictionary.insert(pair<unsigned short, string>(count, P + C));
//			count++;
//			fout << P + C;
//		}
//		else
//		{
//			P = it->second;
//			fout << P;
//			C = P[0];
//			it = dictionary.find(pW);
//			P = it->second;
//			dictionary.insert(pair<unsigned short, string>(count, P + C));
//			count++;
//		}
//		pW = cW;
//	}
//	C_bit *= 16;
//	fin.close();
//	fout.close();
//}
//void LZW::action()
//{
//	clock_t startTime, endTime;
//	startTime = clock();
//	initialize_form_findP();
//	compress();
//	endTime = clock();
//	cout << "LZW 压缩时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//	startTime = clock();
//	decompress();
//	endTime = clock();
//	cout << "LZW 解压时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//	double answer = C_bit / B_bit;
//	answer /= 0.01;
//	cout << "LZW压缩比：" << answer << "%" << endl;
//}
//
//int main()
//{
//	LZW lzw;
//	lzw.action();
//	system("pause");
//	return 0;
//}