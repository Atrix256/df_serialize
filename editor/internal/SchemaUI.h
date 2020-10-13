// This makes imgui UI for the types

#pragma once

#include "../df_serialize/_common.h"

// Enums 

#define ENUM_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{

#define ENUM_ITEM(_NAME, _DESCRIPTION)

#define ENUM_END() \
    }

// Structs

#define STRUCT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{

#define STRUCT_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        ShowUI(*(_BASE*)&value); \

#define STRUCT_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
		ShowUI(value._NAME);

// No serialize means no editor reflection
#define STRUCT_FIELD_NO_SERIALIZE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define STRUCT_DYNAMIC_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        for (size_t index = 0; index < TDYNAMICARRAY_SIZE(value._NAME); ++index) \
            ShowUI(value._NAME[index]);

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
        for (size_t index = 0; index < _SIZE; ++index) \
            ShowUI(value._NAME[index]);

#define STRUCT_END() \
	}

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
		typedef _NAMESPACE::_NAME ThisType;

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._index == ThisType::c_index_##_NAME) \
            ShowUI(value._NAME);

#define VARIANT_END() \
	}

// TODO: enums! need to drop down w/ their items in them
// TODO: built in types!

// Built in types

void ShowUI(uint8_t& value)
{
    int ijkl = 0;
}

void ShowUI(uint16_t& value)
{
    int ijkl = 0;
}

void ShowUI(uint32_t& value)
{
    int ijkl = 0;
}

void ShowUI(uint64_t& value)
{
    int ijkl = 0;
}

void ShowUI(int8_t& value)
{
    int ijkl = 0;
}

void ShowUI(int16_t& value)
{
    int ijkl = 0;
}

void ShowUI(int32_t& value)
{
    int ijkl = 0;
}

void ShowUI(int64_t& value)
{
    int ijkl = 0;
}

void ShowUI(float& value)
{
    int ijkl = 0;
}

void ShowUI(bool& value)
{
    int ijkl = 0;
}

void ShowUI(std::string& value)
{
    int ijkl = 0;
}
