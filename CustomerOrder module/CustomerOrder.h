// Name: YUJIN KIM
// Seneca Student ID: 117826214 
// Seneca email: ykim296@myseneca.ca
// Date of completion: 2022/Nov/26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Utilities.h"
#include "Station.h"


namespace sdds{
    struct Item{
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder{
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};
        
        static size_t m_widthField;
        
        public:
        CustomerOrder();
        CustomerOrder(const std::string& res);
        //copy constructor
        CustomerOrder(const CustomerOrder& res);
        CustomerOrder& operator=(const CustomerOrder& res) = delete;
        //move constructor
        CustomerOrder(CustomerOrder&& res) noexcept;
        CustomerOrder& operator=(CustomerOrder&& res) noexcept;
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
    
}

#endif //SDDS_CUSTOMERORDER_H