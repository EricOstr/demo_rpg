#pragma once
#include "types.h"
#include "playercharacter.h"

class Rogue : public PlayerCharacterDelegate {
public:
  static const inline welltype BASEHP = (welltype)12u;
  static const inline welltype BASEMP = (welltype)0u;
  static const inline stattype BASESTR = (stattype)3u;
  static const inline stattype BASEINT = (stattype)3u;
  static const inline stattype BASEAGI = (stattype)6u;
  Rogue();
private:
  void level_up() noexcept override;
};