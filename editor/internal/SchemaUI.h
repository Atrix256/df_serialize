// This makes imgui UI for the types

#pragma once

#include "../df_serialize/_common.h"

// Enums 

#define ENUM_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	bool ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        typedef _NAMESPACE::_NAME ThisType; \
        ImGui::NextColumn(); \
        int v = (int)value; \
        bool ret = ImGui::Combo("", &v,

#define ENUM_ITEM(_NAME, _DESCRIPTION) \
        #_NAME "\0"

#define ENUM_END() \
        ); \
        if (ret) \
            value = (ThisType)v; \
        ImGui::NextColumn(); \
        return ret; \
    }

// Structs

#define STRUCT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	bool ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        ImGui::NextColumn(); \
        ImGui::NextColumn(); \
        ImGui::Indent(); \
        using namespace _NAMESPACE; \
        ImGui::PushID(#_NAME); \
        bool ret = false;

#define STRUCT_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE, _DESCRIPTION) \
	bool ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        ImGui::NextColumn(); \
        ImGui::NextColumn(); \
        ImGui::Indent(); \
        using namespace _NAMESPACE; \
        ImGui::PushID(#_NAME); \
        bool ret = ShowUI(*(_BASE*)&value); \

#define STRUCT_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        ImGui::PushID(#_NAME); \
        ImGui::Text(#_NAME); \
		ret |= ShowUI(value._NAME); \
        ImGui::PopID(); \

// No serialize means no editor reflection
#define STRUCT_FIELD_NO_SERIALIZE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION)

#define STRUCT_DYNAMIC_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        ImGui::Separator(); \
        if (ImGui::TreeNode(#_NAME)) \
        { \
            int deleteIndex = -1; \
            for (size_t index = 0; index < TDYNAMICARRAY_SIZE(value._NAME); ++index) \
            { \
                ImGui::Separator(); \
                ImGui::NextColumn(); \
                ImGui::NextColumn(); \
                ImGui::PushID((int)index); \
                ret |= ShowUI(value._NAME[index]); \
                if (ImGui::Button("Delete")) \
                    deleteIndex = (int)index; \
                ImGui::PopID(); \
            } \
            ImGui::Separator(); \
            if (ImGui::Button("Add")) \
            { \
                ret = true; \
                value._NAME.push_back(_TYPE{}); \
            } \
            ImGui::TreePop(); \
            if (deleteIndex != -1) \
            { \
                ret = true; \
                value._NAME.erase(value._NAME.begin() + deleteIndex); \
            } \
        } \
        else \
        { \
            ImGui::NextColumn(); \
            ImGui::NextColumn(); \
        }

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
        if (ImGui::TreeNode(#_NAME "[" #_SIZE "]")) \
        { \
            for (size_t index = 0; index < _SIZE; ++index) \
            { \
                ImGui::PushID((int)index); \
                ret |= ShowUI(value._NAME[index]); \
                ImGui::PopID(); \
            } \
            ImGui::TreePop(); \
        } \
        else \
        { \
            ImGui::NextColumn(); \
            ImGui::NextColumn(); \
        }

#define STRUCT_END() \
        ImGui::PopID(); \
        ImGui::Unindent(); \
        return ret; \
	}

// Variants

#define VARIANT_BEGIN(_NAMESPACE, _NAME, _DESCRIPTION) \
	bool ShowUI(_NAMESPACE::_NAME& value) \
	{ \
        ImGui::NextColumn(); \
        ImGui::NextColumn(); \
        ImGui::Indent(); \
		typedef _NAMESPACE::_NAME ThisType; \
        ImGui::PushID(#_NAME); \
        int selectedIndex = -1; \
        bool ret = false; \
        const auto& typeInfo = g_variantTypeInfo_##_NAMESPACE##_##_NAME; \
        for (int i = 0; i < sizeof(typeInfo) / sizeof(typeInfo[0]); ++i) \
        { \
            if(value._index == typeInfo[i]._index) \
                selectedIndex = i; \
        } \
        ImGui::PushID("_type"); \
        ImGui::Text("Object Type"); \
        ImGui::SameLine(); \
        ImGui::NextColumn(); \
        if (ImGui::BeginCombo("", selectedIndex < sizeof(typeInfo) / sizeof(typeInfo[0]) ? typeInfo[selectedIndex].name.c_str() : "", 0)) \
        { \
            for (int n = 0; n < sizeof(typeInfo) / sizeof(typeInfo[0]); ++n) \
            { \
                const bool selected = (selectedIndex == n); \
                if (ImGui::Selectable(typeInfo[n].name.c_str(), selected)) \
                { \
                    value._index = typeInfo[n]._index; \
                    ret = true; \
                } \
                /* Set the initial focus when opening the combo (scrolling + keyboard navigation focus) */ \
                if (selected) \
                    ImGui::SetItemDefaultFocus(); \
            } \
            ImGui::EndCombo(); \
        } \
        ImGui::NextColumn(); \
        ImGui::PopID();

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (value._index == ThisType::c_index_##_NAME) \
            ret |= ShowUI(value._NAME);

#define VARIANT_END() \
        ImGui::PopID(); \
        ImGui::Unindent(); \
        return ret; \
	}

// Built in types

bool ShowUI(uint8_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (uint8_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(uint16_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (uint16_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(uint32_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (uint32_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(uint64_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (uint64_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(int8_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (int8_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(int16_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (int16_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(int32_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (int32_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(int64_t& value)
{
    bool ret = false;
    ImGui::NextColumn();
    int v = (int)value;
    if (ImGui::InputInt("", &v))
    {
        value = (int64_t)v;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(float& value)
{
    ImGui::NextColumn();
    bool ret = ImGui::InputFloat("", &value);
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(bool& value)
{
    ImGui::NextColumn();
    bool ret = ImGui::Checkbox("", &value);
    ImGui::NextColumn();
    return ret;
}

bool ShowUI(std::string& value)
{
    bool ret = false;
    ImGui::NextColumn();

    char buffer[1024];
    strcpy_s(buffer, value.c_str());
    if (ImGui::InputText("", buffer, 1024))
    {
        value = buffer;
        ret = true;
    }
    ImGui::NextColumn();
    return ret;
}
