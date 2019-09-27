#include "BFSClass.h"
#include "helpers.h"

/*
 * void BFSTree::PrintPath(int w, int cost)
 * Prints the shortest path to node w
 * c: cost of node w from it's parent node, i.e. cost[w].
 */
void BFSTree::PrintPath(int w, int c)
{
	if(parent[w]!= -1)
		PrintPath(parent[w],cost[w]);
	if(w != GoalNode)
		NodeValue[w].insert(c*2, "|");
	cout<< NodeValue[w] << "\n";
}

/*
 * bool BFSTree::CheckIfVisited(string &str)
 * Check if the node with value str is already been added to the tree
 * returns true if node already exists in tree else returns false.
 */
bool BFSTree::CheckIfVisited(string &str)
{
	vector<string>::iterator i;
	i = find(NodeValue.begin(), NodeValue.end(), str);
	if(i != NodeValue.end())
		return true;
	else
		return false;
}

/*
 * void BFSTree::TraverseTree(string inputStr, string outputStr, int num)
 *  Traverses the tree using BFS from the source state to goal state
 *  inputStr: Value of the source node
 *  outputStr: Value of the goal state
 *  num: Number of actions, i.e possible actions to flip a pancake.
 */
void BFSTree::TraverseTree(string inputStr, string outputStr, int num)
{
	int n = 0;
	string flipedStr;

	NodeValue.push_back(inputStr);
	cost.push_back(0);
	parent.push_back(-1);
						  
	int i, j=1;
	list<int> queue;

	queue.push_back(n);		//Add the source node to the queue

	// while queue is not empty or until the goal state is reached, expand the nodes in the queue
	while(!queue.empty())
	{
		n = queue.front();	// pop the first element in the queue
		queue.pop_front();

		// for 'num' number of actions, expand the n node by fliping it i times
		for(i=1; i<=num; i++)
		{
			flipedStr = flip(NodeValue[n], i);
			// check if node with the same value is already added to the queue
			if(CheckIfVisited(flipedStr))
				continue;
		
			queue.push_back(j);	// push the child node to the queue
			NodeValue.push_back(flipedStr); // map the node value to node ID
			cost.push_back(i);	// map the cost to the node ID
			parent.push_back(n);	// map the parent of the node

			// if the child node is goal state, stop expanding the tree
			if(flipedStr == outputStr) {
				GoalNode = j;
				break;
			}
			j++;		// next node ID
		}
		if(i<=num)
			break;
	}
	if(GoalNode != -1) {
		// Print the path from source state to the goal state
		cout << "\nOutput:\n";
		PrintPath( GoalNode, cost[GoalNode]);
	} else
		cout << "\nGoal state not found\n";
}

