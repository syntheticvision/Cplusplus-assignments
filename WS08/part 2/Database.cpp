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
#include "Database.h"
#include <algorithm>
#include <iterator>

namespace seneca
{
    // Initialize the static member
    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::db = nullptr;

    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string &filename)
    {
        if (!db)
        {
            db = std::shared_ptr<Database<T>>(new Database(filename));
        }
        return db;
    }

    template <typename T>
    Database<T>::Database(const std::string &filename) : dbFileName(filename)
    {
        std::cout << '[' << this << "] Database(const std::string&)\n";
        std::ifstream dbFileData(filename);
        std::string temp;
        T tempValues;
        while (std::getline(dbFileData, temp))
        {
            keys[entry_count] = temp.substr(0, temp.find_first_of('_')) + " " +
                                temp.substr(temp.find_first_of('_') + 1, temp.find_first_of(' ') -
                                                                         temp.find_first_of('_') - 1);
            if constexpr (std::is_same_v<T, std::string>)
            {
                tempValues = temp.substr(temp.find_last_of(' ') + 1);
                encryptDecrypt(tempValues);
            }
            else
            {
                tempValues = std::stoll(temp.substr(temp.find_last_of(' ') + 1));
                encryptDecrypt(tempValues);
            }
            values[entry_count++] = tempValues;
        }
        dbFileData.close();
    }

    template <typename T>
    Err_Status Database<T>::GetValue(const std::string &key, T &value)
    {
        auto it = std::find(std::begin(keys), std::begin(keys) + entry_count, key);
        if (it != std::begin(keys) + entry_count)
        {
            value = values[it - std::begin(keys)];
            return Err_Status::Err_Success;
        }
        return Err_Status::Err_NotFound;
    }

    template <typename T>
    Err_Status Database<T>::SetValue(const std::string &key, const T &value)
    {
        if (entry_count < 20)
        {
            keys[entry_count] = key;
            values[entry_count++] = value;
            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    template <typename T>
    Database<T>::~Database()
    {
        std::cout << '[' << this << "] ~Database()\n";
        std::string bkpFile = dbFileName + ".bkp.txt";
        std::ofstream backup(bkpFile);
        if (backup.is_open())
        {
            size_t idx = 0;
            T tempValues;
            while (idx < entry_count)
            {
                backup << std::setw(25) << std::left << keys[idx] << " -> ";
                tempValues = values[idx++];
                encryptDecrypt(tempValues);
                backup << tempValues << '\n';
            }
        }
        backup.close();
    }

    template <>
    void Database<std::string>::encryptDecrypt(std::string &value)
    {
        const char secret[] = "secret encryption key";
        for (char &c : value)
        {
            for (size_t j = 0; j < sizeof(secret) - 1; ++j)
            {
                c ^= secret[j];
            }
        }
    }

    template <>
    void Database<long long>::encryptDecrypt(long long &value)
    {
        const char secret[] = "super secret encryption key";
        char *bytes = reinterpret_cast<char *>(&value);
        for (size_t i = 0; i < sizeof(value); ++i)
        {
            for (size_t j = 0; j < sizeof(secret) - 1; ++j)
            {
                bytes[i] ^= secret[j];
            }
        }
    }

    // Explicit template instantiation
    template class Database<std::string>;
    template class Database<long long>;
}

