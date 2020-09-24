#include "Config.h"

// Undefine any macros that may be defined, so they can safely be defined. Lazy define cleanup.

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

#ifdef SCHEMA_DYNAMIC_ARRAY
#undef SCHEMA_DYNAMIC_ARRAY
#endif

#ifdef SCHEMA_STATIC_ARRAY
#undef SCHEMA_STATIC_ARRAY
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

// Needed to be able to provide defaults for fixed sized arrays
#ifndef COMMA
#define COMMA ,
#endif

#ifndef STRIPCOMMASTRING
#define STRIPCOMMASTRING(x) #x
#endif
