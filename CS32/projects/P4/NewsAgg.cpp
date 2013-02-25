#include "provided.h"
#include "Mapper.h"
#include <string>
#include <algorithm>
using namespace std;

bool KeywordSort(const Keyword& a, const Keyword& b)
{ //sorts by number of uses, except if number is the same -- then sorts by keyword
	if (a.numUses > b.numUses) 
		return true;
	else if (a.numUses < b.numUses)
		return false;
	else 
		return (a.keyword < b.keyword);
}

bool ClusterSort(const Cluster& a, const Cluster& b)
{ //sorts by number of uses, except if number is same -- then sorts by kernel title
	if (a.getNumURLs() > b.getNumURLs())
		return true;
	else if (a.getNumURLs() < b.getNumURLs())
		return false;
	else
		return (a.getTitle() < b.getTitle());
}

class NewsAggregatorImpl
{
public:
    NewsAggregatorImpl();
    void addSourceRSSFeed(string feed);
    int getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords);

private:
	set<string> m_sourceRSSFeeds; //holds the feed URLS
	vector<NewsCluster*> m_cluster; //holds the news clusters
};

NewsAggregatorImpl::NewsAggregatorImpl()
{
}

void NewsAggregatorImpl::addSourceRSSFeed(string feed)
{
	m_sourceRSSFeeds.insert(feed);
}

int NewsAggregatorImpl::getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords)
{
	
	set<string> tempURLs; //this is used to avoid duplicate urls
	StringMapper<string> tempData; //holds data temporarily

	//take all the values from the RSS feeds and insert them into RSSprocessors
	for (set<string>::const_iterator it = m_sourceRSSFeeds.begin(); it != m_sourceRSSFeeds.end(); it++)
	{
		RSSProcessor a(*it); //temp, initialized with the feed url
	
		a.getData(); //connects to each url and stores the stories in the rssprocessor
		//now the processor contains sorted stories and urls
		
		string url; string title;
		bool gotItem = a.getFirstItem(url, title);
		while (gotItem)
		{
			int preURLSetSize = tempURLs.size();
			tempURLs.insert(url); //tries to insert the url into the url set
			if (preURLSetSize != tempURLs.size()) //if the size of tempURLs set has changed, the insertion was successful
				tempData.insert(url, title); //this means the URL has not been used yet so green light to insert the story

			gotItem = a.getNextItem(url, title); //iterates
		}
	} //at this point all of the rss feeds have been sorted into stories, dupes have been removed, and
		//they have all been inserted into tempData.

	//time to cluster them all
	string headline; string url; //holds each story and url from the vector
	tempData.getFirstPair(url, headline);
	NewsCluster* temp;
	for (int i = 0; i < tempData.size(); i++)
	{
		temp = new NewsCluster;
		temp->submitKernelStory(headline, url); 
		m_cluster.push_back(temp); //initializes the cluster vector with a bunch of kernels
		tempData.getNextPair(url, headline); //iterates
	}
	//after this loop runs, m_cluster is a vector of NewsClusters, each cluster containing a single
	//news story as its kernel

	bool continueIteration = true; //this tracks whether or not to stop the next loop
	while (continueIteration)
	{
		continueIteration = false;
		bool c = tempData.getFirstPair(url, headline);
		while (c) //submits every story to every cluster
		{
			for (int j = 0; j < m_cluster.size(); j++)
			{
				int preClusterSize = m_cluster[j]->size(); //tracks whether the cluster accepted the new story
				m_cluster[j]->submitStory(headline, url);
				if (preClusterSize != m_cluster[j]->size()) //if the cluster grew, it accepted the story
					continueIteration = true;
			}
			c = tempData.getNextPair(url, headline);
		}
	}
	//when this loop completes all the clusters will be filled and no longer changing
	//Now, need to get rid of all but one cluster, to be used for rest of function

	set<string> duplicateCheck;
	string identifier = m_cluster[0]->getIdentifier();
	for (int i = 0; i < m_cluster.size(); i++)
	{
		NewsCluster* curr = m_cluster[i];
		int preCheckSize = duplicateCheck.size();
		string currIden = curr->getIdentifier();
		duplicateCheck.insert(currIden);
		if (preCheckSize == duplicateCheck.size()) //if the size of the set didnt change, the identifier is a duplicate
		{
			m_cluster.erase(m_cluster.begin() + i);
			i--;
		}

	} 
	//now have to get all the words from the cluster and count them
	vector<Keyword> wordCount;
	for (int k = 0; k != m_cluster.size(); k++)
	{
		set<string> currentStoryWordCount;
		WordExtractor we(m_cluster[k]->getIdentifier()); //uses the identifier b/c W.E. gets rid of the +s
		string currentWord;
		while (we.getNextWord(currentWord))
		{
			if (currentWord.size() < MIN_WORD_SIZE)
				continue; //skip the words less than 4 letters

			bool found = false;
			for (set<string>::const_iterator it = currentStoryWordCount.begin(); it != currentStoryWordCount.end(); it++)
			{
				if (*it == currentWord) //if the current word is in the vector
				{
					found = true;
					break;
				}
			}

			if (!found) //if word wasn't found, add it to the back
				currentStoryWordCount.insert(currentWord);
		}

		for (set<string>::const_iterator it = currentStoryWordCount.begin(); it != currentStoryWordCount.end(); it++)
		{
			bool found = false;
			for (int p = 0; p < wordCount.size(); p++)
			{
				if (*it == wordCount[p].keyword)
				{
					wordCount[p].numUses++;
					found = true;
				}
			} //else doesnt exist in the wordCount vector yet, so add it
			if (!found)
			{
				Keyword key;
				key.keyword = *it;
				key.numUses = 1;
				wordCount.push_back(key);
			}
		}
	}
	
	//wordCount should contain all the words, grouped into keywords and counts
	int clusterCount = 0;
	for (int i = 0; i < m_cluster.size(); i++)
		clusterCount += m_cluster[i]->size(); //adds every story to the count of total stories
	int minimumStories = clusterCount * thresholdPercentage * .01; //min number of stories required to be passed back

	for (int i = 0; i < m_cluster.size(); i++)
	{
		if (m_cluster[i]->size() >=  minimumStories) // if the current cluster has enough stories, add it to the vector
		{
			string url; string headline;
			m_cluster[i]->getFirstNewsItem(headline, url);
			Cluster temp(headline); //title is the kernel value
			temp.addRelatedURL(url);
			while (m_cluster[i]->getNextNewsItem(headline, url))
				temp.addRelatedURL(url);
			topStories.push_back(temp);
		}
	}
	//now topStories should contain all the cluster stories with their associated urls

	int keywordCount = 0;
	for (int i = 0; i < wordCount.size(); i++)
		keywordCount += wordCount[i].numUses;

	int minimumKeywords = keywordCount * thresholdPercentage * .01;
	for (int i = 0; i < wordCount.size(); i++)
	{
		if (wordCount[i].numUses >= minimumKeywords)
			topKeywords.push_back(wordCount[i]);
	}

	//now have to sort the vectors
	
	sort(topStories.begin(), topStories.end(), ClusterSort);
	sort(topKeywords.begin(), topKeywords.end(), KeywordSort);

    return 0;
}

//******************** NewsAggregator functions *******************************

// These functions simply delegate to NewsAggregatorImpl's functions.

NewsAggregator::NewsAggregator()
{
    m_impl = new NewsAggregatorImpl();
}

NewsAggregator::~NewsAggregator()
{
    delete m_impl;
}

void NewsAggregator::addSourceRSSFeed(string feed)
{
    m_impl->addSourceRSSFeed(feed);
}

int NewsAggregator::getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords)
{
    return m_impl->getTopStoriesAndKeywords(thresholdPercentage, topStories,
                                                                  topKeywords);
}
