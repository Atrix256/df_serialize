// undefine anything schema macros that may be defined, so they can safely be defined

#ifdef SCHEMA_BEGIN
#undef SCHEMA_BEGIN
#endif

#ifdef SCHEMA_INHERIT_BEGIN
#undef SCHEMA_INHERIT_BEGIN
#endif

#ifdef SCHEMA_FIELD
#undef SCHEMA_FIELD
#endif

#ifdef SCHEMA_END
#undef SCHEMA_END
#endif

#ifdef SCHEMA_ARRAY
#undef SCHEMA_ARRAY
#endif

#ifdef ENUM_BEGIN
#undef ENUM_BEGIN
#endif

#ifdef ENUM_ITEM
#undef ENUM_ITEM
#endif

#ifdef ENUM_END
#undef ENUM_END
#endif

#ifdef VARIANT_BEGIN
#undef VARIANT_BEGIN
#endif

#ifdef VARIANT_TYPE
#undef VARIANT_TYPE
#endif

#ifdef VARIANT_END
#undef VARIANT_END
#endif

// By default, use a std::vector as the dynamic array type. You can define TDYNAMICARRAY
// to another templated dynamic array type if you wish.
#ifndef TDYNAMICARRAY
#define TDYNAMICARRAY std::vector
#endif
