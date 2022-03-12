#include "ConstructorOfTanks.h"

ConstructorOfTanks::~ConstructorOfTanks()
{
	for (auto it = tanks.begin(); it != tanks.end(); ++it)
	{
		if(*it)
			(*it)->~Tank();
		*it = NULL;
		delete* it;
	}
	tanks.clear();
	connected_tanks_ids.clear();
}
void ConstructorOfTanks::list_fuel_tanks()
{
	for (auto it = tanks.begin(); it != tanks.end(); ++it)
		if (*it)
			(*it)->print();
}
void ConstructorOfTanks::list_connected_tanks()
{
	for (auto it = connected_tanks_ids.begin(); it != connected_tanks_ids.end(); ++it)
		tanks[*it]->print();
}
void ConstructorOfTanks::print_fuel_tank_count()
{
	int sum = 0;
	for (auto it = tanks.begin(); it != tanks.end(); ++it)
		if (*it)
			sum++;
	*Output::out() << "[Info]: Count Of Fuel Tanks = " << sum << std::endl;
}
void ConstructorOfTanks::print_total_fuel_quantity()
{
	long double sum1 = 0;
	for (auto it = tanks.begin(); it != tanks.end(); ++it)
		if(*it)
			sum1 += (*it)->get_fuel_quantity();
	*Output::out() << "[Info]: Total Fuel Quantity Of All Tanks = " << sum1 << std::endl;
}

void ConstructorOfTanks::print_tank_info(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	tanks[(int)tank_id]->print();
}

void ConstructorOfTanks::add_fuel_tank(double capacity)
{
	tanks.push_back(new External_Tank(capacity));
	*Output::out() << "[Info]: New Tank " << tanks.size() - 1 << std::endl;
}
void ConstructorOfTanks::remove_fuel_tank(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	if ((*(tanks.begin() + (int)tank_id))->get_connection() && (*(tanks.begin() + (int)tank_id))->get_valve())
	{
		*Output::out() << "[ERROR]: Tanks Valve is Open\n";
		return;
	}
	tanks[(int)tank_id] = NULL;
	if (std::find(connected_tanks_ids.begin(), connected_tanks_ids.end(), tank_id) != connected_tanks_ids.end())
		connected_tanks_ids.erase(std::find(connected_tanks_ids.begin(), connected_tanks_ids.end(), tank_id));
	*Output::out() << "[Info]: Tank " << tank_id << " is Removed." << std::endl;
}
void ConstructorOfTanks::connect_fuel_tank_to_engine(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	if ((*(tanks.begin() + (int)tank_id))->get_broken())
	{
		*Output::out() << "[ERROR]: The Tank is Broken !\n";
		return;
	}
	if ((*(tanks.begin() + (int)tank_id))->get_connection())
	{
		*Output::out() << "[ERROR]: The Tank is Aldready Connected !\n";
		return;
	}
	connected_tanks_ids.push_back((int)tank_id);
	(*(tanks.begin() + (int)tank_id))->set_connection(1);
	*Output::out() << "[Info]: Tank " << tank_id << " Connected to Engine." << std::endl;
}
void ConstructorOfTanks::disconnect_fuel_tank_from_engine(double tank_id)
{
	if (std::find(connected_tanks_ids.begin(), connected_tanks_ids.end(), tank_id) != connected_tanks_ids.end())
	{
		connected_tanks_ids.erase(std::find(connected_tanks_ids.begin(), connected_tanks_ids.end(), tank_id));
		*Output::out() << "[Info]: The Tank Disconnected from Engine." << std::endl;
	}
	*Output::out() << "[ERROR]: Invalid Tank ID !" << std::endl;
}

void ConstructorOfTanks::open_valve(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	if ((*(tanks.begin() + (int)tank_id))->get_broken())
		*Output::out() << "[warn]: You can not open valve of the tank which is broken.\n";
	else
		(*(tanks.begin() + (int)tank_id))->set_valve(1);
}
void ConstructorOfTanks::close_valve(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	(*(tanks.begin() + (int)tank_id))->set_valve(0);
}
void ConstructorOfTanks::break_fuel_tank(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	(*(tanks.begin() + (int)tank_id))->set_broken(1);
	if ((*(tanks.begin() + (int)tank_id))->get_connection())
		close_valve(tank_id);
}
void ConstructorOfTanks::repair_fuel_tank(double tank_id)
{
	if (!is_valid(tank_id))
		return;
	(*(tanks.begin() + (int)tank_id))->set_broken(0);
}

void ConstructorOfTanks::sum_operator(double id1, double id2, double id3)
{
	if (!is_valid(id1) || !is_valid(id1) || !is_valid(id1))
		return;
	if (!(tanks[(int)id1]->get_valve() && tanks[(int)id2]->get_valve() && tanks[(int)id3]->get_valve()))
	{
		*Output::out() << "[ERROR]: Valves are not open !\n";
		return;
	}
	*(tanks[(int)id1]) = *(tanks[(int)id2]) + *(tanks[(int)id3]);
	*Output::out() << "[Info]: Tank " << id1 << "'s Fuel Quantity = " << tanks[(int)id1]->get_fuel_quantity() << std::endl;
}

void ConstructorOfTanks::fill_tank(double id, double q)
{
	if (!is_valid(id))
		return;
	if ((*(tanks.begin() + (int)id))->get_broken())
	{
		* Output::out() << "[ERROR]: Tank is broken !\n";
		return;
	}	
	if (!(*(tanks.begin() + (int)id))->get_valve())
		(*(tanks.begin() + (int)id))->set_valve(1);

	(*(tanks.begin() + (int)id))->set_fuel_quantity((*(tanks.begin() + (int)id))->get_fuel_quantity()+q);
	*Output::out() << "[Info]: " << q << " Unit Fuel Added to Tank " << (int)id << std::endl;
}
bool ConstructorOfTanks::is_valid(int id)
{
	if (id < 0 || id >= tanks.size() || tanks[id] == NULL)
	{
		*Output::out() << "[ERROR]: Invalid Tank ID : " << id << std::endl;
		return false;
	}
	return true;
}
