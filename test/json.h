// Generates code to read & write data from json files and strings
// Code meant for use with rapidjson
// RapidJSON Website: https://rapidjson.org/
// RapidJSON Github:  https://github.com/Tencent/rapidjson/
#pragma once

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

// Reading
#include "../df_serialize/MakeJSONReadHeader.h"
#include "schemas/schemas.h"
#include "../df_serialize/MakeJSONReadFooter.h"

// Equality testing (used by json writing to not write default values)
#include "../df_serialize/MakeEqualityTests.h"
#include "schemas/schemas.h"

// TypeToString (used by json writing to write the name of types of variants)
#include "../df_serialize/MakeTypeToStringHeader.h"
#include "schemas/schemas.h"
#include "../df_serialize/MakeTypeToStringFooter.h"

// Writing
#include "../df_serialize/MakeJSONWriteHeader.h"
#include "schemas/schemas.h"
#include "../df_serialize/MakeJSONWriteFooter.h"