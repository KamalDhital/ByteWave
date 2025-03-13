CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: analyze_scores

analyze_scores: analyze_scores.o analysis_functions.o
	$(CC) $(CFLAGS) -o analyze_scores analyze_scores.o analysis_functions.o

analyze_scores.o: analyze_scores.c analysis_functions.h
	$(CC) $(CFLAGS) -c analyze_scores.c

analysis_functions.o: analysis_functions.c analysis_functions.h
	$(CC) $(CFLAGS) -c analysis_functions.c

clean:
	rm -f *.o analyze_scores


