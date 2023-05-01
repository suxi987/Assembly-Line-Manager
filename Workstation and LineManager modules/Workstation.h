// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 12/3/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
	// The three deques
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{ nullptr };

	public:
		Workstation(const std::string& str) : Station(str) {}
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station) { m_pNextStation = station; }
		Workstation* getNextStation() const { return m_pNextStation; }
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		// Rule of five, prohibiting copy and move operations
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		Workstation& operator=(Workstation&& src) = delete;
		~Workstation() {}
	};
}
#endif