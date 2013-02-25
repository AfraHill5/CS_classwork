#include "provided.h"
#include <string>
using namespace std;


//Not tested, needs testing (3/9 11:40pm)
class ExtractLinksImpl
{
public:
    ExtractLinksImpl(const string& pageContents);
    bool getNextLink(string& link);

private:
	string m_page; //holds the webpage being scanned
	int m_currentChar; //index of the current spot being scanned in the page
};

ExtractLinksImpl::ExtractLinksImpl(const string& pageContents)
{
	m_page = pageContents;
	m_currentChar = 0;
}

bool ExtractLinksImpl::getNextLink(string& link)
{
	while (m_currentChar < m_page.size())
	{
		if (m_page.substr(m_currentChar, 9) == "<a href=\"") //anchor entrance
		{
			link = ""; //clear passed in string only if link is found
			m_currentChar += 9; //line up with first character
			while (m_page[m_currentChar] != '"')
			{
				link += m_page[m_currentChar]; //add each character of the link until reached another "
				m_currentChar++;
			}
			return true;
		}
		else //different type of tag
			m_currentChar++;
	}
	return false; //reached the end, no links
}

//******************** ExtractLink functions *******************************

// These functions simply delegate to ExtractLinksImpl's functions.
// You probably don't want to change any of this code.

ExtractLinks::ExtractLinks(const string& pageContents)
{
    m_impl = new ExtractLinksImpl(pageContents);
}

ExtractLinks::~ExtractLinks()
{
    delete m_impl;
}

bool ExtractLinks::getNextLink(string& link)
{
    return m_impl->getNextLink(link);
}
