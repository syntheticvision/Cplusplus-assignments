// Algorithms - Copy If
// copy_if.cpp

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// a simple function
bool eq10(int x) { return x == 10; };

// a functor
struct gt7
{
    bool operator()(int x) { return x > 7; }
};

// a lambda expression
auto lte17 = [](int x) { return  x <= 17; }; // or [](int x) -> bool { return  x <= 17; }; 

struct Person { 
	string name; 
	int age; 
};

int main()
{

    std::vector<Person> family  { 
        {"John", 30}, 
        {"Doe", 28}, 
        {"Jill", 2}, 
        {"Jack", 4}, 
        {"Julian", 9}};
    std::vector<Person> parents, dependents;
    std::vector<Person>::iterator iJohn, i9;

    std::cout << "vector<Person> family:" << std::endl;
    for (Person p : family) std::cout << p.name << ", " << p.age << '\n';
    std::cout << std::endl << std::endl;

    std::cout << "********** find (Get One): ********* " << std::endl;
    const int a = 9;

    // run one line at a time:
    iJohn = std::find_if(family.begin(), family.end(), [](Person p){ return p.name == "John"; } ); // using lambda expression
    if (iJohn != family.end())
        std::cout << "John found in family: " << iJohn->name << ' ' << iJohn->age << '\n'<< std::endl;
    else
        std::cout << "John not found in family\n" << std::endl;


    std::cout << "********** copy_if  i.e. Get parents/kids - filtering/query ********* " << std::endl;
    
    std::copy_if(family.begin(), family.end(), std::back_inserter(parents), [](Person p) { return  p.name == "John" || p.name == "Doe"; } ); // using lambda expression 
    std::cout << "Parents:" << std::endl;
    for (Person p : parents) std::cout << p.name << '\n';
    std::cout << std::endl;


    std::copy_if(family.begin(), family.end(), std::back_inserter(dependents), [](Person p) { return  p.age < 18; } ); // using lambda expression 

    std::cout << "dependents:" << std::endl;
    for (Person p : dependents) std::cout << p.name << '\n';
    std::cout << std::endl;

    std::cout << "********** dependents count ********* " << std::endl;
    int count = std::count_if(family.begin(), family.end(), [](Person p) { return  p.age < 18; }); 
    std::cout << "family member count: " << count << std::endl;


}