#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "inout.h"
#include "setup.h"
#include "administrative.h"
#include "play.h"


int boardsize = -1;
char **board;
char **testboard;
char **liboard; //boards that help in finding liberties
char **markliboard;
char **koboarda;
char **koboardb;

int super = 0;

float komi = 0;

int curmove = 0;
int historysize = 0;
char **history; //[movenumber][0 == 'B'||'W', 1 == collumn, 2 == row]

int handicap = 0;
int captures[2]; //captures[0] is how many pieces black has captured and captures[1] for white



int main(int argc, char *argv[]){
	int i;
	int seed = 1;
	
	if(argc > 1){
		for(i = 1; i < argc; i++){
			if(strcmp(argv[i], "-superko") == 0){
				super = 1;
			}
			if(strcmp(argv[i], "-seed") == 0){
				seed = atoi(argv[i + 1]);
			}
		}
	}
	srand(seed);
	
	
	
	int gameloop = 1;
	float blackscore, whitescore;
	int id; //did the user include an id at the input?
	char buffer[ARG_SIZE][BUFFER_SIZE]; //temporarily hold the user's input
	//sizes defined in inout.h & inout.c
	
	captures[0] = 0; //white
	captures[1] = 0; //black

	
	while(gameloop){
		cmdget(&(buffer[0][0]), BUFFER_SIZE, ARG_SIZE);
		if(buffer[0][0] == '\0'){
			continue; //ignore empty lines
		}
		
		if(isdigit(buffer[0][0])){ //check if user included an id
			id = 1;
		}
		else{
			id = 0;
		}
		
		switch(known_command(buffer[0 + id])){
			case 0:{
				printf("? Unknown command: %s\nType list_commands to see available commands.\n\n", buffer[0 + id]);
				break;
			}
			case 1:{
				protocol_version();
				break;
			}
			case 2:{
				name();
				break;
			}
			case 3:{
				version();
				break;
			}
			case 4:{
				if(known_command(buffer[1 + id])){
					printf("= true\n\n");
				}
				else{
					printf("= false\n\n");
				}
				break;
			}
			case 5:{
				list_commands();
				break;
			}
			case 6:{
				quit(&gameloop);
				printf("=\n\n");
				break;
			}
			case 7:{
				switch(setboardsize(atoi(buffer[1 + id]))){
					case 0:{
						printf("? Unable to allocate memmory\n\n");
						break;
					}
					case -1:{
						printf("? Unacceptable size\n\n");
						break;
					}
					default:{
						printf("=\n\n");
						break;
					}
				}
				break;
			}
			case 8:{
				clear_board();
				printf("=\n\n");
				break;
			}
			case 9:{
				switch(check_fixed_handicap(buffer[1 + id])){
					case -1:{
						printf("? Board not set\n\n");
						break;
					}
					case -2:{
						printf("? Invalid argument\n\n");
						break;
					}
					case -3:{
						printf("? Handicap not available for this size\n\n");
						break;
					}
					case -4:{
						printf("? Board must be empty\n\n");
						break;
					}
					case -5:{
						printf("? Max handicap for this size is 4\n\n");
						break;
					}
					case 1:{
						printf("=\n\n");
						break;
					}
					
				}
				break;
			}
			case 10:{
				if(setkomi(buffer[1 + id])){
					printf("=\n\n");
				}
				else{
					printf("?\n\n");
				}
				break;
			}
			case 11:{
				if(!showboard()){
					printf("? Board not initialized\n\n");
				}
				break;
			}
			case 12:{
				if(play(buffer[1 + id], buffer[2 + id])){
					printf("=\n\n");
				}
				else{
					printf("? invalid move\n\n");
				}
				break;
			}
			case 13:{
				genmove(buffer[1 + id]);
				break;
			}
			case 14:{
				if(undo()){
					printf("=\n\n");
				}
				else{
					printf("?\n\n");
				}
				break;
			}
			case 15:{
				final_score(board, &blackscore, &whitescore, captures[0], captures[1]);
				if(blackscore > whitescore){
					printf("= B+%f\n\n", blackscore - whitescore);
				}
				else if(whitescore > blackscore){
					printf("= W+%f\n\n", whitescore - blackscore);
				}
				else{
					printf("= 0\n\n");
				}
				
				break;
			}
		}
		
		fflush(stdout);
	}
	
	clearhistory();
	if(boardsize != -1){ //if the board has been set then free it
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
	return 0;
}
