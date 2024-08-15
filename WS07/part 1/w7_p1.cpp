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
#include <iostream>
#include <iomanip>
#include "Bakery.h"
#include "Bakery.h" // intentional

int cout = 0; // won't compile if headers don't follow convention

void printstars(std::ostream& os, size_t cnt)
{
  for (auto i = 0u; i < cnt; ++i)
    os << "*";
  os << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "Command Line:\n";
  std::cout << "--------------------------\n";
  for (int i = 0; i < argc; ++i)
    std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
  std::cout << "--------------------------\n\n";

  seneca::Bakery bakery(argv[1]);
  std::cout << std::left << std::setw(15) << "Type" << std::setw(23) << "Description"
     << std::setw(8) << "Shelf" << std::setw(8) << "Stock"
     << std::right << std::setw(8) << "Price" << std::endl;
  ::printstars(std::cout, 64);
  bakery.showGoods(std::cout);
  ::printstars(std::cout, 64);

  return cout;
}
