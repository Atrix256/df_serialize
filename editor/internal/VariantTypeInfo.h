// This makes information about variants, used by SchemaUI.h

#pragma once

#include "../df_serialize/_common.h"

struct VariantTypeInfo
{
    std::string name;
    uint32_t _index;
};

// Enums 

#define ENUM_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION)

#define ENUM_ITEM(_NAME, _DESCRIPTION)

#define ENUM_END()

// Structs

#define STRUCT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION)

#define STRUCT_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION)

#define STRUCT_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define STRUCT_FIELD_NO_SERIALIZE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define STRUCT_DYNAMIC_ARRAY(_TYPE, _NAME, _DESCRIPTION)

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION)

#define STRUCT_END()

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
    namespace \
    { \
        typedef _NAMESPACE::_NAME ThisType; \
        VariantTypeInfo g_variantTypeInfo_##_NAMESPACE##_##_NAME[] = {

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) { #_NAME, ThisType::c_index_##_NAME },

#define VARIANT_END() \
        }; \
    };
