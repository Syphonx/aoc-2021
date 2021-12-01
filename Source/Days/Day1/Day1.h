#pragma once

#include "Day.h"

class Day1
	: public AocDay
{
public:
	Day1()
		: AocDay(1)
	{
	}

	std::vector<long> ReadInput(std::string filename)
	{
		std::vector<std::string> lines;
		std::vector<long> data;

		if (!ReadAsStrings(filename, lines))
		{
			std::cerr << "Error reading in the data from " << filename << std::endl;
			return data;
		}

		for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
		{
			long l;
			std::string to_convert = *iter;
			l = strtol(to_convert.c_str(), NULL, 10);
			data.push_back(l);
		}

		return data;
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		return "";
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		return "";
	}
};