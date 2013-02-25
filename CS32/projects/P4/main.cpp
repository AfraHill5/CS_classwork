#include "provided.h"
#include "Mapper.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, char* argv[])
{
	//DEBUG
	/*RSSProcessor temp("http://www.un.org/apps/news/rss/rss_top.asp"); //((TEST))
	temp.getData();
	string headline;
	string url;
	bool gotItem = temp.getFirstItem(url, headline);
	while (gotItem)
	{
		cout << "Headline: " << headline << endl
			  << "URL of story: " << url << endl << endl;
		 gotItem = temp.getNextItem(url, headline);
	}  

	NewsCluster n;
	n.submitKernelStory("testA test testB testC testD", "www.url.com");
	n.submitStory("testTHIS testTHAT a b c", "www.abc.com"); //shouldnt be included
	n.submitStory("testTHAT testME testIT g h i", "www.google.com"); //shouldnt be included
	n.submitStory("testA test testC testG", "www.amazon.com"); //SHOULD be included
	n.submitStory("testB testC testA", "www.gmail.com"); //SHOULD be included
	n.submitStory("testC testD test", "www.lolz.com"); //SHOULD be included

	string abc = n.getIdentifier();
	cout << abc << endl;

	n.getFirstNewsItem(headline, url);
	cout << "Kernel headline: " << headline << endl << "Kernel URL: " << url << endl;
	while(n.getNextNewsItem(headline, url))
		cout << "Headline: " << headline << endl << "URL: " << url << endl;

	cout << "Cluster size: " << n.size() << endl;

	StringMapper<string> SM;
	SM.insert("Headline 1", "URL1");
	SM.insert("Headline 2", "URL2");
	SM.insert("Headline 3", "URL3");
	SM.insert("Headline 1", "URL4");
	SM.insert("Headline 1", "URL1");
	SM.insert("abc", "URL4");
	SM.insert("def", "URL5");

	string changethis = "changethis";
	SM.find("abc", changethis);
	cout << "URL4 ?= " << changethis << endl;

	string from; string to; 
	SM.getFirstPair(from, to);
	cout << "first headline: " << from << endl << "first url: " << to << endl;
	while (SM.getNextPair(from, to))
		cout << "next headline: " << from << endl << "next url: " << to << endl;

	int s = SM.size();
	cout << "size: " << s << endl; 

	NewsAggregator a;
	a.addSourceRSSFeed("http://www.un.org/apps/news/rss/rss_top.asp");
	vector<Cluster> c;
	vector<Keyword> k;

	a.getTopStoriesAndKeywords(1, c, k);
	 */



	string rssURL = "http://feeds.wired.com/wired/index?format=xml";
	RSSProcessor rssp(rssURL);
	rssp.getData();
	string headline, url;
	bool gotItem = rssp.getFirstItem(url, headline);
	while (gotItem)
	{
	cerr << "Headline: " << headline << endl << "URL of story: " << url << endl << endl;
	gotItem = rssp.getNextItem(url, headline);
	}
	NewsCluster nci;
	nci.submitKernelStory("green cheese found on the moon",
		"http://latimes.com/green-cheese-found.html");
	nci.submitStory("green eggs and ham found to annoy astronauts", "http://latimes.com/green-eggs-and-ham.html");
	nci.submitStory("green astronauts eat cheese on the moon", "http://latimes.com/astronauts.html");
	nci.submitStory("green food coloring annoys moon astronauts", "http://latimes.com/green-coloring.html");
	gotItem = nci.getFirstNewsItem(headline, url);
	while (gotItem)
	{
		cerr << "Headline: " << headline << endl << "URL of story: " << url << endl << endl;
		gotItem = nci.getNextNewsItem(url, headline);
	}
	cerr << nci.getIdentifier() << endl;
	NewsAggregator nai;
	vector<Cluster> cl;
	vector<Keyword> kw;
	nai.addSourceRSSFeed("http://rss.macworld.com/macworld/feeds/main");
	nai.addSourceRSSFeed("http://pipes.yahoo.com/pipes/pipe.run?_id=f2f4c27df76c222acfec73277a647631&_render=rss");
	nai.addSourceRSSFeed("http://feeds.pheedo.com/appleinsider");
	nai.addSourceRSSFeed("http://feeds.feedburner.com/macstoriesnet?format=xml");
	nai.getTopStoriesAndKeywords(2, cl, kw);
	url.clear();
	for (int i = 0; i < cl.size(); i++)
	{
		cerr << cl[i].getNumURLs() << " " << cl[i].getTitle() << endl;
		gotItem = cl[i].getFirstURL(url);
		while (gotItem)
		{
			cerr << ' ' << url << endl;
			gotItem = cl[i].getNextURL(url);
		}
		cerr << endl;
	}
	cerr << endl << endl;
	for (int i = 0; i < kw.size(); i++)
	{
		cerr << kw[i].keyword << " " << kw[i].numUses << endl;
	}
	StringMapper<string> sm;
	sm.insert("Zach", "gay");
	sm.insert("Zachary", "gayer");
	sm.insert("Steven", "awesome");
	string from, to;
	gotItem = sm.getFirstPair(from, to);
	while (gotItem)
	{
		cerr << from << " -> " << to << endl;
		gotItem = sm.getNextPair(from, to);
	}
}
