// Generates code to write binary data to memory and files

#include "_common.h"
#include <vector>
#include <strstream>

#ifndef MAKE_BINARY_LOG
#define MAKE_BINARY_LOG(...)
#endif


// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) \
    void BinaryWrite(const _NAMESPACE::_NAME& value, std::vector<char>& output) \
    { \
        typedef _NAMESPACE::_NAME EnumType; \
        switch(value) \
        { \

#define ENUM_ITEM(_NAME) \
            case EnumType::_NAME: BinaryWrite(std::string(#_NAME), output); break; \

#define ENUM_END() \
        } \
    }

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    void BinaryWrite(const _NAMESPACE::_NAME& value, std::vector<char>& output) \
    { \

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    void BinaryWrite(const _NAMESPACE::_NAME& value, std::vector<char>& output) \
    { \
        BinaryWrite(*(const _BASE*)&value, output);

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) BinaryWrite(value._NAME, output);

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION)\
        BinaryWrite((int32_t)value._NAME.size(), output); \
        for (const auto& item : value._NAME) \
            BinaryWrite(item, output); \

#define SCHEMA_END() \
    }

// Built in types

void BinaryWrite(int32_t value, std::vector<char>& output)
{
    size_t offset = output.size();
    output.resize(offset + sizeof(value));
    *((int32_t*)(&output[offset])) = value;
}

void BinaryWrite(float value, std::vector<char>& output)
{
    size_t offset = output.size();
    output.resize(offset + sizeof(value));
    *((float*)(&output[offset])) = value;
}

void BinaryWrite(bool value, std::vector<char>& output)
{
    BinaryWrite(value ? 1 : 0, output);
}

void BinaryWrite(const std::string& value, std::vector<char>& output)
{
    size_t offset = output.size();
    int len = (int)value.length();
    output.resize(output.size() + len + 1);
    char* dest = (char*)&output[offset];
    const char* src = value.c_str();
    for (int i = 0; i <= len; ++i)
        dest[i] = src[i];
}
