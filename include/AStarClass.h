#ifndef __A_STAR_CLASS_H__
#define __A_STAR_CLASS_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

// AStarTree class:
// Functions and variables required to implement A* search for pancake sorter problem
class AStarTree
{
	vector<string> NodeValue;
	vector<int> parent;
	vector<int> heuristics;
	vector<int> cost;
	vector<int> G;
	vector<int> fn;
	int GoalNode = -1;	
public:
	int CalculateHeuristics(string str, int n);
	void SortMinFnValue(list<int> &q);
	void PrintShortestPath(int w, int c);
	int HandleTieBreaker(int i, int j);
	bool CheckIfVisited(string &str);
	void TraverseTree(string inputStr, string outputStr, int num);

};

#endif
