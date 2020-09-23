# df_serialize

**Demofox Serialization Library**

Minimal header only C++ library that allows you to define data schemas which then can be read or written in JSON or binary.  Nested structures, arrays, and struct inheritance are supported.

The test project shows how to use the library.

Schemas are defined in header files using C++ macros, like the below.

```c++
SCHEMA_BEGIN(Lifeforms, Plant)
    SCHEMA_FIELD(std::string, name, "", "The name of the plant.")
    SCHEMA_FIELD(std::string, description, "", "A description of the plant.")
    SCHEMA_FIELD(float, edibleMatter, 1.0f, "The number of kilograms of edible matter on the plant.")
    SCHEMA_FIELD(bool, poisonous, false, "Whether the plant is poisonous")
SCHEMA_END()
```

You define schemas in header files.  Multiple schemas can exist per header file, and you can have multiple header files with schemas in them.

Those schemas are then expanded into definitions of types and serialization code by including specific header files from this library.

If the schema above was the contents of a "schemas.h" file, you could make a file "types.h" and put the below in it.

```c++
#pragma once
#include "df_serialize/MakeTypes.h"
#include "schemas.h"
```

"MakeTypes.h" will turn the schemas into the types they define, as if the types were written out manually in this file. That means you can include
the above "types.h" file in any .h or .cpp that wants those types defined.

Other df_serialize headers do other tasks.  See the "Expanding Schemas" section below for more information.

After expanding your schemas, you can use the types as if you wrote them out by hand.

```c++
Lifeforms::Plant plant;
plant.name = "Hector";
plant.description = "Despite his sedentary nature, Hector is not one to be trifled with";
plant.edibleMatter = 9001.0f;
plant.poisonous = true;
```

Serialization is done via simple function calls

```c++
// Read JSON file
Lifeforms::Plant plant;
if (!ReadFromJSON(plant, "plant.json"))
{
    printf("Could not read plant.json!!\n");
    return false;
}

// Write JSON file
Lifeforms::Plant plant;
if (!WriteToJSON(plant, "plant.json"))
{
    printf("Could not write plant.json!!\n");
    return false;
}

// Read binary file
Lifeforms::Plant plant;
if (!ReadFromBinary(plant, "plant.dat"))
{
    printf("Could not read plant.dat!!\n");
    return false;
}

// Write binary file
Lifeforms::Plant plant;
if (!WriteToBinary(plant, "plant.dat"))
{
    printf("Could not write plant.dat!!\n");
    return false;
}
```

## Schema Definitions

**`SCHEMA_BEGIN(NameSpace, Name)`**

This makes a struct named "Name" in the namespace "Namespace".
The example makes a struct named LifeForms::Plant

**`SCHEMA_INHERIT_BEGIN(NameSpace, Name, Base)`**

Same as SCHEMA_BEGIN but makes the struct derive from Base.

**`SCHEMA_FIELD(Type, Name, Default, Description)`**

This adds a field to the struct of type "Type" with the name "Name".
The field has a default value of "Default" and a description is available in reflected data named "Description".
The first field in the example names a "std::string name" in the struct.
Note that the type can be either other schema defined types (they need to be defined above this schema) or
they can be types defined outside the schema: structs or PODs like ints and such.

**`SCHEMA_ARRAY(Type, Name, Description)`**

This defines a field as an array of another type.
Note that the type can be either other schema defined types (they need to be defined above this schema) or
they can be types defined outside the schema: structs or PODs like ints and such.
When using arrays in schemas, they use a templated type TDYNAMICARRAY for the dynamic array.
By default it defines this as std::vector, but you can set this define to another type if you wish. For instance
even though std::vector is the default, you could explicitly set it to that like this:

```c++
#define TDYNAMICARRAY std::vector
```

**`SCHEMA_END()`**

This specifies the end of the schema definition.

**`ENUM_BEGIN(Namespace, Name)`**

Defines an enum named "Name" in the namespace "Namespace"

**`ENUM_ITEM(Name, Description)`**

Defines an enum value

**`ENUM_END()`**

The end of an enum definition

**`VARIANT_BEGIN(Namespace, Name)`**

This declares a variant named "Name" in the namespace "Namespace".  A variant is an object that can be one of multiple types
where you specify for the variant what types it can be.  It's also possible for it to be no type, so a variant with one
type in it is the same conceptually as a nullable, optional or maybe.  A variant has a "_type" field to tell you which type it is.

**`VARIANT_TYPE(Type, Name, Default, Description)`**

This adds a possible type to the variant of type "Type" with the name "Name".
The type has a default value of "Default" and a description is available in reflected data named "Description".
The type can be either other schema defined types (they need to be defined above this schema) or
they can be types defined outside the schema: structs or PODs like ints and such.

**`VARIANT_END()`**

This specifies the end of the variant definition.

## Expanding Schemas

The header files beginning with underscores are for internal use only. The header files without underscores are meant
to be used by users of the library, as needed.

**`MakeTypes.h`**

This expands the schemas into the types defined. You include this file before the schemas.

Every enum, schema and variant also gets a uint32_t type id of the form NAMESPACE::c_type_NAME which is a compile
time hash of the string "NAMESPACE::TYPE", so can be used as case labels in switch statements and similar.  These
type ids are useful for working with variants, which have a "_type" member to tell you which type it is.

**`MakeHTMLHeader.h` & `MakeHTMLFooter.h`**

These make a function `bool WriteHTML(const char* fileName)` which writes the details of all schemas to an HTML
file. This shows how you could generate documentation or reflect schemas for things other than serialization.
The Header.h should be included before the schemas and Footer.h should be included after the schemas.

**`MakeJSONReadHeader.h` & `MakeJSONReadFooter.h` & `MakeJSONWriteHeader.h` & `MakeJSONWriteFooter.h`**

These expands the schemas into `ReadFromJSON` and `WriteToJSON`.  If you want error reporting, you can define a variadic
macro `MAKE_JSON_LOG(...)` to recieve log messages about failures.
The basic built in type serialization functions (like ints, strings, etc) are found at the bottom of the `Header.h`
file.  You can add more basic types by following the patterns there, either in that file, or in your own files.
The `Header.h` should be included before the schemas and `Footer.h` should be included after the schemas.

JSON Reading

All fields are optional.  Unrecognized fields are ignored. Enum values are read as strings.

JSON Writing

Only fields that are not the default value are written out. Enum values are written as strings. Trailing commas
are generated, but hopefully that is ok, as rapidjson allows you to specify that trailing commas are ok.  White
space (indentation) is written out.

**`MakeTypeToStringHeader.h` & `MakeTypeToStringFooter.h`**

This creates a `MakeTypeToString()` function which takes a type id in and returns the type string that was hashed to make that id.

This is used by json writing to write the type that a variant is.

**`MakeEqualityTest.h`**

This makes `==` and `!=` operators for all the types

**`MakeBinaryReadHeader.h` & `MakeBinaryReadFooter.h` & `MakeBinaryWriteHeader.h` & `MakeBinaryWriteFooter.h`**

This expands the schemas into `ReadFromBinary` and `WriteToBinary`.  If you want error reporting, you can define a variadic
macro `MAKE_BINARY_LOG(...)` to recieve log messages about failures.
The basic built in type serialization functions (like ints, strings, etc) are found at the bottom of the `Header.h`
file.  You can add more basic types by following the patterns there, either in that file, or in your own files.
The `Header.h` should be included before the schemas and `Footer.h` should be included after the schemas.

NOTE: A better binary serializer would read and write the whole structure in a single read or write operation
with pointer fixup after read (for the case of read) and pointer un-fixup before write.  It may also
not store enums as strings, but then would have to deal with enum re-ordering versioning. Calling this good enough
for now, but I would definitely accept a more bare metal binary serializer if someone feels like making one.

Binary Reading

A single `fread()` is done to get the binary file into memory, then each value is pulled out from that memory
buffer individually, and recursively.  Enum values are read as null terminated strings. `std::string` is
read as null terminated strings.

Binary Writing

A memory buffer is built up by visiting all data items recursively, and having each basic type grow a `std::vector`
and put their binary representation into the buffer.  When this is done, that binary buffer is written to disk
in a single `fwrite()`. Enum values are written as null terminated strings. `std::string` is written as null
terminated strings. All fields are written.
