#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*returns the number of lines of the wrapped text*/
int *wrap(char **text, int wordcount, int maxline, int *cost); 

int main(int argc, char *argv[]){
	
	int w, i, j;
	if(argc == 1){
		w = 80;
	}
	else{
		w = atoi(argv[1]);
	}
	
	char ch;
	int afterspace = 1; //indicates if the last read character was a whitespace character
	int curletter = 0; //current letter's number (0 is first)
	int curword = 0; //curent word's number (0 is first)
	char **text; //where the text will be saved
	int textsize = 2;
	char *buffer; //a buffer in which each word is kept before being saved
	int buffersize = 2;
	int *wrappoints; //the index of the last word of each line of the wrapped text
	int cost;
	
	buffer = malloc(buffersize * sizeof(char));
	if(buffer == NULL){
		fprintf(stderr,"ERROR: Failed to allocate memory\n");
		return -1;
	}
	
	text = malloc(textsize * sizeof(char*));
	if(text == NULL){
		fprintf(stderr,"ERROR: Failed to allocate memory\n");
		return -1;
	}
	
	while((ch = getchar()) != EOF){
		if(ch == ' ' || ch == '\n' || ch == '\t'){
			if(afterspace){
				continue; //ignore unnecessary whitespace
			}
			else{
		
				if(curletter + 1 > buffersize){
					buffersize *= 2;
					buffer = realloc(buffer, buffersize * sizeof(char));
					if(buffer == NULL){
						fprintf(stderr,"ERROR: Failed to allocate memory\n");
						return -1;
					}
				}
				*(buffer + curletter) = '\0';
				
				if(curword + 1 > textsize){
					textsize *= 2;
					text = realloc(text, textsize * sizeof(char*));
					if(text == NULL){
						fprintf(stderr,"ERROR: Failed to allocate memory\n");
						return -1;
					}
				}
				
				*(text + curword) = malloc((curletter + 1) * sizeof(char));
				
				if (*(text + curword) == NULL){
					fprintf(stderr,"ERROR: Failed to allocate memory\n");
					return -1;
				}
				
				strcpy(*(text + curword), buffer);
				curword++;
				curletter = 0;
				afterspace = 1;
			}
		}
	
		else{
			if(curletter >= w){
				fprintf(stderr,"ERROR: A word exceeds the size of the line\n");
				return 22;
			}
			if(curletter + 1 > buffersize){
				buffersize *= 2;
				buffer = realloc(buffer, buffersize * sizeof(char));
				if(buffer == NULL){
					fprintf(stderr,"ERROR: Failed to allocate memory\n");
					return -1;
				}
			}
			*(buffer + curletter) = ch;
			curletter++;
			afterspace = 0;
		}
	}
	
	free(buffer);
	
	wrappoints = wrap(text, curword, w, &cost); //wrap the text
	if(wrappoints == NULL){
		fprintf(stderr,"ERROR: Failed to allocate memory\n");
		return -1;
	}
	
	i = 0;
	do{
		for(j = (i == 0 ? 0 : wrappoints[i - 1] + 1); j < wrappoints[i]; j++){
			printf("%s ", text[j]); //print each word and a space after it, except the last word
		}
		printf("%s\n", text[j]); //print the last word of the line and change line
		i++;
	}while(wrappoints[i - 1] != curword - 1);	
	fprintf(stderr,"Words: %d\nWidth: %d\nCost: %d\n", curword, w, cost);
	
	for(i = 0; i <= curword - 1; i++){
		free(text[i]);
	}
	free(text);
	free(wrappoints);
	
	return 0;
}
