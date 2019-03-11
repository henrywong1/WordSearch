#include "Puzzle.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


void displayBoard(struct WordSearch c) {
  //displaying board
  for (int i = 0; i < c.row; i++){
      for (int j = 0; j < c.col; j++){
          printf("%c",c.board[i][j]);
      }
      printf("\n");
  }
}

void lowerCase(struct WordSearch c) {
  //converting to lowercase
  for (int i = 0; i < c.row; i++){
      for (int j = 0; j < c.col; j++){
          c.board[i][j] = tolower(c.board[i][j]);
      }
      printf("\n");
  }
}
void reverseWord(char a[], char b[]) {
      //reversing using a loop
      int counter = 0;
      for (int i = strlen(a) - 1; i >= 0; i--) {
          b[counter++] = a[i];
      }
}


int horizontalSearch(struct WordSearch c, char a[]) {
    int wordSize = strlen(a);
    int counter = 0;
    int colStart = -1, colEnd = -1, savedRow = -1;
    for (int row = 0; row < c.row; row++) {
        for (int col = 0; col < c.col; col++) {
            if (counter < wordSize) {
                if (c.board[row][col] == a[counter]) {
                    if (savedRow == -1) {
                        //set initial coordinates.
                        colStart = col;
                        savedRow = row;
                    }
                    counter++; //moving horizontally.
                    if (counter == wordSize) {
                        colEnd = col; //saving end coordinate.
                        break;
                    }
                } else {
                    counter = 0;
                    colStart = -1;
                    savedRow = -1;
                }
            }
        }
    }
    if (colStart == -1 || colEnd == -1 || savedRow == -1) {
        return 0;
    } else {
        //looping through coordinates and capitalizing them.
        for (int i = colStart; i <= colEnd; i++) {
            c.board[savedRow][i] = toupper(c.board[savedRow][i]);
        }
        return 1;
    }
}
int verticalSearch(struct WordSearch c, char a[]) {
  int wordSize = strlen(a);
  int wordCounter = 0;
  int rowStart = - 1,rowEnd = -1, savedCol = -1;
  for (int col = 0; col < c.col; col++) {
    for (int row = 0; row < c.row; row++) {
      if(wordCounter < wordSize) {
          if (c.board[row][col] == a[wordCounter]) {
              if(savedCol == -1) {
                  //seaving initial coordinates.
                  rowStart = row;
                  savedCol = col;
              }
              wordCounter++;
              if (wordCounter == wordSize) {
                  rowEnd = row; // saving end coordinate.
                  break;
              }
          } else {
              wordCounter = 0;
              rowStart = -1;
              savedCol = -1;
          }
      }
    }
  }
  if (rowStart == -1 || rowEnd == -1 || savedCol == -1) {
      return 0;
      printf("\n");
  } else {
    for (int i = rowStart; i <= rowEnd; i++) {
        c.board[i][savedCol] = toupper(c.board[i][savedCol]);
    }
    return 1;
  }
}
int diagonalSearch(struct WordSearch c, char a[]) {
    int wordSize = strlen(a);
    int found = 0;
    //variables to hold coordinates
    int startingRow = -1, startingCol = -1, endingRow = -1, endingCol = -1;
    //traversing through the 2d array.
    for (int row = 0; row < c.row; row++) {
        for (int col = 0; col < c.col; col++) {
            //counter used to traverse array.
            int counter = 0;
            startingRow = -1;
            startingCol = -1;
            //while loop used to check boundaries.
            while((row+counter) < c.row && (col+counter) < c.col && counter < wordSize) {
                //comparing character of array to word.
                if (c.board[row+counter][col+counter] == a[counter]) {
                    //set initial rows and counters
                    //printf("startRow:%d\n", startingRow);
                    if(startingRow == -1 && startingCol == -1) {
                        startingRow = row;
                        startingCol = col;
                    }
                    counter++;    //increasing counter to move through array.
                } else {
                    //continue on for loop
                    break;
                }
            }
            //checking
            if (counter == wordSize) {
                //printf("Counter:%d", counter);
                endingRow = startingRow + counter - 1;
                endingCol = startingCol + counter - 1;
                found = 1;
                break;
            }
        }
        if (found == 1) {
            break;
        }
    }
    //Checking down left diagonal.
    if (found != 1) {
        for (int row = 0; row < c.row - 1; row++) {
            for (int col = 1; col < c.col; col++) {
                int counter = 0;
                startingRow = -1;
                startingCol = -1;
                while((row+counter) < c.row && (col-counter) >= 0) {
                    if (c.board[row+counter][col-counter] == a[counter]) {
                        if (startingRow == -1 && startingCol == -1) {
                            startingRow = row;
                            startingCol = col;
                        }
                        counter++;
                    } else {
                        break;
                    }
                }
                if (counter == wordSize) {
                    //printf("Counter:%d", counter);
                    endingRow = startingRow + counter - 1;
                    endingCol = startingCol - counter - 1;
                    found = 2;
                    break;
                }
            }
            if (found == 2) {
                break;
            }
        }
    }
    //printf("sRow:%d, sCol:%d, eRow:%d, eCol:%d\n", startingRow, startingCol, endingRow, endingCol);
    int f = 0;
    //checking if down right search finds a word.
    if (found == 1) {
      while (f < wordSize) {
          c.board[startingRow + f][startingCol + f] = toupper(c.board[startingRow + f][startingCol + f]);
          f++;
      }
      return 1;
    } else if (found == 2) {     // else searches for down left.
        while(f < wordSize) {
            c.board[startingRow +f][startingCol - f] = toupper(c.board[startingRow + f][startingCol - f]);
            f++;
        }
        return 1;
    } else
        return 0;


}
