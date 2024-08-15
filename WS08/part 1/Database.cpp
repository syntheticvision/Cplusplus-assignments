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

namespace seneca {

std::shared_ptr<Database> Database::instance = nullptr;

Database::Database(const std::string& filename) : entryCount(0), filename(filename) {
    std::cout << "Instance at " << this << " constructed\n";
    std::ifstream file(filename);
    std::string key, value;
    while (file >> key >> value && entryCount < MAX_SIZE) {
        std::replace(key.begin(), key.end(), '_', ' ');
        keys[entryCount] = key;
        values[entryCount] = value;
        ++entryCount;
    }
}

std::shared_ptr<Database> Database::getInstance(const std::string& filename) {
    if (!instance) {
        instance = std::shared_ptr<Database>(new Database(filename));
    }
    return instance;
}

Err_Status Database::GetValue(const std::string& key, std::string& value) const {
    for (int i = 0; i < entryCount; ++i) {
        if (keys[i] == key) {
            value = values[i];
            return Err_Status::Err_Success;
        }
    }
    return Err_Status::Err_NotFound;
}

Err_Status Database::SetValue(const std::string& key, const std::string& value) {
    if (entryCount >= MAX_SIZE) {
        return Err_Status::Err_OutOfMemory;
    }
    for (int i = 0; i < entryCount; ++i) {
        if (keys[i] == key) {
            values[i] = value;
            return Err_Status::Err_Success;
        }
    }
    keys[entryCount] = key;
    values[entryCount] = value;
    ++entryCount;
    return Err_Status::Err_Success;
}

Database::~Database() {
    std::cout << "Instance at " << this << " destructed\n";
    std::ofstream backupFile(filename + ".bkp.txt");
    for (int i = 0; i < entryCount; ++i) {
        backupFile << std::left << std::setw(25) << keys[i] << " -> " << values[i] << "\n";
    }
}

} // namespace seneca
