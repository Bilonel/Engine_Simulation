#pragma once
#include "Engine.h"

class Time
{
private:
	Engine* instance;
	static Time* time;
	double consumed_fuel_quantity = 0;
	Time();
public:
	~Time();
	static Time* get_time();
	void a_second();
	void engines_fuel();
	void engines_heat();
	void engines_health();

	void print_total_consumed_fuel_quantity();
	void wait(double seconds);
};
