// This creates structs and enums

#include "_common.h"
#include <stdint.h>
#include "_compile_time_crc32.h"

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) \
    namespace _NAMESPACE \
    { \
        static const uint32_t c_type_##_NAME = crc32_rec(1337, #_NAMESPACE "::" #_NAME); \
        enum class _NAME : int32_t \
        {

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
            _NAME,

#define ENUM_END() \
        }; \
    };

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    namespace _NAMESPACE \
    { \
        static const uint32_t c_type_##_NAME = crc32_rec(1337, #_NAMESPACE "::" #_NAME); \
        struct _NAME \
        {

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    namespace _NAMESPACE \
    { \
        static const uint32_t c_type_##_NAME = crc32_rec(1337, #_NAMESPACE "::" #_NAME); \
        struct _NAME : public _BASE \
        {

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
            _TYPE _NAME = _DEFAULT;

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
            TDYNAMICARRAY<_TYPE> _NAME;

#define SCHEMA_END() \
        }; \
    };

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME) \
    namespace _NAMESPACE \
    { \
        static const uint32_t c_type_##_NAME = crc32_rec(1337, #_NAMESPACE "::" #_NAME); \
        struct _NAME \
        { \
            uint32_t _type = 0;

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
            _TYPE _NAME = _DEFAULT;

#define VARIANT_END() \
        }; \
    };
