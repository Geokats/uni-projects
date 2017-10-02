#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int minimumcost(char **text, int firstwordindex, int lastwordindex, int maxline, int **wrappoints){
	int linelen = -1;
	(*wrappoints) = malloc((lastwordindex - firstwordindex + 1) * sizeof(int));
	if(*wrappoints == NULL){
		fprintf(stderr,"ERROR: Failed to allocate memory\n");
		exit(-1);
	}
	int *temppoints;
	int cost;
	int mincost = -1;
	int i, j;
	
	for(i = firstwordindex; i <= lastwordindex; i++){
		linelen += strlen(text[i]) + 1;
		if(linelen > maxline){
			return mincost;
		}
		if(i == lastwordindex){
			(*wrappoints)[0] = lastwordindex;
			mincost = 0;
		}
		else{
			cost = (maxline - linelen) * (maxline - linelen) + minimumcost(text, i + 1, lastwordindex, maxline, &temppoints);
			if(cost < mincost || mincost == -1){
				mincost = cost;
				(*wrappoints)[0] = i;
				for(j = 1; (*wrappoints)[j - 1] != lastwordindex; j++){
					(*wrappoints)[j] = temppoints[j - 1];
				}
			}
			free(temppoints);
		}
		
	}
	return mincost;	
}

int *wrap(char **text, int wordcount, int maxline, int *cost){
	int *wrappoints;
	*cost = minimumcost(text, 0,wordcount - 1, maxline, &wrappoints);	
	return wrappoints;
}
