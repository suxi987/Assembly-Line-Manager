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
