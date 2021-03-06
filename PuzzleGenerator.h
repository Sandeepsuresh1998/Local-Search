#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include "Puzzle.h"
#include "Timer.h"

class PuzzleGenerator{
public:
	PuzzleGenerator(int nRows, int nColumns, int minVal, int maxVal);
	Puzzle GeneratePuzzle(); 
	Puzzle RandomWalk(double timelimit);	// Time limit given in seconds.
	// bool puzzleInSuccessors(std::vector<Puzzle> successors, Puzzle target);
	
private:
	int nRows, nColumns, minVal, maxVal;
	Timer timer;
	double maxtime;
};
