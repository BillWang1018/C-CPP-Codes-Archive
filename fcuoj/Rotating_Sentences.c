#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	//initialize
	char *str[105];
	int len[105] = {0};
	int maxLen = 0;
	int i=0;
	char *temp;
	for(int k=0; k<105; k++)
		str[k] = (char*) malloc(105 * sizeof(char));
	temp = (char*) malloc(105 * sizeof(char));
	//get input
	while(fgets(temp, 105, stdin) != NULL) {
		int j=0;
		while(temp[j]) j++;
		strcpy(str[i], temp);
		len[i] = j-1; //enter will be stored as /0
		maxLen = (maxLen > j) ? maxLen : j;
		i++;
	}
	
	//FOR DEBUG 
	/*
	for(int k=0; k<i; k++) {
		printf("%d: %s\t==len: %d==\n", k, str[k], len[k]);
	}
	*/
	//print in vertical
	for(int k=0; k<maxLen; k++) {
		for(int m=i-1; m>=0; m--) {
			if(len[m] > k) printf("%c", str[m][k]);
			else printf(" ");
		}
		printf("\n");
	}
	
	return 0;
}