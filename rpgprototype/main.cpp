#include "pch.h"
#include <random.h>
#include <item.h>
#include <item_manager.h>
#include <thread>
#include <iostream>
#include <unordered_set>
#include <thread>
#include <chrono>

Player* MainCharacter = nullptr;

int num_monsters = 3;
int monsters_defeated = 0;

std::unordered_set<Fightable*> monster_collection;
Entity* ptr_map[12][13]{};
std::vector<std::thread> monster_threads;


std::mutex gLock;

bool end_game;





void showmap() {
    // Print to terminal based on pointer_map

    clear();
    for(int i=0; i<12; i++){
        for(int j=0; j<13; j++){
            if(dynamic_cast<Block*>(ptr_map[i][j]))
                std::cout<<'x';
            else if(dynamic_cast<Fightable*>(ptr_map[i][j]) && dynamic_cast<Fightable*>(ptr_map[i][j])->IsAlive())
                std::cout<<'M';
            else if(dynamic_cast<Player*>(ptr_map[i][j]) && dynamic_cast<Player*>(ptr_map[i][j])->IsAlive())
                std::cout<<'P';
            else
                std::cout<< " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n' << "move(wasd), inv(i), charsheet(c): \n";
}


void fill_blocks_ptr_map(){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 13; j++) {
            if(i==0 || i==11) ptr_map[i][j] = new Block();
            if(j==0 || j==12) ptr_map[i][j] = new Block();
        }
    }
}



void display_character_sheet() {
  clear();
  std::cout
    << "CHARACTER SHEET\n"
    << "---------------\n\n"
    << "Level: " << MainCharacter->us.GetLevel() << '\n'
    << "XP: " << MainCharacter->us.GetCurrentEXP() << '\n'
    << "Required next level (XP): " << MainCharacter->us.GetEXPToNextLevel() << '\n'
    << "HP: " << MainCharacter->us.GetCurrentHP() << "/" << MainCharacter->us.GetMaxHP() << '\n'
    << "Armor: " << MainCharacter->us.GetTotalArmor() << "  Resistance: " << MainCharacter->us.GetTotalElementRes() << '\n'
    << "STR: " << MainCharacter->us.GetTotalStrength() << " AGI: " << MainCharacter->us.GetTotalAgility() << " INT: " << MainCharacter->us.GetTotalIntellect() << '\n'
    << "\n\nEquipped Gear:\n\n";
  if (MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)) {
    std::string weapon_name = MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->Name;
    std::cout << "MELEE: " << weapon_name << "  damage(" << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MinDamage << '-' << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)->MaxDamage << ")\n";
  }
  if (MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)) {
    std::string weapon_name = MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->Name;
    std::cout << "RANGED: " << weapon_name << "  damage(" << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MinDamage << '-' << MainCharacter->us.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::RANGED)->MaxDamage << ")\n";
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HEAD)->Name;
    std::cout << "HEAD: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::NECK)->Name;
    std::cout << "NECK: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::CHEST)->Name;
    std::cout << "CHEST: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::HANDS)->Name;
    std::cout << "HANDS: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING1)->Name;
    std::cout << "RING1: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::RING2)->Name;
    std::cout << "RING2: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::LEGS)->Name;
    std::cout << "LEGS: " << armor_name << '\n';
  }
  if (MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)) {
    std::string armor_name = MainCharacter->us.GetEquippedArmorAt((unsigned long long)ARMORSLOT::FEET)->Name;
    std::cout << "FEET: " << armor_name << '\n';
  }

  std::cin.ignore(100, '\n');
  std::cout << "\npress enter to continue\n";
  char c = getchar();
}



void open_inventory() {

  bool done = false;
  int selected_item_num = 0;

  while (!done) {
    clear();
    std::vector<Item*> list_of_items = MainCharacter->us.GetBackpackList();
    std::cout
      << "CURRENT INVENTORY\n"
      << "-----------------\n\n";
    int items_in_backpack_count = 0;

    // Print items
    for (const auto& item : list_of_items) {

      if (selected_item_num == items_in_backpack_count) std::cout << "> ";
      else std::cout << "  ";

      std::cout << item->GetData()->Name << '\n';
      if (ItemManager::IsItemPotion(item)) {
        Potion* potion = nullptr;
        ItemManager::CastItemToPotion(item, potion);
        if (potion) std::cout << "    Quantity: " << potion->Quantity << '\n';
      }
      items_in_backpack_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use\n";
    char c = getchar();
    switch (c) {
    case 'd':
      done = true;
      break;
    case 'w':
      selected_item_num--;
      if (selected_item_num < 0)
        selected_item_num = 0;
      break;
    case 's':
      selected_item_num++;
      if (selected_item_num > list_of_items.size() - 1)
        selected_item_num = (int)list_of_items.size() - 1;
      break;
    case 'u':
      if (list_of_items.empty())
        continue;
      if (ItemManager::IsItemPotion(list_of_items[selected_item_num]))
        ItemManager::Use(list_of_items[selected_item_num], &(MainCharacter->us));
      else
        ItemManager::Equip(list_of_items[selected_item_num], &(MainCharacter->us));
      break;
    default:
      break;
    }
  }

}



bool combat_inventory() {
  bool done = false;
  bool action_used = false;
  int selected_item_num = 0;
  while (!done) {
    clear();
    auto list_of_items = MainCharacter->us.GetBackpackList();
    std::cout
      << "CURRENT INVENTORY\n"
      << "-----------------\n\n";
    int items_in_backpack_count = 0;
    for (const auto& item : list_of_items) {
      if (selected_item_num == items_in_backpack_count)
        std::cout << "> ";
      else
        std::cout << "  ";
      std::cout << item->GetData()->Name << '\n';
      if (ItemManager::IsItemPotion(item)) {
        Potion* potion = nullptr;
        ItemManager::CastItemToPotion(item, potion);
        if (potion)
          std::cout << "    Quantity: " << potion->Quantity << '\n';
      }
      items_in_backpack_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use/equip current\n";
    char c = getchar();
    switch (c) {
    case 'd':
      done = true;
      break;
    case 'w':
      selected_item_num--;
      if (selected_item_num < 0)
        selected_item_num = 0;
      break;
    case 's':
      selected_item_num++;
      if (selected_item_num > list_of_items.size() - 1)
        selected_item_num = (int)list_of_items.size() - 1;
      break;
    case 'u':
      if (list_of_items.empty())
        continue;
      if (ItemManager::IsItemPotion(list_of_items[selected_item_num])) {
        action_used = ItemManager::Use(list_of_items[selected_item_num], &(MainCharacter->us));
      } else {
        action_used = ItemManager::Equip(list_of_items[selected_item_num], &(MainCharacter->us));
      }
      break;
    default:
      break;
    }
    if (action_used)
      break;
  }
  return action_used;
}



bool combat_ability_selection(Fightable* fightable) {

  bool ability_done = false;
  bool action_used = false;
  int selected_ability = 0;
  while (!ability_done) {
    auto current_abilities = MainCharacter->us.GetAbilityList();
    clear();
    std::cout
      << "CURRENT ABILITIES\n\n";
    int abilites_in_list_count = 0;
    for (const auto& abil : current_abilities) {
      std::cout << ((selected_ability == abilites_in_list_count) ? "> " : "  ");
      std::cout << abil->GetName() << '\n';
      //todo: cooldowns and mp
      abilites_in_list_count++;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n d = done, w = up, s = down, u = use\n";
    char c = getchar();
    switch (c) {
    case 'd':
      ability_done = true;
      break;
    case 'w':
      selected_ability--;
      if (selected_ability < 0)
        selected_ability = 0;
      break;
    case 's':
      selected_ability++;
      if (selected_ability > current_abilities.size() - 1)
        selected_ability = (int)current_abilities.size() - 1;
      break;
    case 'u':
      if (current_abilities[selected_ability]->GetTarget() == ABILITYTARGET::ENEMY) {
        int total_damage = 0;
        total_damage += current_abilities[selected_ability]->GetHPEffect();
        switch (current_abilities[selected_ability]->GetScaler()) {
        case ABILITYSCALER::STR:
          total_damage += (int)(MainCharacter->us.GetTotalStrength() / 2.f);
          break;
        case ABILITYSCALER::INT:
          total_damage += (int)(MainCharacter->us.GetTotalIntellect() / 2.f);
          break;
        case ABILITYSCALER::AGI:
          total_damage += (int)(MainCharacter->us.GetTotalAgility() / 2.f);
          break;
        default:
          break;
        }
          fightable->monster.HP.ReduceCurrent(total_damage);
      } else {  // itsa heal (probably)
        int total_heal = 0;
        total_heal += current_abilities[selected_ability]->GetHPEffect();
        switch (current_abilities[selected_ability]->GetScaler()) {
        case ABILITYSCALER::STR:
          total_heal += (int)(MainCharacter->us.GetTotalStrength() / 2.f);
          break;
        case ABILITYSCALER::INT:
          total_heal += (int)(MainCharacter->us.GetTotalIntellect() / 2.f);
          break;
        case ABILITYSCALER::AGI:
          total_heal += (int)(MainCharacter->us.GetTotalAgility() / 2.f);
          break;
        default:
          break;
        }
        MainCharacter->us.Heal(total_heal);
      }
      action_used = true;
      break;
    default:
      break;
    }
    if (action_used)
      break;
  }
  return action_used;
}



Item* drop_random_item() {

  int drop_seed = Random::NTK(1, 100);
  if (drop_seed < 6) {
    std::string name;
    CoreStats local_stats;
    int magical_power = Random::NTK(0, 2);
    switch (magical_power) {
    case 0:
        name = "Helmet";
        local_stats = CoreStats(0, 0, 0, 1, 0);
        break;
    case 1:
        name = "+1 Helmet";
        local_stats = CoreStats(1, 1, 1, 2, 1);
        break;
    case 2:
        name = "+2 Helmet";
        local_stats = CoreStats(2, 2, 2, 3, 2);
        break;
    default:
        break;
    }
    return ItemManager::CreateArmor(name, local_stats, ARMORSLOT::HEAD);
  } else if (drop_seed < 12) {
    return ItemManager::CreateArmor("Breastplate", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::CHEST);
  } else if (drop_seed < 18) {
    return ItemManager::CreateArmor("Leg Guards", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::LEGS);
  } else if (drop_seed < 24) {
    return ItemManager::CreateArmor("Boots", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::FEET);
  } else if (drop_seed < 30) {
    return ItemManager::CreateArmor("Gloves", CoreStats(0, 0, 0, 1, 0), ARMORSLOT::HANDS);
  } else if (drop_seed < 36) {
    return ItemManager::CreateArmor("Ring1", CoreStats(1, 1, 1, 0, 0), ARMORSLOT::RING1);
  } else if (drop_seed < 42) {
    return ItemManager::CreateArmor("Ring2", CoreStats(1, 1, 1, 0, 0), ARMORSLOT::RING2);
  } else if (drop_seed < 48) {
    return ItemManager::CreateArmor("Neck Gaurd", CoreStats(0, 0, 0, 1, 1), ARMORSLOT::NECK);
  } else if (drop_seed < 54) {
    return ItemManager::CreateWeapon("1H Sword", CoreStats(0, 0, 0, 0, 0), WEAPONSLOT::MELEE, 2, 3);
  } else if (drop_seed < 60) {
    return ItemManager::CreateWeapon("Bow", CoreStats(0, 0, 0, 0, 0), WEAPONSLOT::RANGED, 2, 3);
  } else if (drop_seed < 91) {
    return ItemManager::CreatePotion("Potion Of Healing", Random::NTK(2, 5), Random::NTK(1, 2));
  }
  return nullptr;
}


Fightable* create_monster() {
    // - create new Fightable
    // - insert into ptr_map
    // - mark into monster_collection


    int lowest_hp = MainCharacter->us.GetLevel() * 2;
    int max_hp = (MainCharacter->us.GetLevel()) * (MainCharacter->us.GetLevel()) * 8;
    int lowest_dam = MainCharacter->us.GetLevel();
    int max_dam = (MainCharacter->us.GetLevel()) * (MainCharacter->us.GetLevel()) * 2;

    Fightable* monster = new Fightable(Random::NTK(lowest_hp, max_hp), lowest_dam, max_dam);

    monster->xpos = Random::NTK(1, 11);
    monster->ypos = Random::NTK(1, 11);

    while (ptr_map[monster->xpos][monster->ypos] != nullptr){
        monster->xpos = Random::NTK(1, 11);
        monster->ypos = Random::NTK(1, 11);
    }

    monster->prev_xpos = monster->xpos;
    monster->prev_ypos = monster->ypos;

    ptr_map[monster->xpos][monster->ypos] = monster;

    monster_collection.insert(monster);

    return monster;
}



void delete_monster(Fightable*& fightable){
    // - adjust ptr_map
    // - delete Fightable object
    // - set fightable ptr to nullptr

    ptr_map[fightable->xpos][fightable->ypos] = nullptr;
    delete fightable;
    fightable = nullptr;
}


void fight_sequence(Fightable* fightable) {
    // Given pointer to monster, start fight sequence

    if (!fightable) return;

    // options available per turn
    enum class FightOptions { NONE, ATTACK, INVENTORY, ABILITY};

    while (MainCharacter->IsAlive() && fightable->IsAlive()) {

        FightOptions action_taken = FightOptions::NONE;
        char action = '\0';

        while (action_taken == FightOptions::NONE) {
            // display fight interface

            clear();
            std::cout
                    << "\n\nPlayer         vs       Monster\n"
                    << "hp: " << MainCharacter->us.GetCurrentHP() << '/' << MainCharacter->us.GetMaxHP() << "                  hp: "
                    << fightable->monster.HP.GetCurrent() << '/' << fightable->monster.HP.GetMax()
                    << "\n\naction(a:attack, i:inv, b:abilites):" << '\n';

            action = getchar();
            switch (action) {
                case 'a':
                    action_taken = FightOptions::ATTACK;
                    fightable->monster.HP.ReduceCurrent(MainCharacter->us.MeleeAttack());
                    break;
                case 'i':
                    action_taken = (combat_inventory()) ? FightOptions::INVENTORY : FightOptions::NONE;
                    break;
                case 'b':
                    action_taken = (combat_ability_selection(fightable)) ? FightOptions::ABILITY : FightOptions::NONE;
                    break;
                default:
                    std::cout << "actionL: "<< action << std::endl;

                    break;
            }
        }

        // monster hits when your turn is over
        if (fightable->IsAlive()) {
            int damage_we_take = fightable->monster.Attack();
            damage_we_take -= MainCharacter->us.GetTotalArmor();
            if (damage_we_take < 1)
                damage_we_take = 1;
            MainCharacter->us.TakeDamage(damage_we_take);
        }
    }

    if (MainCharacter->IsAlive()) {
        clear();
        std::cout << "\nVICTORY!\n\n";

        // gain xp
        MainCharacter->us.GainEXP(fightable->xpworth);
        std::cout << "XP gained: " << fightable->xpworth << '\n';

        // drop a random item
        Item *item_drop = drop_random_item();
        if (item_drop) {
            ItemManager::MoveToBackpack(item_drop, &MainCharacter->us);
            std::cout << "Item recieved: " << item_drop->GetData()->Name << '\n';
        }

        monsters_defeated++;

    } else {
        std::cout << "\nDEFEAT!\n\n";
        end_game = true;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\npress enter to continue\n";
    char a = getchar();
}


void monster_thread_fn(){

    // Keep creating new monsters when one dies

    Fightable* curr_monster;

    while(!end_game){

        curr_monster = create_monster();

        while(curr_monster->IsAlive() && !end_game){

            // Sleep random duration
            std::this_thread::sleep_for(std::chrono::milliseconds (Random::NTK(250,1000)));
//            std::this_thread::sleep_for(std::chrono::seconds(1));

            gLock.lock();

            if(curr_monster->IsAlive() && !end_game){

                int next_xpos = curr_monster->xpos + Random::NTK(-1, 1);
                int next_ypos = curr_monster->ypos + Random::NTK(-1, 1);

                // Landed on Player
                if(dynamic_cast<Player*>(ptr_map[next_xpos][next_ypos])){
                    fight_sequence(curr_monster);
                }

                // Move monster
                else if(!dynamic_cast<Block*>(ptr_map[next_xpos][next_ypos])
                        && (next_xpos != curr_monster->prev_xpos || next_ypos != curr_monster->prev_ypos)){

                    curr_monster->prev_xpos = curr_monster->xpos;
                    curr_monster->prev_ypos = curr_monster->ypos;
                    ptr_map[curr_monster->prev_xpos][curr_monster->prev_ypos] = nullptr;

                    curr_monster->xpos = next_xpos;
                    curr_monster->ypos = next_ypos;
                    ptr_map[curr_monster->xpos][curr_monster->ypos] = curr_monster;

                }
                if(curr_monster->IsAlive() && !end_game) showmap();

            }

            gLock.unlock();


        }

        delete_monster(curr_monster);
    }
    return;
}





void move_player() {

    // Did not move
    if (MainCharacter->xpos == MainCharacter->prev_xpos && MainCharacter->ypos == MainCharacter->prev_ypos)
        return;

    // Landed on monster
    if(dynamic_cast<Fightable*>(ptr_map[MainCharacter->xpos][MainCharacter->ypos]))
        fight_sequence(dynamic_cast<Fightable*>(ptr_map[MainCharacter->xpos][MainCharacter->ypos]));

    // Move player
    else if(!dynamic_cast<Block*>(ptr_map[MainCharacter->xpos][MainCharacter->ypos])){
        ptr_map[MainCharacter->prev_xpos][MainCharacter->prev_ypos] = nullptr;
        ptr_map[MainCharacter->xpos][MainCharacter->ypos] = MainCharacter;
        MainCharacter->prev_xpos = MainCharacter->xpos;
        MainCharacter->prev_ypos = MainCharacter->ypos;
    }else{
        MainCharacter->xpos = MainCharacter->prev_xpos;
        MainCharacter->ypos = MainCharacter->prev_ypos;
    }

}















int main(int argc, char** argv) {

    fill_blocks_ptr_map();
    clear();
    std::cout << "Choose a class: \n"
            << "1 = Cleric    2 = Warrior\n"
            << "3 = Rogue     4 = Wizard\n";

    int choice = 0;
    while (choice == 0) {
        std::cin >> choice;
        std::cout << "chose: " << choice << '\n';
        if (choice < 1 || choice > 4)
            choice = 0;
    }

    switch (choice) {
    case 1:
    {
        MainCharacter = new Player(new Cleric());
    }
    break;
    case 2:
    {
        MainCharacter = new Player(new Warrior());
    }
    break;
    case 3:
    {
        MainCharacter = new Player(new Rogue());
    }
    break;
    case 4:
    {
        MainCharacter = new Player(new Wizard());
    }
    break;
    default:
    return -12;  // failed to make player character
    }

    ptr_map[MainCharacter->xpos][MainCharacter->ypos] = MainCharacter;

    ItemManager::MoveToBackpack(drop_random_item(), &MainCharacter->us);
    ItemManager::MoveToBackpack(drop_random_item(), &MainCharacter->us);

    while(num_monsters--){
        monster_threads.push_back(std::thread(monster_thread_fn));
    }

    showmap();

    while(!end_game){


        //    char c = getchar();
        char c{};
        std::cin.clear();
        std::cin >> c;

        gLock.lock();

        switch (c) {
        case 'w':
          MainCharacter->xpos--;
          break;
        case 's':
          MainCharacter->xpos++;
          break;
        case 'a':
          MainCharacter->ypos--;
          break;
        case 'd':
          MainCharacter->ypos++;
          break;
        case 'i':
          open_inventory();
          break;
        case 'c':
          display_character_sheet();
          break;
        default:
          break;
        }

//        std::cin.clear();

        move_player();

        if (MainCharacter->IsAlive())   showmap();

        gLock.unlock();

    }



    for(auto& thread : monster_threads)
        thread.join();

    std::cout << "Total Monsters Defeated: " << monsters_defeated << '\n';

    char c = getchar();
    return EXIT_SUCCESS;
}