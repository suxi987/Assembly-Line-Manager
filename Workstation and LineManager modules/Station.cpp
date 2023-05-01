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
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds {	

	// class variables initilization
	size_t Station::m_widthField{ 0 };
	int Station::id_generator{ 0 };

	Station::Station(const std::string& str)
	{
		Utilities tempU{};
		size_t nextPos = 0;
		bool more = true;

		m_id = ++id_generator; // id increases by 1 everytime a object is created
		m_name = tempU.extractToken(str, nextPos, more);
		m_serialNo = stoi(tempU.extractToken(str, nextPos, more));
		m_quantity = stoi(tempU.extractToken(str, nextPos, more));
		
		if (Station::m_widthField < tempU.Utilities::getFieldWidth()) // compare and update the max value between Station and Utilities
		{
			m_widthField = tempU.Utilities::getFieldWidth();
		}

		m_desc = tempU.extractToken(str, nextPos, more);
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (!full)
		{
			os << setfill('0') << setw(3) << right << m_id << setfill(' ') << " | "
				<< setw(m_widthField) << left << m_name << "  | "
				<< setfill('0') << setw(6) << right << m_serialNo << setfill(' ') << " | "
				<< endl;
		}
		else
		{
			os << setfill('0') << setw(3) << right << m_id << setfill(' ') << " | "
				<< setw(m_widthField) << left << m_name << "  | "
				<< setfill('0') << setw(6) << right << m_serialNo << setfill(' ') << " | "
				<< setw(4) << m_quantity << " | " 
				<< m_desc << endl;
		}
	}
}