#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *wrap(char **text, int wordcount, int maxline, int *cost){
	int linelen = -1; //current line's lenght
	int curword = 0;
	int curline = 0;
	int maxlines = 2;
	int *wrappoints;
	
	wrappoints = malloc(maxlines * sizeof(int));
	if(wrappoints == NULL){
		return NULL;
	}
	
	*cost = 0;
	
	while(curword < wordcount){
		if(linelen + strlen(text[curword]) + 1 <= maxline){
			linelen += strlen(text[curword]) + 1;
			curword++;
		}
		else{
			wrappoints[curline] = curword - 1; //the current line ends at the previous word	
			*cost += (maxline - linelen) * (maxline - linelen);
			curline++;
			if(curline + 1 > maxlines){
				maxlines *= 2;
				wrappoints = realloc(wrappoints, maxlines * sizeof(int));
				if(wrappoints == NULL){
					return NULL;
				}
			}
			linelen = -1;
		}
	}
	wrappoints[curline] = curword - 1; //end the last line at the last word
	
	return wrappoints; 
}
