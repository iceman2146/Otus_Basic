#include "ZagadaiChislo.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
    
int ZagadayChislo(int max)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % max;
    return random_value;
}