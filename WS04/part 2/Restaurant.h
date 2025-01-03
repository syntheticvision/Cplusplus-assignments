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
#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H
#include "Reservation.h"
namespace seneca
{
    class Restaurant
    {
        Reservation *m_reservations;
        size_t m_numberOfReservations;

    public:
        Restaurant();
        Restaurant(const Reservation *reservations[], size_t cnt);
        Restaurant(const Restaurant &restaurant);
        Restaurant(Restaurant &&restaurant) noexcept;
        ~Restaurant();
        Restaurant &operator=(const Restaurant &restaurant);
        Restaurant &operator=(Restaurant &&restaurant) noexcept;
        size_t size() const;
        friend std::ostream &operator<<(std::ostream &os, const Restaurant & reservation);
    };
}
#endif //!SENECA_RESTAURANT_H