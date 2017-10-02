void setboard(char **board, int boardsize, char value); //set a square board of size boardsize to value

void clear_board(void); //clears the main board

int setboardsize(int size); //sets the main and all the assisting boards to a value

int setkomi(char *input); //sets the komi

int check_fixed_handicap(char *arg); //checks if arg is a valid value for fixed handicap and calls fixed_handicap to set it

void fixed_handicap(int stones); //set the fixed handicap
