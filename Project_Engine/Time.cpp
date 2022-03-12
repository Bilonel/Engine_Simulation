#include "Time.h"

Time::Time()
{
	instance = Engine::get_instance();
}

Time::~Time()
{
	instance = NULL;
	time = NULL;
	delete instance;
	delete time;
}

Time* Time::get_time()
{
	if (!time)
		time = new Time();
	return time;
}

void Time::a_second()
{
	engines_fuel();
	engines_heat();
	engines_health();
	instance->set_boost_mode(-1);
}

void Time::engines_fuel()
{
	if (instance->get_status())
	{
		double k = 1;
		if (instance->get_boost_mode())
			k = 5;
		if (instance->get_internal_tank()->get_fuel_quantity() < (double)(20 * k))
			instance->absorb_fuel();

		if (instance->get_internal_tank()->get_fuel_quantity() >= k * instance->get_fuel_per_second())
		{
			(*(instance->get_internal_tank())).set_fuel_quantity((*(instance->get_internal_tank())).get_fuel_quantity() - k * instance->get_fuel_per_second());
			consumed_fuel_quantity += k * instance->get_fuel_per_second();
		}
		else
		{
			*Output::out() << "[warn]: Fuel Is Over\n";
			*Output::out() << "------------------------------------------\n";
			instance->stop_engine();
		}
	}
}

void Time::engines_heat()
{
	if (!instance->get_status() && instance->get_heat() > 20)
		instance->set_heat(-1);
	else if (instance->get_status() && !instance->get_boost_mode()) {
		if (instance->get_heat() > 90)
			instance->set_heat(-1);
		else if (instance->get_heat() < 90)
			instance->set_heat(1);
	}
	else if (instance->get_status() && instance->get_boost_mode())
		instance->set_heat(5);
	if (instance->get_status())
		*Output::out() << "[Info]: Engine's heat is " << instance->get_heat() << std::endl;
}

void Time::engines_health()
{
	if ( (instance->get_heat() > 130) || (instance->get_boost_mode() && instance->get_heat() < 90))
		instance->set_health(-1);
	if (!instance->get_status())
		return;
	*Output::out() << "[Info]: Engine's health is " << instance->get_health() << std::endl;
	*Output::out() << "---------------------------------- " << std::endl;
}

void Time::print_total_consumed_fuel_quantity()
{
	*Output::out() << "[Info]: Total Consumed Fuel Quantity = " << consumed_fuel_quantity<<std::endl;
}

void Time::wait(double seconds)
{
	for (int i = 0; i < seconds;)
	{
		a_second();
		i++;
		*Output::out() << "[Info]: Remaining " << seconds - i << "..\n";
	}
}
