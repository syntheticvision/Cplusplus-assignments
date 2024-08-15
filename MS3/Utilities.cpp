// Name: Babak Ghafourigivi
// Seneca Student ID: 165118233
// Seneca email: bghafourigivi@myseneca.ca
// Date of completion: 12 July 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <stdexcept>
#include "Utilities.h"

namespace seneca {
       char Utilities::m_delimiter = ',';

       void Utilities::setFieldWidth(size_t newWidth) {
             m_widthField = newWidth;
       }

       size_t Utilities::getFieldWidth() const {
             return m_widthField;
        }

       std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
            if (next_pos >= str.length()) {
                more = false;
                return "";}
            size_t pos = str.find(m_delimiter, next_pos);

            if (pos == std::string::npos) {
                pos = str.length();
                more = false;
            } else {
                more = true;}

            if (pos == next_pos) {
                more = false;
                throw std::invalid_argument("Delimiter found at next_pos");
            }
            std::string token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
            token.erase(0, token.find_first_not_of(' ')); 
            token.erase(token.find_last_not_of(' ') + 1); 
            if (token.length() > m_widthField) {
                  m_widthField = token.length();
            }

            return token;
        }

        void Utilities::setDelimiter(char newDelimiter) {
            m_delimiter = newDelimiter; }

        char Utilities::getDelimiter() {
           return m_delimiter;
        }

}