#include <iostream>
#include <ctime>
#include "globals.h"
#include "Game.h"
#include "History.h"
using namespace std;

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 100);

      // Play the game
    g.play(); 

}