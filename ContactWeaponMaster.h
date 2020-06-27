#pragma once
#include "PartMaster.h"

class ContactWeaponMaster :
    public PartMaster
{
    int maxContactWeaponIndex;

    double* contactDamageMultPres;

    int* partIndexes;

public:
    ContactWeaponMaster(int windowWidth, int windowHeight);

    ContactWeapon* generateContactWeapon(int decorationIndex, Frame* defaultFrame);
};
