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
