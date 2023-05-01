// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 12/3/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{	
		try {
			if (!file.empty())
			{
				ifstream infile(file);
				string str{}, currentStation{}, nextStation{};
				Utilities tempU{};

				if (infile.is_open())
				{
					while (getline(infile, str, '\n'))
					{
						size_t nextPos = 0;
						bool more = true;

						// get the current station from the data file
						currentStation = tempU.extractToken(str, nextPos, more);
						if (more)
						{
							// get the next station from the data file
							nextStation = tempU.extractToken(str, nextPos, more);
						}
						else
						{
							nextStation = "End of Line";
						}

						// find the station name that matches the captured strings, stores the results in iterators that points to the element of Workstation* stations
						auto activeIter = std::find_if(stations.begin(), stations.end(), [=](const Workstation* ptr)
							{
								return ptr->getItemName() == currentStation;
							});

						auto nextIter = std::find_if(stations.begin(), stations.end(), [=](const Workstation* ptr)
							{
								return ptr->getItemName() == nextStation;
							});

						// stores the workstations in the order received to m_activeLine
						m_activeLine.push_back(*activeIter);

						// If there is a next station, stores the address of the next workstation in each element
						if (nextStation != "End of Line")
						{
							(*activeIter)->setNextStation(*nextIter);
						}
					}

					// identify the m_firstStation
					std::for_each(stations.begin(), stations.end(), [=](Workstation* ptr1)
						{
							// nested loop, if stations have no address to match with next stations, assign that none_of address to m_firstStation
							auto found = std::none_of(stations.begin(), stations.end(), [=](const Workstation* ptr2) { return ptr2->getNextStation() == ptr1; });
							
							if (found && ptr1->getNextStation())
							{
								m_firstStation = ptr1;
							}							
						});

					// update the m_cnt with the value of CustomerOrder g_pending
					m_cntCustomerOrder = g_pending.size();
				}
			}
		}
		catch (...)
		{
			throw std::string("Something is wrong");
		}
	}

	void LineManager::reorderStations()
	{
		std::vector<Workstation*> temp{};

		// start with the first station
		temp.push_back(m_firstStation);

		// proceeds to the next station
		while (temp.size() < m_activeLine.size())
		{
			auto it = temp.back();
			temp.push_back(it->getNextStation());
		}
		m_activeLine = temp;
	}

	bool LineManager::run(std::ostream& os)
	{
		static int count{};

		// keep track of the number of being called
		++count;
		os << "Line Manager Iteration: " << count << endl;

		if (!g_pending.empty())
		{
			// moves the g_pending orders to m_firstStation in the form of FIFO
			(*m_firstStation) += std::move(g_pending.front());

			// remove the empty g_pending at the front after its data is moved to Workstation
			g_pending.pop_front();
		}

		// for each station, executes fill operation
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr) { ptr->fill(os); });

		// move the unfilled order down the line
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr) { ptr->attemptToMoveOrder(); });

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder; // check all orders have been processed
	}

	void LineManager::display(std::ostream& os) const
	{
		for (auto i : m_activeLine)
		{
			i->display(os);
		}
	}


}