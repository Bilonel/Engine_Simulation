#pragma once
#include "Time.h"

class Functions
{
private:
	Engine* instance;
	Time* time;
	typedef void (Functions::* fn0)();
	typedef void (Functions::* fn1)(double a);
	typedef void (Functions::* fn2)(double a, double b);
	typedef void (Functions::* fn3)(double a, double b, double c);

	std::map<std::string, fn0> fmap0;
	std::map<std::string, fn1> fmap1;
	std::map<std::string, fn2> fmap2;
	std::map<std::string, fn3> fmap3;

	static Functions* func;
	Functions();

	bool open = 0;
	sf::RenderWindow window;
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;
	sf::Texture texture,texture_sim;
	sf::Sprite sprite,sprite_sim;
public:
	static Functions* get_func();
	~Functions();
	void Run();
	void run_window();
	void print_engine_info() { instance->print(); }
	void absorb_fuel() { instance->absorb_fuel(); }
	void start_engine() { instance->start_engine(); }
	void stop_engine() { instance->stop_engine(); }
	void change_engine_block() { instance->change_engine_block(); }
	void repair_engine() { instance->repair_engine(); }
	void full_throttle(double seconds) { instance->full_throttle(seconds); }

	void list_fuel_tanks() { instance->get_constructor_of_tanks()->list_fuel_tanks(); }
	void list_connected_tanks() { instance->get_constructor_of_tanks()->list_connected_tanks(); }
	void print_fuel_tank_count() { instance->get_constructor_of_tanks()->print_fuel_tank_count(); }
	void print_total_fuel_quantity() { instance->get_constructor_of_tanks()->print_total_fuel_quantity(); }
	void print_tank_info(double tank_id) { instance->get_constructor_of_tanks()->print_tank_info(tank_id); }
	void add_fuel_tank(double capacity) { instance->get_constructor_of_tanks()->add_fuel_tank(capacity); }
	void remove_fuel_tank(double tank_id) { instance->get_constructor_of_tanks()->remove_fuel_tank(tank_id); }
	void connect_fuel_tank_to_engine(double tank_id) { instance->get_constructor_of_tanks()->connect_fuel_tank_to_engine(tank_id); }
	void disconnect_fuel_tank_from_engine(double tank_id) { instance->get_constructor_of_tanks()->disconnect_fuel_tank_from_engine(tank_id); }
	void open_valve(double tank_id) { instance->get_constructor_of_tanks()->open_valve(tank_id); }
	void close_valve(double tank_id) { instance->get_constructor_of_tanks()->close_valve(tank_id); }
	void break_fuel_tank(double tank_id) { instance->get_constructor_of_tanks()->break_fuel_tank(tank_id); }
	void repair_fuel_tank(double tank_id) { instance->get_constructor_of_tanks()->repair_fuel_tank(tank_id); }
	void fill_tank(double id, double q) { instance->get_constructor_of_tanks()->fill_tank(id,q); }
	void sum_operator(double result_tank, double tank1,double tank2) { instance->get_constructor_of_tanks()->sum_operator(result_tank, tank1,tank2); }

	void wait(double seconds) { 
		//time->wait(seconds);
		while (seconds--)
		{
			run_window();
			Sleep(500);
			time->a_second();
			*Output::out() << "[Info]: Remaining " << seconds << "..\n";
		}
	}
	void print_total_consumed_fuel_quantity() { time->print_total_consumed_fuel_quantity(); }

	void stop_simulation() { *Output::out() << "[Info]: Simulation Stopped.\n"; }
};

