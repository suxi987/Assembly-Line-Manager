// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 11/19/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>

namespace sdds {
	class Utilities
	{
		size_t m_widthField = 1;
		static char m_delimiter; // class variable
	public:		
		void setFieldWidth(size_t newWidth) { m_widthField = newWidth; }
		size_t getFieldWidth() const { return m_widthField; }
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		std::string trim(const std::string& res);

		// class functions
		static void setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }
		static char getDelimiter() { return m_delimiter; }
	};
}
#endif