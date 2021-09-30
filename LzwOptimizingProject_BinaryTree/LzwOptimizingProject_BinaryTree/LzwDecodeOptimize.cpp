#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<time.h>
using namespace std;

typedef struct {
	char	rWord;
	int		rParent = -2;
}Dictionary;

int num = 1;

void expand(vector<vector<Dictionary>>& A, int n, int m) {
	A.resize(m + 1);
	for (int i = n; i <= m; ++i)
		A[i].resize(256);
}

pair<int, int> convert_index(int i) {
	int m = (i - 1) / 256;
	int n = (i - 1) - m * 256;
	return { m, n };
}

int initDict(vector<vector<Dictionary>>& A) {
	A.resize(1);
	A[0].resize(256);
	int number;
	ifstream infile;
	infile.open("dict.txt", ios::binary);
	if (infile) {
		//获取初始字典数
		infile.seekg(-(int)sizeof(int), ios::end);
		streampos sp = infile.tellg();
		infile.read(reinterpret_cast<char *>(&number), sizeof(int));
		infile.seekg(-number * ((int)sizeof(int) + (int)sizeof(char)) - (int)sizeof(int), ios::end);
		int origin_index;
		char word;
		while (infile.tellg() != sp) {
			infile.read(reinterpret_cast<char *>(&origin_index), sizeof(int));
			infile.read(reinterpret_cast<char *>(&word), sizeof(char));
			pair<int, int> real_index = convert_index(origin_index);
			if (real_index.first > (int)(A.size() - 1))
				expand(A, A.size(), real_index.first);
			A[real_index.first][real_index.second].rWord = word;
			A[real_index.first][real_index.second].rParent = -1;
		}
		//for (int i = 0; i < number; ++i) {
		//	infile.read(reinterpret_cast<char *>(&origin_index), sizeof(int));
		//	infile.read(reinterpret_cast<char *>(&word), sizeof(char));
		//	cout << origin_index << ' ' << word << endl;
		//	pair<int, int> real_index = convert_index(origin_index);
		//	if ( (occ != 0) && (occ % 256 == 0) )
		//		expand(A);
		//	/*A[real_index.first][real_index.second].rWord = word;
		//	A[real_index.first][real_index.second].rParent = -1;
		//	occ++;*/
		//}

		////获取初始字典
		//infile.seekg(-(int)sizeof(int), ios::end);
		//int origin_index;
		//char word;
		//for (int i = 0; i < number; ++i) {
		//	infile.seekg(-(int)sizeof(char), ios::cur);
		//	infile.seekg(-(int)sizeof(int), ios::cur);
		//	infile.read(reinterpret_cast<char *>(&origin_index), sizeof(int));
		//	infile.read(reinterpret_cast<char *>(&word), sizeof(char));
		//	cout << origin_index << ',' << word << endl;
		//	pair<int, int> real_index = convert_index(origin_index);
		//	if ( (occ != 0) && (occ % 256 == 0) )
		//		expand(A);
		//	/*A[real_index.first][real_index.second].rWord = word;
		//	A[real_index.first][real_index.second].rParent = -1;*/
		//	occ++;
		//	infile.seekg(-(int)sizeof(char), ios::cur);
		//	infile.seekg(-(int)sizeof(int), ios::cur);
		//}
	}
	else
		cout << "no such file!" << endl;

	infile.clear();
	infile.close();
	return number;
}

string getstring(vector<vector<Dictionary>>& A, int i) {
	string s = "";
	pair<int, int> t = convert_index(i);
	do {
		s += A[t.first][t.second].rWord;
		if (A[t.first][t.second].rParent != -1)
			t = convert_index(A[t.first][t.second].rParent);
		else
			break;
	} while (true);

	reverse(s.begin(), s.end());
	return s;
}

void Decode(vector<vector<Dictionary>>& A) {
	int index;
	int dictnumber = initDict(A);
	ifstream infile;
	infile.open("test.clzw", ios::binary);
	ofstream otfile;
	otfile.open("decompression.txt", ios::binary);
	//infile.seekg(-5 * (dictnumber + 1), ios::end);
	//streampos sp = infile.tellg();
	//infile.seekg(0, ios::beg);

	//特殊处理
	infile.read(reinterpret_cast<char *>(&index), sizeof(int));
	pair<int, int> f = convert_index(index);
	otfile << A[f.first][f.second].rWord;

	while (!infile.eof()) {
		int new_code;
		//infile.get(c);
		infile.read(reinterpret_cast<char *>(&new_code), sizeof(int));
		pair<int, int> code = convert_index(new_code);

		//获取字符串
		string s;
		if (A[code.first][code.second].rParent == -2)
			s = getstring(A, index);
		else
			s = getstring(A, new_code);
		otfile << s;
		pair<int, int> t = convert_index(num);

		//获取下标
		if (t.first > (int)(A.size() - 1))
			expand(A, A.size(), t.first);
		while (A[t.first][t.second].rParent != -2) {
			num++;
			t = convert_index(num);
			if (t.first > (int)(A.size() - 1))
				expand(A, A.size(), t.first);
		}
		if (t.first > (int)(A.size() - 1))
			expand(A, A.size(), t.first);

		A[t.first][t.second].rWord = s.at(0);
		A[t.first][t.second].rParent = index;
		index = new_code;
	}

	otfile.clear();
	otfile.close();
	infile.clear();
	infile.close();
}

void print(vector<vector<Dictionary>>& A) {
	for (int i = 0; i < A[0].size(); ++i) {
		//cout << '(' << A[0][i].rWord << ',' << A[0][i].rParent << ')' << endl;
		printf("(%c,%d)\n", A[0][i].rWord, A[0][i].rParent);
	}
	/*cout << A[0][0].rWord << ',' << A[0][0].rParent << endl;
	cout << A[0][2].rWord << ',' << A[0][2].rParent << endl;
	cout << A[0][6].rWord << ',' << A[0][6].rParent << endl;
	cout << A[0][9].rWord << ',' << A[0][9].rParent << endl;*/
}

int main() {
	vector<vector<Dictionary>> A;
	clock_t startTime, endTime;
	startTime = clock();
	Decode(A);
	endTime = clock();
	cout << "LZW 解压时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//print(A);
	system("pause");
	return 0;
}