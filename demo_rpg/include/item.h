#pragma once
#include "buff.h"
#include <string>
#include <typeinfo>





class ItemDelegate {
public:
    std::string Name;
protected:
    ItemDelegate(std::string name) : Name(name) {}
    virtual ~ItemDelegate() = default;

    friend class Item;
};




class EquipmentDelegate : public ItemDelegate {
public:
    const std::uint32_t UniqueId;
    CoreStats Stats;
protected:
    EquipmentDelegate(std::string name, CoreStats cstats);
    virtual ~EquipmentDelegate() = default;
};




class Item final {

public:

    const ItemDelegate* GetData() { return _data; }
    bool GetMarkedForDeletion() const { return _marked_for_deletion; }
    bool GetMarkedAsBackpackRefGone() const { return _marked_as_backpack_ref_gone; }

private:

    ItemDelegate* _data;
    bool _marked_for_deletion = false;
    bool _marked_as_backpack_ref_gone = false;

    Item(ItemDelegate* item) : _data(item) {}
    ~Item() {   // only ItemManger can call destructor
        if (_data) {
          delete _data;
          _data = nullptr;
        }
    }
    friend class ItemManager;
    
};

