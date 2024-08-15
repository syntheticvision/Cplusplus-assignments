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
#include <numeric>
#include <algorithm>
#include <stdexcept>

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
            good.type = BakedType::PASTERY;
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

    int totalStock = 0;
    double totalPrice = 0.0;

    for (const auto& b : goods) {
        totalStock += b.stock;
        totalPrice += b.price;
    }

    os << "Total Stock: " << totalStock << std::endl;
    os << "Total Price: " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
}

void Bakery::sortBakery(const std::string& field) {
    if (field == "Description") {
        std::stable_sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            if (a.description == b.description) {
                return a.price < b.price;
            }
            return a.description < b.description;
        });
    } else if (field == "Shelf") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            if (a.description == b.description) {
                return a.price < b.price;
            }
            return a.shelfLife < b.shelfLife;
        });
    } else if (field == "Stock") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            if (a.description == b.description) {
                return a.price < b.price;
            }
            return a.stock < b.stock;
        });
    } else if (field == "Price") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            if (a.description == b.description) {
                return a.price < b.price;
            }
            return a.price < b.price;
        });
    } else {
        throw std::invalid_argument("Invalid sort field.");
    }
}


std::vector<BakedGood> Bakery::combine(const Bakery& other) const {
    std::vector<BakedGood> combined = goods;
    combined.insert(combined.end(), other.goods.begin(), other.goods.end());

    std::sort(combined.begin(), combined.end(), [](const BakedGood& a, const BakedGood& b) {
        return a.price < b.price;
    });

    return combined;
}

bool Bakery::inStock(const std::string& description, BakedType type) const {
    auto it = std::find_if(goods.begin(), goods.end(), [&](const BakedGood& b) {
        return b.description == description && b.type == type && b.stock > 0;
    });
    return it != goods.end();
}

std::list<BakedGood> Bakery::outOfStock(BakedType type) const {
    std::list<BakedGood> outOfStockGoods;
    std::copy_if(goods.begin(), goods.end(), std::back_inserter(outOfStockGoods), [&](const BakedGood& b) {
        return b.type == type && b.stock == 0;
    });
    return outOfStockGoods;
}


std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
    out << "* " << std::left << std::setw(10) << ((b.type == BakedType::BREAD) ? "Bread" : "Pastry") << " * "
        << std::setw(20) << b.description << " * "
        << std::setw(5) << b.shelfLife << " * "
        << std::setw(5) << b.stock << " * "
        << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price << " * ";
    return out;
}

}
