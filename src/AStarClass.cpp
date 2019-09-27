#include "AStarClass.h"
#include "helpers.h"

int max(int a, int b)
{
	if(a>b)
		return a;
	else
		return b;
}

/*
 * int AStarTree::CalculateHeuristics(string str, int n)
 * 
 * Calculates the Heuristics
 *
 * Heuristics fn: max (the ID of the largest pancake 
 * that is still out of place , the number of b characters 
 * in this state)
 *
 * str: value of the node of which the heuristics is to be 
 * calculated
 * n: no. of pancakes
 *
 * returns the Heuristics
 */
int AStarTree::CalculateHeuristics(string str, int n)
{
	int h = 0, k = 0;
	char digits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for(int i =0 , j=0; i<(2*n); i+=2, j++) {
		if(str[i] != digits[j])
			h = j+1;
		if(str[i+1] == 'b')
			k++;
	}
	return max(h, k);
}

/*
 * int AStarTree::HandleTieBreaker(int i, int j)
 * *************************************************
 * Tie breaker mechanism:
 * *************************************************
 * If two nodes have same g+h value, then convert 
 * the node values to numbers by replacing “w” with 1 and 
 * “b” with 0 and then find the minimum value of those no.s.
 * e.g. if there is a tie between 4b3w2b1b and 3w4w2b1b, 
 * then 4b3w2b1b will be chosen as 40312010>31412010
 * i and j : node IDs of nodes with tie value
 */
int AStarTree::HandleTieBreaker(int i, int j)
{
	int num1, num2;
	string temp[2];

	temp[0] = NodeValue[i];
	temp[1] = NodeValue[j];
	
	for(int k=1; k<NodeValue[i].size(); k+=2) {
		if(NodeValue[i][k] == 'b')
			temp[0][k] = '0';
		else if(NodeValue[i][k] == 'w')
			temp[0][k] = '1';

		if(NodeValue[j][k] == 'b')
			temp[1][k] = '0';
		else if(NodeValue[j][k] == 'w')
			temp[1][k] = '1';
	}

	num1 = stoi(temp[0], 0, 10);
	num2 = stoi(temp[1], 0, 10);

	if(num1 < num2)
		return i;
	else
		return j;
}

/*
 * void AStarTree::SortMinFnValue(list<int> &q)
 * Finds the minimum g+h value of all the elements in the
 * queue and then moves the node with minimum g+h value  
 * into the first element of the queue.
 * &q: reference to the queue
 */
void AStarTree::SortMinFnValue(list<int> &q)
{
	int n, i=0;
	n = q.size();
	int *a = new int [n];
	
	// move all the elements in the queue to an array
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
		} else if(fn[a[i]] == min) {	
			// if there is a tie between two nodes then use tie breaker 
			// mechanism to handle it
			 min = HandleTieBreaker(a[0], a[i]);
			 if(min != a[0]) {
				min = a[i];
			 	a[i] = a[0];
			 	a[0] = min;
			 }
				 
			 min = fn[min];
		}
	}
	// push the min sorted array back to queue
	for(i=0; i<n; i++)
		q.push_back(a[i]);
}

/*
 * void AStarTree::PrintShortestPath(int w, int c)
 * Prints the shortest path to node w
 * c: cost of node w from it's parent node, i.e. cost[w].
 */
void AStarTree::PrintShortestPath(int w, int c)
{
	 if(parent[w]!= -1)
		 PrintShortestPath(parent[w], cost[w]);
	 if(w != GoalNode)
		 NodeValue[w].insert(c*2, "|");
	  cout<< NodeValue[w] << " g = " << G[w] <<", h = "<< heuristics[w] << "\n";	
}

/*
 * bool AStarTree::CheckIfVisited(string &str)
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

/*
 * void AStarTree::TraverseTree(string inputStr, string outputStr, int num)
 * Traverses the tree using A* from the source state to goal state
 * inputStr: Value of the source node
 * outputStr: Value of the goal state
 * num: Number of actions, i.e possible actions to flip a pancake.
 */
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

	queue.push_back(n);		//Add the source node to the queue

	// while queue is not empty or until the goal state is reached, expand the nodes in the queue
	while(!queue.empty())
	{
		SortMinFnValue(queue);       // Find the minimum (g+h) value of all the elements in the queue
		n = queue.front();	     // Pop the node with minimum (g+h) value 
		queue.pop_front();

		// for 'num' number of actions, expand the n node by fliping it i times
		for(i=1; i<=num; i++)
		{
			flipedStr = flip(NodeValue[n], i);
			// check if node with the same value is already added to the queue
			if(CheckIfVisited(flipedStr))
				continue;

			 queue.push_back(j);	 // push the child node to the queue
			 NodeValue.push_back(flipedStr);  // map the node value to node ID
			 cost.push_back(i);	// map the cost to node ID
			 G.push_back(G[n] + cost[j]);	// calculate the g value and map it to the node ID
			 parent.push_back(n);	// map the parent of the node
			 heuristics.push_back(CalculateHeuristics(flipedStr, num)); // calculate the h value and map it to node ID
			 fn.push_back(G[j] + heuristics[j]); // calculate the g+h value and map it to node ID
			 
			  // if the child node is goal state, stop expanding the tree
			 if(flipedStr == outputStr) {
				 GoalNode = j;
				 break;
			 }
			 j++; //next node ID
		}
		if(i<=num)
			break;
	}

	if(GoalNode != -1) {
		// Print the path from source state to the goal state
		cout << "\nOutput:\n";
		PrintShortestPath(GoalNode, cost[GoalNode]);
	} else
		cout << "\nGoal state not found\n";
}
