//Zach North
//603 885 768
//Homework 3, Problem 3

#include <iostream>
using namespace std;

int countPaths(const int dist[][10], int ur, int uc)
{
    if (dist[ur][uc] == 0)
		return 1;				//If (ur,uc) is the starting coordinate, then return 1.
    int total = 0;
	if (dist[ur-1][uc] == dist[ur][uc] - 1) //if the location to the north is on the shortest path
		total += countPaths(dist, ur-1, uc);
	
	if (dist[ur+1][uc] == dist[ur][uc] - 1) //if the location to the south is on the shortest path
		total += countPaths(dist, ur+1, uc);
	
	if (dist[ur][uc-1] == dist[ur][uc] - 1) //if the location to the left is on the shortest path
		total += countPaths(dist, ur, uc-1);
	
	if (dist[ur][uc+1] == dist[ur][uc] - 1) //if the location to the east is on the shortest path
		total += countPaths(dist, ur, uc+1);

	return total;
}
