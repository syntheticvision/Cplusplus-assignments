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
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
#include <iostream>
#include <fstream>
namespace seneca
{
    class SpellChecker
    {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        int m_replacements[6] = {0};
        bool loadFromFile(const char *filename);

    public:
        SpellChecker(const char *filename);
        void operator()(std::string &text);
        void showStatistics(std::ostream &out) const;
    };
};
#endif // SENECA_SPELLCHECKER_H