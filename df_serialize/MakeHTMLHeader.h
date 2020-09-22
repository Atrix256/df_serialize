// This creates a function "bool WriteHTML(const char* fileName)" which will write the details
// of schemas to an html file.

#include "_common.h"
#include <stdio.h>
#include <sstream>

inline bool WriteHTML(const char* fileName)
{
    FILE* file = nullptr;
    fopen_s(&file, fileName, "w+b");
    if (!file)
        return false;

    std::stringstream enums, structs;

// Enums

#define ENUM_BEGIN(_NAMESPACE, _NAME) enums << \
    "<table>\n" \
    "<tr><th colspan=2>" #_NAMESPACE "::" #_NAME "</th></tr>\n" \
    ;

#define ENUM_ITEM(_NAME, _DESCRIPTION) enums << \
    "<tr><td>" #_NAME "</td><td>" _DESCRIPTION "</td></tr>\n" \
    ;

#define ENUM_END() enums << \
    "</table>\n" \
    "<br/>\n" \
    "\n" \
    ;

// Structs

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) structs << \
    "<table>\n" \
    "<tr><th colspan=3>" #_NAMESPACE "::" #_NAME "</th></tr>\n" \
    ;

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) structs << \
    "<table>\n" \
    "<tr><th colspan=3>" #_NAMESPACE "::" #_NAME " - Inherits from " #_BASE "</th></tr>\n" \
    ;

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) structs << \
    "<tr><td>" #_TYPE " " #_NAME "</td><td>" #_DEFAULT "</td><td>" _DESCRIPTION "</td></tr>\n" \
    ;

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) structs << \
    "<tr><td>" #_TYPE " " #_NAME "[]</td><td></td><td>" _DESCRIPTION "</td></tr>\n" \
    ;

#define SCHEMA_END() structs << \
    "</table>\n" \
    "<br/>\n" \
    "\n" \
    ;
