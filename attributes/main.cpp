//
// New C++20 Attributes
//
//  - [[likely]] / [[unlikely]] - hint on likeliness of code path
//  - [[[nodiscard]]] - can now supply a message, and use in ctors
//
#include <iostream>


// [[nodiscard]] - in C++20 can now define message too
// pre-C++20: [[nodiscard]]
[[nodiscard("You must use my return because blah")]]
int PleaseUseMyReturn() {
    return 1;
}

class MyClass {
    int someResource;
public:
    MyClass() { }      // OK not to discard me 

    [[nodiscard("You must do X Y Z with the object, don't just discard")]]
    MyClass( std::string resourceName) {
        // Allocate some resource, which caller needs
        // to handle
     }
};

int main()
{
    // nodiscard message
    //
    // PleaseUseMyReturn();     // Fails at compile time: prints our message above

    // discard CTOR
    MyClass{};      // OK to discard, as lacks attribute
    // MyClass{"importantThing"};   // compile error
    MyClass x = MyClass{"importantThing"};
    MyClass y{"blah"};

    // likely & unlikely
    //
    int a = 10;
    if( a < 100 ) [[likely]]
    {
        // to commonly done thing
    }
    else
    {
        // do rare thing
    }
}