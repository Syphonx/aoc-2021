#include <iostream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <stack>
#include <deque>
#include <stdlib.h>

#include "Days.h"

struct Advent
{
	AocDay* day;
	std::string input;
};

static const Advent s_Advent[] =
{
	{ new Day1(),  "Input/Day01.txt" },
	{ new Day2(),  "Input/Day02.txt" },
	{ new Day3(),  "Input/Day03.txt" },
	{ new Day4(),  "Input/Day04.txt" },
	{ new Day5(),  "Input/Day05.txt" },
	{ new Day6(),  "Input/Day06.txt" },
	{ new Day7(),  "Input/Day07.txt" },
	{ new Day8(),  "Input/Day08.txt" },
	{ new Day9(),  "Input/Day09.txt" },
	{ new Day10(), "Input/Day10.txt" },
	{ new Day11(), "Input/Day11.txt" },
	{ new Day12(), "Input/Day12.txt" },
	{ new Day13(), "Input/Day13.txt" },
	{ new Day14(), "Input/Day14.txt" },
	{ new Day15(), "Input/Day15.txt" },
	{ new Day16(), "Input/Day16.txt" },
	{ new Day17(), "Input/Day17.txt" },
	{ new Day18(), "Input/Day18.txt" },
	{ new Day19(), "Input/Day19.txt" },
	{ new Day20(), "Input/Day20.txt" },
	{ new Day21(), "Input/Day21.txt" },
	{ new Day22(), "Input/Day22.txt" },
	{ new Day23(), "Input/Day23.txt" },
	{ new Day24(), "Input/Day24.txt" },
	{ new Day25(), "Input/Day25.txt" },
};

struct CommandLine
{
	CommandLine()
		: day(0)
		, part(0)
		, extra_args()
	{
	}

	bool RunSpecificDay() const
	{
		return day != 0;
	}

	bool RunSpecificPart() const
	{
		return part != 0;
	}

	int day;
	int part;
	std::vector<std::string> extra_args;
};

void usage(std::string prog_name)
{
	std::cerr << "Usage for " << prog_name << std::endl;
	std::cerr << "   Run all: " << prog_name << " -a" << std::endl;
	std::cerr << "   Run one day: " << prog_name << " -d day [extra_args...]" << std::endl;
	std::cerr << "   Run one day/part: " << prog_name << " -d day -p part" << std::endl;
}

double BenchPart(const Advent& advent, int part)
{
	double totalTime = 0;
	auto now = std::chrono::steady_clock::now();
	std::string result;
	
	if (part == 1)
	{
		result = advent.day->part1(advent.input, {});
	}
	else if (part == 2)
	{
		result = advent.day->part2(advent.input, {});
	}
	
	auto elapsed = std::chrono::steady_clock::now() - now;
	printf("Part %d: %s\n", part, result.c_str());
	totalTime += elapsed.count();
	printf("Took: [%lld us]\n", int64_t(elapsed.count() * 1e-3));

	return totalTime;
}

double BenchDay(const Advent& advent, int part)
{
	printf("\nRunning solution for Day %d...\n", advent.day->GetDay());

	double totalTime = 0;

	if (part == 0)
	{
		totalTime += BenchPart(advent, 1);
		totalTime += BenchPart(advent, 2);
	}
	else
	{
		if (part == 1)
		{
			totalTime += BenchPart(advent, 1);
		}
		else if (part == 2)
		{
			totalTime += BenchPart(advent, 2);
		}
	}

	return totalTime;
}

int main(int argc, char* argv[])
{
	CommandLine cmd;
	std::deque<std::string> args;
	for (int i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	if (args.size() == 0)
	{
		usage("AoC");
		return 1;
	}

	while (!args.empty())
	{
		std::string arg = args.front();
		args.pop_front();

		if (arg == "-d" || arg == "-p")
		{
			std::string val = args.front();
			args.pop_front();

			if (arg == "-d")
			{
				cmd.day = std::stoi(val);
			}
			else if (arg == "-p")
			{
				cmd.part = std::stoi(val);
			}
		}
		else
		{
			if (arg == "-a")
			{
				cmd.day = 0;
				cmd.part = 0;
			}
		}
	}

	double totalTime = 0;

	if (cmd.RunSpecificDay())
	{
		totalTime += BenchDay(s_Advent[cmd.day - 1], cmd.part);
	}
	else
	{
		for (const Advent& advent : s_Advent)
		{
			totalTime += BenchDay(advent, cmd.part);
		}
	}

	printf("\nTotal: %lld us\n", int64_t(totalTime * 1e-3));

	return 0;
}