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
#include "Restaurant.h"
#include <iostream>
using namespace std;
using namespace seneca;
namespace seneca
{
    Restaurant::Restaurant()
    {
        m_numberOfReservations = 0u;
        m_reservations = nullptr;
    }
    Restaurant::Restaurant(const Reservation *reservations[], size_t cnt)
    {
        m_numberOfReservations = cnt;
        m_reservations = new Reservation[cnt];
        for (auto i = 0u; i < cnt; i++)
        {
            m_reservations[i] = *reservations[i];
        }
    }
    Restaurant::Restaurant(const Restaurant &restaurant) : Restaurant()
    {
        *this = restaurant;
    }
    Restaurant::Restaurant(Restaurant &&restaurant) noexcept : Restaurant()
    {
        *this = std::move(restaurant);
    }
    Restaurant::~Restaurant()
    {
        delete[] m_reservations;
    }
    Restaurant &Restaurant::operator=(const Restaurant &restaurant)
    {
        if (this != &restaurant)
        {
            delete[] m_reservations;
            m_numberOfReservations = restaurant.size();
            m_reservations = new Reservation[m_numberOfReservations];
            for (auto i = 0u; i < m_numberOfReservations; i++)
            {
                m_reservations[i] = restaurant.m_reservations[i];
            }
        }
        return *this;
    }
    Restaurant &Restaurant::operator=(Restaurant &&restaurant) noexcept
    {
        if (this != &restaurant)
        {
            m_reservations = restaurant.m_reservations;
            restaurant.m_reservations = nullptr;
            m_numberOfReservations = restaurant.m_numberOfReservations;
            restaurant.m_numberOfReservations = 0u;
        }
        return *this;
    }
    size_t Restaurant::size() const
    {
        return m_numberOfReservations;
    }
    std::ostream &operator<<(std::ostream &os, const Restaurant &restaurant)
    {
        static size_t counter = 0u;
        cout << "--------------------------\n";
        cout << "Fancy Restaurant (" << ++counter << ")\n";
        cout << "--------------------------\n";
        if (restaurant.size() == 0u)
        {
            cout << "This restaurant is empty!\n";
        }
        else
        {
            for (auto i = 0u; i < restaurant.m_numberOfReservations; i++)
            {

                os << restaurant.m_reservations[i];
            }
        }
        cout << "--------------------------\n";
        return os;
    }
}