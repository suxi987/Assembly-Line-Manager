// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 12/3/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Workstation.h"
#include "Utilities.h"
using namespace std;

namespace sdds {
    // initialize the externs
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    void Workstation::fill(std::ostream& os)
    {
        if (m_orders.size())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;
        
        if (!m_orders.empty())
        {
            if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() < 1)
            {
                if (m_pNextStation) // if next station exists, push the order
                {
                    m_pNextStation->m_orders.push_back(move(m_orders.front())); 
                } 
                else // if it is the end of the line, check order completion
                {
                    if (m_orders.front().isOrderFilled())
                    {
                        g_completed.push_back(std::move(m_orders.front())); 
                    }
                    else
                    {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                m_orders.pop_front(); // remove the empty order after it's moved
                moved = true;
            }
        }
        return moved;
    }

    void Workstation::display(std::ostream& os) const
    {
        os << Station::getItemName() << " --> ";
        if (m_pNextStation)
        {
            os << m_pNextStation->Station::getItemName();
        }
        else
        {
            os << "End of Line";
        }
        os << endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {        
        m_orders.push_back(std::move(newOrder));

        return *this;
    }
}