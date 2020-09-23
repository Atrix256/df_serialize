// STL replacement types, to test / ensure STL is not required

#pragma once

#include <string.h>
#include <initializer_list>

template <typename T>
struct MyVector
{
    ~MyVector()
    {
        clear();
    }

    void clear()
    {
        if (m_array)
        {
            delete[] m_array;
            m_array = nullptr;
        }
        m_size = 0;
    }

    void resize(size_t n)
    {
        if (n == m_size)
            return;

        T* newArray = new T[n];

        size_t copyCount = (n < m_size) ? n : m_size;
        for (size_t i = 0; i < copyCount; ++i)
            newArray[i] = m_array[i];

        clear();
        m_array = newArray;
        m_size = n;
    }

    size_t size() const
    {
        return m_size;
    }

    T& operator [](size_t i) { return m_array[i]; }
    const T& operator [](size_t i) const { return m_array[i]; }

    T* begin() { return m_array; }
    T* end() { return m_array + m_size; }

    const T* begin() const { return m_array; }
    const T* end() const { return m_array + m_size; }

    T* data()
    {
        return m_array;
    }

    const T* data() const
    {
        return m_array;
    }

private:
    T* m_array = nullptr;
    size_t m_size = 0;
};

template <typename T, size_t N>
struct MyArray
{
    MyArray()
    {

    }

    MyArray(std::initializer_list<T> il)
    {
        int index = 0;
        for (const T& src : il)
        {
            if (index >= N)
                break;
            m_array[index] = src;
            index++;
        }
    }

    T& operator [](size_t i) { return m_array[i]; }
    const T& operator [](size_t i) const { return m_array[i]; }

    T* begin() { return m_array; }
    T* end() { return m_array + N; }

    const T* begin() const { return m_array; }
    const T* end() const { return m_array + N; }

    T* data()
    {
        return m_array;
    }

    const T* data() const
    {
        return m_array;
    }

private:
    T m_array[N];
};

struct MyString
{
    MyString(const char* s = nullptr)
    {
        set(s);
    }

    ~MyString()
    {
        clear();
    }

    size_t length() const
    {
        return m_string ? strlen(m_string) : 0;
    }

    void resize(size_t newSize)
    {
        if (newSize == 0)
        {
            clear();
            return;
        }

        char* newString = new char[newSize];
        memset(newString, 0, newSize);
        if (m_string)
        {
            strcpy(newString, m_string);
            delete m_string;
        }
        m_string = newString;
    }

    const char* c_str() const
    {
        return m_string;
    }

    void operator = (const char* s)
    {
        set(s);
    }

    bool operator == (const MyString& other) const
    {
        size_t thisLen = length();
        size_t otherLen = other.length();

        if (thisLen == 0 && otherLen == 0)
            return true;

        if (thisLen != otherLen)
            return false;

        return strcmp(m_string, other.c_str()) == 0;
    }

    bool operator != (const MyString& other) const
    {
        return !(*this == other);
    }

    void operator += (const char* s)
    {
        if (!s)
            return;

        if (!m_string)
        {
            set(s);
            return;
        }

        char* newString = new char[strlen(m_string) + strlen(s) + 1];
        strcpy(newString, m_string);
        strcat(newString, s);
        clear();
        m_string = newString;
    }

    void clear()
    {
        if (m_string)
        {
            delete[] m_string;
            m_string = nullptr;
        }
    }

    char& operator [](size_t i) { return m_string[i]; }
    const char& operator [](size_t i) const { return m_string[i]; }

private:
    void set(const char* s)
    {
        clear();
        if (s)
        {
            m_string = new char[strlen(s) + 1];
            strcpy(m_string, s);
        }
    }

    char* m_string = nullptr;
};