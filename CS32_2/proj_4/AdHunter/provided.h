#ifndef PROVIDED_INCLUDED
#define PROVIDED_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class ExtractLinksImpl;

class ExtractLinks
{
public:
    ExtractLinks(const std::string& pageContents);
    ~ExtractLinks();
    bool getNextLink(std::string& link);
private:
    ExtractLinksImpl* m_impl;
      // We prevent an ExtractLinks object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    ExtractLinks(const ExtractLinks& other);
    ExtractLinks& operator=(const ExtractLinks& other);
};

class DocumentImpl;

class Document 
{
public:
    Document(std::string url, const std::string& text);
    ~Document();
    std::string getURL() const;
    bool contains(std::string word) const;
    bool getFirstWord(std::string& word);
    bool getNextWord(std::string& word);
private:
    DocumentImpl* m_impl;
      // We prevent a Document object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Document(const Document& other);
    Document& operator=(const Document& other);
};

class CrawlerImpl;

class Crawler
{
public:
    Crawler(std::string seedSite);
    ~Crawler();
    Document* crawl();
private:
    CrawlerImpl* m_impl;
      // We prevent a Crawler object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Crawler(const Crawler& other);
    Crawler& operator=(const Crawler& other);
};

class RuleImpl;

class Rule
{
public:
    Rule(std::string ruleText);
    ~Rule();
    Rule(const Rule& other);
    Rule& operator=(const Rule& other);
    std::string getName() const;
    double getDollarValue() const;
    int getNumElements() const;
    std::string getElement(int elementNum) const;
    std::string getAd() const;
    bool match(const Document& doc) const;
private:
    RuleImpl* m_impl;
};

struct Match
{
    std::string url;
    std::string ruleName;
    std::string ad;
    double dollarValue;
};

class MatcherImpl;

class Matcher 
{
public:
    Matcher(std::istream& ruleStream);
    ~Matcher();
    void process(Document& doc, double minPrice, std::vector<Match>& matches) const;
private:
    MatcherImpl* m_impl;
      // We prevent a Matcher object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Matcher(const Matcher& other);
    Matcher& operator=(const Matcher& other);
};

class AdHunterImpl;

class AdHunter
{
public:
    AdHunter(std::istream& ruleStream);
    ~AdHunter();
    void addSeedSite(std::string site);
    int getBestAdTargets(double minPrice, int pagesPerSite, std::vector<Match>& matches);
private:
    AdHunterImpl* m_impl;
      // We prevent an AdHunter object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    AdHunter(const AdHunter& other);
    AdHunter& operator=(const AdHunter& other);
};

class Tokenizer
{
public:
    Tokenizer(const std::string& text, std::string separators)
     : m_text(text), m_separators(separators), m_nextChar(0)
    {}

    bool getNextToken(std::string& token)
    {
          // skip leading separators
        size_t start = m_text.find_first_not_of(m_separators, m_nextChar);
	if (start == std::string::npos)
	{
	    m_nextChar = m_text.size();
	    token.clear();
	    return false;
	}

          // find next separator
	m_nextChar = m_text.find_first_of(m_separators, start+1);
	if (m_nextChar == std::string::npos)
	    m_nextChar = m_text.size();
	token.assign(m_text, start, m_nextChar - start);
	return true;
    }

private:
    std::string m_text;
    std::string m_separators;
    size_t      m_nextChar;
};

#endif // PROVIDED_INCLUDED
