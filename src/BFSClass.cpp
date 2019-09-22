#include "BFSClass.h"
#include "helpers.h"

/* 
 * BFSTree(int n)
 * constructor
 * n: no. of actions (possible no. of slices in case of pancake problem).
 */
BFSTree::BFSTree(int n)
{
	treeSize = n+1;
	adj = new list<int>[gMaximumList];
}

/*
 * void AddEdge(int v, int w)
 * Adds a node w to vertex v in the tree
 */
void BFSTree::AddEdge(int v, int w)
{
	// If the node exceeds the size of adj array, then resize the array
	if(w >= gMaximumList) {
		list<int> *temp, *temp1;
		temp = new list<int>[w+1];
		for(int i=0; i<gMaximumList; i++)
			temp[i].assign(adj[i].begin(), adj[i].end());
		adj = temp;
		gMaximumList = w+1;
	}
	adj[v].push_back(w);
}

/*
 * void BFS(int s);
 * Traverses the tree using BFS
 * s: source node, generally 0.
 */
void BFSTree::BFS(int s) 
{ 
	bool *visited = new bool [treeSize];
	parent = new int [treeSize];
       	
	for(int i = 0; i < treeSize; i++) {
		visited[i] = false;
		parent[i] = -1;	
	}
		  
	list<int> queue; 
		      
	visited[s] = true; 
	queue.push_back(s);


	list<int>::iterator i; 

	while(!queue.empty()) 
	{ 
		s = queue.front();  
		queue.pop_front(); 

		for (i = adj[s].begin(); i != adj[s].end(); ++i) 
		{ 
			if (!visited[*i]) 
			{ 
				visited[*i] = true; 
				parent[*i] = s;
				queue.push_back(*i);	
			} 
		} 
	}
}

/*
 * void PrintPath(int w, int cost)
 * Prints the shortest path to node w
 * cost: cost of node w from it's parent node, i.e. cost[w].
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
 * bool CheckIfVisited(string &str)
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
 * void CreateTree(string inputStr, string outputStr, int num)
 * Creates the tree by expanding the source node to goal node
 * and finds the shortest path to goal node.
 * inputStr: value of source node
 * outputStr: value of goal node
 * num: no. of actions (no. of slices in pancake problem)
 */
void BFSTree::CreateTree(string inputStr, string outputStr, int num)
{
	int n = 0;
	
	NodeValue.push_back(inputStr);
	cost.push_back(0);
	
	string flipedStr;
	int j=1, i;
	
	while(n < treeSize){
		/*
		 * for num number of actions,
		 * expand node n to find the next 
		 * possible states/nodes.
		 */
		for(i=1; i<=num; i++){
			flipedStr = flip(NodeValue[n], i);

			if(CheckIfVisited(flipedStr))
				continue;

			NodeValue.push_back(flipedStr);
			cost.push_back(i);
			AddEdge(n,j);
			
			/* 
			 * If the next state/ child node is goal state,
			 * then terminate the further expansion of tree.
			 */
			if (flipedStr == outputStr ) {
				GoalNode = j;
				break;
			}
			j++;
		}
		if(i <= num) {
			treeSize = NodeValue.size();
			break;
		}

		treeSize += num;

		n++;
	}
	BFS(0);
	cout << "\nOutput: \n";
	PrintPath(GoalNode, cost[GoalNode]);
}
