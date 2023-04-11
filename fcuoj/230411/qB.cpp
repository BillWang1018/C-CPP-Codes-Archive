#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void count_chars(char *str, int size) {
	char *c;
	int count[256]{};
	for(c = str; c != str+size; c++)
		count[tolower(*c)]++;
	for(int i='a'; i<='z'; i++)
		cout << (char)i << ": " << count[i] << "\n";
}

int main() {
	string s;
	getline(cin, s);
	
	count_chars((char *)s.c_str(), s.size());

	return 0;
}
