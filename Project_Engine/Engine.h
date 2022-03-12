#pragma once
#include "ConstructorOfTanks.h"

class Engine
{
private:
	static Engine* instance;
	Engine();

	Internal_Tank* internal_tank;
	ConstructorOfTanks* constructor_of_tanks;

	bool status_on_off=0;
	double seconds_boost_mode=0;
	const double fuel_per_second = 5.5;
	int health=100;
	int heat=20;

	sf::Font font;
	sf::RectangleShape starton;
	sf::Text starttext;
	sf::Text heat_t, health_t;
	sf::Texture texture,tex_heat;
	sf::Sprite sprite,sp_heat;
public:
	~Engine();
	void render(sf::RenderWindow* win);
	static Engine* get_instance();
	ConstructorOfTanks* get_constructor_of_tanks() { return constructor_of_tanks; }
	Tank* get_internal_tank() { return internal_tank;}

	void set_heat(int adon) { heat = heat + adon; }
	void set_health(int adon) { health = health + adon; }
	void set_boost_mode(int adon) { seconds_boost_mode += adon; if (!get_boost_mode())seconds_boost_mode = 0; }
	int get_heat() { return heat; }
	int get_health() { return health; }
	bool get_status() { return status_on_off; }
	bool get_boost_mode() { return seconds_boost_mode>0; }
	const double get_fuel_per_second() { return fuel_per_second; }

	void absorb_fuel();
	void start_engine();
	void stop_engine();
	void change_engine_block();
	void repair_engine();
	void full_throttle (double seconds);
	void print();
};		



