// index table is a linked list of words, each word is stored in a struct that contains the word, frequency of that 
//		word and an array with size equal to the total number of lines in the document which holds value
// 		1 if the word appears in that line and 0 if it doesn't
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct node{
	char key[30];
	int fre;
	int *line;
	struct node * next;
};

typedef struct node * item; 

int get_num_of_words(char *filename){
	int n=0;
	char str[20];
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){
		printf("cannot open file");
		return -1;
	}
	while(fgets(str, 20, fp) != NULL){
		n++;
	}
	fclose(fp);
	return n;
}

void read_stopw(char *filename, char ** stopw){
	FILE *fp = fopen(filename, "r");
	char str[20], c;
	int i=0;
	if(fp == NULL){
		printf("cannot open file\n");
		return; 
	}
	while(fgets(str, 20, fp) != NULL){
		if(str[strlen(str)-1] == '\n' && str[strlen(str)-2] == '\r'){
			str[strlen(str)-2] = '\0';
		}
		strcpy(stopw[i], str);
		// last 2 charaters of the string read are \r and \n (abbreviation cr and lf(or nl), ascii 13 and 10)
		// lines end with crlf on windows and nl on linux (\r\n and \n), hence the 2 redundant characters
		i++;
	}
	fclose(fp);

}

bool check_in_stopw(char *word, char ** stopw, int num_of_stopw){
	int n = num_of_stopw;
	for (int i=0; i<n; i++){
		if(strcmp(word, stopw[i]) == 0){
			return true;
		}
	}
	return false;
}

void store_in_list(char *word, item * word_list, int line /*the line the word appears in*/, int total_line /*total line of doc*/){
	item * tmp, cur;
	tmp = word_list;
	int flag=0; // 0 if the word needs to be stored at the end of the list
	int last=0; // 1 if the last node is encountered
	if((*tmp) == NULL){ // check if list is empty, if empty, malloc first item and store data 
		(*tmp) = (item)malloc(sizeof(struct node));
		(*tmp)->line = (int*)malloc(total_line*sizeof(int));
		strcpy((*tmp)->key, word);
		(*tmp)->fre = 1;
		(*tmp)->line[line] = 1;
		(*tmp)->next = NULL;
	}else{ // iterate the list if the word is already in the list, update fre and line, if not insert new item
		cur = *word_list;
		// if the word is smaller than the head node
		if(strcmp(word, (*word_list)->key)<0){
				item new = (item)malloc(sizeof(struct node));
				(new)->line = (int*)malloc(total_line*sizeof(int));
				strcpy(new->key, word);
				new->fre = 1;
				new->line[line] = 1;
				new->next = (*word_list);
				(*word_list) = new;
				flag = 1;
				return;
		}
		else{
			while(last==0){
				if(strcmp(word, cur->key) == 0){
					(cur->fre)+=1;
					cur->line[line] = 1;
					flag = 1;
					return;
				}
				else if(cur->next != NULL){
					if(strcmp(word, cur->key)>0 && strcmp(word, cur->next->key)<0){
						item new = (item)malloc(sizeof(struct node));
						(new)->line = (int*)malloc(total_line*sizeof(int));
						strcpy(new->key, word);
						new->fre = 1;
						new->line[line] = 1;
						new->next = cur->next;
						cur->next = new;
						flag = 1;
						return;
					}
					cur=cur->next;
				}
				else if(cur->next == NULL){
					last = 1;
				}
			}
			
			if(flag == 0){
				// printf("flag = 0, word: %s, line: %d\n", word, line);
				// printf("//////////////////////%s\n", cur->key);
				item new = (item)malloc(sizeof(struct node));
				(new)->line = (int*)malloc(total_line*sizeof(int));
				strcpy(new->key, word);
				new->fre = 1;
				new->line[line] = 1;
				new->next = NULL;
				cur->next = new;
			}
		}
	}
}

bool is_alphabet(char c){
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		return true;
	}
	else return false;
}

void lower(char * str){
	for(int i=0; i<strlen(str); i++){
		if(isupper(str[i])){
			str[i] = tolower(str[i]);
		}
	}
}

void read_words(char *filename, item * word_list, char ** stopw, int num_of_stopw, int total_line){
	FILE *fp = fopen(filename, "r");
	char line[200], word[30];
	int line_num = 0, dot = 0; //check if a dot is encountered
	int space=0; // right after a space or a tab...
	memset(line, 0, 200);
	memset(word, 0, 20);
	if(fp == NULL){
		printf("cannot open file\n");
		return;
	}
	char c;
	// READ EACH LINE IN THE FILE THEN SCAN EACH WORD
	// check dot, convert into lower case then check stopw
	while(fgets(line, 200, fp) != NULL){
		line_num++;
		for(int i=0; i<strlen(line); i++){
			c = line[i]; // get character

			// if c is an alphabet character store in word
			if((c >='a' && c<='z') || (c>='A' && c<='Z')){
				word[strlen(word)] = c;
			}
			// if not, check the word and store in list
			else{

				if(word[0] != '\0'){
					//printf("===============%s===%d\n", word, dot);
				
					if(word[0] != '\0'){
						word[strlen(word)] = '\0';
					// check if the first character of the word is capitalized
						if(isupper(word[0])){
							if(dot == 0){
								if(line == 0 && i==0){
									if(check_in_stopw(word, stopw, num_of_stopw)){
											memset(word, 0, strlen(word));
									}else{
										lower(word);
										store_in_list(word, word_list, line_num , total_line);
										memset(word, 0, strlen(word));
									}
								}
								memset(word, 0, strlen(word));
							}
							else if(dot == 1){
								//printf("word???????????????????????: %s\n", word);
								lower(word);
								if(check_in_stopw(word, stopw, num_of_stopw)){
									memset(word, 0, strlen(word));
								}
								// after a dot, not in stopw => store to list
								else{
									store_in_list(word, word_list, line_num , total_line);
									memset(word, 0, strlen(word));
								}
							}
						}
						else{
							if(check_in_stopw(word, stopw, num_of_stopw)){
									memset(word, 0, strlen(word));
							}
							// not capitalized, not in stopw => store to list
							else{
								lower(word);
								store_in_list(word, word_list, line_num , total_line);
								memset(word, 0, strlen(word));
							}
						}
					}
					dot = 0; // done inserting word reset dot to 0
				}
				if(isdigit(c)){
					dot = 0; // done inserting word reset dot to 0
				}
			}
			if(c == '.'){
				dot = 1;
				//printf("dotttttttttttttttttttttttttttttttttt\n");
			}
		}
	}
}

int main(int argc, char * argv[]){
	item word_list = NULL;
	int total_line = get_num_of_words("vanban.txt");
	int n = get_num_of_words("stopw.txt");
	//printf("%d\n", n);
	char ** stopw, *str="aba";
	stopw = (char**)malloc(n*sizeof(char*));
	for(int i=0; i<n; i++){
		stopw[i] = (char*)malloc(20*sizeof(char));
	}
	read_stopw("stopw.txt", stopw);
	read_words(argv[1], &word_list, stopw, n, total_line);
	//printf("1\n");
	item cur = word_list;
	while(cur != NULL){
		printf("%s===%d", cur->key, cur->fre);
		for(int i=0; i<total_line; i++){
			if(cur->line[i] == 1){
				printf(",%d", i);
			}
		}
		printf("\n");
		cur = cur->next;
	}
	return 0;
}
