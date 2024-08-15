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
#include "Directory.h"
#include "Flags.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>

namespace seneca
{
    seneca::Directory::Directory(std::string dirname) { this->m_name = dirname; }

    void Directory::update_parent_path(const std::string &path)
    {
        m_parent_path = path;
        for (auto resource : m_contents)
        {
            resource->update_parent_path(this->path());
        }
    }

    NodeType Directory::type() const
    {
        return NodeType::DIR;
    }

    std::string Directory::path() const
    {
        if (!m_parent_path.empty() && m_parent_path.back() == '/')
        {
            return m_parent_path + m_name;
        }
        else if (!m_parent_path.empty())
        {
            return m_parent_path + "/" + m_name;
        }
        else
        {
            return m_name;
        }
    }

    std::string Directory::name() const
    {
        return m_name;
    }

    int Directory::count() const
    {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const
    {
        size_t total_size = 0;
        for (const auto &resource : m_contents)
        {
            total_size += resource->size();
        }
        return total_size;
    }

    Directory &Directory::operator+=(Resource *resource)
    {
        auto it = std::find_if(m_contents.begin(), m_contents.end(), [&resource](Resource *r)
                               { return r->name() == resource->name(); });

        if (it != m_contents.end())
        {
            throw std::runtime_error("Resource with the same name already exists.");
        }

        m_contents.push_back(resource);
        resource->update_parent_path(this->path());
        return *this;
    }

    Resource *Directory::find(const std::string &name, const std::vector<OpFlags> &flags)
    {
        auto it = std::find_if(m_contents.begin(), m_contents.end(), [&name](Resource *r)
                               { return r->name() == name; });

        if (it != m_contents.end())
        {
            return *it;
        }

        if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end())
        {
            for (auto &resource : m_contents)
            {
                if (resource->type() == NodeType::DIR)
                {
                    Resource *res = static_cast<Directory *>(resource)->find(name, flags);
                    if (res != nullptr)
                    {
                        return res;
                    }
                }
            }
        }

        return nullptr;
    }

    Directory::~Directory()
    {
        for (auto resource : m_contents)
        {
            delete resource;
        }
    }

    void Directory::remove(const std::string &path, const std::vector<OpFlags> &flags)
    {
        auto it = std::remove_if(m_contents.begin(), m_contents.end(), [&path](Resource *r)
                                 { return r->path() == path; });

        if (it != m_contents.end())
        {
            delete *it;
            m_contents.erase(it, m_contents.end());
        }
    }

    void Directory::display(std::ostream &os, const std::vector<FormatFlags> &flags) const
    {
        os << "--------------------------\n";
        os << "      RESOURCE INFO\n";
        os << "--------------------------\n";
        os << count() << std::setw(5) << size() << " bytes " << path() << '\n';

        for (const auto &resource : m_contents)
        {
            os << std::setw(5) << resource->count() << std::setw(5) << resource->size() << " bytes " << resource->path() << '\n';
        }

        os << "--------------------------\n";
    }
}
