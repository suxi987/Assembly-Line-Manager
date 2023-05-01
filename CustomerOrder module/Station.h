// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 11/19/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds {
	class Station
	{
		int m_id{};
		std::string m_name{};
		std::string m_desc{};
		size_t m_serialNo{};
		size_t m_quantity{};

		// class variables
		static size_t m_widthField;
		static int id_generator;
	public:
		Station() {}
		Station(std::string& str);
		const std::string& getItemName() const { return m_name; }
		size_t getNextSerialNumber() { return m_serialNo++; }
		size_t getQuantity() const { return m_quantity; }
		void updateQuantity() { m_quantity--; }
		void display(std::ostream& os, bool full) const;
	};
}
#endif