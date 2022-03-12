#pragma once
#include "Sub_Tank.h"

class ConstructorOfTanks
{
	friend class Engine;
	std::vector<Tank*> tanks;
	std::vector<int> connected_tanks_ids;
public:
	ConstructorOfTanks() {}
	~ConstructorOfTanks();
	std::vector<int> get_connected_tanks_id(int index) { return connected_tanks_ids; }
	void render(sf::RenderWindow* win)
	{
		int i = 0;
		for (auto it : connected_tanks_ids)
		{
			tanks[it]->render(win, 260 + 110 * i++, 35);
		}
		i = 0;
		for (auto it : tanks)
			if(it!=NULL && !it->get_connection())
				it->render(win, 290 + 110 * i++, 140);
	}
	bool is_valid(int);
	void list_fuel_tanks();
	void list_connected_tanks();
	void print_fuel_tank_count();
	void print_total_fuel_quantity();
	void print_tank_info(double tank_id);
	void add_fuel_tank(double capacity);
	void remove_fuel_tank(double tank_id);
	void connect_fuel_tank_to_engine(double tank_id);
	void disconnect_fuel_tank_from_engine(double tank_id);
	void open_valve(double tank_id);
	void close_valve(double tank_id);
	void break_fuel_tank(double tank_id);
	void repair_fuel_tank(double tank_id);
	void sum_operator(double id1, double id2,double id3);
	void fill_tank(double id, double q);
};


