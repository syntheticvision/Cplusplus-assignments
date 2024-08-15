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
#include <utility>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Filesystem.h"
#include "File.h"

std::string seneca::Filesystem::readNextInput(std::string input, unsigned int &pos, bool spaces)
{
    char cur = input[pos];
    std::string result = "";
    bool seenFirstNotSpace = false;
    std::string spacesToAdd = "";
    while (pos < input.length())
    {
        if (cur == '\n' || cur == '|' || cur == '\r')
        {
            break;
        }
        else if (cur != ' ' && !seenFirstNotSpace)
        {
            seenFirstNotSpace = true;
            result += cur;
        }
        else if (seenFirstNotSpace)
        {
            if (cur == ' ')
            {
                if (spaces)
                {
                    spacesToAdd += cur;
                }
            }
            else
            {
                result += spacesToAdd + cur;
                spacesToAdd = "";
            }
        }
        cur = input[++pos];
    }
    pos++;
    return result;
}
std::vector<std::string> seneca::Filesystem::getFilePath(std::string path)
{
    int pos = 0;
    std::vector<std::string> paths;
    for (unsigned int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/')
        {
            int prevPos = pos;
            pos = i + 1;
            paths.emplace_back(path.substr(prevPos, pos - prevPos));
        }
    }
    return paths;
}
std::string seneca::Filesystem::getFileName(std::string path)
{
    int pos = 0;
    std::string name = "";
    for (unsigned int i = 0; i < path.length(); i++)
    {
        if (path[i] == '/')
        {
            pos = i + 1;
        }
    }
    name = path.substr(pos, path.length());
    return name;
}
seneca::Filesystem::Filesystem(std::string filename, std::string root)
{
    Directory *temp = new Directory(root);
    m_root = temp;
    m_current = temp;
    std::ifstream f(filename);
    std::string line, name, contents;
    std::vector<std::string> paths;
    unsigned int pos = 0;
    if (f.is_open())
    {
        while (std::getline(f, line))
        {
            name = readNextInput(line, pos, false);
            contents = readNextInput(line, pos, true);
            paths = getFilePath(name);
            name = getFileName(name);
            Directory *cur = m_root;
            std::vector<seneca::OpFlags> oflags;
            oflags.push_back(seneca::OpFlags::RECURSIVE);
            for (auto it = paths.begin(); it != paths.end(); it++)
            {
                Directory *dir = new Directory(*it);
                try
                {
                    *cur += dir;
                    cur = dir;
                }
                catch (...)
                {
                    delete dir;
                    cur = dynamic_cast<Directory *>(cur->find(*it));
                }
            }
            if (name.length() > 0)
            {
                File *file = new File(name, contents);
                try
                {

                    *cur += file;
                }
                catch (...)
                {
                    delete file;
                }
            }
            // delete cur;
            pos = 0;
        }
    }
    else
    {
        delete temp;
        throw std::invalid_argument("Invalid file!");
    }
}
seneca::Filesystem::Filesystem(Filesystem &&f)
{
    *this = std::move(f);
}
seneca::Filesystem &seneca::Filesystem::operator=(Filesystem &&f)
{
    if (this == &f)
    {
        return *this;
    }
    std::swap(m_root, f.m_root);
    std::swap(m_current, f.m_current);
    return *this;
}
seneca::Filesystem &seneca::Filesystem::operator+=(Resource *r)
{
    *m_current += r;
    return *this;
}
seneca::Directory *seneca::Filesystem::change_directory(const std::string &path)
{
    if (path == "")
    {
        m_current = m_root;
    }
    else
    {
        Resource *r = m_current->find(path);
        if (r == nullptr)
        {
 throw std::invalid_argument("Cannot change directory! " + path + " was not found!");
        }
        else
        {
            m_current = dynamic_cast<Directory *>(r);
        }
    }
    return m_current;
}
seneca::Directory *seneca::Filesystem::get_current_directory() const
{
    return m_current;
}
seneca::Filesystem::~Filesystem()
{
    delete m_root;
}