// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 19 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

namespace seneca {
     size_t Station::m_widthField = 0;
     size_t Station::id_generator = 0;

     Station::Station(const std::string& record) : s_id(++id_generator) {
         Utilities obj;
         size_t next_pos = 0;
         bool moreToken = true;
         s_itemName = obj.extractToken(record, next_pos, moreToken);
         s_serialNumber = std::stoul(obj.extractToken(record, next_pos, moreToken));
         s_itemsNum = std::stoul(obj.extractToken(record, next_pos,moreToken));
         m_widthField = std::max(m_widthField, obj.getFieldWidth());
         s_description = obj.extractToken(record, next_pos, moreToken);
    }
    size_t Station::getQuantity() const {
         return s_itemsNum;
    }

    void Station::updateQuantity() {
        if (s_itemsNum> 0) {
            --s_itemsNum;
         }
     }

    const std::string& Station::getItemName() const {
         return s_itemName;
    }

    size_t Station::getNextSerialNumber() {
         return s_serialNumber++;
    }


     void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::right << std::setfill('0') << s_id << " | "<< std::setw(m_widthField) 
           << std::left << std::setfill(' ') << s_itemName << " | " << std::setw(6) << std::setfill('0') 
           << std::right << s_serialNumber << " | ";

        if (full == true) {
            os << std::setw(4) << std::setfill(' ') << s_itemsNum << " | " << s_description;}
          os << std::endl;
    }
}