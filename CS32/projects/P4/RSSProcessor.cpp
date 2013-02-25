#include "provided.h"
#include "http.h"
#include "Mapper.h"
#include <string>
using namespace std;

class RSSProcessorImpl
{
public:
    RSSProcessorImpl(string rssURL);
    bool getData();
    bool getFirstItem(string& link, string& title);
    bool getNextItem(string& link, string& title);

private:
	string rawInput; //holds the raw website input
	StringMapper<string> m_stories; //holds the story input
};

RSSProcessorImpl::RSSProcessorImpl(string rssURL)
{
	HTTP().get(rssURL, rawInput); //copies the inputted rss feed raw into rawInput string
}

bool RSSProcessorImpl::getData()
{
    //responsible for parsing through the source of the XML linked website and 
	//extracts all the news stories from the page.

	size_t begin = rawInput.find("<item>");
	string temp;
	while (begin != string::npos) //ends at the end of the string
	{
		//finds the end of the item
		size_t end = rawInput.find("</item>", begin);
		//copies all of the item into a string.
		for (int i = int(begin) + 6 /*length of "<item>"*/; i < int(end); i++)
			temp += rawInput[i];
		begin = rawInput.find("<item>", end);
	}
	//at this point all the code has been added into temp.

	vector<string> titles;
	vector<string> links;

	begin = temp.find("<title>", 0);
	size_t end = begin;
	while (begin != string::npos)
	{
		begin = temp.find("<title>", end);
		end = temp.find("</title>", begin);
		if (begin == string::npos)
			break; //reached the end

		//finds the end of the titles
		string a;
		for (int k = int(begin) + 7 /*length of "<title>"*/; k < int(end); k++)
			a += temp[k];
		titles.push_back(a);
	}

	begin = temp.find("<link>", 0);
	end = begin;
	while (begin != string::npos)
	{
		begin = temp.find("<link>", end);
		end = temp.find("</link>", begin);
		if (begin == string::npos)
			break;
		//finds the end of the links
		string b;
		for (int k = int(begin) + 6 /*length of "<link>"*/; k < int(end); k++)
			b += temp[k];
		links.push_back(b);
	}

	if (titles.size() != links.size())
		//something went wrong because we parsed more links than stories.
		return false;
	for (int i = 0; i < titles.size(); i++) //pushes all of the data into private member storage
	{
		m_stories.insert(links[i], titles[i]);
	}
	return true;
}

bool RSSProcessorImpl::getFirstItem(string& link, string& title)
{
    return ( m_stories.getFirstPair(link, title) );
}

bool RSSProcessorImpl::getNextItem(string& link, string& title)
{
    return ( m_stories.getNextPair(link, title) );
}

//******************** RSSProcessor functions **********************************

// These functions simply delegate to RSSProcessorImpl's functions.

RSSProcessor::RSSProcessor(string rssURL)
{
    m_impl = new RSSProcessorImpl(rssURL);
}

RSSProcessor::~RSSProcessor()
{
    delete m_impl;
}

bool RSSProcessor::getData()
{
    return m_impl->getData();
}

bool RSSProcessor::getFirstItem(string& link, string& title)
{
    return m_impl->getFirstItem(link, title);
}

bool RSSProcessor::getNextItem(string& link, string& title)
{
    return m_impl->getNextItem(link, title);
}
