// Name: Wai Hing William Tse
// Seneca Student ID: 149 992 216
// Seneca email: wtse11@myseneca.ca
// Date of completion: 11/26/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;

namespace sdds {

	// class variables initilization
	size_t CustomerOrder::m_widthField{ 0 };

	void CustomerOrder::deallocate()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities tempU{};
		size_t nextPos = 0;
		bool more = true;
				
		m_name = tempU.extractToken(str, nextPos, more);
		m_product = tempU.extractToken(str, nextPos, more);
		m_cntItem = (std::count(str.begin(), str.end(), Utilities::getDelimiter())) - 1; // count with delimiters, - 1 refers to the initial '|' in the data file in every line
		
		// 2-layer DMA: array then each element
		m_lstItem = new Item* [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			m_lstItem[i] = new Item(tempU.extractToken(str, nextPos, more));
		}		
		
		// compare and update the max value between Station and Utilities
		if (CustomerOrder::m_widthField < tempU.Utilities::getFieldWidth()) 
		{
			m_widthField = tempU.Utilities::getFieldWidth();
		}
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool filledOrNot = true;

		for (size_t i = 0; i < m_cntItem && filledOrNot == true; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				filledOrNot = false;
			}
		}
		return filledOrNot;


	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filledOrNot = true;

		for (size_t i = 0; i < m_cntItem && filledOrNot == true; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false)
			{
				filledOrNot = false;
			}
		}
		return filledOrNot;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool haveIt = false;		

		for (size_t i = 0; i < m_cntItem && haveIt == false; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) // if station has it and order item is unfilled
			{
				haveIt = true;
			}

			if (haveIt)
			{
				if (station.getQuantity() > 0)
				{
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity(); // -1
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else
				{
					os << "Unable to fill" << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		if (os)
		{
			os << m_name << " - " << m_product << endl;
			for (size_t i = 0; i < m_cntItem; i++)
			{				
				os << "[" << setfill('0') << setw(6) << m_lstItem[i]->m_serialNumber << "] " << setfill(' ')
					<< setw(m_widthField) << left << m_lstItem[i]->m_itemName << "   - ";

				auto status = m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED";
				os << status << endl;
			}			
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			if (m_lstItem)
			{
				deallocate();
			}

			m_name = src.m_name;
			src.m_name = '\0';
			m_product = src.m_product;
			src.m_product = '\0';
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		deallocate();
	}
}