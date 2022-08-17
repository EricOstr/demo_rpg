#include "statblock.h"

StatBlock::StatBlock(stattype s, stattype i, stattype a, stattype arm, stattype elres){
    base.Strength = s;
    base.Intellect = i;
    base.Agility = a;
    base.Armor = arm;
    base.ElementRes = elres;
}

[[nodiscard]] const stattype StatBlock::GetBaseStrength() const noexcept { return   base.Strength; }
[[nodiscard]] const stattype StatBlock::GetBaseIntellect() const noexcept { return  base.Intellect; }
[[nodiscard]] const stattype StatBlock::GetBaseAgility() const noexcept { return    base.Agility; }
[[nodiscard]] const stattype StatBlock::GetBaseArmor() const noexcept { return      base.Armor; }
[[nodiscard]] const stattype StatBlock::GetBaseElementRes() const noexcept { return base.ElementRes; }

[[nodiscard]] const stattype StatBlock::GetTotalStrength() const noexcept { return   base.Strength + fromBuffs.Strength; }
[[nodiscard]] const stattype StatBlock::GetTotalIntellect() const noexcept { return  base.Intellect + fromBuffs.Intellect; }
[[nodiscard]] const stattype StatBlock::GetTotalAgility() const noexcept { return    base.Agility + fromBuffs.Agility; }
[[nodiscard]] const stattype StatBlock::GetTotalArmor() const noexcept { return      base.Armor + fromBuffs.Armor; }
[[nodiscard]] const stattype StatBlock::GetTotalElementRes() const noexcept { return base.ElementRes + fromBuffs.ElementRes; }

void StatBlock::add_or_refresh_buff(Buff b) {
    for (Buff& _buff : Buffs) {
        if (b.Name == _buff.Name) {
            _buff.Duration = b.Duration;
            return;
        }
    }
    Buffs.push_back(b);
    recalculate_buffs();
}
void StatBlock::increase_stats(stattype s, stattype i, stattype a, stattype arm, stattype elres) {
  base.Strength += s;
  base.Intellect += i;
  base.Agility += a;
  base.Armor += arm;
  base.ElementRes += elres;
}
void StatBlock::increase_stats(CoreStats cs) {
  base += cs;
}
void StatBlock::recalculate_buffs() {
  CoreStats tmp_total;
  for (const Buff& b : Buffs) {
    if (b.isDebuff) tmp_total -= b.BuffedStats;
    else tmp_total += b.BuffedStats;
  }
  fromBuffs = tmp_total;
}