#include "IO.h"

Input::Input()
{
	InFile.open("file.txt");
	if (!InFile.is_open())
		throw std::exception("Input File Couldn't Open !");
	std::cout<<std::endl;
}
Input* Input::get_input()
{
	if (!input)
		input = new Input();
	return input;
}
std::string* Input::get_command()
{
	std::string str;
	static std::string parts_of_line[5];
	if (InFile.eof())
	{
		std::cout << "\n[ERROR]: Please, do not forget last command 'stop_simulation'\n";
		parts_of_line[0] = "stopsimulation";
		parts_of_line[4] = "1";
		return parts_of_line;
	}
	getline(InFile, str);
	str.erase(std::remove(str.begin(), str.end(), '_'), str.end());
	std::stringstream sstream_of_a_line(str);
	int i = 0;
	while (1)
	{
		sstream_of_a_line >> parts_of_line[i];
		if (parts_of_line[i][parts_of_line[i].size() - 1] == ';')
		{
			parts_of_line[i].pop_back();
			break;
		}
		i++;
	}
	parts_of_line[4] = std::to_string(i + 1);
	return parts_of_line;
}

Output::Output()
{
	outfile = new std::ofstream("out.txt");
	std::cout<<std::endl;
}
std::ofstream* Output::out()
{
	if (!outfile)
		output = new Output();
	return outfile;
}
