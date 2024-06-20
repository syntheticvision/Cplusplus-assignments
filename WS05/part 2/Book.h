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
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <string>
namespace seneca
{
    class Book
    {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

    public:
        Book();
        const std::string &title() const;
        const std::string &country() const;
        const size_t &year() const;
        double &price();
        Book(const std::string &strBook);
        template <typename T>
        void fixSpelling(T &spellChecker)
        {
            spellChecker(m_description);
        }
        friend std::ostream &operator<<(std::ostream &os, const Book &book);
    };
}
#endif // SENECA_BOOK_H