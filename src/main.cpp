#include "BFSClass.h"
#include "helpers.h"

int main()
{
	string str;
	int n;
	cout << "Please Enter the no. of pancakes:\n";
	cin  >> n;
	
	cout << "Please Enter the order of pancakes in following format,\n";
	cout<< "Pancake size: (1-9) followed by b/w (b:burnt , w: white) \n";
	cin >> str;

	BFSTree t(n);

	t.CreateTree(str, CreateOutputString(n), n);
}
