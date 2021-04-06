// Three way comparison - spaceship operator - operator<=>
//
// a <=> b : is a less, equal or greater than b? 
// This allows us to reduce the number of comparison operators that we need to define as compiler can use it instead of <, <=, >, >=
// So, implementing <=> and == gives you 6 operators (<, <=, >, >=, ==, !=)
// 
//
// Requires g++ version 10+ (and -std=c++20 / -std=c++2a)
//   on ubuntu: sudo apt install g++-10
//   compile with: g++-10 -std=c++20 <files>
//
#include <iostream>

/*
// OLD WAY: Pre-C++20
//
// We define all 6 comparison operators, by convention in terms
// of == and <
//
// Also remember that by convention they are implemented externally to
// the class, with access to the class members granted via 'friend', to
// remove restriction of lhs of expression being 'this' (i.e. allow implicit conversion on lhs too).
// 
// e.g. the following (as a member function rather than friend) also works;
//    class MyClass { 
//        bool operator==(const MyClass& rhs) const { return this.value == rhs.value; }
//    }
// but wouldn't support: 
//    42 == myClassInstance // can't pass 42 as 'this', but could cast if was friend
//
class MyClass {

private:
  int value;

public:
  MyClass(int value): value{value} { }

    friend bool operator==(const MyClass& lhs, const MyClass& rhs);
    friend bool operator!=(const MyClass& lhs, const MyClass& rhs);
    friend bool operator<( const MyClass& lhs, const MyClass& rhs);
    friend bool operator<=(const MyClass& lhs, const MyClass& rhs);
    friend bool operator>(const MyClass& lhs, const MyClass& rhs);
    friend bool operator>=(const MyClass& lhs, const MyClass& rhs);
};

bool operator==(const MyClass& lhs, const MyClass& rhs) { 
    return lhs.value == rhs.value; 
}
bool operator!=(const MyClass& lhs, const MyClass& rhs) {
    return !(lhs == rhs);
}
bool operator<(const MyClass& lhs, const MyClass& rhs)  { 
    return lhs.value < rhs.value;
}
bool operator<=(const MyClass& lhs, const MyClass& rhs) {
    return !(rhs < lhs);
}
bool operator>(const MyClass& lhs, const MyClass& rhs)  {
    return rhs < lhs;
}
bool operator>=(const MyClass& lhs, const MyClass& rhs) {
    return !(lhs < rhs);
}
*/

// New Way: C++20
//
#include <compare>  // C++20; for comparison categories

class MyClass {

private:
  int value;

public:
  MyClass(int value): value{value} { }

    // C++20 Note: doesn't have to be a non-member function to support
    /// implicit conversion on lhs
    // Note: We could also use a default (= default)
    std::strong_ordering operator<=>( const MyClass& rhs ) const {
        std::cout << "threeway called" << std::endl;
        // primitive types have <=> defined for us
        // or could use std::compare_3way() which falls back to 2 way
        return (*this).value <=> rhs.value;
    }

    bool operator==(const MyClass& rhs) const = default;

    bool operator==( int rhs ) const {
        std::cout << "== called" << std::endl;
        return *this <=> rhs == 0;
    }
};

int main()
{
    MyClass a{8};
    MyClass b{4};

    if( (a > b) && (64 > a) && (8 == a))
    {
        std::cout << "test passed" << std::endl; 
    }
}