#include "IO.h"

class Tank
{
protected:
	double capacity;
	double fuel_quantity = 0;
	bool broken = 0;
	bool valve = 0;
	bool connected = 0;
	int id;
	static int count_of_tanks;

	sf::RectangleShape tank_b;
	sf::RectangleShape tank;
	sf::Text tank_t;
	sf::Font font;
	sf::Texture texture,tex;
	sf::Sprite sprite,sp;
public:
	Tank(double c) : capacity(c),id(count_of_tanks++)
	{
		if (!font.loadFromFile("calibri.ttf"))
			std::cerr << "LOAD ERROR";
		texture.loadFromFile("res/pipe.png");
		tex.loadFromFile("res/tank.png");
		sp.setTexture(tex);
		sprite.setTexture(texture);
		sp.setScale(0.15, 0.15);
		tank.setSize(sf::Vector2f(sp.getGlobalBounds().width, 0));
		tank.setFillColor(sf::Color::Cyan);
		tank_t.setString(std::to_string(id));
		tank_t.setFont(font);
		tank_t.setCharacterSize(24);
		tank_t.setStyle(sf::Text::Bold);
		tank_t.setFillColor(sf::Color::Black);
		sprite.setScale(0.07, 0.1);
	}
	~Tank();
	void render(sf::RenderWindow* win, double x,double y)
	{
		sprite.setPosition(x-sprite.getGlobalBounds().width, y-8);
		tank.setPosition(x, y+ sp.getGlobalBounds().height);
		tank.setSize(sf::Vector2f(sp.getGlobalBounds().width, -sp.getGlobalBounds().height * fuel_quantity / capacity));
		sp.setPosition(x, y);
		tank_t.setPosition(x+35, y+50);
		if (get_connection())
			win->draw(sprite);
		win->draw(tank);
		win->draw(sp);
		win->draw(tank_t);
	}
	virtual void print() {}
	virtual Tank operator+ (Tank& fueltank) { return *this; }
	void operator= (Tank fueltank) { set_fuel_quantity(fuel_quantity + fueltank.get_fuel_quantity()); }
	void set_broken(bool t);
	double get_fuel_quantity() { return fuel_quantity; }
	void set_fuel_quantity(double q);
	double get_capacity() { return capacity; }
	bool get_broken() { return broken; }
	void set_valve(bool t);
	bool get_valve() { return valve; }
	void set_connection(bool is) { connected = is; }
	bool get_connection() { return connected; }
	int get_id() { return id; }
};

