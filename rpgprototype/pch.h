#pragma once
#include <playercharacter.h>
#include <playableclasses_fwd.h>
#include <monster.h>


char the_map[12][13] =
{ "xxxxxxxxxxxx",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "xxxxxxxxxxxx" };


struct Player {

    PlayerCharacter us;
    int prev_xpos = 3;
    int prev_ypos = 3;
    int xpos = 3;
    int ypos = 3;

    Player(PlayerCharacterDelegate* charclass) : us(charclass) {}
    Player() = delete;
    bool IsAlive() { return (us.GetCurrentHP() > 0); }

};


struct Fightable {

    Monster monster;
    int prev_xpos{};
    int prev_ypos{};
    int xpos{};
    int ypos{};
    int xpworth{};

    Fightable(int hp, int min, int max) : monster(hp, min, max) { xpworth = (hp + min + max) * 2; }
    bool IsAlive() { return (monster.HP.GetCurrent() > 0); }
    Fightable() = delete;
};

