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
#include "Bakery.h"

namespace seneca {

Bakery::Bakery(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        BakedGood good;
        std::string typeStr = trim(line.substr(0, 8));
        std::string description = trim(line.substr(8, 20));
        std::string shelfLifeStr = trim(line.substr(28, 14));
        std::string stockStr = trim(line.substr(42, 8));
        std::string priceStr = trim(line.substr(50, 6));

        if (typeStr == "Bread") {
            good.type = BakedType::BREAD;
        } else if (typeStr == "Pastry") {
            good.type = BakedType::PASTRY;
        } else {
            throw std::runtime_error("Unknown BakedType: " + typeStr);
        }

        good.description = description;
        good.shelfLife = std::stoi(shelfLifeStr);
        good.stock = std::stoi(stockStr);
        good.price = std::stod(priceStr);

        goods.push_back(good);
    }
}

void Bakery::showGoods(std::ostream& os) const {
    std::for_each(goods.begin(), goods.end(), [&os](const BakedGood& b) {
        os << b << std::endl;
    });
}

std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
    out << "* " << std::left << std::setw(10) << ((b.type == BakedType::BREAD) ? "Bread" : "Pastry") << " * "
        << std::setw(20) << b.description << " * "
        << std::setw(5) << b.shelfLife << " * "
        << std::setw(5) << b.stock << " * "
        << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price << " * ";
    return out;
}

} // namespace seneca

