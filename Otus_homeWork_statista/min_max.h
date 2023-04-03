#pragma once
#include "baseStatistic.h"


class IStatistics;
class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics 
{
public:
	Max() : m_max{ std::numeric_limits<double>::lowest() } 
	{
		
	}

	void update(double next) override 
	{
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override 
	{
		return m_max;
	}

	const char* name() const override 
	{
		return "max";
	}

private:
	double m_max;
};