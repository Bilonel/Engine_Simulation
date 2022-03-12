#include "Tank.h"

Tank::~Tank()
{
	*Output::out() << "[Tank "<<id<<"]: Simulation Stopped !\n";
}
void Tank::set_broken(bool t)
{
	if (t)
	{
		broken = 1;
		*Output::out() << "[Info]: The Tank is broken. \n";
		fuel_quantity = 0;
	}
	else
	{
		broken = 0;
		*Output::out() << "[Info]: The Tank is not broken. \n";
	}
}

void Tank::set_valve(bool t)
{
	if (t)
	{
		valve = 1;
		*Output::out() << "[Info]: Valve is Open\n";
		return;
	}
	valve = 0;
	*Output::out() << "[Info]: Valve is Off\n";
}
void Tank::set_fuel_quantity(double q)
{
	if (q < 0)
		q = 0;
	if (q > capacity)
		q = capacity;
	fuel_quantity = q;
}
