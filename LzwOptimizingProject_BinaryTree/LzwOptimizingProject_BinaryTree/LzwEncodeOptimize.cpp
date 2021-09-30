#include <iostream>
#include <vector>
#include <fstream>
#include<time.h>
using namespace std;

typedef struct {
	char	rWord;
	int		rCode;		//表示字符/字符串在哈希表中对应的编码
	int		rChild;		//初始 -1，若存在孩子，则为下一个一维数组在二维数组中的序号
}Dictionary;

int num = 2;

void initDict(vector<vector<Dictionary>>& A) {
	ifstream infile;
	infile.open("test4.txt", ios::in);
	Dictionary t;
	t.rChild = -1;
	t.rWord = infile.get();
	t.rCode = 1;

	vector<Dictionary> init;
	init.emplace_back(t);
	A.emplace_back(init);
	infile.clear();
	infile.close();
}

int find(vector<Dictionary> A, char c) {
	for (int i = 0; i < A.size(); ++i)
		if (A[i].rWord == c)
			return i;
	int len = A.size();
	return -len;
}

void dictSave(vector<vector<Dictionary>>& A) {
	ofstream otfile;
	otfile.open("dict.txt", ios::binary);
	if (otfile) {
		for (int col = 0; col < A[0].size(); ++col) {
			otfile.write(reinterpret_cast<char *>(&A[0][col].rCode), sizeof(int));
			otfile.write(reinterpret_cast<char *>(&A[0][col].rWord), sizeof(char));
		}
	}
	else
		cerr << "no such file!" << endl;
	int n = A[0].size();
	otfile.write(reinterpret_cast<char *>(&n), sizeof(int));
	otfile.clear();
	otfile.close();
}

void Encode(vector<vector<Dictionary>>& A, int i, int j) {
	initDict(A);
	ifstream infile;
	infile.open("test4.txt", ios::binary);
	infile.seekg(1);
	ofstream otfile;
	otfile.open("test.clzw", ios::binary);
	char c;
	while (!infile.eof()) {
		infile.get(c);
		bool flag = false;
		if (A[i][j].rChild == -1) {
			otfile.write(reinterpret_cast<char *>(&A[i][j].rCode), sizeof(int));
			flag = true;
			i = A[i][j].child = newLine();
			A[i][j].rChild = A.size();
			i = A[i][j].rChild;
			j = 0;
			vector<Dictionary> newLine;
			Dictionary t;
			t.rCode = num++;
			t.rWord = c;
			t.rChild = -1;
			newLine.emplace_back(t);
			A.emplace_back(newLine);
		}
		else {
			int m = A[i][j].rChild;
			int n = find(A[m], c);
			if (n < 0) { //未找到，-n为插入位置
				otfile.write(reinterpret_cast<char *>(&A[i][j].rCode), sizeof(int));
				flag = true;
				i = m;
				j = -n;
				Dictionary t;
				t.rCode = num++;
				t.rWord = c;
				t.rChild = -1;
				A[i].emplace_back(t);
			}
			else {
				i = m;
				j = n;
				flag = false;
			}
		}
		if (flag) {
			i = 0;
			j = find(A[0], c);
			if (j < 0) { //第0行的新字符，在-j插入
				j = -j;
				Dictionary t;
				t.rCode = num++;
				t.rWord = c;
				t.rChild = -1;
				A[0].emplace_back(t);
			}
		}
	}

	otfile.clear();
	otfile.close();
	infile.clear();
	infile.close();

	dictSave(A);
}



void print(vector<vector<Dictionary>> A) {
	for (int j = 0; j < A[0].size(); ++j) {
		/*cout << '(' << A[0][j].rCode;
		cout << ',' << A[0][j].rWord;
		cout << ',' << A[0][j].rChild << ')';*/
		printf("(%d,%c,%d)\n", A[0][j].rCode, A[0][j].rWord, A[0][j].rChild);
	}
}

int main() {
	vector<vector<Dictionary>> A;
	clock_t startTime, endTime;
	startTime = clock();
	Encode(A, 0, 0);
	endTime = clock();
	cout << "LZW 压缩时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	print(A);
	system("pause");
	return 0;
}