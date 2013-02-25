#include "provided.h"
#include "http.h"
#include <set>
#include <string>
using namespace std;

class CrawlerImpl
{
public:
    CrawlerImpl(string seedSite);
    Document* crawl();

private:
	bool linkHasSameDomain(string link, string url); //self explanatory
	string m_seed;
	set<string> m_linkedSites;
	set<string> m_usedSites;
	set<string>::iterator m_currentSite;
};

CrawlerImpl::CrawlerImpl(string seedSite)
{
	m_seed = seedSite;
	m_linkedSites.insert(m_seed); //seed url is first to be searched
	m_currentSite = m_linkedSites.begin();
	//usedSites holds sites that have already been searched and is empty
}

Document* CrawlerImpl::crawl()
{
	if (m_linkedSites.size() == 0) //ran out of links
		return NULL;

	//m_currentSite points to the current site being checked in the set

	string currText;
	HTTP().get(*m_currentSite, currText); //holds the websites text

	ExtractLinks extractor(currText);

	string linkOnPage;
	while (extractor.getNextLink(linkOnPage))
	{
		if (linkHasSameDomain(linkOnPage, *m_currentSite) &&
			m_usedSites.count(linkOnPage) == 0)
			m_linkedSites.insert(linkOnPage); 
			//get every url from the page and push onto the set
			//if it is a member of the same domain.
			//sets automatically disallow duplicates
	}
	Document* doc = new Document(*m_currentSite, currText);
	
	m_usedSites.insert(*m_currentSite); //move the used site to keep track of it
	m_linkedSites.erase(m_currentSite); //erase from active sites
	m_currentSite = m_linkedSites.begin(); //reset the current site
	return doc;
}

bool CrawlerImpl::linkHasSameDomain(string link, string url)
{
	string domain;
	int charPos;
	if (url.find("http://") == 0) //condition: url starts with http://
		charPos = 7; //skip ahead past the http://
	else
		charPos = 0;

	for (int charPos = 7; charPos < url.size() && url[charPos] != '/'; charPos++)
		//add chars to domain until end of string or / is reached
		domain += url[charPos];
	
	if (domain.size() == 0)
		return false; //there is no explicit domain in url

	return (link.find(domain) != string::npos);
	//true if the domain can be found somewhere in the link string
}


//******************** Crawler functions *******************************

// These functions simply delegate to CrawlerImpl's functions.
// You probably don't want to change any of this code.

Crawler::Crawler(string seedSite)
{
    m_impl = new CrawlerImpl(seedSite);
}

Crawler::~Crawler()
{
    delete m_impl;
}

Document* Crawler::crawl()
{
    return m_impl->crawl();
}
