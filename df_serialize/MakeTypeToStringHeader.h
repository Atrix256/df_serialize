// This makes a TypeToString function which converts a typeid to the string for that type

#include "_common.h"
#include <stdint.h>
#include "_compile_time_crc32.h"

const char* TypeToString(uint32_t type)
{
    switch(type)
    {

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) case crc32_rec(1337, #_NAMESPACE "::" #_NAME): return #_NAMESPACE "::" #_NAME;

#define ENUM_ITEM(_NAME, _DESCRIPTION)

#define ENUM_END()

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) case crc32_rec(1337, #_NAMESPACE "::" #_NAME): return #_NAMESPACE "::" #_NAME;

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) case crc32_rec(1337, #_NAMESPACE "::" #_NAME): return #_NAMESPACE "::" #_NAME;

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION)

#define SCHEMA_END()

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME) case crc32_rec(1337, #_NAMESPACE "::" #_NAME): return #_NAMESPACE "::" #_NAME;

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define VARIANT_END()
