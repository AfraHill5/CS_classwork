//Zach North
//603-885-768
//Project 5

#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;

void shiftLeft(char w1[][MAX_WORD_LENGTH+1], int start, int n) //shifts the words in an array over to the left to overlap the word at pos start
{
	for (start; start < n; start++)
		strcpy(w1[start], w1[start+1]);
}

void shiftDistanceLeft(int i1[], int start, int n) //shifts the distance array over to match the words
{
	for (start; start < n; start++)
		i1[start] = i1[start+1];
}

int standardizeCriteria(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nCriteria)
{ //removes bad criteria, removes duplicates, and returns the number of correct criteria
	for (int k = 0; k < nCriteria; k++)
	{
		if (distance[k] <= 0) //nonzero distance is not allowed
		{
			shiftLeft(word1, k, nCriteria);
			shiftLeft(word2, k, nCriteria);
			shiftDistanceLeft(distance, k, nCriteria);
			nCriteria--; //nCriteria and k shift backwards to keep up with the shifting arrays.
			k--;
		}
		else //runs these checks only if distance is positive
		{
			bool word1Stop = false, word2Stop = false;
			for (int j = 0; j < MAX_WORD_LENGTH+1; j++)
			{
				if (word1[k][0] == '\0') //checks to see that the current word in word1 is not blank, and removes the criterion if it is 
				{
						shiftLeft(word1, k, nCriteria); 
						shiftLeft(word2, k, nCriteria);
						shiftDistanceLeft(distance, k, nCriteria);
						nCriteria--;
						k--;
						break;
				}
				if (word2[k][0] == '\0') //checks to see that the current word in word2 is not blank, and removes the criterion if it is
				{
						shiftLeft(word1, k, nCriteria); 
						shiftLeft(word2, k, nCriteria);
						shiftDistanceLeft(distance, k, nCriteria);
						nCriteria--;
						k--;
						break;
				}
				if (word1[k][j] == '\0') //these 2 lines stop the loop when it reaches the end of the current word
					word1Stop = true;
				if (word2[k][j] == '\0')
					word2Stop = true;
				if (word1Stop == false)
				{
					if (!isalpha(word1[k][j])) 
					{
						shiftLeft(word1, k, nCriteria); //shifts everything left if current char is not a letter
						shiftLeft(word2, k, nCriteria);
						shiftDistanceLeft(distance, k, nCriteria);
						nCriteria--;
						k--;
						break;
					}
					if (isupper(word1[k][j])) //checks uppercase and shifts to lower
						word1[k][j] = tolower(word1[k][j]);
				}
				if (word2Stop == false)
				{
					if (!isalpha(word2[k][j]))
					{
						shiftLeft(word1, k, nCriteria); //shifts everything left
						shiftLeft(word2, k, nCriteria);
						shiftDistanceLeft(distance, k, nCriteria);
						nCriteria--;
						k--;
						break;
					}
					if (isupper(word2[k][j])) //checks uppercase and shifts to lower
						word2[k][j] = tolower(word2[k][j]);
				}
			}
			if (strcmp(word1[k], word2[k]) == 0)
			{
				shiftLeft(word1, k, nCriteria); //shifts everything left
				shiftLeft(word2, k, nCriteria);
				shiftDistanceLeft(distance, k, nCriteria);
				nCriteria--;
				k--;
			}
		}
	}
	int a = 0;
	while (a < nCriteria)
	{
		int b = a+1; //double loop -- b is always ahead of a so it doesn't double up results
		while (b < nCriteria)
		{
			if ((strcmp(word1[a], word1[b]) == 0) && (strcmp(word2[a], word2[b]) == 0)) //compares each valid element of the test arrays to each other to find repeats
			{ 
				if (distance[a] < distance[b]) //checks which one has the smaller distance operator
				{
					shiftLeft(word1, a, nCriteria); //if the first has the smaller distance value, removes those 3 elements
					shiftLeft(word2, a, nCriteria);
					shiftDistanceLeft(distance, a, nCriteria);
					nCriteria--;
				}
				else
				{
					shiftLeft(word1, b, nCriteria); //if the second, removes those 3 elements
					shiftLeft(word2, b, nCriteria);
					shiftDistanceLeft(distance, b, nCriteria);
					nCriteria--;
				}
			}
			else //moves on to the next step
			{
				b++;
			}
		}
		a++; //next step
	}
	return nCriteria;
}

int calculateScore(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nCriteria, const char document[]) 
{ //checks the document for the match string returned in standardizeCriteria and returns the "score" (number of hits)
	char testDoc[200][200];
	bool reachedEnd = false;
	int currentChar = 0, numberWords = 0;
	for (int k = 0; k < 200; k++) //runs through each char of document and assigns the characters to "words" in cstring testDoc
	{
		char temp[200] = ""; //blanks the temp string before running the loop
		int j = 0;
		for (currentChar; currentChar < 200; currentChar++) //steps through characters in document
		{
			if (document[currentChar] == '\0' || currentChar == 200) //the loop reached the end of the document if this occurs
			{
				reachedEnd = true;
				break;
			}
			if (document[currentChar] == ' ') //stops the loop at space characters
			{
				temp[j] = '\0'; //attaches an \0 to the temp variable and quits the loop
				currentChar++;
				break;
			}
			else if (!isalpha(document[currentChar])) //does nothing at non letter characters
				;
			else if (isupper(document[currentChar])) //shifts uppercase to lower
			{
				temp[j] = tolower(document[currentChar]);
				j++;
			}
			else //adds any letters to temp
			{
				temp[j] = document[currentChar];
				j++;
			}
		}
		if (temp[0] == '\0')
			k--; //prevents the program from adding blank spaces in as words if there are multiple blank spaces between words in document
		else
		{
			numberWords++; //increments the number of words in the element
			strcpy(testDoc[k], temp); //each array element in testDoc is a different word containing temp
		}
		if (reachedEnd) //if the steps have reached the end of document, breaks the loop
			break;
	}
	strcpy(testDoc[numberWords], ""); //adds on a zero byte to the last element in testDoc for debug purposes
	
	int score = 0; //counter to hold the return score
	for (int n = 0; n < nCriteria; n++) //steps through each criteria
	{
		for (int k = 0; k < numberWords; k++) //steps through each word in testDoc
		{
			if (strcmp(word1[n], testDoc[k]) == 0) //looks for a match between the first word and the word in testDoc
			{
				bool word2Match = false;
				for (int j = 1; j <= distance[n]; j++) //looks ahead of the first matched word for the second criteria, with max distance specified by the distance array
				{
					if (strcmp(word2[n], testDoc[j+k]) == 0) //if it finds another match, adds one to the score and moves on to the next criteria
					{
						score++;
						word2Match = true;
						break;
					}
				}
			if (word2Match == true) //only matches once per criteria
						break;
			}
		}
	}
	return score;
}
void printArray(char a[][MAX_WORD_LENGTH+1], int n)
{
	cerr << "{";
	for (int i = 0; i < n; i++)
	{
		cerr << a[i];
		if (i != n - 1)
			cerr << ", ";
	}
	cerr << "}" << endl;
}

void printArray(int a[], int n)
{
	cerr << "{";
	for (int i = 0; i < n; i++)
	{
		cerr << a[i];
		if (i != n - 1)
			cerr << ", ";
	}
	cerr << "}" << endl;
}

int main() //test function
{
	/*int testDistance[10]					 = {1, 1, 1, 3}; //distance array
	char testWord1[10][MAX_WORD_LENGTH+1]    = {"test", "test", "test", "test"}; // first word array
	char testWord2[10][MAX_WORD_LENGTH+1]    = {"one", "two", "test", "two"}; //second word array
	int nCriteria							 = 4; //number of criteria

	cout << "First array: ";
	for (int k = 0; k < nCriteria; k++) //outputs the words in the first word array
		cout << testWord1[k] << " ";
	cout << endl << "Second array: ";
	for (int j = 0; j < nCriteria; j++) //outputs the words in the second word array
		cout << testWord2[j] << " ";
	cout << endl << "Distances: ";
	for (int l = 0; l < nCriteria; l++) //outputs the distances
		cout << testDistance[l] << " ";
	
	standardizeCriteria(testDistance, testWord1, testWord2, nCriteria);
	int standardizedResults = standardizeCriteria(testDistance, testWord1, testWord2, nCriteria);
	cout << endl << "Standarized criteria: " << standardizedResults << endl;
	cout << "First array is now: ";
	for (int k = 0; k < standardizedResults; k++) //outputs the words in the first word array
		cout << testWord1[k] << " ";
	cout << endl << "Second array is now: ";
	for (int j = 0; j < standardizedResults; j++) //outputs the words in the second word array
		cout << testWord2[j] << " ";
	cout << endl << "Distances are now: "; //outputs the distances
	for (int l = 0; l < standardizedResults; l++)
		cout << testDistance[l] << " ";
	cout << endl;

	char testString[200] = "This is a test. Test one test two. ABCDefghijklmnopqrstuvxyz";
	cout << "Document score is: " << calculateScore(testDistance, testWord1, testWord2, nCriteria, testString) << endl;

	//SMALLBERG TESTING
			const int TEST1_NCRITERIA = 4;
            int test1dist[TEST1_NCRITERIA] = {
                2,           4,          1,           13
            };
            char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
                "mad",       "deranged", "nefarious", "have"
            };
            char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
                "scientist", "robot",    "plot",      "mad"
            };
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                "The mad UCLA scientist unleashed    a deranged robot.") == 2);
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                "**** 2010 ****") == 0);
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                "  What a NEFARIOUS plot!") == 1);
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA, //broke
                "deranged deranged robot deranged robot robot") == 1);
            assert(calculateScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                "Two mad scientists have deranged-robot fever.") == 0);
            cout << "All tests succeeded" << endl;*/

	cerr << "TEST 1" << endl;
	cerr << "======" << endl;
	
	const int TEST1_NCRITERIA = 7;
	int test1dist[TEST1_NCRITERIA] = {
		2,           4,          1,           13,     2,               5,          0
	};
	char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
		"mad",       "deranged", "nefarious", "have", "cra-a-a-a-azy", "deranged", "tron"
	};
	char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
		"scientist", "ROBOT",    "plot",      "mad",  "just like me",  "robot",    "legacy"
	};
	int new_criteria = standardizeCriteria(test1dist, test1w1, test1w2, TEST1_NCRITERIA);
	
	cerr << "test1dist: ";
	printArray(test1dist, new_criteria);
	cerr << "test1w1: ";
	printArray(test1w1, new_criteria);
	cerr << "test1w2: ";
	printArray(test1w2, new_criteria);

	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						   "The mad UCLA scientist unleashed a deranged evil giant robot.") << " ?= " << 2 << endl;
	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						  "The mad UCLA scientist unleashed    a deranged robot.") << " ?= " << 2 << endl;
	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						  "**** 2010 ****") << " ?= " << 0 << endl;
	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						  "  What a NEFARIOUS plot!" )<< " ?= " << 1 << endl;
	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						  "deranged deranged robot deranged robot robot") << " ?= " << 1 << endl;
	cerr << calculateScore(test1dist, test1w1, test1w2, new_criteria,
						  "Two mad scientists have deranged-robot fever.") << " ?= " << 0 << endl;
	
	cerr << endl;
	
	cerr << "TEST 2" << endl;
	cerr << "======" << endl;
	
	const int TEST2_NCRITERIA = 8;
	int test2dist[TEST2_NCRITERIA] = {
		4,      2,        1,        2,          -2,    5,     12,     10
	};
	char test2w1[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
		"that", "pretty", "tron",   "master",  "lols", "f e", "daft", "has"
	};
	char test2w2[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
		"is",   "cool",   "legacy", "PrOgRaM", "cats", "**",  "punk", "is"
	};
	int new_criteria2 = standardizeCriteria(test2dist, test2w1, test2w2, TEST2_NCRITERIA);
	
	cerr << "test2dist: ";
	printArray(test2dist, new_criteria2);
	cerr << "test2w1: ";
	printArray(test2w1, new_criteria2);
	cerr << "test2w2: ";
	printArray(test2w2, new_criteria2);
	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   " Tron Legacy looks like a pretty cool movie. ") << " ?= " << 2 << endl;	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   "master control program is a lols cats.") << " ?= " << 1 << endl;	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   "too bad that master     *** control is stupid.") << " ?= " << 1 << endl;	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   " has a i's.") << " ?= " << 1 << endl;	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   " Tron-Legacy looks like a pretty cool movie. ") << " ?= " << 1 << endl;	
	cerr << calculateScore(test2dist, test2w1, test2w2, new_criteria2,
						   "has is is is has is") << " ?= " << 1 << endl;

	
}