#include <stdio.h>
#include <stdlib.h>

void changeline(int indlvl){ //changes line and sends the cursor at the given identation level
	int i;
	putchar('\n');
	for (i = 1; i <= indlvl; i++){
				putchar('\t');
	}
}

int main(void){
	
	int indlvl = 0; //indentation level
	int afterspace = 1; //indicates if the cursor is after a whitespace
	int parlvl = 0; //number of parentheses the cursor is currently in
	int endofline = 0; //indicates if the cursor is at the end of a line and needs to change line
	int i;
	int ch;
	
	ch = getchar();
	while (ch != EOF){ 
		if(endofline){ 
			while(ch == ' ' || ch == '\t' || ch == '\n'){ //skip whitespace characters
				ch = getchar();
			}
			if(ch == EOF){ //if we reach the EOF break the while loop and end the program
				break;
			}
			else if (ch == '#'){
				changeline(0);
			}
			else if(ch == '{' || ch == '}'){
				//do nothing
			}
			else{
				changeline(indlvl);
			}
			endofline = 0;
			afterspace = 1;
		}
		switch(ch){
			case '#':{
				while (ch != '\n' && ch != EOF){
					putchar(ch);
					ch = getchar();
				}
				endofline = 1;
				break;
			}
			case ' ':
			case '\t':
			case '\n':{
				if (!afterspace){
					putchar(' ');
					afterspace = 1;
				}
				break;
			}
			case '(':{
				putchar('(');
				afterspace = 0;
				parlvl++;
				break;
			}
			case ')':{
				putchar(')');
				afterspace = 0;
				parlvl--;
				break;
			}
			case '{':{
				changeline(indlvl);
				putchar('{');
				indlvl++;
				endofline = 1;
				break;
			}
			case '}':{
				changeline(--indlvl);
				putchar('}');
				endofline = 1;
				break;
			}
			case ';':{
				putchar(';');
				if(!parlvl){ //if not in a parenthesis
					endofline = 1;
				}
				break;
			}
			case '"':{
				putchar('"');
				ch = getchar();
				while(ch != '"'){ // print everything until next "
					putchar(ch);
					if (ch == '\\'){ // handling characters after \ in the string
						ch = getchar();
						putchar(ch);
					}
					ch = getchar();
				}
				putchar('"');
				afterspace = 0;
				break;
			}
			case '\'':{
				putchar('\'');
				ch = getchar();
				while(ch != '\''){ // print everything until next '
					putchar(ch);
					if(ch == '\\'){ // handling characters after \ in the string
						ch = getchar();
						putchar(ch);
					}
					ch = getchar();
				}
				putchar('\'');
				afterspace = 0;
				break;
			}
			default:{		
				putchar(ch);
				afterspace = 0;
				break;
			}
		}
		ch = getchar();
	}
	return 0;
}
