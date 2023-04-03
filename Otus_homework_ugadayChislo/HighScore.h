#pragma once
#include <string>
struct person
{
    std::string user_name="none";
	int attempt=0;
};
//int CreateandWriteinFile(const std::string& user_name, int atempt);
int CreateandWriteinFile(person p);
int ReadFile();
//void WriteFile();
void qSortMas(person*,int);
void removeNulEllemFromMas(person*,int&);
void removeDuplicatedEllemFromMas(person*,int&);