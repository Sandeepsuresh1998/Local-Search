#include "PuzzleGenerator.h"
#include <limits>
#include <cmath>
#include <vector>

using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 59.9;	// To make sure we don't exceed a minute
	
	double random_walk_time = 5;	// 5 seconds.
	
	Puzzle p(nRows, nColumns, minVal, maxVal);
	Puzzle best_puzzle = p;
	vector<Puzzle> seen_successors;


	while(timer.GetElapsedTime() < maxtime) {
		vector<Puzzle> successors;
		best_puzzle.GetAllSuccessors(successors);
		for (int i = 0; i < successors.size(); i++) {

			bool seen_before = puzzleInSuccessors(seen_successors, successors[i]);
			
			// Checking whether the value is better
			if(successors[i].GetValue() > best_puzzle.GetValue() && !seen_before) {
				best_puzzle = successors[i];
			}

			// If we haven't seen before, we've seen it now
			if(!seen_before) {
				seen_successors.push_back(successors[i]);
			}

		}
	}

	return best_puzzle;



//*
	//return RandomWalk(random_walk_time);	// Do a random walk for some time and return the solution.
/*/
	// We could also do as many random walks as we can within the given time limit.
	Puzzle bestPuzzle = Puzzle(nRows, nColumns, minVal, maxVal);
	int bestValue = std::numeric_limits<int>::min();
	while (timer.GetElapsedTime() < maxtime-random_walk_time)
	{
		Puzzle p = RandomWalk(random_walk_time);
		int value = p.GetValue();
		if (value > bestValue) 
		{
			bestValue = value;
			bestPuzzle = p;
		}
	}
	return bestPuzzle;
//*/
}

//Helper member function
bool PuzzleGenerator::puzzleInSuccessors(vector<Puzzle> successors, Puzzle target) {
	if (successors.size() == 0) {
		return false;
	}
	for(int i = 0; i < successors.size(); i++) {
		if(successors[i].equals(target)) {
			return true;
		}
	}
	return false;
}

Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that start at a random configuration and keeps randomly modifying it
	// until t hits the time limit. Returns the best solution found so far.

	Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	
	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;			
	int bestValue = p.GetValue();
	
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	
	// Loop until we hit the time limit.
	while (t.GetElapsedTime() < timelimit-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{
		// Generate a successor of p by randomly changing the value of a random cell 
		// (since we are doing a random walk, we just replace p with its successor).
		p = p.GetRandomSuccessor();	
		int value = p.GetValue();
		
		// Update the current best solution.
		if (value > bestValue)	// Calling GetValue() for the first time is costly
										// since the puzzle has to be evaluated first.
		{
			bestValue = value;	// Calling it a second time simply returns the value that was computed before.
			bestPuzzle = p;
		}
	}
	
	return bestPuzzle;
	
	// The following code is not executed in this function. It exists just as an example for getting all the successors of a puzzle.
	vector<Puzzle> successors;
	bestPuzzle.GetAllSuccessors(successors);
}
