//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           June 15, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#include "Movie.h"
#include "SpellChecker.h"
#include <iostream>
#include <iomanip>
namespace seneca
{
    Movie::Movie(const std::string &strMovie)
    {

        std::stringstream ss(strMovie);
        std::string token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_title = token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_year = std::stoi(token);
        std::getline(ss, token);
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_description = token;
    }
};