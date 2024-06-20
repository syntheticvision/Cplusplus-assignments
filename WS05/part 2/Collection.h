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
#ifndef COLLECTION_H
#define COLLECTION_H
#include <iostream>
#include <string>
namespace seneca
{
    template <typename T>
    class Collection
    {
        std::string m_name{};
        T *m_collection{};
        size_t m_size{};
        void (*ptrToObserver)(const Collection<T> &co, const T &ro){};

    public:
        Collection(const std::string &name)
        {
            m_name = name;
        }
        Collection(const Collection<T> &toCopy) = delete;
        Collection<T> operator=(const Collection<T> &toAssign) = delete;
        ~Collection()
        {
            delete[] m_collection;
            m_collection = nullptr;
        }
        const std::string &name() const { return m_name; }
        size_t size() const { return m_size; }
        void setObserver(void (*observer)(const Collection<T> &, const T &))
        {
            ptrToObserver = observer;
        }
        Collection<T> &operator+=(const T &item)
        {
            bool found = false;
            for (size_t i = 0; i < m_size; i++)
            {
                if (m_collection[i].title() == item.title())
                {
                    found = true;
                }
            }
            if (!found)
            {
                T *temp{};
                temp = new T[m_size + 1];
                for (size_t i = 0; i < m_size; i++)
                {
                    temp[i] = m_collection[i];
                }
                temp[m_size] = item;
                delete[] m_collection;
                m_collection = temp;
                m_size++;
                if (ptrToObserver)
                {
                    ptrToObserver(*this, item);
                }
            }
            return *this;
        }
        T &operator[](size_t idx) const
        {
            if (idx > m_size - 1)
            {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. " + "Collection has [" + std::to_string(idx) + "] items.");
            }
            else
            {
                return m_collection[idx];
            }
        }
        T *operator[](const std::string &title) const
        {
            T *temp{nullptr};
            bool found = false;
            for (size_t i = 0; i < m_size && !found; i++)
            {
                if (m_collection[i].title() == title)
                {
                    temp = &m_collection[i];
                    found = true;
                }
            }
            return temp;
        }
    };
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Collection<T> &ro)
    {
        for (size_t i = 0; i < ro.size(); i++)
        {
            os << ro[i];
        }
        return os;
    }
}
#endif // !COLLECTION_H