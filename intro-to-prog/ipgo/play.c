#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "go.h"
#include "inout.h"

int countliberties(char color, char collumn, char line, char **board){
	markliboard[collumn][line] = 1; //this place has been checked
	int liberties = 0;
	
	if(collumn > 0){ //check left
		if(board[collumn - 1][line] == 0 && markliboard[collumn - 1][line] == 0){
			liberties++;
			markliboard[collumn - 1][line] = 1;
		}
		else if(board[collumn - 1][line] == color && markliboard[collumn - 1][line] == 0){
			liberties += countliberties(color, collumn - 1, line, board);
		}
	}
	
	if(collumn < boardsize - 1){ //check right
		if(board[collumn + 1][line] == 0 && markliboard[collumn + 1][line] == 0){
			liberties++;
			markliboard[collumn + 1][line] = 1;
		}
		else if(board[collumn + 1][line] == color && markliboard[collumn + 1][line] == 0){
			liberties += countliberties(color, collumn + 1, line, board);
		}
	}
	
	if(line > 0){ //check down
		if(board[collumn][line - 1] == 0 && markliboard[collumn][line - 1] == 0){
			liberties++;
			markliboard[collumn][line - 1] = 1;
		}
		else if(board[collumn][line - 1] == color && markliboard[collumn][line - 1] == 0){
			liberties += countliberties(color, collumn, line - 1, board);
		}
	}
	
	if(line < boardsize - 1){ //check down
		if(board[collumn][line + 1] == 0 && markliboard[collumn][line + 1] == 0){
			liberties++;
			markliboard[collumn][line + 1] = 1;
		}
		else if(board[collumn][line + 1] == color && markliboard[collumn][line + 1] == 0){
			liberties += countliberties(color, collumn, line + 1, board);
		}
	}
	
	return liberties;
}

int checkliberties(char color, char collumn, char line, char **board){ //gets the liberties for one place
	setboard(markliboard, boardsize, 0);
	return countliberties(color, collumn, line, board);
}

void getliberties(char **board, char **liboard){ //gets the liberties of all the board
	int i, j;
	
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			if(board[i][j] != 0){
				liboard[i][j] = checkliberties(board[i][j], i, j, board);
			}
		}
	}
}

int getcaptured(char **board, char color){
	int i, j, captures = 0;
	
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			if(board[i][j] == color && liboard[i][j] == 0){
				captures++;
				board[i][j] = 0;
			}
		}
	}
	return captures;
}

int willcapture(char color, char collumn, char line, char **board){
	
	board[collumn][line] = color;
	getliberties(board, liboard);
	board[collumn][line] = 0;
	
	if(collumn > 0){
		if(board[collumn - 1][line] == (color == 'B' ? 'W' : 'B') && liboard[collumn - 1][line] == 0){
			return 1;
		}
	}
	if(collumn < boardsize - 1){
		if(board[collumn + 1][line] == (color == 'B' ? 'W' : 'B') && liboard[collumn + 1][line] == 0){
			return 1;
		}
	}
	if(line > 0){
		if(board[collumn][line - 1] == (color == 'B' ? 'W' : 'B') && liboard[collumn][line - 1] == 0){
			return 1;
		}
	}
	if(line < boardsize - 1){
		if(board[collumn][line + 1] == (color == 'B' ? 'W' : 'B') && liboard[collumn][line + 1] == 0){
			return 1;
		}
	}
	
	return 0;	
}

int superko(char color, char collumn, char line, char **board){
	int i;
	cpboard(koboarda, board);
	koboarda[collumn][line] = color;
	getliberties(koboarda, liboard);
	getcaptured(koboarda, color == 'B' ? 'W' : 'B');
	
	if(super = 1){
		setboard(koboardb, boardsize, 0);
		
		for(i = 0; i < curmove; i++){
			playhistory(i, koboardb);
			if(boardcomp(koboarda, koboardb)){
				return 0;
			}
		}	
		return 1;
	}
	else{
		for(i = 0; i < curmove - 4; i++){
			playhistory(i, koboardb);
		}
		for(i = curmove - 4; i < curmove; i++){
			playhistory(i, koboardb);
			if(boardcomp(koboarda, koboardb)){
				return 0;
			}
		}
		return 1;
	}
}

int validplay(char color, char collumn, char line, char **board){
	if(board[collumn][line] != 0){
		return 0;
	}
	else if(checkliberties(color, collumn, line, board) == 0 && !willcapture(color, collumn, line, board)){
		return 0;
	}
	else if(superko(color, collumn, line, board) == 0){
		return 0;
	}
	else{
		return 1;
	}
}
	
int play(char *color, char *move){
	char collumn, line;
	
	if(!validcolor(color)){
		return 0;
	}
	
	capitalize(move);
	if(strcmp(move, "PASS") == 0){
		addhistory(color, -1, -1);
		
		//TODO: CHECK ENDGAME
		
		return 1;
	}
	else if(validvertex(move)){
		getvertex(move, &collumn, &line);
		
		if(validplay(color[0], collumn, line, board)){
			board[collumn][line] = color[0];
			addhistory(color[0], collumn, line);
			getliberties(board, liboard);
			captures[color[0] == 'B' ? 0 : 1] += getcaptured(board, color[0] == 'B' ? 'W' : 'B');
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

int iseye(char collumn, char line, char **board, char color){
	int possible = 0;
	int count = 0;
	if(collumn > 0){
		possible++;
		if(board[collumn - 1][line] == color){
			count++;
		}
	}
	if(collumn < boardsize - 1){
		possible++;
		if(board[collumn + 1][line] == color){
			count++;
		}
	}
	if(line > 0){
		possible++;
		if(board[collumn][line - 1] == color){
			count++;
		}
	}
	if(line < boardsize - 1){
		possible++;
		if(board[collumn][line + 1] == color){
			count++;
		}
	}
	
	return count == possible;
}

void makemove(char color, char *collumn, char *line, char **board){
	int i;
		
	*collumn = rand() % boardsize;
	*line = rand() % boardsize;
	
	for(i = 0; i < boardsize * boardsize; i++){
		if(validplay(color, *collumn, *line, board) && !iseye(*collumn, *line, board, color)){
			return;
		}
		else{
			if(*collumn > 0){
				(*collumn)--;
			}
			else{
				(*collumn) = boardsize - 1;
				if(*line > 0){
					(*line)--;
				}
				else{
					(*line) = boardsize - 1;
				}
			}
		}
	}
	
	*collumn = *line = -1;
	return;
	
}

void genmove(char *color){
	char collumn, line;
	
	char letters[] = {'A', 'B', 'C', 'D', 'E', 
				      'F', 'G', 'H', 'J', 'K',
				  	  'L', 'M', 'N', 'O', 'P',
				  	  'Q', 'R', 'S', 'T', 'U',
				  	  'V', 'W', 'X', 'Y', 'Z'};
	
	if(boardsize == -1){
		printf("? board not initialized\n\n");
		return;
	}
	
	if(validcolor(color)){
		makemove(color[0], &collumn, &line, board);
		addhistory(color[0], collumn, line);
		
		if(collumn == -1 && line == -1){
			printf("= pass\n\n");
		}
		else{
			board[collumn][line] = color[0];
			getliberties(board, liboard);
			captures[color[0] == 'B' ? 0 : 1] += getcaptured(board, color[0] == 'B' ? 'W' : 'B');
			printf("= %c%d\n\n", letters[collumn], line + 1);
		}		
	}
	else{
		printf("?\n\n");
	}
}

int playhistory(int movenum, char **board){
	if(history[movenum][1] < 0 || history[movenum][2] < 0){
		return 0;
	}
	board[history[movenum][1]][history[movenum][2]] = history[movenum][0];
	getliberties(board, liboard);
	return getcaptured(board,history[movenum][0] == 'B' ? 'W' : 'B');
}

int undo(void){
	if(curmove <= 0){
		return 0;
	}
	
	int i;

	curmove--;
	setboard(board, boardsize, 0);
	captures[0] = captures[1] = 0;
	
	fixed_handicap(handicap);
	
	for(i = 0; i < curmove; i++){
		captures[history[i][0] == 'B' ? 0 : 1] = playhistory(i, board);
	}
	return 1;
}

void final_score(char **board, float *blackscore, float *whitescore, int blackcaptures, int whitecaptures){
	int bcount, wcount, i, j;
	
	*blackscore = blackcaptures;
	*whitescore = whitecaptures + komi;
	
	for(i = 0; i < boardsize; i++){
		for(j = 0; j < boardsize; j++){
			if(board[i][j] == 'B'){
				(*blackscore)++;
			}
			else if(board[i][j] == 'W'){
				(*whitescore)++;
			}
			else{
				bcount = wcount = 0;
				if(i > 0){
					if(board[i - 1][j] == 'B'){
						bcount++;
					}
					else if(board[i - 1][j] == 'W'){
						wcount++;
					}
				}
				if(i < boardsize - 1){
					if(board[i + 1][j] == 'B'){
						bcount++;
					}
					else if(board[i + 1][j] == 'W'){
						wcount++;
					}
				}
				if(j > 0){
					if(board[i][j - 1] == 'B'){
						bcount++;
					}
					else if(board[i][j - 1] == 'W'){
						wcount++;
					}
				}
				if(j < boardsize - 1){
					if(board[i][j + 1] == 'B'){
						bcount++;
					}
					else if(board[i][j + 1] == 'W'){
						wcount++;
					}
				}
				
				if(bcount > wcount){
					(*blackscore)++;
				}
				else if (wcount > bcount){
					(*whitescore)++;
				}
			}
		}
	}
}
