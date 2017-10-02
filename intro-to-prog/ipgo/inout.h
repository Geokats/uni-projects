#define BUFFER_SIZE 100
#define ARG_SIZE 10

int isnum(char *s); //checks if string s is a number

void capitalize(char *text); //capitalizes string text

int validcolor(char *color); //checks if string color is a valid color

int showboard(void); //prints the board

void cmdget(char buffer[ARG_SIZE][BUFFER_SIZE], int buffersize, int argsize); //reads users input

int validvertex(char *s); //checks if string s represents a valid vertex

void getvertex(char *s, char *collumn, char *line); //gets coordinates from string s (which is a valid vertex)

int addhistory(char color, char collumn, char line); //adds move to history

void clearhistory(void); //clears move history

void cpboard(char **dest, char **inp); //copies board inp to board dest

int boardcomp(char **a, char **b); //return 1 if boards are identical, 0 if not
