#if __has_include("df_serialize_editor_config.h")

#include "df_serialize_editor_config.h"

#elif __has_include("../df_serialize_editor_config.h")

#include "../df_serialize_editor_config.h"

#else

// include your schema(s) and any headers they need for their types
#include <string>
#include <array>
#include <vector>
#include "../test/schemas/schemas.h"

// Set the root document type
#define RootDocumentType Lifeforms::Root

#endif