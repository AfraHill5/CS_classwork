//Zach North
//603885768
//CS32 Project 1
//1/17/2012

#include "Arena.h"
#include "Game.h"
#include "globals.h"
#include "History.h"
#include "Player.h"
#include "Robot.h"


#include <ctime>
using namespace std;


int main()
{
      // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 50);

      // Play the game
    g.play();
}
