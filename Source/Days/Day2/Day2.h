#pragma once

#include "Day.h"

// #define TEST_INPUT

class Day2
	: public AocDay
{
public:
	Day2()
		: AocDay(1)
	{
	}

	std::vector<std::vector<std::string>> ReadInput(std::string filename)
	{
#ifdef TEST_INPUT
		return {
			{ "forward", "5" },
			{ "down", "5" },
			{ "forward", "8" },
			{ "up", "3" },
			{ "down", "8" },
			{ "forward", "2" }
		};
#endif
		std::vector<std::vector<std::string>> lines;
		ReadAsSplitStrings(filename, lines, ' ');
		return lines;
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		int x = 0;
		int y = 0;
		
		for (auto& line : ReadInput(filename))
		{
			int amount = std::stoi(line[1]);
			if (line[0].at(0) == 'f')
			{
				x += amount;
			}
			else if (line[0].at(0) == 'd')
			{
				y += amount;
			}
			else if (line[0].at(0) == 'u')
			{
				y -= amount;
			}
		}

		return std::to_string(x * y);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		int x = 0;
		int y = 0;
		int aim = 0;

		for (auto& line : ReadInput(filename))
		{
			int amount = std::stoi(line[1]);
			if (line[0].at(0) == 'f')
			{
				x += amount;
				y += (aim * amount);
			}
			else if (line[0].at(0) == 'd')
			{
				aim += amount;
			}
			else if (line[0].at(0) == 'u')
			{
				aim -= amount;
			}
		}

		return std::to_string(x * y);
	}
};