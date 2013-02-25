#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	Map<int, double> mid;
	Map<string, int> msi;
	mid.insert(42, -1.25);
	msi.insert("Maroon", 5);
}