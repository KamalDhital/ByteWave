#include <stdio.h>
#include <stdlib.h>
#include "analysis_functions.h"

#define NUM_TEAMS 10
#define NUM_ROWS 45
#define NUM_COLS 4

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Run the program with a list of input files, followed by the output file\n");
        printf("./runScores file_name.txt ... results.txt\n");
        return 1;
    }

    int numYears = argc - 2;
    int wins[NUM_TEAMS][numYears];    // store wins per team per year
    int totals[NUM_TEAMS][numYears];  // store total points per team per year
    int years[numYears];

    FILE *outputFile = fopen(argv[argc - 1], "w");
    if (!outputFile) {
        printf("Error opening output file: %s\n", argv[argc - 1]);
        return 1;
    }

     // process each input file
    for (int i = 1; i < argc - 1; i++) {
        int teamData[NUM_ROWS][NUM_COLS];

        years[i - 1] = load_data(NUM_ROWS, NUM_COLS, teamData, argv[i]);
        findTotals(NUM_TEAMS, totals[i - 1], NUM_ROWS, NUM_COLS, teamData);
        findWins(NUM_TEAMS, wins[i - 1], NUM_ROWS, NUM_COLS, teamData);
        findWinner(NUM_TEAMS, wins[i - 1], totals[i - 1], years[i - 1], outputFile);
    }

     // making line spaces
    fprintf(outputFile, "\n\n");

     // print header row
    fprintf(outputFile, "Team\t");
    for (int i = 0; i < numYears; i++) {
        fprintf(outputFile, "%d\t", years[i]);  // wins columns
    }
    for (int i = 0; i < numYears; i++) {
        fprintf(outputFile, "%d\t", years[i]);  // scores columns
    }
    fprintf(outputFile, "\n");

     // print each team's data
    for (int team = 0; team < NUM_TEAMS; team++) {
        fprintf(outputFile, "%d\t", team + 1);  // print team number
        for (int yearIdx = 0; yearIdx < numYears; yearIdx++) {
            fprintf(outputFile, "%d\t", wins[yearIdx][team]);  // print wins per year
        }
        for (int yearIdx = 0; yearIdx < numYears; yearIdx++) {
            fprintf(outputFile, "%d\t", totals[yearIdx][team]);  // print total points per year
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    return 0;
}

