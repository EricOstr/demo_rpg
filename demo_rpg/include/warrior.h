#pragma once
#include "playercharacter.h"

class Warrior : public PlayerCharacterDelegate {
public:
  static const inline welltype BASEHP = (welltype)18u;
  static const inline welltype BASEMP = (welltype)0u;
  static const inline stattype BASESTR = (stattype)6u;
  static const inline stattype BASEINT = (stattype)2u;
  static const inline stattype BASEAGI = (stattype)2u;
  Warrior();
private:
  void level_up() noexcept override;
};