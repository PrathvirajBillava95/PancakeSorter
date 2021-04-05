/*
 * Pancake sorter using BFS and AStar algorithms
 * Author: Prathviraj Billava
 *
 * helper.cpp : helper functions definitions
 *
 */
 
#include <string>

using namespace std;

#include "helpers.h"

/*
 * string flip(string str, int i)
 * Flips the order of pancakes i times
 */
string flip(string str, int i)
{
	char temp[2], start = 0;
	i *= 2;
	int j = i-1;
	string flipedStr = str;
	// for each flip, swap the position of the pancakes
	// and revert the burnt/ white face.
	while(start < j )
	{
		temp[0] = flipedStr[start];
		temp[1] = flipedStr[start+1];
		flipedStr[start] = flipedStr[j-1];
		flipedStr[start+1] = (flipedStr[j] == 'b')?'w':'b';
		flipedStr[j-1] = temp[0];
		flipedStr[j] = (temp[1] == 'b')?'w':'b';	
		j -= 2;
		start += 2;
	}
	return flipedStr;
}

/*
 * string CreateOutputString(int n)
 * Creates the final state of pancakes
 * n: no. of pancakes
 * e.g. input: n=4, output: "1w2w3w4w"
 */
string CreateOutputString(int n)
{
	char digits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char *s = new char [n*2];
	string str;
	for(int i=0, j=0; i<(2*n); i+=2, j++) {
			s[i] = digits[j];
			s[i+1] = 'w';
	}
	str.assign(s);
	return str;
}
