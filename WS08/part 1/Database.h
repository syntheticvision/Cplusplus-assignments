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

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

namespace seneca {

enum class Err_Status {
    Err_Success,
    Err_NotFound,
    Err_OutOfMemory,
};

class Database {
private:
    static std::shared_ptr<Database> instance;
    static constexpr int MAX_SIZE = 20;
    std::string keys[MAX_SIZE];
    std::string values[MAX_SIZE];
    int entryCount;
    std::string filename;

    Database(const std::string& filename);

public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static std::shared_ptr<Database> getInstance(const std::string& filename);

    Err_Status GetValue(const std::string& key, std::string& value) const;
    Err_Status SetValue(const std::string& key, const std::string& value);

    ~Database();
};

}

#endif // SENECA_DATABASE_H
