#pragma once
#include "types.h"
#include "pointwell.h"
#include <memory>

class Monster {

public:
    PointWell HP;

    Monster(welltype hp, damagetype min, damagetype max);

    [[nodiscard]] const damagetype Attack() const;
    [[nodiscard]] const damagetype GetMinDamage() const noexcept;
    [[nodiscard]] const damagetype GetMaxDamage() const noexcept;

private:

    damagetype MinDamage, MaxDamage;

    Monster() = delete;
    Monster(const Monster&) = delete;
    Monster(const Monster&&) = delete;
};

