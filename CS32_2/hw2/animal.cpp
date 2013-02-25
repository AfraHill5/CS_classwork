
class Animal
{
public:
	Animal(string s) :  m_name(s) {}
	virtual ~Animal() {}
	virtual string move() const {return "walk";}
	string name() const  {return m_name;} 
	virtual string speak() const = 0; 
private:
	string m_name;
};

class Pig : public Animal
{
public:
	Pig(string s, int weight) : Animal(s), m_lbs(weight) {} 
	virtual ~Pig() {cout << "Destroying " << name() << " the pig\n";}
	virtual string speak() const
	{
		if (m_lbs >= 180)
			return "Grunt";
		else
			return "Oink";
	}
private:
	int m_lbs;
};

class Cat : public Animal
{
public:
	Cat(string s) : Animal(s) {}
	virtual ~Cat() {cout << "Destroying " << name() << " the cat\n";}
	virtual string speak() const {return "Meow"; } 
};

class Duck : public Animal
{
public:
	Duck(string s) : Animal(s) {}
	virtual ~Duck() {cout << "Destroying " << name() << " the duck\n"; }
	virtual string move() const {return "swim";} 
	virtual string speak() const {return "Quack";} 
};

