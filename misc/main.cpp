//
// Misc:
//
//  - range based for loop init section
//      variables in init are in scope of ranged for block
//      like what was done for if statements in C++17
//
// complie:
//      g++-10 -std=c++20 main.cpp 
//
#include <iostream>
#include <string>
#include <map>


// Reminder: C++17 if init section
//
void Cpp17Reminder()
{
    // pre-c++17
    std::map< std::string, int > MyMap;
    MyMap["item1"] = 1;
    MyMap["item2"] = 2;

    // pre-C++17, needed to prepare variable outside of if, which
    // means visible not just in 'if' where we need it
    auto iter = MyMap.insert( {"item2", 2 } );
    if( !iter.second ) {
        // already exists
    }
    // ! iter still in scope here, but we don't need it..

    // C++17, we can use if's init section
    if( auto cpp17 = MyMap.insert( {"item2", 2 } ); !cpp17.second ) {
        // already exists
    }
    // cpp17 not in scope
}

// In C++20 we have init section in ranged for loop too
//
void Cpp20RangedForInit()
{
    std::map< std::string, int > MyMap;
    MyMap["item1"] = 1;
    MyMap["item2"] = 2;

    // Before C++20
    std::size_t i = 0;
    for (auto& d : MyMap) {
        std::cout << i++ << ' ' << d.first << '\n';
    }
    // ! i still in scope, but we only want to use it in the for loop

    // C++20, allows us to init in the ranged for loop;
    for( std::size_t cpp20 = 0; auto& d : MyMap ) {
        std::cout << cpp20++ << ' ' << d.first << '\n';
    }
    // cpp20 not in scope

}

int main()
{
    Cpp17Reminder();

    Cpp20RangedForInit();
}

