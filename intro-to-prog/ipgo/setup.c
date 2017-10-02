#include <stdlib.h>
#include "go.h"
#include "inout.h"

void setboard(char **board, int boardsize, char value){
	int i, j;
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			board[i][j] = value;
		}
	}
}

void clear_board(void){
	setboard(board, boardsize, 0);
	clearhistory();
}

int setboardsize(int size){
	int i;
	
	if(size > 25 || size < 1){
		return -1;
	}
	
	if(boardsize != -1){ //if the board has been set in a different size
		for(i = 0; i < boardsize; i++){
			free(board[i]);
			free(liboard[i]);
			free(markliboard[i]);
			free(testboard[i]);
			free(koboarda[i]);
			free(koboardb[i]);
		}
		free(board);
		free(liboard);
		free(markliboard);
		free(testboard);
		free(koboarda);
		free(koboardb);
	}
	
	boardsize = size;
	board = malloc(boardsize * sizeof(char*));
	if(board == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		board[i] = malloc(boardsize * sizeof(char));
		if(board[i] == NULL){
			return 0;
		}
	}
	
	liboard = malloc(boardsize * sizeof(char*));
	if(liboard == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		liboard[i] = malloc(boardsize * sizeof(char));
		if(liboard[i] == NULL){
			return 0;
		}
	}
	
	markliboard = malloc(boardsize * sizeof(char*));
	if(markliboard == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		markliboard[i] = malloc(boardsize * sizeof(char));
		if(markliboard[i] == NULL){
			return 0;
		}
	}
	
	testboard = malloc(boardsize * sizeof(char*));
	if(testboard == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		testboard[i] = malloc(boardsize * sizeof(char));
		if(testboard[i] == NULL){
			return 0;
		}
	}
	
	koboarda = malloc(boardsize * sizeof(char*));
	if(koboarda == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		koboarda[i] = malloc(boardsize * sizeof(char));
		if(koboarda[i] == NULL){
			return 0;
		}
	}
	
	koboardb = malloc(boardsize * sizeof(char*));
	if(koboardb == NULL){
		return 0;
	}
	for(i = 0; i < boardsize; i ++){
		koboardb[i] = malloc(boardsize * sizeof(char));
		if(koboardb[i] == NULL){
			return 0;
		}
	}
	
	clear_board();
	
	return 1;
}

int setkomi(char *input){
	int i;
	int point = 0;
	if(input[0] == '\0'){
		return 0;
	}
	for(i = 0; input[i] != '\0'; i++){
		if(!isdigit(input[i])){
			if(input[i] == '.'){
				if(point == 0){
					point++;
				}
				else{
					return 0;
				}
			}
			else{
				return 0;
			}
		}
	}
	
	komi = atof(input);
	return 1;
}

int check_fixed_handicap(char *arg){
	int stones;
	
	if(boardsize == -1){
		return -1;	
	}
	else if(boardsize < 7){
		return -3;
	}
	
	if(curmove != 0 || handicap != 0){
		return -4;
	}
	
	if(isnum(arg)){
		stones = atoi(arg);
		if(stones <= 0 || stones > 9){
			return -2;
		}
	}
	else{
		return -2;
	}
	
	if((boardsize == 7 || boardsize % 2 == 0) && stones > 4){
		return -5;
	}
	
	fixed_handicap(stones);
	return 1;
}

void fixed_handicap(int stones){
	
	
	int d = (boardsize < 13 ? 0 : 1);
		
	switch(stones){
		case 9:
		case 8:
			board[boardsize/2][2 + d] = 'B';
			board[boardsize/2][boardsize - (3 + d)] = 'B';
		case 7:
		case 6:
			board[2 + d][boardsize/2] = 'B';
			board[boardsize - (3 + d)][boardsize/2] = 'B';
		case 5:
		case 4:
			board[2 + d][boardsize - (3 + d)] = 'B';
		case 3:
			board[boardsize - (3 + d)][2 + d] = 'B';
		case 2:
			board[boardsize - (3 + d)][boardsize - (3 + d)] = 'B';
			board[2 + d][2 + d] = 'B';
	}
	if(stones == 5 || stones == 7 || stones == 9){
		board[boardsize/2][boardsize/2] = 'B';
	}
	
	handicap = stones;
}
