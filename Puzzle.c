//Lab 04 Henry Wong h_wong14@u.pacific.edu
#include <stdio.h>
#include <stdlib.h>
#include "Puzzle.h"
#include <string.h>


int main () {
    struct WordSearch puzzle;
    char filename[25];
    FILE* fp;

    char word[25];
    printf("\n\nHello! Welcome to word puzzle solver. Please input the name of your text file.\n");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("no file found.");
        return 0;
    } else {
      fscanf(fp,"%d%d\n", &puzzle.row, &puzzle.col);  //Scans first two integers and save it.
      puzzle.board = (char **) malloc(puzzle.row * sizeof(char*)); //allocate space for board.
      for (int i = 0; i < puzzle.row; i++) {
          puzzle.board[i] = (char*)malloc(puzzle.col * sizeof(char));
      }
      // initializing array, scanning in, and ignoring whitespaces.
      char a;
      for (int i = 0; i < puzzle.row; i++){
          for (int j = 0; j < puzzle.col; j++){
              a = getc(fp);
              fscanf(fp, " ");
              if (a != EOF) {
                  puzzle.board[i][j] = a;
              }
            }
          }
    }
    //performing lowercase to all values of array.
    lowerCase(puzzle);
    displayBoard(puzzle);
    while(1) {
      printf("type in a word that you would like to search for :\n\n");
      scanf("%s", word);
      if (strcmp(word,"exit") == 0 || strcmp(word,"EXIT") == 0) {
        printf("Exiting....................................\n");
        return 0;
      }
      //sets reverse of string to search for if regular is not found.
      char reverse[strlen(word)];
      reverseWord(word,reverse);
      //checks using an int, to check if found >  0, meaning that it would be found.
      int found = horizontalSearch(puzzle, word) + verticalSearch(puzzle, word) + diagonalSearch(puzzle, word);
      displayBoard(puzzle);
      printf("word: %s found!\n", word);
      printf("--------------------\n");
      //if found is still 0, none were found before, and will use a reverse search.
      if (found == 0) {
        found = horizontalSearch(puzzle, reverse) + verticalSearch(puzzle, reverse) + diagonalSearch(puzzle, reverse);
        displayBoard(puzzle);
        printf("word: %s found!\n", word);
        printf("--------------------\n");
      }
      //after both searches, print out that
      if (found == 0) {
          printf("does not exist------\n");
          displayBoard(puzzle);
      }
    }

    fclose(fp);
    return 0;
}
