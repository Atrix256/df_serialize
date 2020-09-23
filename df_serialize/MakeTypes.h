// This creates structs and enums

#include "_common.h"
#include <stdint.h>

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
    namespace _NAMESPACE \
    { \
        enum class _NAME : int32_t \
        {

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
            _NAME,

#define ENUM_END() \
        }; \
    };

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
    namespace _NAMESPACE \
    { \
        struct _NAME \
        {

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION) \
    namespace _NAMESPACE \
    { \
        struct _NAME : public _BASE \
        {

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
            _TYPE _NAME = _DEFAULT;

#define SCHEMA_DYNAMIC_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
            TDYNAMICARRAY<_TYPE> _NAME;

#define SCHEMA_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
            TSTATICARRAY<_TYPE, _SIZE> _NAME = _DEFAULT;

#define SCHEMA_END() \
        }; \
    };

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
    namespace _NAMESPACE \
    { \
        struct _NAME \
        { \
            static const uint32_t c_index_None = (uint32_t)-1; \
            uint32_t _index = c_index_None;

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
            static const uint32_t c_index_##_NAME = __COUNTER__; \
            _TYPE _NAME = _DEFAULT;

#define VARIANT_END() \
        }; \
    };
