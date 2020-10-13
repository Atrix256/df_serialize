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
	{ \
        ImGui::PushID(#_NAME); \

#define STRUCT_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        ImGui::PushID(#_NAME); \
        ShowUI(*(_BASE*)&value); \

#define STRUCT_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        ImGui::PushID(#_NAME); \
        ImGui::Text(#_NAME); \
        ImGui::SameLine(); \
		ShowUI(value._NAME); \
        ImGui::PopID(); \

// No serialize means no editor reflection
#define STRUCT_FIELD_NO_SERIALIZE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define STRUCT_DYNAMIC_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        if (ImGui::TreeNode(#_NAME)) \
        { \
            ImGui::PushID(#_NAME); \
            for (size_t index = 0; index < TDYNAMICARRAY_SIZE(value._NAME); ++index) \
                ShowUI(value._NAME[index]); \
            ImGui::TreePop(); \
            ImGui::PopID(); \
        }

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
        if (ImGui::TreeNode(#_NAME)) \
        { \
            ImGui::PushID(#_NAME); \
            for (size_t index = 0; index < _SIZE; ++index) \
                ShowUI(value._NAME[index]); \
            ImGui::TreePop(); \
            ImGui::PopID(); \
        }

#define STRUCT_END() \
        ImGui::PopID(); \
	}

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
		typedef _NAMESPACE::_NAME ThisType; \
        ImGui::PushID(#_NAME); \

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._index == ThisType::c_index_##_NAME) \
        { \
            ImGui::PushID(#_NAME); \
            ShowUI(value._NAME); \
            ImGui::PopID(); \
        }

#define VARIANT_END() \
        ImGui::PopID(); \
	}

// TODO: enums! need to drop down w/ their items in them. also push / pop id
// TODO: built in types!
// TODO: variants probably need to be clearer about their type. maybe have a tree control for that?

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
    ImGui::Checkbox("", &value);
}

void ShowUI(std::string& value)
{
    char buffer[1024];
    strcpy_s(buffer, value.c_str());
    if (ImGui::InputText("", buffer, 1024))
        value = buffer;
}
