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
#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H
#include <string>
#include <vector>
#include "Resource.h"
#include "Flags.h"
namespace seneca
{
    class Directory : public Resource
    {
        std::vector<Resource *> m_contents;

    public:
        Directory(std::string dirname);
        void update_parent_path(const std::string &) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        Directory &operator+=(Resource *);
        Resource *find(const std::string &, const std::vector<OpFlags> &flags = {});
        ~Directory();
        Directory &operator=(const Directory &) = delete;
        Directory &operator=(Directory &&) = delete;
        void remove(const std::string &path, const std::vector<OpFlags> &flags =
                                                 {});
        void display(std::ostream &, const std::vector<FormatFlags> &flags = {})
            const;
    };
};
#endif