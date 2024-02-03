#include <iostream>
#include "Array.h"
#include <array>

#define SIZE 10

struct Test
{
    Test(int n = 1) : _n(n)
    {
    }

    Test(const Test &Other)
        : _n(Other._n)
    {
        _PRINT_("[TEST]: Copy");
    }

    Test(Test &&_T)
        : _n(_T._n)
    {
        _PRINT_("[TEST]: Move");
    }

    ~Test()
    {
        _PRINT_("[TEST]: Delete")
    }

    friend std::ostream &operator<<(std::ostream &os, Test &_T)
    {
        os << _T._n;
        return os;
    }

    inline Test &operator=(int n)
    {
        _n = n;
        return *this;
    }

    inline Test &operator=(const Test &_O)
    {
        _PRINT_("[TEST]: Copy");
        _n = _O.Get();
        return *this;
    }

    inline Test &operator=(Test &&_O)
    {
        _PRINT_("[TEST]: Move");
        _n = _O._n;
        return *this;
    }

    inline const int Get() const { return _n; }

    int _n = 0;
};

int main(int argc, char const *argv[])
{
    {
        Array<Test, 1> _Array;
        _Array.Emplace(0, 2);
    
        for(auto& i : _Array)
            _PRINT_(i)
    }

    std::cin.get();

    return 0;
}
