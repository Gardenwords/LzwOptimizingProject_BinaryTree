//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//constexpr auto NOT_EXIST = -1;
//
//typedef struct {
//	char**	seq;
//	int*	code;
//	int		size;
//	int		max_size;
//} Dictionary;
//
//void insert_seq(Dictionary* dict, const char* seq) {
//	int i = dict->size;
//	dict->seq[i] = (char*)malloc(sizeof(char) * strlen(seq));
//	dict->code[i] = i;
//	dict->size++;
//	strcpy(dict->seq[i], seq);
//}
//
//void init_dictionary(Dictionary* dict, int max_size) {
//	dict->max_size	= max_size;
//	dict->size		= 0;
//	dict->seq		= (char**)malloc(sizeof(char*) * max_size);
//	dict->code		= (int*)malloc(sizeof(int) * max_size);
//	
//	insert_seq(dict, "#");
//	char seq[2] = "A";
//	for (int i = 0; i < 26; ++i) {
//		insert_seq(dict, seq);
//		seq[0]++;
//	}
//}
//
//int get_seq_code(Dictionary* dict, const char* seq) {
//	for (int i = 0; i < dict->size; ++i) {
//		if (strcmp(dict->seq[i], seq) == 0)
//			return dict->code[i];
//	}
//	return NOT_EXIST;
//}
//
//char* get_seq_code(Dictionary* dict, int code) {
//	if (code < 0 || code > dict->size)
//		return NULL;
//	else
//		return dict->seq[code];
//}
//
//void print_dictionary(Dictionary* dict) {
//	printf("=======================\n");
//	printf("Code        Sequence\n");
//	printf("=======================\n");
//	for (int i = 0; i < dict->size; ++i) {
//		printf("%4d%8c", dict->code[i], ' ');
//		printf("%s\n", dict->seq[i]);
//	}
//	printf("=======================\n");
//}
//
//void lzw_encode(char* text, Dictionary* dict) {
//	char current[1000];
//	char next;
//	int code;
//	int i = 0;
//	while (i < strlen(text)) {
//		sprintf(current, "%c", text[i]);
//		next = text[i + 1];
//		while (get_seq_code(dict, current) != NOT_EXIST) {
//			sprintf(current, "%s%c", current, next);
//			i++;
//			next = text[i + 1];
//		}
//		current[strlen(current) - 1] = '\0';
//		next = text[i];
//		code = get_seq_code(dict, current);
//		sprintf(current, "%s%c", current, next);
//		insert_seq(dict, current);
//
//		printf("%d %s\n", code, current);
//	}
//}
//
//void lzw_decode(int codes[], int n, Dictionary* dict) {
//	char	prev[1000];
//	char*	output;
//
//	output = get_seq_code(dict, codes[0]);
//	printf("%s", output);
//
//	for (int i = 1; i < n; ++i) {
//		strcpy(prev, output);
//		output = get_seq_code(dict, codes[i]);
//		sprintf(prev, "%s%c", prev, output[0]);
//		insert_seq(dict, prev);
//
//		printf("%s", output);
//	}
//}
//
//int main() {
//	Dictionary dict;
//	char text[] = "TOBEORNOTTOBEORTOBEORNOT";
//	int arr[] = { 20, 15, 2, 5, 15, 18, 14, 15, 20, 27, 29, 31, 36, 30, 30, 32, 34 };
//	init_dictionary(&dict, 1000);
//	print_dictionary(&dict);
//	lzw_encode(text, &dict);
//	lzw_decode(arr, 17, &dict);
//	return 0;
//}