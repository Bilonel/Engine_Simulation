#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <stdexcept>

class Input
{
private:
	std::ifstream InFile;
	static Input* input;
	Input();
public:
	static Input* get_input();
	std::string* get_command();
};

class Output
{
private:
	static std::ofstream* outfile;
	static Output* output;
	Output();
public:
	static std::ofstream* out();
};
