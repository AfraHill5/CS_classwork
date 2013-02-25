#include "provided.h"
#include "MyHashMap.h"
#include <string>
#include <algorithm>
using namespace std;

class DocumentImpl 
{
public:
    DocumentImpl(string url, const string& text);
    string getURL() const;
    bool contains(string word) const;
    bool getFirstWord(string& word);
    bool getNextWord(string& word);

public:
	string m_url;
	string m_source; //holds the source text of the document
	MyHashMap<int> m_map; // maps all words in the document to their frequency
};

DocumentImpl::DocumentImpl(string url, const string& text) : m_map()
{
	m_url = url;
	m_source = text;

	string s;

	Tokenizer t(text, " ,!.\"\t\n\\/{}()[]+-<>:;=_@#$%&*?~!^'"); //lots of different seperators
	while (t.getNextToken(s))
	{
			//convert to all lower case to make things simple
		transform(s.begin(), s.end(), s.begin(), tolower);
		int total;
		int* m = m_map.find(s);
		if (m == NULL)
			total = 0;
		else
			total = *m;
		//gets the value in the map so it isn't overwritten accidentally

		m_map.associate(s, total+1);
		//pushes all words onto the hash map, and increments 
		//their occurance counter if they already exist in the map

	}
}

string DocumentImpl::getURL() const
{
    return m_url;
}

bool DocumentImpl::contains(string word) const
{
    return (m_map.find(word) != NULL);  //delegates task to hashmap
}

bool DocumentImpl::getFirstWord(string& word)
{
    return (m_map.getFirst(word)); //delegates to the hashmap
}

bool DocumentImpl::getNextWord(string& word)
{
    return (m_map.getNext(word));  // This is not always correct; it's just here to compile.
}

//******************** Document functions *******************************

// These functions simply delegate to DocumentImpl's functions.
// You probably don't want to change any of this code.

Document::Document(string url, const string& text)
{
    m_impl = new DocumentImpl(url, text);
}

Document::~Document()
{
    delete m_impl;
}

string Document::getURL() const
{
    return m_impl->getURL();
}

bool Document::contains(string word) const
{
    return m_impl->contains(word);
}

bool Document::getFirstWord(string& word)
{
    return m_impl->getFirstWord(word);
}

bool Document::getNextWord(string& word)
{
    return m_impl->getNextWord(word);
}
