#include "Functions.h"

using namespace std;

Functions* Functions::func = nullptr;
Engine* Engine::instance = nullptr;	//STATIC Initialize
Time* Time::time = nullptr;
Input* Input::input = nullptr;
std::ofstream* Output::outfile = nullptr;
Output* Output::output = nullptr;
int Tank::count_of_tanks = 0;

int main()
{
	try {
		Functions* functions=Functions::get_func();
		functions->Run();
	}
	catch (exception const& ex) {
		cerr << "Exception: " << ex.what() << endl;
		return -1;
	}
	return 0;
}

