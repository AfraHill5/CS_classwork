#ifndef GAME_H
#define GAME_H

#include <string>


class Arena; //prototype declaration

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
    std::string takeRobotsTurn();
};


#endif