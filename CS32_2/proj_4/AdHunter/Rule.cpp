#include "provided.h"
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class RuleImpl
{
public:
    RuleImpl(string ruleText);
    string getName() const;
    double getDollarValue() const;
    int getNumElements() const;
    string getElement(int elementNum) const;
    string getAd() const;
    bool match(const Document& doc) const;

private:
	string m_name;
	double m_dollarValue;
	vector<string> m_elements;
	string m_ad;

};

RuleImpl::RuleImpl(string ruleText)
{
	int i = 0;
	for (i; i < 13; i++)
		m_name += ruleText[i];
	
	i+= 2; //lines up with the price element of ruleText
	
	char tempDollarVal[8];
	int x = 0;
	while (ruleText[i] != ' ')
	{
		tempDollarVal[x] = ruleText[i];
		i++;
		x++;
	}
	m_dollarValue = atof(tempDollarVal);

	i++;
	while (ruleText[i] != '>') //getting the elements
	{
		string temp = "";
		while(ruleText[i] != ' ') //skip spaces
		{
			temp += ruleText[i];
			i++;
		}
		if (temp.size() > 0) //if there was a word parsed
			m_elements.push_back(temp);
		i++; //space, go to next 
	}

	i+= 2; //skipping the "> "

	while (i < ruleText.size()) //the rest of the string is the ad
	{
		m_ad += ruleText[i];
		i++;
	}
}

string RuleImpl::getName() const
{
    return m_name;
}

double RuleImpl::getDollarValue() const
{
    return m_dollarValue;
}

int RuleImpl::getNumElements() const
{
    return m_elements.size();
}

string RuleImpl::getElement(int elementNum) const
{
    return m_elements[elementNum];
}

string RuleImpl::getAd() const
{
    return m_ad;
}

bool RuleImpl::match(const Document& doc) const
{
	int i = 0;
	stack<string> operationStack; //used for postfix operation
	string curr;
	for (i; i < m_elements.size(); i++)
	{
		curr = m_elements[i];
		if (curr == "|" || curr == "&") //encountered an operator
		{
			string firstOperand = operationStack.top();
			operationStack.pop();
			string secondOperand = operationStack.top();
			operationStack.pop();

			//convert to all lower case before operation
			transform(firstOperand.begin(), firstOperand.end(), 
						firstOperand.begin(), tolower);
			transform(secondOperand.begin(), secondOperand.end(), 
				secondOperand.begin(), tolower);

			if (firstOperand == "" || secondOperand == "") //invalid expression
				return false; //check this later, should set the rule to invalid
			
			if (curr == "|") //operation "OR"
			{
				if (!(doc.contains(firstOperand) || doc.contains(secondOperand)))
					return false;
				else //push a contained value so it will evaluate to "true" later
				{
					if (doc.contains(firstOperand))		
						operationStack.push(firstOperand);
					else
						operationStack.push(secondOperand);
				}
			}

			else //curr == "&". operation "AND"
			{
				if (!(doc.contains(firstOperand)))
					operationStack.push(firstOperand);
					//if it does not contain the first operand, push it for a "false" value
				else
					operationStack.push(secondOperand);
					//if it does contain the first operand, push the second for correct "value"
			}
		}
		else //encountered an operand
			operationStack.push(curr);
	}
	if (operationStack.size() > 1) 
		return false; //something went wrong, most likely malformed postfix exp.
	else if (operationStack.size() == 1) //no operators, just checking one word
		return (doc.contains(operationStack.top()));
	else
		return false; //no words to check
}

//******************** Rule functions *******************************

// These functions simply delegate to RuleImpl's functions.
// You probably don't want to change any of this code.

Rule::Rule(string ruleText)
{
    m_impl = new RuleImpl(ruleText);
}

Rule::~Rule()
{
    delete m_impl;
}

string Rule::getName() const
{
    return m_impl->getName();
}

double Rule::getDollarValue() const
{
    return m_impl->getDollarValue();
}

int Rule::getNumElements() const
{
    return m_impl->getNumElements();
}

string Rule::getElement(int elementNum) const
{
    return m_impl->getElement(elementNum);
}

string Rule::getAd() const
{
    return m_impl->getAd();
}

bool Rule::match(const Document& doc) const
{
    return m_impl->match(doc);
}
