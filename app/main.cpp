#include "app.h"
#include <iostream>
int main(int argc, char** argv)
{
	if (App::init(argc, argv)) {
		App::start();
		App::close();
	}

	return 0;
}
