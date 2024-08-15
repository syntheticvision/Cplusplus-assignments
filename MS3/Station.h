// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 19 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include "Utilities.h"

namespace seneca {
    class Station {
    private:
        int s_id;
        std::string s_itemName;
        std::string s_description;
        size_t s_serialNumber;
        size_t s_itemsNum;
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
        
    };
}

#endif