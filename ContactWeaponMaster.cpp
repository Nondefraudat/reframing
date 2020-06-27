#include "ContactWeaponMaster.h"


ContactWeaponMaster::ContactWeaponMaster(int windowWidth, int windowHeight) :
	PartMaster(windowWidth, windowHeight)
{
	maxContactWeaponIndex = 1;
	
	contactDamageMultPres = new double[maxContactWeaponIndex];

	partIndexes = new int[maxContactWeaponIndex];

	partIndexes[0] = 4;
	contactDamageMultPres[0] = 5.0;
}

ContactWeapon* ContactWeaponMaster::generateContactWeapon(int contactWeaponIndex, Frame* defaultFrame)
{
	if (contactWeaponIndex < maxContactWeaponIndex)
	{
		return new ContactWeapon(&titlePres[partIndexes[contactWeaponIndex]], &descriptionsPres[partIndexes[contactWeaponIndex]],
			totalResistancePres[partIndexes[contactWeaponIndex]], contactDamageMultPres[partIndexes[contactWeaponIndex]],
			linkSystemMaster->generateLinkSystem(linkSystemInexes[partIndexes[contactWeaponIndex]]),
			shapeMaster->generateShape(shapeIndexes[partIndexes[contactWeaponIndex]]), defaultFrame);
	}
	return nullptr;
}