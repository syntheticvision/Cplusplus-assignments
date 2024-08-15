// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 19 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() : m_name{ }, m_product{  }, m_cntItem{} {
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities obj;
		size_t pos = 0;
		bool moreToken = true;

		m_name = obj.extractToken(str, pos, moreToken);
		m_product = obj.extractToken(str, pos, moreToken);

		std::string list;
		size_t count = 0;
		do{
			std::string temp = obj.extractToken(str, pos, moreToken);
			if (list.length() > 0){
				list += Utilities::getDelimiter(); }
			list += temp;
			count++;
		} while (moreToken);

		m_lstItem = new Item * [count];
		m_cntItem = count;
		pos = 0;
		count = 0;
		moreToken = true;

		do{
			std::string temp = obj.extractToken(list, pos, moreToken);
			m_lstItem[count++] = new Item(temp);
		} while (moreToken);

		if (m_widthField < obj.getFieldWidth()) {
			m_widthField = obj.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other) {
		throw "Error! Copy constructor is not allowed!";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept :CustomerOrder() {
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
		if (this != &other) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];}
			delete[] m_lstItem;
			
			 m_name = std::move(other.m_name);
			 m_product = std::move(other.m_product);
			 m_cntItem = other.m_cntItem;
			 m_lstItem = other.m_lstItem;

			 other.m_name = "";
			 other.m_product = "";
                         other.m_lstItem = nullptr;
			 other.m_cntItem = 0; 
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;

	}


	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++){
			if ( m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false) {
				if (station.getQuantity() > 0){
                                        station.updateQuantity();
					m_lstItem[i]->m_serialNumber =  station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					
					os << std::setw(11) << std::right;
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" 
                                           << std::endl;
					break;
				}else{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" 
                                           << std::endl;
				}
			}
		}
	}

        bool CustomerOrder::isOrderFilled() const {
		return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [](const Item* item){
				return item->m_isFilled;
			});
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const{
		return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](Item* it){
				if (it->m_itemName == itemName){
					return (it->m_isFilled);}
				return true;
			});
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << std::right;
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::left;
			os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << std::endl;}
	}

}