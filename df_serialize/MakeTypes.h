// This creates structs and enums

#include "_common.h"
#include <stdint.h>

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) namespace _NAMESPACE {  enum class _NAME : int32_t {

#define ENUM_ITEM(_NAME, _DESCRIPTION) _NAME,

#define ENUM_END() }; };

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) namespace _NAMESPACE {  struct _NAME {

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) namespace _NAMESPACE {  struct _NAME : public _BASE {

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
    _TYPE _NAME = _DEFAULT;

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
    TDYNAMICARRAY<_TYPE> _NAME;

#define SCHEMA_END() }; };
