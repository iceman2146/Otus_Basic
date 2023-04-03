#include <iostream>
#include <string>
#include <typeinfo>

#include "ZagadaiChislo.h"
#include "HighScore.h"


void GameLoop(int a, int b,int&c);
void Setup(int&,int);


int main(int argc, char** argv)
 {
	person Player;
	int max_value=100;
	if (argc>1&&!strcmp(argv[1],"-max")&&(argv[2])&&atoi(argv[2])>0)
		max_value=atoi(argv[2]);
	else if(argc>1&&!strcmp(argv[1],"-table"))
	{
		ReadFile();
		return 0;
	}
	else if (argc>1&&!strcmp(argv[1],"-level")&&(argv[2])&&atoi(argv[2])>0)
		switch (atoi(argv[2]))
		{
		case 1:
			max_value=10;
			break;
		case 2:
			max_value=50;
			break;
		case 3:
			max_value=100;
			break;
		default:
			break;
		}
	else
	max_value=100;
	//std::cout<<(argc > 1&&std::string(argv[1])=="-max")<<max_value <<std::endl;

    //std::string user_name;
	Player.attempt=1;

    int target;
    int current_value=0;
    std::cout << "Hi! Enter your name, please:" << std::endl;
	std::cin >> Player.user_name;

    Setup(target,max_value);


std::cout << target << std::endl;//лень
std::cout <<Player.user_name <<" enter your guess:" << std::endl;

GameLoop(current_value,target, Player.attempt);
CreateandWriteinFile (Player);
ReadFile();
	return 0; 
}

void GameLoop(int current_value, int target, int& attempt)
{
	
    	do {
		std::cin >> current_value;

		if (current_value < target) {
			std::cout << "Less " << current_value << std::endl;
			attempt++;
		}
		else if (current_value > target) {
			std::cout << "Greater " << current_value << std::endl;
			attempt++;
		}
		else {
			std::cout << "Win!" << std::endl;
			break;
		}

	} while(true);

}
void Setup(int &target, int max_value)
{
    target=ZagadayChislo(max_value);
}