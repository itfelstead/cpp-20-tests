//
// Modules
//
//  TODO: g++ 10 doesn't support it
//

#include <iostream>

// Module: myModule
export module myModule;
export void CanAccess() { } 
void CannotAccess() { }

int main()
{
    std::cout << "Modules:" << std::endl;
}
