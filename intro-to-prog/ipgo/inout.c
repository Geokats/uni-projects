#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "go.h"

#define BUFFER_SIZE 100
#define ARG_SIZE 10

char letters[] = {'A', 'B', 'C', 'D', 'E', 
				  'F', 'G', 'H', 'J', 'K',
				  'L', 'M', 'N', 'O', 'P',
				  'Q', 'R', 'S', 'T', 'U',
				  'V', 'W', 'X', 'Y', 'Z'};
	
int isnum(char *s){
	int i;
	if(s[0] == '\0'){
		return 0;
	}
	for(i = 0; s[i] != '\0'; i++){
		if(!isdigit(s[i])){
			return 0;
		}
	}
	return 1;
}

void capitalize(char *text){
	int i;
	for(i = 0; text[i] != '\0'; i++){
		if(text[i] >= 'a' && text[i] <= 'z'){
			text[i] += 'A' - 'a';
		}
	}
}

int validcolor(char *color){
	capitalize(color);
	if(strcmp(color,"BLACK") == 0 || strcmp(color,"B") == 0){
		return 1;
	}
	else if(strcmp(color,"WHITE") == 0 || strcmp(color,"W") == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int showboard(void){
				  
	if(boardsize == -1){
		return 0;
	}
	
	int i, j;
	
	printf("=\n");
	printf("   ");
	for(i = 0; i < boardsize; i++){
		printf("%c ", letters[i]);
	}
	printf("\n");
	
	for(i = boardsize; i > 0; i--){
		printf("%2d ", i);
		for(j = 0; j < boardsize; j++){
			if(board[j][i - 1] == 'B'){
				printf("X ");
			}
			else if(board[j][i - 1] == 'W'){
				printf("O ");
			}
			else{	
				printf(". ");
			}			
		}
		printf("%d\n", i);
	}
	printf("   ");
	
	for(i = 0; i < boardsize; i++){
		printf("%c ", letters[i]);
	}
	printf("\n\n");
	return 1;
}

void cmdget(char buffer[ARG_SIZE][BUFFER_SIZE], int buffersize, int argsize){ 
	char ch;
	int wordcount = 0;
	int lettercount = 0;
	
	while((ch = getchar()) != '\n' && (lettercount < buffersize - 1) && (wordcount < argsize - 1)){
		if(ch == '#'){
			while((ch = getchar()) != '\n');
			break; //ignore comments
		}
		else{
			if(ch == ' ' || ch == '\t'){
				if(lettercount){ //if not at the start of a new word
					buffer[wordcount][lettercount] = '\0';
					wordcount++; //go to the next word
					lettercount = 0; //go ot the first letter of the next word
				}
			}
			else if(iscntrl(ch)){
				continue; //ignore control characters
			}
			else{
				buffer[wordcount][lettercount] = ch;
				lettercount++;
			}
		}
	}
	buffer[wordcount][lettercount] = '\0';
}

int validvertex(char *s){
	int i;
	
	capitalize(s);
	
	if(!isnum(&(s[1]))){
		return 0;
	}
	else if(atoi(&(s[1])) > boardsize || atoi(&(s[1])) < 1){
		return 0;
	}
	for(i = 0; i < boardsize; i++){
		if(s[0] == letters[i]){
			return 1;
		}
	}
	return 0;
}

void getvertex(char *s, char *collumn, char *line){
	int i;
	
	capitalize(s);
	
	if(strcmp(s,"PASS") == 0){
		*line = -1;
		*collumn = -1;
	}
	
	for(i = 0; i < boardsize; i++){
		if(letters[i] == s[0]){
			*collumn = i;
			break;
		}
	}
	
	*line = atoi(&(s[1])) - 1;
	
}

int addhistory(char color, char collumn, char line){
	int i;
	
	if(historysize == 0){
		historysize = 12;
		
		history = malloc(historysize * sizeof(char*));
		if(history == NULL){
			return NULL;
		}
		
		for(i = 0; i < historysize; i++){
			history[i] = malloc(3 * sizeof(char));
			if(history[i] == NULL){
				return NULL;
			}
		}
	}
	else if(historysize < curmove + 1){
		historysize *= 2;
		
		history = realloc(history, historysize * sizeof(char*));
		if(history == NULL){
			return NULL;
		}
		
		for(i = historysize/2; i < historysize; i++){
			history[i] = malloc(3 * sizeof(char));
			if(history[i] == NULL){
				return NULL;
			}
		}		
	}
	
	history[curmove][0] = color;
	history[curmove][1] = collumn;
	history[curmove][2] = line;
	curmove++;
	return 1;
}

void clearhistory(void){
	int i;
	
	if(historysize != 0){
		for(i = 0; i < historysize; i++){
			free(history[i]);
		}
		free(history);
	}
	historysize = 0;
	curmove = 0;
	handicap = 0;
}

void cpboard(char **dest, char **inp){
	int i, j;
	
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			dest[i][j] = inp[i][j];
		}
	}
}

int boardcomp(char **a, char **b){
	int i, j;
	
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			if(a[i][j] != b[i][j]){
				return 0;
			}
		}
	}
	return 1;
}
