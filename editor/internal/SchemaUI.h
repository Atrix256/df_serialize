// This makes imgui UI for the types

#pragma once

#include "../df_serialize/_common.h"

// Enums 

#define ENUM_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        typedef _NAMESPACE::_NAME ThisType; \
        int v = (int)value; \
        if(ImGui::Combo("", &v,

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
        #_NAME "\0"

#define ENUM_END() \
        )) \
            value = (ThisType)v; \
    }

// Structs

#define STRUCT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        using namespace _NAMESPACE; \
        ImGui::PushID(#_NAME); \

#define STRUCT_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION) \
	void ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        using namespace _NAMESPACE; \
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
            for (size_t index = 0; index < TDYNAMICARRAY_SIZE(value._NAME); ++index) \
            { \
                ImGui::PushID((int)index); \
                ShowUI(value._NAME[index]); \
                ImGui::PopID(); \
            } \
            ImGui::TreePop(); \
            if (ImGui::Button("Add")) \
                value._NAME.push_back(_TYPE{}); \
        }

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
        if (ImGui::TreeNode(#_NAME)) \
        { \
            for (size_t index = 0; index < _SIZE; ++index) \
            { \
                ImGui::PushID((int)index); \
                ShowUI(value._NAME[index]); \
                ImGui::PopID(); \
            } \
            ImGui::TreePop(); \
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
            if (ImGui::TreeNode(#_NAME)) \
            { \
                ShowUI(value._NAME); \
                ImGui::TreePop(); \
            } \
        }

#define VARIANT_END() \
        ImGui::PopID(); \
	}

// TODO: add delete button for dynamic arrays
// TODO: be able to change / set variant type somehow (button?)
// TODO: does all the editing work? liter min/max didn't seem to change!

// Built in types

void ShowUI(uint8_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (uint8_t)value;
}

void ShowUI(uint16_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (uint16_t)value;
}

void ShowUI(uint32_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (uint32_t)value;
}

void ShowUI(uint64_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (uint64_t)value;
}

void ShowUI(int8_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (int8_t)value;
}

void ShowUI(int16_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (int16_t)value;
}

void ShowUI(int32_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (int32_t)value;
}

void ShowUI(int64_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        v = (int64_t)value;
}

void ShowUI(float& value)
{
    ImGui::InputFloat("", &value);
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
