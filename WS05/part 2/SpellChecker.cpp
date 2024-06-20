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
#include "SpellChecker.h"
#include <iomanip>
#include <string>
namespace seneca
{
    SpellChecker::SpellChecker(const char *filename)
    {

        if (!loadFromFile(filename))
            throw std::runtime_error("Bad file name!");
    }
    bool SpellChecker::loadFromFile(const char *filename)
    {
        std::ifstream file(filename);
        if (!file)
            return false;
        std::string line;
        int count = 0;
        while (std::getline(file, line) && count < 6)
        {

            size_t pos = line.find(" ");
            if (pos != std::string::npos)
            {
                m_badWords[count] = line.substr(0, pos);
                m_goodWords[count] = line.substr(pos + 1);
                m_goodWords[count] =
                    m_goodWords[count].substr(m_goodWords[count].find_first_not_of(" "));
                count++;
            }
        }
        file.close();
        return true;
    }
    void SpellChecker::operator()(std::string &text)
    {
        for (int i = 0; i < 6; i++)
        {
            size_t pos = text.find(m_badWords[i]);
            while (pos != std::string::npos)
            {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
            }
        }
    }
    void SpellChecker::showStatistics(std::ostream &out) const
    {
        out << "Spellchecker Statistics" << std::endl;
        for (int i = 0; i < 6; i++)
        {
            out << std::setw(15) << std::right << m_badWords[i] << ": "
                << m_replacements[i] << " replacements" << std::endl;
        }
    }
};