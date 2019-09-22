#include "AStarClass.h"
#include "helpers.h"

int AStarTree::CalculateHeuristics(string str, int n)
{
	int h = 0;
	char digits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for(int i =0 , j=0; i<(2*n); i+=2, j++) {
		if(str[i] != digits[j])
			h++;
		if(str[i+1] == 'b')
			h++;
	}
	return h;
}

void AStarTree::SortMinFnValue(list<int> &q)
{
	int n, i=0;
	n = q.size();
	int *a = new int [n];

	while(!q.empty()) {
		a[i++] = q.front();
		q.pop_front();
	}

	int min = fn[a[0]];
	
	for(i=1; i<n; i++) {
		if(fn[a[i]] < min) {
			min = a[i];
			a[i] = a[0];
			a[0] = min;
			min = fn[min];
		}
	}

	for(i=0; i<n; i++)
		q.push_back(a[i]);
}

void AStarTree::PrintShortestPath(int w, int c)
{
	 if(parent[w]!= -1)
		 PrintShortestPath(parent[w], cost[w]);
	 if(w != GoalNode)
		 NodeValue[w].insert(c*2, "|");
	  cout<< NodeValue[w] << " g = " << G[w] <<", h = "<< heuristics[w] << "\n";	
}

/*
 * bool CheckIfVisited(string &str)
 * Check if the node with value str is already been added to the tree
 * returns true if node already exists in tree else returns false.
 */
bool AStarTree::CheckIfVisited(string &str)
{
	vector<string>::iterator i;
	i = find(NodeValue.begin(), NodeValue.end(), str);
	if(i != NodeValue.end())
		return true;
	else
		return false;
}


void AStarTree::TraverseTree(string inputStr, string outputStr, int num)
{
	int n = 0;
	string flipedStr;

	NodeValue.push_back(inputStr);
	cost.push_back(0);
	G.push_back(0);
	parent.push_back(-1);
	heuristics.push_back(CalculateHeuristics(inputStr, num));
	fn.push_back(cost[0] + heuristics[0]);

	int i, j=1;
	list<int> queue;

	queue.push_back(n);

	while(!queue.empty())
	{
		SortMinFnValue(queue);
		n = queue.front();
		queue.pop_front();

		for(i=1; i<=num; i++)
		{
			flipedStr = flip(NodeValue[n], i);
			if(CheckIfVisited(flipedStr))
				continue;

			 queue.push_back(j);
			 NodeValue.push_back(flipedStr);
			 cost.push_back(i);
			 G.push_back(G[n] + cost[j]);
			 parent.push_back(n);
			 heuristics.push_back(CalculateHeuristics(flipedStr, num));
			 fn.push_back(G[j] + heuristics[j]);
			 
			 if(flipedStr == outputStr) {
				 GoalNode = j;
				 break;
			 }
			 j++;
		}
		if(i<=num)
			break;
	}
	cout << "Output:\n";
	PrintShortestPath(GoalNode, cost[GoalNode]);
}
