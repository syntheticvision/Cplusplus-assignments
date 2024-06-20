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
#include "Book.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
using namespace seneca;
namespace seneca
{
    Book::Book() : m_year(0), m_price(0.0) {}
    const std::string &Book::title() const
    {
        return m_title;
    }
    const std::string &Book::country() const
    {
        return m_country;
    }
    const size_t &Book::year() const
    {
        return m_year;
    }
    double &Book::price()
    {
        return m_price;
    }
    Book::Book(const std::string &strBook) : m_year(0), m_price(0.0)
    {
        std::stringstream ss(strBook);
        std::string token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_author = token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_title = token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_country = token;
        std::getline(ss, token, ',');
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_price = std::stod(token);
        std::getline(ss, token, ',');
        m_year = std::stoi(token);
        std::getline(ss, token);
        token = token.substr(token.find_first_not_of(' '));
        token = token.substr(0, token.find_last_not_of(' ') + 1);
        m_description = token;
    }
    std::ostream &operator<<(std::ostream &os, const Book &book)
    {
        os << std::setw(20) << std::right << book.m_author << " | ";
        os << std::setw(22) << book.m_title << " | ";
        os << std::setw(5) << book.m_country << " | ";
        os << std::setw(4) << book.m_year << " | ";
        os << std::fixed << std::setprecision(2) << std::setw(6) << book.m_price << " | ";
        os << book.m_description << std::endl;
        return os;
    }
}