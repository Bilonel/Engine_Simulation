#include "Engine.h"

Engine::Engine()
{
	constructor_of_tanks = new ConstructorOfTanks();
	internal_tank = new Internal_Tank();
	constructor_of_tanks->tanks.push_back(internal_tank);

	if (!font.loadFromFile("calibri.ttf"))
		std::cerr << "LOAD ERROR";
	sp_heat.setPosition(-30, 325);
	starton.setSize(sf::Vector2f(60, 45));
	starton.setPosition(63, 150);
	starttext.setPosition(91, 155);
	starttext.setCharacterSize(25);
	starttext.setFont(font);
	starttext.setStyle(sf::Text::Bold);
	heat_t.setFillColor(sf::Color::Red);
	heat_t.setFont(font);
	heat_t.setCharacterSize(30);
	heat_t.setOutlineThickness(1);
	heat_t.setStyle(sf::Text::Bold);
	health_t.setFillColor(sf::Color::Green);
	health_t.setFont(font);
	health_t.setCharacterSize(30);
	health_t.setStyle(sf::Text::Bold);
	health_t.setOutlineThickness(1);
}
void Engine::render(sf::RenderWindow* win)
{
	if (status_on_off)
	{
		starton.setFillColor(sf::Color::Color::Green);
		starttext.setString("ON");
		starttext.setOrigin(starttext.getGlobalBounds().width / 2.0, 0);
	}
	else
	{
		starton.setFillColor(sf::Color::Color::Red);
		starttext.setString("OFF");
		starttext.setOrigin(starttext.getGlobalBounds().width / 2.0, 0);
	}
	heat_t.setString(std::to_string(heat) + '\u00B0'+'C');
	health_t.setString(std::to_string(health));
	
	int x = heat / 13;
	if (x > 10)
		x = 10;
	tex_heat.loadFromFile("res/"+std::to_string(x) + ".png");
	sp_heat.setTexture(tex_heat);
	sp_heat.setScale(0.27, 0.27);
	heat_t.setOrigin(heat_t.getGlobalBounds().width / 2, heat_t.getGlobalBounds().height / 2);
	heat_t.setPosition(-30+sp_heat.getGlobalBounds().width/2, 330+ sp_heat.getGlobalBounds().height/2);

	sprite = sp_heat;
	int y = health / 10;
	texture.loadFromFile("res/" + std::to_string(y) + ".png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color::Color(0,255,0));
	sprite.setPosition(-30, 200);
	health_t.setOrigin(health_t.getGlobalBounds().width / 2, health_t.getGlobalBounds().height / 2);
	health_t.setPosition(-30 + sprite.getGlobalBounds().width / 2, 205 + sprite.getGlobalBounds().height / 2);


	win->draw(sp_heat);
	win->draw(sprite);
	win->draw(heat_t);
	win->draw(health_t);
	win->draw(starton);
	win->draw(starttext);
}

Engine::~Engine()
{
	*Output::out() << "[Engine]: Simulation Stopped !\n";
	constructor_of_tanks->~ConstructorOfTanks();
	instance = NULL;
	constructor_of_tanks = NULL;
	delete instance;
	delete constructor_of_tanks;
}

Engine* Engine::get_instance()
{
	if (!instance)
		instance= new Engine();
	return instance;
}

void Engine::absorb_fuel()
{
	double fuel_to_be_transferred = internal_tank->get_capacity() - internal_tank->get_fuel_quantity();
	for (auto it = constructor_of_tanks->connected_tanks_ids.begin(); it != constructor_of_tanks->connected_tanks_ids.end(); ++it)
	{
		if (constructor_of_tanks->tanks[*it]->get_valve() && !constructor_of_tanks->tanks[*it]->get_broken() && constructor_of_tanks->tanks[*it]->get_fuel_quantity() > 0)
			if (fuel_to_be_transferred > constructor_of_tanks->tanks[*it]->get_fuel_quantity())
			{
				fuel_to_be_transferred -= constructor_of_tanks->tanks[*it]->get_fuel_quantity();
				internal_tank->set_fuel_quantity(constructor_of_tanks->tanks[*it]->get_fuel_quantity()+internal_tank->get_fuel_quantity());
				*Output::out() << "[Info]: Fuel Added to Engine +" << constructor_of_tanks->tanks[*it]->get_fuel_quantity() << std::endl;
				constructor_of_tanks->tanks[*it]->set_fuel_quantity(0);
			}
			else
			{
				internal_tank->set_fuel_quantity(fuel_to_be_transferred + internal_tank->get_fuel_quantity());
				constructor_of_tanks->tanks[*it]->set_fuel_quantity(constructor_of_tanks->tanks[*it]->get_fuel_quantity()-fuel_to_be_transferred);
				*Output::out() << "[Info]: Fuel Added to Engine +" << fuel_to_be_transferred << std::endl;
				*Output::out() << "-----------------------------------\n";
				return;
			}
	}
}
void Engine::start_engine()
{
	if (health <= 20)
		*Output::out() << "[ERROR]: Engine can not starts ; Health is lower or equal 20 !\n";
	else if (constructor_of_tanks->connected_tanks_ids.size() < 1)
		*Output::out() << "[ERROR]: Engine doesn't have a connected tank !\n";
	else
	{
		if (internal_tank->get_fuel_quantity() < fuel_per_second)
			absorb_fuel();
		if (internal_tank->get_fuel_quantity() < fuel_per_second)
		{
			*Output::out() << "[ERROR]: Engine doesn't have enough fuel to running !\n";
			*Output::out() << "[Info]: Engine is Off.\n";
			status_on_off = 0;
			return;
		}
		status_on_off = 1;
		*(Output::out()) << "[Info]: Engine is On\n";
	}
}

void Engine::stop_engine()
{
	*(Output::out()) << "[Info]: Engine is Off.\n";
	status_on_off = 0;
}

void Engine::change_engine_block()
{
	if (status_on_off)
		*(Output::out()) << "[ERROR]: Engine Block can not be changed while engine is running !\n";
	else if (health != 0)
		*(Output::out()) << "[ERROR]: Engine Block can not be changed ; health is not zero !\n";
	else
	{
		*(Output::out()) << "[Info]: Engine Block changed ; health is full !\n";
		health = 100;
	}
}
void Engine::repair_engine()
{
	if (status_on_off)
		*(Output::out()) << "[ERROR]: Engine can not be repaired while engine is running !\n";
	else if (health <= 0)
		*(Output::out()) << "[ERROR]: Engine can not be repaired ; health is zero !\n";
	else
	{
		*(Output::out()) << "[Info]: Engine repaired ; health is full !\n";
		health = 100;
	}
}
void Engine::full_throttle(double seconds)
{
	seconds_boost_mode = ++seconds;
}
void Engine::print()
{
	*Output::out() << std::setw(15) << "[Info]: Engine's :" <<std::setw(14)<<
		"Status = " << status_on_off << std::setw(25) <<
		"Full Throttle = " << (bool)(seconds_boost_mode > 0) << std::setw(15) <<
		"Health = " << health << std::setw(15) <<
		"Heat = " << heat << "\n";
	internal_tank->print();
}
