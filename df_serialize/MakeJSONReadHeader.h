// Generates code to read data from json files and strings.
// Code meant for use with rapidjson
// RapidJSON Website: https://rapidjson.org/
// RapidJSON Github:  https://github.com/Tencent/rapidjson/

#include "_common.h"
#include <vector>

#ifndef MAKE_JSON_LOG
#define MAKE_JSON_LOG(...)
#endif

// This is for debugging. put trace calls in the macros below to see info logged about what functions were called etc
#define MAKE_JSON_TRACE(...)
//MAKE_JSON_LOG(__VA_ARGS__)

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) \
    template <typename DOCUMENT> \
    bool JSONRead(_NAMESPACE::_NAME& value, DOCUMENT& document) \
    { \
        MAKE_JSON_TRACE(__FUNCSIG__ "\n"); \
        typedef _NAMESPACE::_NAME EnumType; \
        if (!document.IsString()) \
        { \
            MAKE_JSON_LOG("Trying to read a " #_NAMESPACE "::" #_NAME " but it wasn't a string\n"); \
            return false; \
        } \
        const char* stringValue = document.GetString();

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
        if (!_stricmp(stringValue, #_NAME)) \
        { \
            value = EnumType::_NAME; \
            return true; \
        }

#define ENUM_END() \
        MAKE_JSON_LOG("Unknown Enum Value: \"%s\"", stringValue); \
        return false; \
    }

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    template <typename DOCUMENT> \
    bool JSONRead(_NAMESPACE::_NAME& value, DOCUMENT& document) \
    { \
        MAKE_JSON_TRACE(__FUNCSIG__ "\n");

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    template <typename DOCUMENT> \
    bool JSONRead(_NAMESPACE::_NAME& value, DOCUMENT& document) \
    { \
        MAKE_JSON_TRACE(__FUNCSIG__ "\n"); \
        if (!JSONRead(*(_BASE*)&value, document)) \
            return false;

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (document.HasMember(#_NAME) && !JSONRead(value.##_NAME, document[#_NAME])) \
        { \
            MAKE_JSON_LOG("Could not read member " #_NAME "\n"); \
            return false; \
        }

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        if (document.HasMember(#_NAME)) \
        { \
            if (!document[#_NAME].IsArray()) \
            { \
                MAKE_JSON_LOG("'" #_NAME "' is not an array.\n"); \
                return false; \
            } \
            auto arr = document[#_NAME].GetArray(); \
            value._NAME.resize(arr.Size()); \
            int index = 0; \
            for (const rapidjson::Value& item : arr) \
            { \
                if(!JSONRead(value._NAME[index], item)) \
                    return false; \
                index++; \
            } \
        }

#define SCHEMA_END() \
        return true; \
    }

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME) \
    template <typename DOCUMENT> \
    bool JSONRead(_NAMESPACE::_NAME& value, DOCUMENT& document) \
    { \
        using namespace _NAMESPACE; \
        std::string _type; \
        if (document.HasMember("_type") && !JSONRead(_type, document["_type"])) \
            return false; \
        value._type = crc32_rec(1337, _type.c_str());

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._type == c_type_##_TYPE && !JSONRead(value._NAME, document)) \
            return false;

#define VARIANT_END() \
        return true; \
    }

// A catch all template type to make compile errors about unsupported types easier to understand

template <typename T, typename U>
bool JSONRead(T& value, U& document)
{
    static_assert(false, __FUNCSIG__ ": Unsupported type encountered!");
    return false;
}

// Built in types

template <typename T>
bool JSONRead(uint8_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read a uint8 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(uint16_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read a uint16 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(uint32_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read a uint32 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(uint64_t& value, T& document)
{
    if (!document.IsInt64())
    {
        MAKE_JSON_LOG("Trying to read a uint64 but it wasn't an int64\n");
        return false;
    }

    value = document.GetInt64();
    return true;
}

template <typename T>
bool JSONRead(int8_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read an int8 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(int16_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read an int16 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(int32_t& value, T& document)
{
    if (!document.IsInt())
    {
        MAKE_JSON_LOG("Trying to read an int32 but it wasn't an int\n");
        return false;
    }

    value = document.GetInt();
    return true;
}

template <typename T>
bool JSONRead(int64_t& value, T& document)
{
    if (!document.IsInt64())
    {
        MAKE_JSON_LOG("Trying to read an int64 but it wasn't an int64\n");
        return false;
    }

    value = document.GetInt64();
    return true;
}

template <typename T>
bool JSONRead(float& value, T& document)
{
    if (!document.IsDouble())
    {
        int intValue = 0;
        if (JSONRead(intValue, document))
        {
            value = (float)intValue;
            return true;
        }

        MAKE_JSON_LOG("Trying to read a float but it wasn't a float\n");
        return false;
    }

    value = (float)document.GetDouble();
    return true;
}

template <typename T>
bool JSONRead(bool& value, T& document)
{
    if (!document.IsBool())
    {
        MAKE_JSON_LOG("Trying to read a bool but it wasn't a bool\n");
        return false;
    }

    value = document.GetBool();
    return true;
}

template <typename T>
bool JSONRead(std::string& value, T& document)
{
    if (!document.IsString())
    {
        MAKE_JSON_LOG("Trying to read a string but it wasn't a string\n");
        return false;
    }

    value = document.GetString();
    return true;
}
