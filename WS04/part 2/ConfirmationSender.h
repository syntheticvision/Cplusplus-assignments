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
#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H
#include "Reservation.h"
namespace seneca
{
    class ConfirmationSender
    {
        const Reservation **reservePtr{};
        size_t numPtr{};

    public:
        ConfirmationSender();
        ConfirmationSender(const ConfirmationSender &c);
        ConfirmationSender(ConfirmationSender &&c);
        ConfirmationSender &operator=(const ConfirmationSender &c);
        ConfirmationSender &operator=(ConfirmationSender &&c);
        virtual ~ConfirmationSender();
        ConfirmationSender &operator+=(const Reservation &res);
        ConfirmationSender &operator-=(const Reservation &res);
        friend std::ostream &operator<<(std::ostream &ostr, const ConfirmationSender &c);
    };
}
#endif