#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager
	{
		std::vector<Workstation*> m_activeLine{}; // actual order of stations
		size_t m_cntCustomerOrder{}; // should be the same as g_pending queue
		Workstation* m_firstStation{}; // beginning of the first station

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif
