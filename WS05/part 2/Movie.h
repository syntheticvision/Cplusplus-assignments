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
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include <string>
#include <iostream>
#include <iomanip>
class SpellChecker;
namespace seneca
{
    class Movie
    {
        std::string m_title;
        int m_year;
        std::string m_description;

    public:
        Movie() : m_year(0) {};
        Movie(const std::string &strMovie);
        const std::string &title() const
        {
            return m_title;
        };
        template <typename T>
        void fixSpelling(T &spellChecker)
        {
            spellChecker(m_title);
            spellChecker(m_description);
        };
        friend std::ostream &operator<<(std::ostream &os, const Movie &movie)
        {
            os << std::setw(40) << std::right << movie.m_title << " | "
               << std::setw(4) << std::left << movie.m_year << " | "
               << movie.m_description << std::endl;
            return os;
        };
    };
}
#endif // SENECA_MOVIE_H