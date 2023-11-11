//
// Created by dawid on 07.05.2023.
//

#include "Weapon.h"

Weapon::Weapon(int DMG,int nrOfUse)
{
    uses_per_turn=nrOfUse;
    current_uses=uses_per_turn;
    damage=DMG;
    kind_of_weapon=SWORD;
    SetBuffsMessages();
//    SetSound();
}

void Weapon::SetBuffsMessages()
{
    /*
     Funkcja ma na celu dodanie do wektora mozliwych do pozniejszego wylosowania bonusow (nazwy)
     * */
    buffs_messages.push_back("Damage increase: ");
    buffs_messages.push_back("Uses per turn increase: ");
}
void Weapon::play_my_sound()
{
    sound.play();

}

void Weapon::apply_buff(Buff buff)
{
    /*
     Funckja zmienia poszczegolne parametry broni
     buff wyznacza jaki parametr broni ma zostac zmieniony oraz o jaka wartosc zostanie zmieniony
     mozliwe zmienienie:
     -damage
     -uses_per_turn
     * */
    if(buff.message.compare("Damage increase: ")==0)damage+=buff.value;
    else if(buff.message.compare("Uses per turn increase: ")==0)uses_per_turn+=buff.value;
}


void Weapon::DecreaseCurrentUses()
{
    current_uses--;
}

int Weapon::get_dmg() const
{
    return damage;
}

int Weapon::get_current_number_of_use() const
{
    return current_uses;
}

int Weapon::get_number_of_use() const
{
    return uses_per_turn;
}

void Weapon::end_of_turn()
{
    current_uses=uses_per_turn;
}

WEAPON Weapon::get_kind() const
{
    return kind_of_weapon;
}
int Weapon::get_range() const
{
    return -1;
}
