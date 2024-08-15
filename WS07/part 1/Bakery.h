//==============================================
// Name:           Babak Ghafourigivi
// Student Number: 165118233
// Email:          bghafourigivi@myseneca.ca
// Section:        ZDD
// Date:           July 14, 2024
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or 3rd party content provider.
//==============================================
#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace seneca {

enum class BakedType {
    BREAD,
    PASTRY
};

struct BakedGood {
    BakedType type;
    std::string description;
    int shelfLife;
    int stock;
    double price;
};

class Bakery {
private:
    std::vector<BakedGood> goods;

public:
    Bakery(const std::string& filename);
    void showGoods(std::ostream& os) const;
};

inline std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

std::ostream& operator<<(std::ostream& out, const BakedGood& b);

}

#endif // SENECA_BAKERY_H
