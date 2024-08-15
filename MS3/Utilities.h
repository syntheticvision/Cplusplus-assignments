// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 19 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef  SENECA_UTILITIES_H
#define  SENECA_UTILITIES_H

#include <string>

namespace seneca {
    class Utilities {
    private:
        size_t m_widthField = 1;
        static char m_delimiter;
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}

#endif
