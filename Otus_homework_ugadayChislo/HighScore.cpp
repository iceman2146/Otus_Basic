#include "HighScore.h"

#include <iostream>
#include <iomanip>
#include <fstream>


//int CreateandWriteinFile(const std::string& user_name, int atempt) //con
int CreateandWriteinFile(person Player)
{

	const std::string high_scores_filename = "high_scores.txt";

		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
		// Append new results to the table:
		out_file << Player.user_name << ' ';
		out_file << Player.attempt;
		out_file << std::endl;
}
int ReadFile()
	{
		int size=100;
		person* savedata=new person[size];	

		
        char answer;
        std::cout<<"Posmotrim records?(y or somthing else)";
        std::cin>>answer;
        if(answer=='y')
        {
        const std::string high_scores_filename = "high_scores.txt";
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
		int counter=0;
		while (true)
		 {
			// Read the username first
			in_file >>  savedata[counter].user_name;
			
			// Read the high score next
			in_file >> savedata[counter].attempt;
			// Ignore the end of line symbol
			in_file.ignore();
			counter++;

			if (in_file.fail()) {
				break;
			}
		}
		
		qSortMas(savedata,counter);
		removeNulEllemFromMas(savedata,counter);
		

		//removeDuplicatedEllemFromMas(savedata,counter);//!!!!!в данном цикле ошибка, не могу понять почему, но обязательно разберусь
		std::cout << "High scores table:" <<counter<< std::endl;
		
		for(int i=0;i<counter-1;i++)
		{
			std::cout<<std::setw(10)<<std::setiosflags(std::ios::left)<<savedata[i].user_name<<":       "<<savedata[i].attempt<<std::endl;
		}
		
		
		}
        
        return 0;
	}

void qSortMas(person *massive, int size)

{
	int nachalo_massiva=0;
	int Konec_massiva=size-1;
	person middle_ellement=massive[size/2];

	do
	{
		while(massive[nachalo_massiva].attempt<middle_ellement.attempt){nachalo_massiva++;}
		while(massive[Konec_massiva].attempt>middle_ellement.attempt){Konec_massiva--;}
		if(nachalo_massiva<=Konec_massiva)
		{
			person tmp;
			tmp=massive[nachalo_massiva];
			massive[nachalo_massiva]=massive[Konec_massiva];
			massive[Konec_massiva]=tmp;
			nachalo_massiva++;
			Konec_massiva--;
		}

	}while (nachalo_massiva<=Konec_massiva);
	if(Konec_massiva>0)
	qSortMas(massive,Konec_massiva+1);
	if(nachalo_massiva<size)
	qSortMas(&massive[nachalo_massiva],size-nachalo_massiva);
	
}
void removeNulEllemFromMas(person *massive, int &size)
{
	int nullCounter=0;
	for (int i=0;i<size-1;i++)
	{
		if(massive[i].attempt<=0) nullCounter++;
	}
	for (int i=0;i<size-1;i++)
	{
		massive[i].user_name=massive[i+nullCounter].user_name;
		massive[i].attempt=massive[i+nullCounter].attempt;
	}
	size-=nullCounter;
}

void removeDuplicatedEllemFromMas(person *massive, int &size)
{
	int counter=0;
	for (int i=0;i<size;i++){
		for (int j=i+1;j<size;j++){
			if(massive[i].user_name==massive[j].user_name){
				massive[j].user_name=massive[j+1].user_name;
				massive[j].attempt=massive[j+1].attempt;
				size--;
			}
		}
	}
}