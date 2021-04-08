// “Concepts” - compile time check of template constraints
//
// compile with;
//      g++-10 -std=c++20 -fconcepts main.cpp
//

#include <iostream>

//
// Concept Example 1: 
// 

class Creature {};
class Bird : public Creature {};
class Cat : public Creature {};

template<class T> class canFly {            // most can't fly
public:
    static constexpr bool answer = false;
}; 

template<> class canFly<class Bird> {         // specialisation; birds can fly
public:
    static constexpr bool answer = true;
};

// The Concept: TestFlight
//     i.e. TestFlight enforces only types that can fly
//
template<typename T> concept TestFlight = canFly<T>::answer;

// Using the Concept to restrict applicable types:
//     ensure only types that can fly can use this function
//
template<TestFlight T> void FlyToClouds( const T& Creature ) {
    // flies to the clouds, because it can
}

// Example 2: Requires
//
template<typename T> concept TestFlight2 = requires(T a)
{
    requires canFly<T>::answer;
};

template<typename T> 
requires TestFlight2<T>
void FlyToClouds2( const T& Creature ) {
    // flies to the clouds, because it can
}

// Or...
template<typename T> 
requires canFly<T>::answer
void FlyToClouds2b( const T& Creature ) {
    // flies to the clouds, because it can
}

// Example 3: Use the concept instead of typename
//
template<TestFlight2 T> 
void FlyToClouds3( const T& Creature ) {
    // flies to the clouds, because it can
}

int main()
{
    std::cout << "Concepts:" << std::endl;

    // Example 1:
    //
    Bird myBird{};
    Cat myCat{};

    FlyToClouds( myBird );      // OK, concept's requirements satisfied

    // FlyToClouds( myCat );    // Compile time error: 
                                // use of function ‘void FlyToClouds(const T&) [with T = Cat]’ with unsatisfied constraints

    // Example 2:
    //
    FlyToClouds2( myBird );
    // FlyToClouds2( myCat );   // Compile time error
    FlyToClouds2b( myBird );
    // FlyToClouds2b( myCat );   // Compile time error

    // Example 3:
    //
    FlyToClouds3( myBird );
    //FlyToClouds3( myCat );   // Compile time error
}