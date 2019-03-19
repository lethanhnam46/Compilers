#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// struct node{
// 	char key[30];
// 	struct item * next;
// 	int * line;
// };

// typedef struct node * item; 

// void store_in_list(char *word, item * word_list, int line){
// 	item * tmp;
// 	tmp = word_list;
// 	if((*tmp) == NULL){
// 		(*tmp) = (item)malloc(sizeof(struct node));
// 		(*tmp)->line = (int*)malloc(10*sizeof(int));
// 		strcpy((*tmp)->key, word);
// 		(*tmp)->next=NULL;
// 		(*tmp)->line[line]=1;
// 	}
	
// }
// void modify(item *word_list){
// 	item cur = * word_list;
// 	strcpy(cur->key, "second");
// }
// void lower(char * str){
// 	for(int i=0; i<strlen(str); i++){
// 		if(isupper(str[i])){
// 			str[i] = tolower(str[i]);
// 		}
// 	}
// }
// int main(){
// 	item word_list=NULL;
// 	store_in_list("First", &word_list, 3);
// 	lower(word_list->key);
// 	printf("%s===%d\n", word_list->key, word_list->line[3]);
// 	char c='2';
// 	if (isdigit(c)){
// 		printf("good\n");
// 	}
// 	// modify(&word_list);
// 	// printf("%s\n", word_list->key);
// 	return 0;
// }

int main(int argc, char * argv[]){
	printf("filename is: %s\n", argv[1]);
	return 0;
}