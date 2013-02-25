#include "provided.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class AdHunterImpl
{
public:
    AdHunterImpl(istream& ruleStream);
    void addSeedSite(string site);
    int getBestAdTargets(double minPrice, int pagesPerSite, vector<Match>& matches);

private:
	vector<string> m_seedSites;
	Matcher m_matcher;
};

AdHunterImpl::AdHunterImpl(istream& ruleStream) : m_matcher(ruleStream)
{
	//leave m_seedSites empty because no seeds yet
}

void AdHunterImpl::addSeedSite(string site)
{
	m_seedSites.push_back(site);
}

int AdHunterImpl::getBestAdTargets(double minPrice, int pagesPerSite, vector<Match>& matches)
{
    matches.clear();
	for (int i = 0; i < m_seedSites.size(); i++)
	{
		Crawler c(m_seedSites[i]);
		int page = 0;
		for (Document* d = c.crawl();  page < pagesPerSite && d != NULL; page++, d = c.crawl())
			m_matcher.process(*d,minPrice,matches);
	}

	return matches.size();
}

//******************** AddHunter functions *******************************

// These functions simply delegate to AdHunterImpl's functions.
// You probably don't want to change any of this code.

AdHunter::AdHunter(istream& ruleStream)
{
    m_impl = new AdHunterImpl(ruleStream);
}

AdHunter::~AdHunter()
{
    delete m_impl;
}

void AdHunter::addSeedSite(string site)
{
    return m_impl->addSeedSite(site);
}

int AdHunter::getBestAdTargets(double minPrice, int pagesPerSite, vector<Match>& matches)
{
    return m_impl->getBestAdTargets(minPrice, pagesPerSite, matches);
}
