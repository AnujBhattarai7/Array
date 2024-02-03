#include <iostream>
#include "Array.h"
#include <array>

#define SIZE 200

int main(int argc, char const *argv[])
{
    {
        // std::array<int, 3> _A;
   
    }
    
    {
        Array<int ,10> _Array;
        _Array.Fill(10, 2);
        _Array.Erase(0);
        for(auto& i : _Array)
            _PRINT_(i);
    }

    return 0;
}
