// Generates code to write data to json files.

#include "_common.h"
#include <vector>
#include <strstream>

#ifndef MAKE_JSON_LOG
#define MAKE_JSON_LOG(...)
#endif

// This is for debugging. put trace calls in the macros below to see info logged about what functions were called etc
#define MAKE_JSON_TRACE(...)
//MAKE_JSON_LOG(__VA_ARGS__)

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) \
    void JSONWrite(const _NAMESPACE::_NAME& value, std::stringstream& output, int indent) \
    { \
        typedef _NAMESPACE::_NAME EnumType; \
        switch(value) \
        { \

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
            case EnumType::_NAME: output << "\"" #_NAME "\""; break;

#define ENUM_END() \
        } \
    }

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    void JSONWrite(const _NAMESPACE::_NAME& value, std::stringstream& output, int indent, bool writeBraces = true) \
    { \
        if(writeBraces) \
        { \
            WriteIndentation(output, indent); \
            output << "{\n"; \
            indent++; \
        }

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    void JSONWrite(const _NAMESPACE::_NAME& value, std::stringstream& output, int indent, bool writeBraces = true) \
    { \
        if(writeBraces) \
        { \
            WriteIndentation(output, indent); \
            output << "{\n"; \
            indent++; \
        } \
        JSONWrite(*(const _BASE*)&value, output, indent, false);

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._NAME != _DEFAULT) \
        { \
            WriteIndentation(output, indent); \
            output << "\"" #_NAME "\": "; \
            JSONWrite(value._NAME, output, indent); \
            output << ",\n"; \
        }

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION)\
        if (value._NAME.size() > 0) \
        { \
            WriteIndentation(output, indent); \
            output << "\"" #_NAME "\": "; \
            output << "[\n"; \
            for (const auto& item : value._NAME) \
            { \
                JSONWrite(item, output, indent + 1); \
                output << "\n"; \
            } \
            WriteIndentation(output, indent); \
            output << "],\n"; \
        }

#define SCHEMA_END() \
        if (writeBraces) \
        { \
            indent--; \
            WriteIndentation(output, indent); \
            if (indent > 0) \
                output << "},"; \
            else \
                output << "}"; \
        } \
    }

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME) \
    void JSONWrite(const _NAMESPACE::_NAME& value, std::stringstream& output, int indent, bool writeBraces = true) \
    { \
        using namespace _NAMESPACE; \
        if(writeBraces) \
        { \
            WriteIndentation(output, indent); \
            output << "{\n"; \
            indent++; \
        } \
        WriteIndentation(output, indent); \
        output << "\"_type\":\"" << TypeToString(value._type) << "\",\n";

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._type == c_type_##_TYPE && value._NAME != _DEFAULT) \
            JSONWrite(value._NAME, output, indent, false); \

#define VARIANT_END() \
        if (writeBraces) \
        { \
            indent--; \
            WriteIndentation(output, indent); \
            if (indent > 0) \
                output << "},"; \
            else \
                output << "}"; \
        } \
    }

// indentation helper
void WriteIndentation(std::stringstream& output, int indent)
{
    for (int i = 0; i < indent; ++i)
        output << "    ";
}

// A catch all template type to make compile errors about unsupported types easier to understand

template <typename T>
void JSONWrite(T value, std::stringstream& output, int indent)
{
    static_assert(false, __FUNCSIG__ ": Unsupported type encountered!");
    return false;
}

// Built in types

void JSONWrite(uint8_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(uint16_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(uint32_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(uint64_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(int8_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(int16_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(int32_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(int64_t value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(float value, std::stringstream& output, int indent)
{
    output << value;
}

void JSONWrite(bool value, std::stringstream& output, int indent)
{
    output << (value ? "true" : "false");
}

void JSONWrite(const std::string& value, std::stringstream& output, int indent)
{
    output << "\"" << value << "\"";
}
