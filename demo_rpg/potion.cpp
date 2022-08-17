#include "potion.h"


Potion::Potion(std::string name, welltype hp_heal, itemcount quant, Buff* buf)
        : ItemDelegate(name), HealAmount(hp_heal), Quantity(quant), _buff(buf) {}

Potion::~Potion() {  // only ItemManger can clean this up
    if (_buff) {
        delete _buff;
        _buff = nullptr;
    }
}

[[nodiscard]] const Buff* Potion::GetBuff() const noexcept { return _buff; }

void Potion::SetBuff(Buff* new_buff) {
  if (_buff) {
    delete _buff;
    _buff = nullptr;
  }
  _buff = new_buff;
}

