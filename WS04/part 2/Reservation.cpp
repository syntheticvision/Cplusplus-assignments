//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           June 9, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#include <string>
#include <iostream>
#include "Reservation.h"
using namespace std;
namespace seneca
{
    void Reservation::removeTrailingLeadingSpaces(std::string &word)
    {
        while (word[0] == ' ')
        {
            word = word.substr(1, (word.size() - 1));
        }
        while (word[word.size() - 1] == ' ')
        {
            word = word.substr(0, (word.size() - 1));
        }
    }
    Reservation::Reservation()
    {
        m_reservation_id = "";
        m_name = "";
        m_email = "";
        m_numberOfPeople = 0u;
        m_day = 0u;
        m_hour = 0u;
    }
    void Reservation::update(int day, int time) {
        m_day = day;
        m_hour = time;
    }
    Reservation::Reservation(const std::string &res) : Reservation()
    {
        size_t colonPosition = res.find(':');
        m_reservation_id = res.substr(0, colonPosition);
        removeTrailingLeadingSpaces(m_reservation_id);
        size_t commaForName = res.find(',');
        m_name = res.substr(colonPosition + 1, commaForName - colonPosition -
                                                   1);
        removeTrailingLeadingSpaces(m_name);
        size_t commaForEmail = res.find(',', commaForName + 1);
        m_email = res.substr(commaForName + 1, commaForEmail - commaForName -
                                                   1);
        removeTrailingLeadingSpaces(m_email);
        size_t commaForNumber = res.find(',', commaForEmail + 1);
        m_numberOfPeople = stoi(res.substr(commaForEmail + 1, commaForNumber -
                                                                  commaForEmail - 1));
        size_t commaForDay = res.find(',', commaForNumber + 1);
        m_day = stoi(res.substr(commaForNumber + 1, commaForDay - commaForEmail - 1));
        size_t commaForTime = res.find(',', commaForDay);
        m_hour = stoi(res.substr(commaForTime + 1, res.size()));
    }
    std::ostream &operator<<(std::ostream &os, const Reservation &reservation)
    {
        os << "Reservation ";
        os.width(10);
        os << right << reservation.m_reservation_id << ": ";
        os.width(20);
        os << right << reservation.m_name;
        os.width(25);
        os << left << ("  <" + reservation.m_email + ">");
        if (reservation.m_hour >= 6 && reservation.m_hour <= 9)
        {
            os << " Breakfast on day ";
        }
        else if (reservation.m_hour >= 11 && reservation.m_hour <= 15)
        {
            os << " Lunch on day ";
        }
        else if (reservation.m_hour >= 17 && reservation.m_hour <= 21)
        {
            os << " Dinner on day ";
        }
        else
        {
            os << " Drinks on day ";
        }
        os << reservation.m_day << " @ " << reservation.m_hour << ":00 for " << reservation.m_numberOfPeople;
        os << (reservation.m_numberOfPeople == 1 ? " person.\n" : " people.\n");
        return os;
    }
}