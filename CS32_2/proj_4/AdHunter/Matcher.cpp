#include "provided.h"
#include "MyHashMap.h"
#include <iostream>
#include <vector>
#include <algorithm> //for sort
using namespace std;

/* struct Match {
 *   string url;
 *   string ruleName;
 *   double dollarValue;
 *   string ad;  
 *   };   */

bool MatchSort(const Match& m1, const Match& m2)
{
	return (m1.dollarValue > m2.dollarValue);
}

class MatcherImpl
{
public:
    MatcherImpl(istream& ruleStream);
    void process(Document& doc, double minPrice, vector<Match>& matches) const;

private:
	vector<Rule*> m_ruleVector;

	vector<Rule*> findRuleSubset(Document& doc) const;	
	bool match(Rule* rule, Document doc);
};

MatcherImpl::MatcherImpl(istream& ruleStream)
{
	string s;
	while (getline(ruleStream, s))
	{
		Rule* r = new Rule(s);
		m_ruleVector.push_back(r); //pushes every line into vector as a Rule object
	}
}

void MatcherImpl::process(Document& doc, double minPrice, vector<Match>& matches) const
{
	vector<Rule*> applicableRules = findRuleSubset(doc);
	//gets the applicable rules to doc
	for (int i = 0; i < applicableRules.size(); i++)
	{
		if (applicableRules[i]->match(doc) &&
			applicableRules[i]->getDollarValue() >= minPrice)
		{ //rule match, add to matches vector
			Match m;
			m.url = doc.getURL();
			m.dollarValue = applicableRules[i]->getDollarValue();
			m.ruleName = applicableRules[i]->getName();
			m.ad = applicableRules[i]->getAd();

			matches.push_back(m);
		}
	}
	//need to sort the matches before returning
	sort(matches.begin(), matches.end(), MatchSort);
}

vector<Rule*> MatcherImpl::findRuleSubset(Document& doc) const
{
	vector<Rule*> matchedRules;
	string currWord;
	for (int i = 0; i < m_ruleVector.size(); i++)
	{
		for (int j = 0; j < m_ruleVector[i]->getNumElements(); j++)
		{
			if (doc.contains(m_ruleVector[i]->getElement(j)))//match
				matchedRules.push_back(m_ruleVector[i]);
		}
	}
	return matchedRules;
}

//******************** Matcher functions *******************************

// These functions simply delegate to MatcherImpl's functions.
// You probably don't want to change any of this code.

Matcher::Matcher(istream& ruleStream)
{
    m_impl = new MatcherImpl(ruleStream);
}

Matcher::~Matcher()
{
    delete m_impl;
}

void Matcher::process(Document& doc, double minPrice, vector<Match>& matches) const
{
    m_impl->process(doc, minPrice, matches);
}
