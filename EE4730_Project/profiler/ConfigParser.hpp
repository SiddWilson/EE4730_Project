#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <functional>
#include <locale>
#include <cstdlib>
#include <vector>

#include "Defines.hpp"

namespace Common
{
	const char ConfigDelimiter = ':';

	inline std::string removeWhitespace(const std::string& is)
	{
		std::string s = is;
		//// Not very safe version: http://stackoverflow.com/questions/14233065/remove-whitespace-in-stdstring
		//s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

		// Supposedly safer than above
		s.erase(std::remove_if(s.begin(), s.end(), std::bind(std::isspace<char>, std::placeholders::_1, std::locale::classic())), s.end());

		return s;
	};

	inline std::vector<std::string>& tokenize(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) 
		{
			elems.push_back(item);
		}
		return elems;
	};

	inline std::vector<std::string> tokenize(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		tokenize(s, delim, elems);
		return elems;
	};

	inline std::vector<VPFloat> strvec2float(const std::vector<std::string>& Values)
	{
		std::vector<VPFloat> FValues;
		for (auto& Val : Values)
			FValues.push_back(std::atof(Val.c_str()));

		return FValues;
	};

	inline std::vector<VPFloat> parseValueCS(const std::string& Value)
	{
		std::vector<VPFloat> OutScales;
		if (Value.empty() == false)
		{
			auto CSValues = Common::strvec2float(Common::tokenize(Value, ','));
			for (auto& CSV : CSValues)
				OutScales.push_back(CSV);
		}

		return OutScales;
	};

	// Parse ini-type files
	inline std::map<std::string, std::string> parseConfigFile(const std::string& FileName)
	{
		std::map<std::string, std::string> Output;
		std::fstream File(FileName, std::ios::in);

		if (File.is_open())
		{
			// Parse line by line
			std::string Line;
			while (std::getline(File, Line))
			{
				if (Line[0] == '#' || Line[0] == '%') // Comment lines
					continue;

				auto Splits = Common::tokenize(Line, ConfigDelimiter);
				if (Splits.size() > 2)
				{
					std::cout << "[ WARN ]: parseConfigFile() - (> 3) delimiters (" << ConfigDelimiter << ") found in the following line in the file " << FileName << "\n" << Line << std::endl;
					return Output;
				}
				if (Splits.size() < 2) // Skip this line as a newline or comment line
					continue;

				std::string Key = Common::removeWhitespace(Splits[0]);
				std::string Value = Common::removeWhitespace(Splits[1]);
				//std::cout << "Found key " << Key << " and value " << Value << std::endl;
				Output.insert(std::make_pair(Key, Value));
			}
		}
		else
			std::cout << "[ WARN ]: parseConfigFile() - Unable to open file " << FileName << std::endl;

		return Output;
	};
} // namespace Common
