//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           May 26, 2024
//I declare that this submission is the result of my own work and I only copied the code 
//that my professor provided to complete my workshops and assignments. 
//This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H
#include <string>
namespace seneca
{
    class ProteinDatabase
    {
        std::string *m_proteinArr{};
        size_t m_size = 0;

    public:
        ProteinDatabase();
        ProteinDatabase(const char *fileName);
        // rule of 5
        ProteinDatabase(const ProteinDatabase &src);
        ProteinDatabase &operator=(const ProteinDatabase &src);
        ProteinDatabase(ProteinDatabase&& src); //move constructor
        ProteinDatabase& operator=(ProteinDatabase&& src); //move assignment
        virtual ~ProteinDatabase();
        size_t size() const;
        std::string operator[](size_t) const;

    private:
        void readFile(const char *fileName);
        void operator~();
    };
}
#endif // !SENECA_PROTEINDATABASE_H