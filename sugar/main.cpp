//
// Misc Syntactic Sugar
//
//  - Designated Initialisers
//  - 
//
#include <iostream>

// Designated Initialisers: call out members by name in initialisation list, can skip.
struct MyStruct {
    int memberA;
    std::string memberB;
    float memberC;
};

int main()
{
    std::cout << "Misc Syntactic Sugar" << std::endl;


    // Designated Initialisers: 
    MyStruct oldway{ 1, "b", 3.14f };   // OK, as before
    MyStruct oldway2{ 1, "b" };         // OK, as before
    // MyStruct oldway3{ "b" };         // Compile error, as before - but see b below
    MyStruct abc{ .memberA=1, .memberB="b", .memberC=3.14f };
    MyStruct b{ .memberB="b" };         // Can now init specific members
    // MyStruct unordered{ .memberC=3.14f, .memberA=1, .memberB="b" };   // Complilastion error: must be in declaration order
    

}