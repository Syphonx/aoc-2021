#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

/*. 
	@input - the input string to split. assume newline is removed, or else it will be addded to the last item
	@delimiter - the value to split on
	@quote - an optional parameter - a quote character to indicate a that quoted sections will be used and ignore delimiters
	@comment_char - an optional parameter - if this is the first character in a line, that line is treated as a comment and skipped.
*/
static std::vector<std::string> SplitLineToStrings(std::string input, char delimiter, char quote_char, char comment_char)
{
#ifdef DEBUG_RUNNER
	std::cout << "original input is [" << input << "]" << std::endl;
#endif

	std::vector<std::string> splits;
	char* pos = (char*)input.c_str();

	if (comment_char && *pos == comment_char)
	{
#ifdef DEBUG_RUNNER
		std::cout << "Comment line found" << std::endl;
#endif
		return splits;
	}

	bool in_quote = false;
	std::ostringstream current;
	while (*pos != '\0')
	{
		if (quote_char && in_quote)
		{
			if (*pos == quote_char)
			{
				in_quote = false;
#ifdef DEBUG_RUNNER
				std::cout << "Leaving quotes" << std::endl;
#endif
			}
			else
			{
				current << (*pos);
			}
		}
		else
		{
			if (quote_char && *pos == quote_char)
			{
				in_quote = true;
#ifdef DEBUG_RUNNER
				std::cout << "In quotes" << std::endl;
#endif
			}
			else if (*pos == delimiter)
			{
				// ABCDE,ABCDE,ABCDE
				// first string goes from 0 to 4...construct as string(0,5). pos will be 5 for the comma. so 5-0=5
				// second string goes from 6 to 10...construct as string(6,5)...pos wil be 11 for the comma. so 11-6=5
				// third string goes from 12 to 16...construct as string(12,5) but need to do this out of loop as its the last string
#ifdef DEBUG_RUNNER
				std::cout << "appending [" << current.str() << "] as a string" << std::endl;
#endif
				splits.push_back(current.str());
				current = std::ostringstream();
			}
			else
			{
				current << (*pos);
			}
		}
		pos++;
	}

	// append the last string. pos will be pointed to the null terminator at 17, so string(12,5) would be pos(17)-start(12)
#ifdef DEBUG_RUNNER
	std::cout << "appending [" << current.str() << "] as the last string" << std::endl;
#endif
	splits.push_back(current.str());

	return splits;
}

static bool ReadAsStrings(std::string filename, std::vector<std::string> & lines)
{
	std::ifstream infile(filename);
	if (!infile)
	{
		std::cerr << "*****Error opening file " << filename << std::endl;
		return false;
	}

	std::string line;
	while (getline(infile, line))
	{
#ifdef DEBUG_RUNNER
		std::cout << "Read line [" << line << "] from file" << std::endl;
#endif
		lines.push_back(line);
	}
	infile.close();

	return true;
}

static bool ReadAsSplitStrings(std::string filename, std::vector<std::vector<std::string>> & split_strings, char delimiter, char quote_char, char comment_char)
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		std::vector<std::string> results = SplitLineToStrings(*iter, delimiter, quote_char, comment_char);
		if (results.size() > 0)
		{
			split_strings.push_back(results);
		}
	}

	return true;
}

static bool ReadAsSplitLongs(std::string filename, std::vector<std::vector<long>> & split_longs, char delimiter, char quote_char, char comment_char)
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		std::vector<std::string> long_strings = SplitLineToStrings(*iter, delimiter, quote_char, comment_char);
		std::vector<long> longs;

		for (std::vector<std::string>::iterator str_long_iter = long_strings.begin(); str_long_iter != long_strings.end(); ++str_long_iter)
		{
			std::string str_long = *str_long_iter;
			longs.push_back(strtol(str_long.c_str(), NULL, 10));
		}

		split_longs.push_back(longs);
	}

	return true;
}