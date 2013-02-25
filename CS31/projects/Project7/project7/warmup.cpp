#include <iostream>
#include <string>

using namespace std;

class Pet
{
  public:
    Pet(string nm, int initialHealth);
    void eat(int amt);
    void play();
    string name() const;
    int health() const;
    bool alive() const;
  private:
    string m_name;
    int m_health;
};

  // Initialize the state of the pet
Pet::Pet(string nm, int initialHealth)
{
    m_name = nm;
    m_health = initialHealth;
}

//increases the pet's health by amt
void Pet::eat(int amt)
{
	m_health += amt;
}

//decreases the pet's health for the energy consumed
void Pet::play()
{
	m_health--;
}

//returns the pet's name
string Pet::name() const
{
	return m_name;
}

//returns the pet's health
int Pet::health() const
{
	return m_health;
}


bool Pet::alive() const
{
	if (m_health > 0)
		return true;
	return false;
}

void reportStatus(const Pet* p)
{
    cout << p->name() << " has health level " << p->health();
    if ( ! p->alive())
        cout << ", so has died";
    cout << endl;
}

void careFor(Pet* p, int d)
{
    if ( ! p->alive())
    {
        cout << p->name() << " is still dead" << endl;
        return;
    }

      // Every third day, you forget to feed your pet
    if (d % 3 == 0)
        cout << "You forgot to feed " << p->name() << endl;
    else
    {
        p->eat(1);  // Feed the pet one unit of food
        cout << "You fed " << p->name() << endl;
    }

    p->play();
    reportStatus(p);
}

int main()
{
    Pet* myPets[2];
    myPets[0] = new Pet("Fluffy", 2);
    myPets[1] = new Pet("Frisky", 4);
    for (int day = 1; day <= 9; day++)
    {
        cout << "======= Day " << day << endl;
        for (int k = 0; k < 2; k++)
            careFor(myPets[k], day);
    }
    cout << "=======" << endl;
    for (int k = 0; k < 2; k++)
    {
        if (myPets[k]->alive())
            cout << "Animal Control has come to rescue "
                 << myPets[k]->name() << endl;
        delete myPets[k];
    }
}

//DESIRED OUTPUT
/*

======= Day 1
You fed Fluffy
Fluffy has health level 2
You fed Frisky
Frisky has health level 4
======= Day 2
You fed Fluffy
Fluffy has health level 2
You fed Frisky
Frisky has health level 4
======= Day 3
You forgot to feed Fluffy
Fluffy has health level 1
You forgot to feed Frisky
Frisky has health level 3
======= Day 4
You fed Fluffy
Fluffy has health level 1
You fed Frisky
Frisky has health level 3
======= Day 5
You fed Fluffy
Fluffy has health level 1
You fed Frisky
Frisky has health level 3
======= Day 6
You forgot to feed Fluffy
Fluffy has health level 0, so has died
You forgot to feed Frisky
Frisky has health level 2
======= Day 7
Fluffy is still dead
You fed Frisky
Frisky has health level 2
======= Day 8
Fluffy is still dead
You fed Frisky
Frisky has health level 2
======= Day 9
Fluffy is still dead
You forgot to feed Frisky
Frisky has health level 1
=======
Animal Control has come to rescue Frisky

*/