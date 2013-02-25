#include <string>
#include <iostream>
#include <fstream>
#include "provided.h"
#include "http.h"
using namespace std;

#include <cassert>
#include "MyHashMap.h"
int main(int argc, char *argv[])
{ 
	if (argc != 5) //incorrect command line call
	{
		cout << "Usage: proj4.exe rulesFile seedSiteFile maxPages minPrice" << endl;
		exit(0);
	}

	ifstream rulesFile(argv[1]); 
	if (! rulesFile) 
	{
		cout << "Error: cannot open advertisement rules file!" << endl;
		exit(0);
	}

	ifstream seedSiteFile(argv[2]);
	if (! seedSiteFile)
	{
		cout << "Error: cannot open seed sites file!" << endl;
		exit(0);
	}

	AdHunter ah(rulesFile); 
	string seedSite;
	while(getline(seedSiteFile, seedSite)) //add all seeds from file
		ah.addSeedSite(seedSite);

	int maxPages = atoi(argv[3]); //convert from character inputs
	double minPrice = atof(argv[4]);
	vector<Match> matches;

	cout << "Crawling..." << endl;

	ah.getBestAdTargets(minPrice, maxPages, matches); 
	//run the actual calculation

	printf("There were %i matches that met the minimum price of $%.2f per ad:\n",
			matches.size(), minPrice);
	//output every ad match
	for (unsigned i = 0; i < matches.size(); i++)
	{
		cout << "Match " << i << ": "	<< matches[i].ruleName
		     << " triggered on "		<< matches[i].url
			 << " for a value of $"		<< matches[i].dollarValue
		     << "\n\tAdvertisement: "	<< matches[i].ad 
		     << endl;
	}
}


