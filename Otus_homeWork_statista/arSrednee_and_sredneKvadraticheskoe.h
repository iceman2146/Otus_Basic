#pragma once
#include <cmath>
#include <vector>
#include <numeric>
#include "baseStatistic.h"
class IStatistics;
class Mean : public IStatistics
{
public:
	Mean() : sum{0}, numCounter{0}
	{
	}

	void update(double next) override
	{
		// std::cout<<sum<<std::endl;
		sum += next;

		++numCounter;
	}

	double eval() const override
	{
		return sum / numCounter;
	}

	const char *name() const override
	{
		return "mean";
	}

private:
	double sum;
	int numCounter;
};
class Std : public IStatistics
{
public:
	Std() : sum{0}, numCounter{0}
	{
	}

	void update(double next) override
	{
		input_arr.push_back(next);
		// int i=0;
		// std::cout<<i++<<std::endl;
		// input_array[numCounter - 1] = next;
		// sum += next;
		//++numCounter;
	}

	double eval() const override
	{
		double temp_sum=0.0;
		double sum = 0.0;
		sum = std::accumulate(input_arr.begin(), input_arr.end(), 0.0);
		double mean=static_cast<double>(sum/input_arr.size());
		// for (int i = 0; i < numCounter; i++)
		//{
		//	temp_sum += ((input_array[i] - (sum / numCounter)) * (input_array[i] - (sum / numCounter))) / numCounter;
		// }
		std::vector<double> new_arr;
		/*for each(double var in input_arr)
		{
			std::cout<<" . ";
			temp_sum+=(var-mean)*(var-mean);	
		}*/
		for(int i=0;i<input_arr.size();i++)
		{
			
			temp_sum+=(input_arr[i]-mean)*(input_arr[i]-mean);
		}
		temp_sum=temp_sum/input_arr.size();


		return std::sqrt(temp_sum);
	}

	const char *name() const override
	{
		
		return "std";
	}

private:
	double sum;
	int numCounter;
	double *input_array = new double[numCounter];
	std::vector<double> input_arr;
};