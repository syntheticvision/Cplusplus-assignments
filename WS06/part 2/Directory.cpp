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
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "Directory.h"
seneca::Directory::Directory(std::string _name)
{
    this->m_name = _name;
}
size_t seneca::Directory::size() const
{
    size_t total{0u};
    size_t fileSize = {0u};
    ;
    if (m_contents.empty())
    {
        return 0u;
    }
    else
    {
        for (size_t i = 0u; i < m_contents.size(); i++)
        {
            if (m_contents.at(i)->type() == NodeType::FILE)
            {
                fileSize = m_contents.at(i)->size();
                total += fileSize;
            }
            else if (m_contents.at(i)->type() == NodeType::DIR)
            {
                fileSize = m_contents.at(i)->size();
                total += fileSize;
            }
        }
    }
    return total;
}
seneca::Directory &seneca::Directory::operator+=(Resource *src)
{
    bool exists = false;
    for (auto it = m_contents.begin(); it != m_contents.end(); it++)
    {
        if ((*it)->name() == src->name())
        {
            exists = true;
            break;
        }
    }
    if (exists)
    {
        throw std::invalid_argument("Resource already exists!");
    }
    else
    {
        src->update_parent_path(path());
        m_contents.emplace_back(src);
    }
    return *this;
}
void seneca::Directory::update_parent_path(const std::string &src)
{
    m_parent_path = src;
    for (auto it = m_contents.begin(); it != m_contents.end(); it++)
    {
        (*it)->update_parent_path(path());
    }
}
seneca::NodeType seneca::Directory::type() const
{
    return NodeType::DIR;
}
std::string seneca::Directory::path() const
{
    return m_parent_path + m_name;
}
std::string seneca::Directory::name() const
{
    return m_name;
}
int seneca::Directory::count() const
{
    return m_contents.size();
}
seneca::Resource *seneca::Directory::find(const std::string &str, const std::vector<OpFlags> &flag)
{
    Resource *res = nullptr;
    bool a = false;
    for (auto it = flag.begin(); it != flag.end(); it++)
    {
        if ((*it) == OpFlags::RECURSIVE)
        {
            a = true;
            break;
        }
    }
    for (auto i = m_contents.begin(); i != m_contents.end(); i++)
    {
        if ((*i)->name() == str)
        {
            res = (*i);
            break;
        }
        else if (a && (*i)->type() == NodeType::DIR)
        {
            Directory *temp = dynamic_cast<Directory *>(*i);
            res = temp->find(str, flag);
        }
    }
    return res;
}
seneca::Directory::~Directory()
{
    for (auto it = m_contents.begin(); it != m_contents.end(); it++)
    {
        delete *it;
    }
}
void seneca::Directory::remove(const std::string &str, const std::vector<OpFlags> &
                                                         flag)
{
    bool a = false;
    for (auto i = flag.begin(); i != flag.end(); i++)
    {
        if ((*i) == OpFlags::RECURSIVE)
        {
            a = true;
            break;
        }
    }
    Resource *res = find(str);
    if (res == nullptr)
    {
        throw std::string(str + "does not exist in " + name());
    }
    else if (res->type() == NodeType::DIR)
    {
        if (a)
        {
            for (unsigned int i = 0; i < m_contents.size(); i++)
            {
                if (m_contents[i]->name() == str)
                {
                    Resource *temp = m_contents[i];
                    m_contents.erase(m_contents.begin() + i);
                    delete temp;
                    break;
                }
            }
        }
        else
        {
 throw std::invalid_argument(str + "is a directory. Pass the recursive flag to delete directories.");
        }
    }
    else
    {
        for (unsigned int i = 0; i < m_contents.size(); i++)
        {
            if (m_contents[i]->name() == str)
            {
                Resource *temp = m_contents[i];
                m_contents.erase(m_contents.begin() + i);
                delete temp;
                break;
            }
        }
    }
}
void seneca::Directory::display(std::ostream &os, const std::vector<FormatFlags> &
                                                    flag) const
{
    bool a = false;
    for (auto it = flag.begin(); it != flag.end(); it++)
    {
        if ((*it) == FormatFlags::LONG)
        {
            a = true;
            break;
        }
    }
    os << "Total size: " << size() << " bytes" << std::endl;
    for (auto i = m_contents.begin(); i != m_contents.end(); i++)
    {
        if ((*i)->type() == NodeType::FILE)
        {
            os << "F | ";
        }
        else
        {
            os << "D | ";
        }
        os << std::setw(15) << std::left << (*i)->name() << " |";
        if (a)
        {
            os << " ";
            if ((*i)->count() >= 0)
            {
                os << std::setw(2) << std::right << std::to_string((*i)->count());
            }
            else
            {
                os << std::setw(2) << std::right << "";
            }
            os << " | ";
            os << std::right << std::setw(10) << (std::to_string((*i)->size()) + std::string(" bytes"));
            os << " | ";
        }
        os << std::endl;
    }
}