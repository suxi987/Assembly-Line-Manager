// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 11/19/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"
using namespace std;

namespace sdds {

	// class variables initilization
	char Utilities::m_delimiter{ 1 };

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string tempStr{};
		size_t lastPos{};

		if (m_delimiter && str.size())
		{
			lastPos = str.find(m_delimiter, next_pos);
			tempStr = str.substr(next_pos, lastPos - next_pos);
			tempStr.size() ? tempStr = trim(tempStr) : tempStr;
			next_pos = lastPos + 1;

			if (m_widthField < tempStr.size()) // update the m_widthField
			{
				m_widthField = tempStr.size();
			}
		}

		if (lastPos == string::npos || lastPos == 0) // if the index reaches the end or 0, set more to false 
		{
			more = false;
		}
		if (!tempStr.size() || next_pos == lastPos) // if extracted string is empty or delimiter is found at next_pos, throw
		{
			more = false;
			throw std::string("Error");			
		}

		return tempStr;
	}

	std::string Utilities::trim(const std::string& res)
	{
		size_t start = res.find_first_not_of(' ');
		size_t end = res.find_last_not_of(' ');
		string str = res.substr(start, end - start + 1);

		return str;
	}

}