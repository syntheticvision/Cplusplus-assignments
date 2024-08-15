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
#include "File.h"

seneca::File::File(std::string filename, std::string contents) : m_contents{contents}
{
    this->m_name = filename;
}
void seneca::File::update_parent_path(const std::string &path)
{
    m_parent_path = path;
}
seneca::NodeType seneca::File::type() const
{
    return NodeType::FILE;
}
std::string seneca::File::path() const
{
    return m_parent_path + m_name;
}
std::string seneca::File::name() const
{
    return m_name;
}
int seneca::File::count() const
{
    return -1;
}
size_t seneca::File::size() const
{
    return m_contents.length();
}