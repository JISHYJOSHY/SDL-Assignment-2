#include "Application.h"

int main(int argc, char* argv[])
{
	Application app(1280, 720);

	if(app.init())
		app.run();

	return 0;
}