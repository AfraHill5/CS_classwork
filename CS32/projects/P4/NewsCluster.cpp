#include "provided.h"
#include "Mapper.h"
#include <string>
using namespace std;


class NewsClusterImpl
{
public:
    NewsClusterImpl();
    bool submitKernelStory(string headline, string url);
    bool submitStory(string headline, string url);
    string getIdentifier() const;
    bool getFirstNewsItem(string& headline, string& url);
    bool getNextNewsItem(string& headline, string& url);
    int size() const;

private:
	StringMapper<string> m_cluster; //holds the cluster stories
	string m_kernel; //holds the initial kernel story for reference
	set<string> m_headlineSet; //holds the headlines for alphabetical reference
};

NewsClusterImpl::NewsClusterImpl()
{
}

bool NewsClusterImpl::submitKernelStory(string headline, string url)
{
	if (m_kernel != "") //if a kernel already exists
		return false;
	m_cluster.insert(headline, url);
	m_kernel = headline; //keeps track of the kernel story
	m_headlineSet.insert(headline); //set tracks only headlines
	return true;
}

bool NewsClusterImpl::submitStory(string headline, string url)
{
	//breaks the inputted headline into word chunks, and stores them in a set.
	WordExtractor current(headline);
	string tempCurr;
	set<string> concatenatedCurrentHeadline;
	while(current.getNextWord(tempCurr))
	{
		if (tempCurr.size() >= MIN_WORD_SIZE)
			concatenatedCurrentHeadline.insert(tempCurr);
	}
	
	string from; string to; //strings to hold the values from the cluster
	m_cluster.getFirstPair(from, to);

	do //repeats this step for every story in the cluster
	{
		WordExtractor base(from);
		//use wordextractor to split the current story up into words and stores them in a seperate set
		string tempBase;
		set<string> concatenatedBaseHeadline;
		while (base.getNextWord(tempBase))
		{
			if (tempBase.size() >= MIN_WORD_SIZE)
				concatenatedBaseHeadline.insert(tempBase); 
		}
	
		//now we have 2 sets containing all the words greater than 4 letters in the current word in the cluster
		//and the compared headline
		int identicalWordCount = 0; //counter to keep track of the matching words
		for (set<string>::const_iterator it1 = concatenatedBaseHeadline.begin(); it1 != concatenatedBaseHeadline.end(); it1++)
		{
			for (set<string>::const_iterator it2 = concatenatedCurrentHeadline.begin(); it2 != concatenatedCurrentHeadline.end(); it2++)
			{
				if (*it1 == *it2)
				{
					identicalWordCount++;
					break;
				}
			}
		}
		if (identicalWordCount >= REQUIRED_WORDS_IN_COMMON) //if the current headline has enough in common with the cluster headline
		{
			m_cluster.insert(headline, url);
			m_headlineSet.insert(headline);
			return true; //value was successfully inserted
		}
	} while (m_cluster.getNextPair(from, to));
	return false; //didn't insert the value
}

string NewsClusterImpl::getIdentifier() const
{
    string holder;
	for (set<string>::const_iterator it = m_headlineSet.begin(); it != m_headlineSet.end(); it++)
		holder += *it + "+";
	holder.erase(holder.size()-1); //gets rid of that last +
	return holder;
}

bool NewsClusterImpl::getFirstNewsItem(string& headline, string& url)
{
	return (m_cluster.getFirstPair(headline, url) );
}

bool NewsClusterImpl::getNextNewsItem(string& headline, string& url)
{
    return (m_cluster.getNextPair(headline, url) );
}

int NewsClusterImpl::size() const
{
    return m_cluster.size();
}

//******************** NewsCluster functions **********************************

// These functions simply delegate to NewsClusterImpl's functions.

NewsCluster::NewsCluster()
{
    m_impl = new NewsClusterImpl();
}

NewsCluster::~NewsCluster()
{
    delete m_impl;
}

NewsCluster::NewsCluster(const NewsCluster& other)
{
    m_impl = new NewsClusterImpl(*other.m_impl);
}

NewsCluster& NewsCluster::operator=(const NewsCluster& rhs)
{
    if (this != &rhs)
    {
        NewsCluster temp(rhs);
        std::swap(m_impl, temp.m_impl);
    }
    return *this;
}

bool NewsCluster::submitKernelStory(string headline, string url)
{
    return m_impl->submitKernelStory(headline, url);
}

bool NewsCluster::submitStory(string headline, string url)
{
    return m_impl->submitStory(headline, url);
}

string NewsCluster::getIdentifier() const
{
    return m_impl->getIdentifier();
}

bool NewsCluster::getFirstNewsItem(string& headline, string& url)
{
    return m_impl->getFirstNewsItem(headline, url);
}

bool NewsCluster::getNextNewsItem(string& headline, string& url)
{
    return m_impl->getNextNewsItem(headline, url);
}

int NewsCluster::size() const
{
    return m_impl->size();
}
