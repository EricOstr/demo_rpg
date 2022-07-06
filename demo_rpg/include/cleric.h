#pragma once
#include "types.h"
#include "playercharacter.h"

class Cleric : public PlayerCharacterDelegate {
public:
  static const inline welltype BASEHP = (welltype)14u;
  static const inline welltype BASEMP = (welltype)10u;
  static const inline stattype BASESTR = (stattype)3u;
  static const inline stattype BASEINT = (stattype)5u;
  static const inline stattype BASEAGI = (stattype)1u;
  Cleric();
private:
  void level_up() noexcept override;
};