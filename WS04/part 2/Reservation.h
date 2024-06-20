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
#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H
#include <iostream>
namespace seneca
{
    class Reservation
    {
        std::string m_reservation_id;
        std::string m_name;
        std::string m_email;
        size_t m_numberOfPeople;
        size_t m_day;
        size_t m_hour;
        void removeTrailingLeadingSpaces(std::string &word);

    public:
        Reservation();
        void update(int day, int time);
        Reservation(const std::string &res);
        friend std::ostream &operator<<(std::ostream &os, const Reservation & reservation);
    };
}
#endif // ! SENECA_RESERVATION_H