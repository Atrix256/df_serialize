// Generates code to read binary data from memory and files

#include "_common.h"
#include <vector>

#ifndef MAKE_BINARY_LOG
#define MAKE_BINARY_LOG(...)
#endif

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) \
    bool BinaryRead(_NAMESPACE::_NAME& value, const std::vector<char>& data, size_t& offset) \
    { \
        typedef _NAMESPACE::_NAME EnumType; \
        std::string stringValue; \
        if(!BinaryRead(stringValue, data, offset)) \
        { \
            MAKE_BINARY_LOG("Trying to read a " #_NAMESPACE "::" #_NAME " as a string, but we couldn't\n"); \
            return false; \
        }

#define ENUM_ITEM(_NAME) \
        if (!_stricmp(stringValue.c_str(), #_NAME)) \
        { \
            value = EnumType::_NAME; \
            return true; \
        }

#define ENUM_END() \
        MAKE_BINARY_LOG("Unknown Enum Value: \"%s\"", stringValue.c_str()); \
        return false; \
    }

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    bool BinaryRead(_NAMESPACE::_NAME& value, const std::vector<char>& data, size_t& offset) \
    {

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    bool BinaryRead(_NAMESPACE::_NAME& value, const std::vector<char>& data, size_t& offset) \
    { \
        if (!BinaryRead(*(_BASE*)&value, data, offset)) \
            return false;

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (!BinaryRead(value.##_NAME, data, offset)) \
        { \
            MAKE_BINARY_LOG("Could not read member " #_NAME "\n"); \
            return false; \
        }

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        { \
            int arrayCount = 0; \
            if (!BinaryRead(arrayCount, data, offset)) \
            { \
                MAKE_BINARY_LOG("Could not read array count of array " #_NAME "\n"); \
                return false; \
            } \
            value._NAME.resize(arrayCount); \
            for (auto& item : value._NAME) \
            { \
                if(!BinaryRead(item, data, offset)) \
                { \
                    MAKE_BINARY_LOG("Could not read an array item for array " #_NAME "\n"); \
                    return false; \
                } \
            } \
        }

#define SCHEMA_END() \
        return true; \
    }

// Built in types

bool BinaryRead(int& value, const std::vector<char>& data, size_t& offset)
{
    if (offset + sizeof(value) > data.size())
        return false;

    value = *(int*)&data[offset];
    offset += sizeof(value);

    return true;
}

bool BinaryRead(float& value, const std::vector<char>& data, size_t& offset)
{
    if (offset + sizeof(value) > data.size())
        return false;

    value = *(float*)&data[offset];
    offset += sizeof(value);

    return true;
}

bool BinaryRead(bool& value, const std::vector<char>& data, size_t& offset)
{
    int intValue = 0;
    if (!BinaryRead(intValue, data, offset))
        return false;

    value = intValue ? true : false;

    return true;
}

bool BinaryRead(std::string& value, const std::vector<char>& data, size_t& offset)
{
    // Yes, the strings are null terminated in the binary file
    value = (const char*)&data[offset];
    offset += value.length() + 1;
    return true;
}
