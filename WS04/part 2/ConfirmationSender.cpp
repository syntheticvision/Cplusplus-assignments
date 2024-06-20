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
#include "ConfirmationSender.h"
#include <iostream>
namespace seneca
{
    ConfirmationSender::ConfirmationSender()
    {
        reservePtr = nullptr;
        numPtr = 0;
    }
    ConfirmationSender::ConfirmationSender(const ConfirmationSender &src)
    {
        *this = src;
    }
    ConfirmationSender::ConfirmationSender(ConfirmationSender &&src)
    {
        *this = std::move(src);
    }
    ConfirmationSender &ConfirmationSender::operator=(const ConfirmationSender &src)
    {
        if (this != &src)
        {
            delete[] reservePtr;
            reservePtr = new const Reservation *[src.numPtr];
            numPtr = src.numPtr;
            for (size_t i = 0; i < numPtr; i++)
            {
                reservePtr[i] = src.reservePtr[i];
            }
        }
        return *this;
    }
    ConfirmationSender &ConfirmationSender::operator=(ConfirmationSender &&src)
    {
        if (this != &src)
        {
            delete[] reservePtr;
            reservePtr = src.reservePtr;
            numPtr = src.numPtr;
            src.reservePtr = nullptr;
            src.numPtr = 0;
        }
        return *this;
    }
    ConfirmationSender::~ConfirmationSender()
    {
        delete[] reservePtr;
    }
    ConfirmationSender &ConfirmationSender::operator+=(const Reservation &res)
    {
        size_t i = 0;
        while (i < numPtr && reservePtr[i] != &res)
        {
            i++;
        }
        if (i == numPtr)
        {
            const Reservation **temp = new const Reservation *[numPtr + 1];
            for (size_t i = 0; i < numPtr; i++)
            {
                temp[i] = reservePtr[i];
            }
            temp[numPtr] = &res;
            delete[] reservePtr;
            reservePtr = temp;
            numPtr++;
        }
        return *this;
    }
    ConfirmationSender &ConfirmationSender::operator-=(const Reservation &res)
    {
        size_t i = 0;
        while (i < numPtr && reservePtr[i] != &res)
        {
            i++;
        }
        if (i < numPtr)
        {
            const Reservation **temp = new const Reservation *[numPtr - 1];
            size_t j = 0;
            while (j < i)
            {
                temp[j] = reservePtr[j];
                j++;
            }
            while (j < numPtr - 1)
            {
                temp[j] = reservePtr[j + 1];
                j++;
            }
            delete[] reservePtr;
            reservePtr = temp;
            numPtr--;
        }
        return *this;
    }
    std::ostream &operator<<(std::ostream &os, const ConfirmationSender &src)
    {
        os << "--------------------------" << std::endl;
        os << "Confirmations to Send" << std::endl;
        os << "--------------------------" << std::endl;
        if (src.numPtr == 0)
        {
            os << "There are no confirmations to send!" << std::endl;
        }
        else
        {
            for (size_t i = 0; i < src.numPtr; i++)
            {
                os << *src.reservePtr[i];
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }
}