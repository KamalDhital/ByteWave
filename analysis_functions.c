#include <stdio.h>
#include <stdlib.h>
#include "analysis_functions.h"

 // function to load data from file into a 2D array
int load_data(int numRows, int numCols, int teamData[][numCols], char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Error opening file: %s\n", fileName);
        exit(1);
    }

    int year;
    fscanf(file, "Year: %d", &year);

    for (int i = 0; i < numRows; i++) {
        fscanf(file, "%d %d %d %d", &teamData[i][0], &teamData[i][1], &teamData[i][2], &teamData[i][3]);
    }

    fclose(file);
    return year;
}

 // function to calculate total points scored per team
void findTotals(int numTeams, int totals[], int numRows, int numCols, int teamData[][numCols]) {
    for (int i = 0; i < numTeams; i++) {
        totals[i] = 0;
    }

    for (int i = 0; i < numRows; i++) {
        int awayTeam = teamData[i][0] - 1;
        int homeTeam = teamData[i][1] - 1;
        totals[awayTeam] += teamData[i][2];
        totals[homeTeam] += teamData[i][3];
    }
}

 // function to calculate number of wins per team
void findWins(int numTeams, int wins[], int numRows, int numCols, int teamData[][numCols]) {
    for (int i = 0; i < numTeams; i++) {
        wins[i] = 0;
    }

    for (int i = 0; i < numRows; i++) {
        int awayTeam = teamData[i][0] - 1;
        int homeTeam = teamData[i][1] - 1;
        int awayScore = teamData[i][2];
        int homeScore = teamData[i][3];

        if (awayScore > homeScore) {
            wins[awayTeam]++;
        } else if (homeScore > awayScore) {
            wins[homeTeam]++;
        } else { // In case of a tie, both teams get a win
            wins[awayTeam]++;
            wins[homeTeam]++;
        }
    }
}

 // function to determine the top team of the year
void findWinner(int numTeams, int wins[], int totals[], int year, FILE *outputFile) {
    int maxWins = 0, maxPoints = 0;
    int bestTeam = -1, tiedTeam = -1;

    for (int i = 0; i < numTeams; i++) {
        if (wins[i] > maxWins) {
            maxWins = wins[i];
            maxPoints = totals[i];
            bestTeam = i + 1;
            tiedTeam = -1;
        } else if (wins[i] == maxWins) {
            if (totals[i] > maxPoints) {
                maxPoints = totals[i];
                bestTeam = i + 1;
                tiedTeam = -1;
            } else if (totals[i] == maxPoints) {
                tiedTeam = i + 1;
            }
        }
    }

    if (tiedTeam == -1) {
        printf("The top team of %d was Team %d.\n", year, bestTeam);
        fprintf(outputFile, "The top team of %d was Team %d.\n", year, bestTeam);
    } else {
        printf("The top team of %d was tied between Team %d and Team %d.\n", year, bestTeam, tiedTeam);
        fprintf(outputFile, "The top team of %d was tied between Team %d and Team %d.\n", year, bestTeam, tiedTeam);
    }
}
