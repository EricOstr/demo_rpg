//
// Created by Eric Ostring on 08/05/2022.
//

#include <gtest/gtest.h>
#include "../demo_rpg/include/playercharacter.h"
#include "../demo_rpg/include/types.h"
#include "../demo_rpg/include/item_manager.h"
#include "../demo_rpg/include/playableclasses_fwd.h"
#include "../demo_rpg//include/monster.h"





TEST(ExampleTests, EquipTest) {

    PlayerCharacter rogue(new Rogue());

    EXPECT_TRUE(
            ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false),
            &rogue)
            );

    EXPECT_TRUE(
            rogue.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)
            );

    EXPECT_EQ(
            ItemManager::Equip(ItemManager::CreatePotion("Armor", 0, 1, new Buff("ArmorBuff", CoreStats(0,0,0,3,0), 5)), &rogue),
            false
            );
}

TEST(Corestats, corestats) {

    CoreStats statsa(5);
    EXPECT_EQ(5, statsa.Strength);

    CoreStats statsb(1,2,3,4,5);
    statsa -= statsb;

    EXPECT_EQ(4, statsa.Strength);
}


TEST(Weapon, weapon) {
    Item* weapona = ItemManager::CreateWeapon("MagicWeapon", CoreStats(5), WEAPONSLOT::MELEE, 1, 3, false);
    EXPECT_TRUE(ItemManager::IsItemWeapon(weapona));
    EXPECT_FALSE(ItemManager::IsItemArmor(weapona));

    {
        const Weapon* weapon = dynamic_cast<const Weapon*>(weapona->GetData());
        EXPECT_TRUE(weapon);
        EXPECT_EQ(5, weapon->Stats.Strength);
        EXPECT_FALSE(weapon->is2H);
    }

    ItemManager::DeleteItem(weapona);
    EXPECT_FALSE(weapona);
}




TEST(ExampleTests, EquipTest2) {

    PlayerCharacter rogue(new Rogue());

    EXPECT_TRUE(
            ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false),
                               &rogue)
    );

    EXPECT_TRUE(
            rogue.GetEquippedWeaponAt((unsigned long long)WEAPONSLOT::MELEE)
    );

    EXPECT_EQ(
            ItemManager::Equip(ItemManager::CreatePotion("Armor", 0, 1, new Buff("ArmorBuff", CoreStats(0,0,0,3,0), 5)), &rogue),
            false
    );
}






TEST(Monster, monster) {

    Monster monster(10, 2, 4);

    EXPECT_EQ(10, monster.HP.GetMax());

    int damage_rando = 0;

    for (int i=0; i<10; ++i) {
        damage_rando = monster.Attack();
        EXPECT_GE(damage_rando, monster.GetMinDamage());
        EXPECT_LE(damage_rando, monster.GetMaxDamage());
    }
}



TEST(Simplebattle, simplebattle) {
    PlayerCharacter rogue(new Rogue());

    EXPECT_TRUE(ItemManager::Equip(ItemManager::CreateWeapon("Dagger", CoreStats(), WEAPONSLOT::MELEE, 1, 3, false), &rogue));

    Monster monster1(10,2,4);

    while(monster1.HP.GetCurrent() > 0 && rogue.GetCurrentHP() > 0) {
        monster1.HP.ReduceCurrent(rogue.MeleeAttack());
        rogue.TakeDamage(monster1.Attack());
    }

    EXPECT_TRUE(monster1.HP.GetCurrent() == 0 || rogue.GetCurrentHP() == 0);
}



















