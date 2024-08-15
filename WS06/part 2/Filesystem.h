//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           July 6, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H
#include "Resource.h"
#include "Directory.h"
namespace seneca
{
    class Filesystem
    {
        Directory *m_root;
        Directory *m_current;
        std::string readNextInput(std::string input, unsigned int &pos, bool spaces = false);
        std::vector<std::string> getFilePath(std::string);
        std::string getFileName(std::string);

    public:
        Filesystem(std::string filename, std::string root = "");
        Filesystem(const Filesystem &) = delete;
        Filesystem(Filesystem &&);
        Filesystem &operator=(const Filesystem &) = delete;
        Filesystem &operator=(Filesystem &&);
        Filesystem &operator+=(Resource *);
        Directory *change_directory(const std::string &path = "");
        Directory *get_current_directory() const;
        ~Filesystem();
    };
};
#endif
