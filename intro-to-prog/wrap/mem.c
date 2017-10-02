#include <stdlib.h>
#include <string.h>

int *wrap(char **text, int wordcount, int maxline, int *cost){
	int i, j, linelen, curcost, *temp;
	
	int *mincost; //the minimum cost up to word i
	mincost = malloc(wordcount * sizeof(int));
	if(mincost == NULL){
		return NULL;
	}
	for(i = 0; i < wordcount; i++){
		mincost[i] = -1; //not yet found
	}
	
	int *wrappoints;
	wrappoints = malloc(wordcount * sizeof(int));
	if(wrappoints == NULL){
		return NULL;
	}
	int *len; 
	//len[i] is the length of a line that has all the words up to i
	//len[i] doesn't count the spaces between words
	
	len = malloc(wordcount * sizeof(int));
	if(len == NULL){
		return NULL;
	}
	len[0] = strlen(text[0]);
	for(i = 1; i < wordcount; i++){
		len[i] = len[i - 1] + strlen(text[i]);
	}
	
	
	
	for(i = 0; i < wordcount; i++){
		for(j = i; j < wordcount; j++){
			if(i == 0){ //find current line's length
				linelen = len[j] + j;
			}
			else{
				linelen = len[j] - len[i - 1] + j - i; 
			}
			if(linelen > maxline){
				break;
			}
			else{
				if(j == wordcount - 1){ //if the last word of the line is the last word of the text
					curcost = (i > 0 ? mincost[i - 1] : 0) + 0; //then the cost is 0
				}
				else{
					curcost = (i > 0 ? mincost[i - 1] : 0) + (maxline - linelen) * (maxline - linelen);
				}
				if(curcost < mincost[j] || mincost[j] == -1){
					mincost[j] = curcost;
					wrappoints[j] = i;
				}
			}
		}
	}
	
	//modify the wrappoints to fit the main function's printing standards
	
	temp = malloc(wordcount * sizeof(int));
	if(temp == NULL){
		return NULL;
	}
	
	j = wordcount - 1;
	i = 0;
	while(j > 0){
		temp[i] = wrappoints[j] - 1;
		j = wrappoints[j] - 1;
		i++;
	}
	
	j = 0;
	for(i -= 2; i >= 0; i--){
		wrappoints[j] = temp[i];
		j++;
	}
	wrappoints[j] = wordcount - 1;
	
	
	*cost = mincost[wordcount - 1];
	free(len);
	free(mincost);
	free(temp);
	return wrappoints;
}
