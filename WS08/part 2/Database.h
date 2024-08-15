//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           July 21, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

namespace seneca
{
    enum class Err_Status
    {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template <typename T>
    class Database
    {
    public:
        static std::shared_ptr<Database> getInstance(const std::string &filename);
        Err_Status GetValue(const std::string &key, T &value);
        Err_Status SetValue(const std::string &key, const T &value);
        ~Database();

    private:
        static std::shared_ptr<Database<T>> db;
        Database();
        explicit Database(const std::string &filename);
        void encryptDecrypt(T &value);

        size_t entry_count{0};
        std::string keys[20];
        T values[20];
        std::string dbFileName{};
    };

    // Specialize the encryptDecrypt method for std::string
    template <>
    void Database<std::string>::encryptDecrypt(std::string &value);

    // Specialize the encryptDecrypt method for long long
    template <>
    void Database<long long>::encryptDecrypt(long long &value);
}

#endif // SENECA_DATABASE_H

