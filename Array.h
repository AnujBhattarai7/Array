#pragma once

#include <initializer_list>
#include "../Iterator.h"

#define _PRINT_(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

template <typename _Tp, int _Nm>
struct __array_traits
{
    using _Type = _Tp[_Nm];
};

template <typename _T, int _Size>
class Array
{
public:
    using ValueType = _T;
    using Iterator = _Iterator_Base<ValueType>;

public:
    Array(const std::initializer_list<_T> &_D) { *this = _D; }
    Array(const _T Data[_Size]) { *this = Data; }
    Array() {}
    ~Array() {}

    // Getters
    const int Max_Size() const { return _Size; }
    const int Size() const { return _OccupiedSize; }
    const _T *Data() const { return _Array; }
    const _T &At(int i) const { return this->operator[](i); }

    // Fills up to n the value _O
    void Fill(int n, _T &&_O);
    void Fill(int n, const _T &_O);

    // Erases the object at given index i
    void Erase(int i);

    // Rather than moving creates adds to _V from given args...
    template <typename... Args>
    _T &Emplace(int i, Args &&...args);

    // Operators..
    _T &operator[](int i) { return _Get(i); }

    const _T &operator[](int i) const
    {
        _AuthIndex(i);
        return _Array[i];
    }

    Iterator begin() { return Iterator(_Array); }
    Iterator end() { return Iterator(_Array + _OccupiedSize); }

    inline Array<_T, _Size> &operator=(const std::initializer_list<_T> &_D);
    inline Array<_T, _Size> &operator=(const _T _D[_Size]);

    inline void Push_Back(const char _L) { _Array[_OccupiedSize++] = _L; }

    void _Flush_() { _Flush(); }

private:
    // The main array whichs stores the data
    _T _Array[_Size];

    // Ocuupied size
    int _OccupiedSize = 0;

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
inline Array<_T, _Size> &Array<_T, _Size>::operator=(const std::initializer_list<_T> &_D)
{
    if (_D.size() > _Size)
    {
        _PRINT_("Size: " << _D.size() << " out of range!!!")
        exit(EXIT_FAILURE);
    }

    int _i = -1;

    for (auto &i : _D)
        _Array[_i] = std::move(i);

    return *this;
}

template <typename _T, int _Size>
inline Array<_T, _Size> &Array<_T, _Size>::operator=(const _T _D[_Size])
{
    for (int _OccupiedSize = 0; _OccupiedSize < _Size; _OccupiedSize++)
        _Array[_OccupiedSize] = std::move(_D[_OccupiedSize]);

    return *this;
    // TODO: insert return statement here
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

template <typename _T, int _Size>
template <typename... Args>
inline _T &Array<_T, _Size>::Emplace(int i, Args &&...args)
{
    _AuthIndex(i);

    new (&_Array[i]) _T(std::forward<Args>(args)...);
    return _Array[i];
}
