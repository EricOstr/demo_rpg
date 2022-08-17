#pragma once
#include <playercharacter.h>
#include <playableclasses_fwd.h>
#include <monster.h>
#include <iostream>


struct Entity {
    virtual void fn(){};
};




struct Block : public Entity {};





void clear(){
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

struct Player : public Entity {

    PlayerCharacter us;
    int prev_xpos = 3;
    int prev_ypos = 3;
    int xpos = 3;
    int ypos = 3;

    Player(PlayerCharacterDelegate* charclass) : us(charclass) {}
    Player() = delete;
    bool IsAlive() { return (us.GetCurrentHP() > 0); }

};


struct Fightable : Entity {

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

