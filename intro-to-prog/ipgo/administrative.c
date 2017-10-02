#include <stdio.h>
#include <string.h>

char *commands[] = {"protocol_version",
			  		"name",
			  		"version",
			  		"known_command",
			  		"list_commands",
			  		"quit",
			  
			  		"boardsize",
			  		"clear_board",
			  		"fixed_handicap",
			  		"komi",
			  
			  		"showboard",
					  
					"play",
					"genmove",
					"undo",
					"final_score"};
			  
			  
void protocol_version(void){
	printf("= 2\n\n");
}

void name(void){
	printf("= Katso's Go Machine\n\n");
}

void version(void){
	printf("= 1\n\n");
}

int known_command(char *command){
	int cmdsize = sizeof(commands) / sizeof(commands[0]); //number of available commands
	int i;
	
	for(i = 0; i < cmdsize; i++){
		if(!strcmp(command, commands[i])){
			return i + 1; //return command id
		}
	}
	return 0;
}

void list_commands(void){
	int cmdsize = sizeof(commands) / sizeof(commands[0]); //number of available commands
	int i;
	printf("=\n");
	for(i = 0; i < cmdsize; i++){
		printf("%s\n", commands[i]);
	}
	printf("\n\n");
}

void quit(int *gameloop){
	*gameloop = 0;
}

