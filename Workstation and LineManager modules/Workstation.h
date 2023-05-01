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
