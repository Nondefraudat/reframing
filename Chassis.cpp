#include "Chassis.h"

Chassis::Chassis(int width, int height, CreationBase* base)
	: FunctionalObject(width, height)
{
	itemTag = IT_CHASSIS;
	this->base = base;
}

Chassis::~Chassis()
{

}

int Chassis::action(int& itemTag, int& operation)
{
	if (itemTag != IT_CHASSIS)
	{
		return AR_UNKNOWNOPERATION;
	}
	switch (operation)
	{
	case OL_MOVE_TOLEFT:
		base->setX(base->getX() - 10);
		break;
	case OL_MOVE_TORIGHT:
		base->setX(base->getX() + 10);
		break;
	case OL_MOVE_TOUP:
		base->setY(base->getY() + 10);
		break;
	case OL_MOVE_TODOWN:
		base->setY(base->getY() - 10);
		break;
	default:
		break;
	}
	return AR_SUCCESS;
}
