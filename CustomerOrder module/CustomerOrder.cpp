// Name: YUJIN KIM
// Seneca Student ID: 117826214 
// Seneca email: ykim296@myseneca.ca
// Date of completion: 2022/Nov/26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include "CustomerOrder.h"


namespace sdds{

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(){
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }

    CustomerOrder::CustomerOrder(const std::string& res){
        Utilities util;
        size_t pos = 0;
        bool more = true;

        try{
            m_name = util.extractToken(res,pos,more);
            if(more) m_product = util.extractToken(res,pos,more);
            if(more) m_cntItem = std::count(res.begin(), res.end(), util.getDelimiter()) -1;
            if(m_cntItem && more){
                m_lstItem = new Item*[m_cntItem];
                size_t index = 0;

                while(more){
                    m_lstItem[index] = new Item(util.extractToken(res,pos,more));
                    index++;
                }
            }

            if(util.getFieldWidth() > CustomerOrder::m_widthField){
                CustomerOrder::m_widthField = util.getFieldWidth();
            }
            
        }catch(std::string err){
            throw false;
        }
    }

    //copy constructor
    CustomerOrder::CustomerOrder(const CustomerOrder& res){
        throw false;
    }
    //move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& res) noexcept{
        *this = std::move(res);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& res) noexcept{
        if(this != &res){
            if (m_lstItem) //1
            {
                for (size_t i = 0; i < m_cntItem; i++) {
                    delete m_lstItem[i]; //2
                    m_lstItem[i] = nullptr;
                }
                delete[] m_lstItem;
                m_lstItem = nullptr;
            }
            m_name = res.m_name;
            m_product = res.m_product;
            m_cntItem = res.m_cntItem;
            m_lstItem = res.m_lstItem;

            res.m_name = '\0';
            res.m_product = '\0';
            res.m_cntItem = 0;
            res.m_lstItem = nullptr;
        }
        return *this;
    }
        
    CustomerOrder::~CustomerOrder(){
        for(size_t i = 0; i<m_cntItem; i++){
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    bool CustomerOrder::isOrderFilled() const{
        bool isOrderFilled = true;

        for(size_t i=0; i<m_cntItem; i++){
            if(!m_lstItem[i]->m_isFilled) isOrderFilled = false;
        }

        return isOrderFilled;
    }
    bool CustomerOrder::isItemFilled(const std::string& itemName) const{
        bool isItemFilled = true;

        for(size_t i=0; i<m_cntItem; i++){
            if(m_lstItem[i]->m_itemName == itemName ) isItemFilled = false;
        }
        return isItemFilled;
    }
    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        for(size_t i=0; i<m_cntItem; i++){
            if(m_lstItem[i]->m_itemName == station.getItemName()){
                if(station.getQuantity()){
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    FILLED ";
                }else{
                    os << "    Unable to fill ";
                }
                os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
        
    }
    void CustomerOrder::display(std::ostream& os) const{
        os << m_name << " - " << m_product <<std::endl;
        for(size_t i=0; i<m_cntItem; i++){
            os << "[" << std::setw(6) << std::setfill('0') <<  m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(CustomerOrder::m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << "   - ";
            
            if(m_lstItem[i]->m_isFilled){
                os << "FILLED" << std::endl;
            }else{
                os << "TO BE FILLED" << std::endl;
            }
        }
    }
    
}