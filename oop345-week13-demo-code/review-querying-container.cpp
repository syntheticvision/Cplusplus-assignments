// Algorithms - Copy If
// copy_if.cpp

#include <vector>
#include <algorithm>
#include <iostream>

// a simple function
bool eq10(int x) { return x == 10; };

// a functor
struct gt7
{
    bool operator()(int x) { return x > 7; }
};

// a lambda expression
auto lte17 = [](int x) { return  x <= 17; }; // or [](int x) -> bool { return  x <= 17; }; 


int main()
{
    std::vector<int> v = {1, 2, 4, 5, 7, 8, 10, 13, 17, 21, 43};
    std::vector<int> c1(15), c2;
    std::vector<int>::iterator it;

    std::cout << "vector<int> v:" << std::endl;
    for (auto e : v) std::cout << e << " ";
    std::cout << std::endl << std::endl;

    std::cout << "vector<int> c1:" << std::endl;
    for (auto e : c1) std::cout << e << " ";
    std::cout << std::endl << std::endl;

    std::cout << "vector<int> c2:" << std::endl;
    for (auto e : c2) std::cout << e << " ";
    std::cout << std::endl << std::endl;



    std::cout << "********** Get One: ********* " << std::endl;
    const int search1 = 10;

    // run one line at a time:
    // it = std::find (v.begin(), v.end(), search1); 
    // it = std::find_if(v.begin(), v.end(), [](int e){ return e == search1; } ); // using lambda expression
    it = std::find_if(v.begin(), v.end(), eq10 ); // using a simple function eq10
    if (it != v.end())
        std::cout << "Element found in v: " << *it << '\n'<< std::endl;
    else
        std::cout << "Element not found in v\n" << std::endl;


    std::cout << "********** copy i.e., Get All ********* " << std::endl;
    std::copy(v.begin(), v.end(), c1.begin() );  // unexpected ""..., 0, 0" at the end. no good unless same size for the 2 containers
    for (auto e : c1) std::cout << e << " ";
    std::cout << std::endl << std::endl;
    
    // std::copy(v.begin(), v.end(), std::back_inserter(c2) ); // use std::back_inserter(c2) rather than c2.begin()
    std::for_each(v.begin(), v.end(), [&](int e){ 
            c2.push_back(e); 
        } );
    for (auto e : c2) std::cout << e << " ";
    std::cout << std::endl << std::endl;

    std::cout << "********** copy_if  i.e. Get subset - filtering/query ********* " << std::endl;
    c2.clear();
    // run one line at a time:
    // std::copy_if(v.begin(), v.end(), std::back_inserter(c2), eq10 ); // using a simple function eq10
    std::copy_if(v.begin(), v.end(), std::back_inserter(c2), gt7() ); // using a functor gt7
    // std::copy_if(v.begin(), v.end(), std::back_inserter(c2), lte17 ); // using lambda expression lte17
    // std::copy_if(v.begin(), v.end(), std::back_inserter(c2), [](int x) { return  x <= 17; } ); // using lambda expression 

    for (auto e : c2) std::cout << e << " ";
    std::cout << std::endl << std::endl;


    std::cout << "********** Update original collection (transform) ********* " << std::endl;
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x + 2;  } ); // using lambda expression 
    for (auto e : v) std::cout << e << " ";
    std::cout << std::endl << std::endl;


    //"********** delete ********* 
    // delete: .erase()
    
    // Try: replace all "vector" with "list" and then compile/run the file/program again
}