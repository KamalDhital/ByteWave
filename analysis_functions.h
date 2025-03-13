#ifndef ANALYSIS_FUNCTIONS_H
#define ANALYSIS_FUNCTIONS_H

// function to load data from a file into a 2D array
int load_data(int numRows, int numCols, int teamData[][numCols], char *fileName);

// function to compute total points per team
void findTotals(int numTeams, int totals[], int numRows, int numCols, int teamData[][numCols]);

// function to compute total wins per team
void findWins(int numTeams, int wins[], int numRows, int numCols, int teamData[][numCols]);

// function to determine the top team of the year
void findWinner(int numTeams, int wins[], int totals[], int year, FILE *outputFile);

#endif
