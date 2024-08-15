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
#ifndef SENECA_DIRECTORY_H__
#define SENECA_DIRECTORY_H__
#include <vector>
#include "Resource.h"
namespace seneca
{
    class Directory : public Resource
    {
        std::vector<Resource *> m_contents{};

    public:
        Directory();
        Directory(std::string dirName);
        void update_parent_path(const std::string &path);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;
        Directory &operator+=(Resource *newRes);
        Resource *find(const std::string &name, const std::vector<OpFlags> &
                                                    flags = {});
        Directory(const Directory &) = delete;
        Directory &operator=(const Directory &) = delete;
        Directory(Directory &&) = delete;
        Directory &operator=(Directory &&) = delete;
        ~Directory();
        void remove(const std::string &name, const std::vector<OpFlags> &flags = {});
        void display(std::ostream &os = std::cout, const std::vector<FormatFlags> &flags = {}) const;

    private:
        auto findPos(Resource *ptr) -> std::vector<Resource *>::iterator const;
    };
}
#endif // !SENECA_DIRECTORY_H__