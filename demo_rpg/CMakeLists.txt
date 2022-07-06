cmake_minimum_required(VERSION 3.21)
project(demo_rpg)
set(CMAKE_CXX_STANDARD 17)


set(
        Sources
        ability.cpp
        armor.cpp
        buff.cpp
        cleric.cpp
        corestats.cpp
        item.cpp
        item_manager.cpp
        monster.cpp
        playercharacter.cpp
        pointwell.cpp
        potion.cpp
        random.cpp
        rogue.cpp
        statblock.cpp
        types.cpp
        warrior.cpp
        weapon.cpp
        wizard.cpp
)

set(
        Headers
        include/ability.h
        include/armor.h
        include/buff.h
        include/cleric.h
        include/corestats.h
        include/item.h
        include/item_manager.h
        include/monster.h
        include/playableclasses_fwd.h
        include/playercharacter.h
        include/pointwell.h
        include/potion.h
        include/random.h
        include/rogue.h
        include/statblock.h
        include/types.h
        include/warrior.h
        include/weapon.h
        include/wizard.h
        pc_macros.h
        playableclasses_fwd.h
)


add_library(demo_rpg ${Headers} ${Sources})

target_include_directories(demo_rpg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# PUBLIC means that any target consuming this library will inherit the 'include' directory