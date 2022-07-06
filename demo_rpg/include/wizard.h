#pragma once
#include "types.h"
#include "playercharacter.h"

class Wizard : public PlayerCharacterDelegate {
public:
  static const inline welltype BASEHP = (welltype)10u;
  static const inline welltype BASEMP = (welltype)14u;
  static const inline stattype BASESTR = (stattype)1u;
  static const inline stattype BASEINT = (stattype)8u;
  static const inline stattype BASEAGI = (stattype)2u;
  Wizard();
private:
  void level_up() noexcept override;
};