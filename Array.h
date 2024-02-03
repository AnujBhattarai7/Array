#pragma once

#include <initializer_list>
#include "Iterator.h"

#define _PRINT_(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

template <typename _T, int _Size>
class Array
{
public:
    using ValueType = _T;
    using Iterator = _Iterator_Base<ValueType>;

public:
    Array() {}
    ~Array() { _Flush(); }

    const int Size() const { return _Size; }
    const _T *Data() const { return _Array; }
    const _T &At(int i) const { return this->operator[](i); }

    void Fill(int n, _T &&_O);
    void Fill(int n, const _T &_O);

    void Erase(int i);

    _T &operator[](int i) { return _Get(i); }
    const _T &operator[](int i) const { return _Get(i); }

    Iterator begin() { return Iterator(_Array); }
    Iterator end() { return Iterator(_Array + _Size); }

private:
    // The main array whichs stores the data
    _T _Array[_Size];

    // Flushes the elements of _Array
    void _Flush();

    // Checks if the given i exists in _Size
    void _AuthIndex(int i) const;

    // Checks and returns teh value in i in _Array
    _T &_Get(int i);
};

template <typename _T, int _Size>
inline void Array<_T, _Size>::Fill(int n, _T &&_O)
{
    if (n > _Size)
    {
        _PRINT_("Size: " << n << " out of range!!!")
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
        _Array[i] = std::move(_O);
}

template <typename _T, int _Size>
inline void Array<_T, _Size>::Fill(int n, const _T &_O)
{
    if (n > _Size)
    {
        _PRINT_("Size: " << n << " out of range!!!")
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
        _Array[i] = _O;
}

template <typename _T, int _Size>
inline void Array<_T, _Size>::Erase(int i)
{
    _AuthIndex(i);

    _Array[i].~_T();
}

template <typename _T, int _Size>
inline void Array<_T, _Size>::_Flush()
{
    for (int i = 0; i < _Size; i++)
        Erase(i);
}

template <typename _T, int _Size>
inline void Array<_T, _Size>::_AuthIndex(int i) const
{
    if (i >= _Size)
    {
        _PRINT_("[ARRAY]: Index: " << i << " out of range!!")
        exit(EXIT_FAILURE);
    }
}

template <typename _T, int _Size>
inline _T &Array<_T, _Size>::_Get(int i)
{
    _AuthIndex(i);
    return _Array[i];
}