#ifndef PUZZLE_H_
#define PUZZLE_H_

//struct that holds info of the text
struct WordSearch{
      int row,col;
      char **board;
};

//functions
void filesearch(char file[]);
void displayBoard(struct WordSearch);
void lowerCase(struct WordSearch);
void reverseWord(char [], char []);
//search functions
int horizontalSearch(struct WordSearch, char[]);
int verticalSearch(struct WordSearch, char[]);
int diagonalSearch(struct WordSearch, char[]);
#endif
