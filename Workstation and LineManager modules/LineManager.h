// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 12/3/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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