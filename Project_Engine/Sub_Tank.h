#include "Tank.h"

#define base 55

class External_Tank : public Tank
{
public:
	External_Tank(double c) : Tank(c) {}

	Tank operator + (Tank& fueltank) override {
		
		this->set_fuel_quantity(fuel_quantity + fueltank.get_fuel_quantity());
		fueltank.set_fuel_quantity(0);
		return *this;
	}

	void print() override {
		*Output::out() << "External [" << id << "] Tank's : " << std::setw(11) <<
			"Fullnes = " << std::setw(4) << fuel_quantity << " / " << std::setw(3) << capacity << std::setw(15) <<
			"Valve = " << valve << std::setw(15) <<
			"Broken = " << broken << std::setw(15) <<
			"Connected = " << connected
			<< std::endl;
	}
};
class Internal_Tank : public Tank
{
public:

	Internal_Tank(double c = base) :Tank(c) { Tank::connected = 1; }
	void print() override {
		*Output::out() << "Internal [" << id << "] Tank's : " << std::setw(11) <<
			"Fullnes = " << std::setw(4) << fuel_quantity << " / " << std::setw(3) << capacity << std::setw(15) <<
			"Valve = " << valve << std::setw(15) <<
			"Broken = " << broken <<
			std::endl;
	}
};
 