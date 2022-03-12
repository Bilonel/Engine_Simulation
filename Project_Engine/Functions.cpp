#include "Functions.h"

Functions::Functions()
{
	instance = Engine::get_instance();
	time = Time::get_time();
	
	rect.setSize(sf::Vector2f(1000, 1000));
	rect.setOrigin(1000, 0);
	rect.setPosition(200, 0);
	rect.setFillColor(sf::Color::Color(250, 250, 150));
	window.create(sf::VideoMode(720, 480), "Interface");
	text.setPosition(360, 400);
	text.setCharacterSize(52);
	text.setFillColor(sf::Color::Black);
	if (!font.loadFromFile("calibri.ttf"))
		std::cerr << "LOAD ERROR";
	text.setFont(font);

	texture.loadFromFile("res/engine.png");
	texture_sim.loadFromFile("res/start.png");
	sprite_sim.setTexture(texture_sim);
	sprite.setTexture(texture);
	sprite_sim.setPosition(300, 340);
	sprite.setPosition(30,20);
	sprite_sim.setScale(0.8, 0.8);
	
	fmap0 = {
		{ "printengineinfo" , &Functions::print_engine_info } ,
		{ "stopengine" , &Functions::stop_engine } ,
		{ "startengine" , &Functions::start_engine } ,
		{ "repairengine" ,&Functions::repair_engine },
		{ "listfueltanks" , &Functions::list_fuel_tanks },
		{ "stopsimulation" , &Functions::stop_simulation },
		{ "changeengineblock" ,&Functions::change_engine_block },
		{ "listconnectedtanks" , &Functions::list_connected_tanks },
		{ "printfueltankcount" , &Functions::print_fuel_tank_count },
		{ "printtotalfuelquantity" , &Functions::print_total_fuel_quantity },
		{ "printtotalconsumedfuelquantity" , &Functions::print_total_consumed_fuel_quantity },
	};
	fmap1 = {
		{ "wait" , &Functions::wait },
		{ "openvalve" , &Functions::open_valve },
		{ "closevalve" , &Functions::close_valve },
		{ "addfueltank" , &Functions::add_fuel_tank },
		{ "fullthrottle" ,&Functions::full_throttle },
		{ "printtankinfo" , &Functions::print_tank_info },
		{ "breakfueltank" , &Functions::break_fuel_tank },
		{ "repairfueltank" , &Functions::repair_fuel_tank },
		{ "removefueltank" , &Functions::remove_fuel_tank },
		{ "connectfueltanktoengine" , &Functions::connect_fuel_tank_to_engine },
		{ "disconnectfueltankfromengine" , &Functions::disconnect_fuel_tank_from_engine },
	};
	fmap2 = {
		{ "filltank" , &Functions::fill_tank }
	};
	fmap3 = {
		{ "sumoperator" , &Functions::sum_operator }
	};
}
Functions* Functions::get_func()
{
	if (!func)
		func = new Functions();
	return func;
}
Functions::~Functions()
{
	fmap0.clear();
	fmap1.clear();
	fmap2.clear();
	fmap3.clear();

	time->~Time();
	instance->~Engine();
	time = NULL;
	instance = NULL;
	func = NULL;
	delete func;
	delete time;
	delete instance;
}
void Functions::Run()
{
	std::string* p = nullptr;
	std::string tmp="", str = "";
	
	while (window.isOpen())
	{
		if (open)
		{
			time->a_second();

			p = (Input::get_input())->get_command();
			tmp = str = *p;

			int i = 0;
			*Output::out() << "[COMMAND]: " << str << " ";
			while (i < stoi(*(p + 4)) - 1)
			{
				i++;
				tmp += " " + *(p + i);
				*Output::out() << *(p + i) << " ";
			}
			*Output::out() << std::endl;


			if (*(p + 4) == "1" && fmap0.find(str) != fmap0.end())
				(this->*(fmap0[(*p)]))();
			else if (*(p + 4) == "2" && fmap1.find(str) != fmap1.end())
				(this->*(fmap1[(*p)]))(stod(*(p + 1)));
			else if (*(p + 4) == "3" && fmap2.find(str) != fmap2.end())
				(this->*(fmap2[(*p)]))(stod(*(p + 1)), stod(*(p + 2)));
			else if (*(p + 4) == "4" && fmap3.find(str) != fmap3.end())
				(this->*(fmap3[(*p)]))(stod(*(p + 1)), stod(*(p + 2)), stod(*(p + 3)));
			else
				*Output::out() << "[ERROR]: Command Is Not Exist !\n";
			*Output::out() << "====================================================\n";
			if (tmp == "stopsimulation")
				text.setString("SIMULATION STOPPED");
			else
				text.setString(tmp);
			text.setOrigin(text.getGlobalBounds().width / 2.0, 0);
			if (instance->get_status())
				Sleep(1100);
			else
				Sleep(700);
		}
		run_window();
	}
	p = NULL;
	delete p;
	this->~Functions();
}

void Functions::run_window()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				if (sprite_sim.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					open = 1;
			break;
		default:
			break;
		}
	}
	window.clear(sf::Color::Color(230,255,40));
	window.draw(rect);
	if (!open)
		window.draw(sprite_sim);
	instance->render(&window);
	instance->get_constructor_of_tanks()->render(&window);
	window.draw(text);
	window.draw(sprite);
	window.display();
}
