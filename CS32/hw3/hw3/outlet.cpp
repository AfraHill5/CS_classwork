//Zach North
//603 885 768
//HW3, #1

#include <string>
#include <iostream>
using namespace std;

class Outlet
{
public:
	Outlet(const string& name) {m_name = name;}; 
	virtual ~Outlet() {};
	virtual string connect() const = 0;
	string id() const {return m_name;};
	virtual string transmit(string msg) const;
private:
	string m_name;
};

string Outlet::transmit(string msg) const
{
	string temp = "text: ";
	temp += msg;
	return temp;
}

string Outlet::connect() const
{
	return m_name;
}


class TwitterAccount : public Outlet
{
public:
	TwitterAccount(string name);
	virtual ~TwitterAccount();
	virtual string connect() const;
};

TwitterAccount::~TwitterAccount()
{
	cout << "Destroying the Twitter account " << id() << "." << endl;
}

TwitterAccount::TwitterAccount(string name) : Outlet(name)
{}

string TwitterAccount::connect() const
{
	return "Tweet";
}

class FacebookAccount : public Outlet
{
public:
	FacebookAccount(string name);
	~FacebookAccount();
	virtual string connect() const;
};

FacebookAccount::FacebookAccount(string name) : Outlet(name)
{}

FacebookAccount::~FacebookAccount()
{
	cout << "Destroying the Facebook account " << id() << "." << endl;
}

string FacebookAccount::connect() const
{
	return "Write to wall";
}

class Phone : public Outlet
{
public:
	Phone(string number, int type);
	~Phone();
	virtual string connect() const;
	virtual string transmit(string msg) const;
private:
	int m_preferredType;
};

Phone::Phone(string name, int type) : Outlet(name)
{
	m_preferredType = type;
}

Phone::~Phone()
{
	cout << "Destroying phone " << id() << "." << endl;
}

string Phone::connect() const
{
	return "Call";
}


string Phone::transmit(string msg) const
{
	if (m_preferredType == VOICE)
	{
		string temp = "voice: ";
		temp += msg;
		return temp;
	}

	else
	{
		string temp = "text: ";
		temp += msg;
		return temp;
	}
}

