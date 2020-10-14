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
        { \
            char buffer[256]; \
            sprintf_s(buffer, #_NAME "[%i]", (int)TDYNAMICARRAY_SIZE(value._NAME)); \
            if (ImGui::TreeNode(buffer)) \
            { \
                int deleteIndex = -1; \
                for (size_t index = 0; index < TDYNAMICARRAY_SIZE(value._NAME); ++index) \
                { \
                    ImGui::PushID((int)index); \
                    ShowUI(value._NAME[index]); \
                    ImGui::PopID(); \
                    if (ImGui::Button("Delete")) \
                        deleteIndex = (int)index; \
                } \
                ImGui::TreePop(); \
                if (ImGui::Button("Add")) \
                    value._NAME.push_back(_TYPE{}); \
                if (deleteIndex != -1) \
                    value._NAME.erase(value._NAME.begin() + deleteIndex); \
            } \
        }

#define STRUCT_STATIC_ARRAY(_TYPE, _NAME, _SIZE, _DEFAULT, _DESCRIPTION) \
        if (ImGui::TreeNode(#_NAME "[" #_SIZE "]")) \
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
        struct TypeInfo \
        { \
            std::string name; \
            uint32_t _index; \
        }; \
        std::vector<TypeInfo> typesInfo; \
        int selectedIndex = -1; \
        int currentIndex = -1;

#define VARIANT_TYPE(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        currentIndex++; \
        typesInfo.push_back({#_NAME, ThisType::c_index_##_NAME}); \
        if (value._index == ThisType::c_index_##_NAME) \
        { \
            selectedIndex = currentIndex; \
            if (ImGui::TreeNode(#_NAME)) \
            { \
                ShowUI(value._NAME); \
                ImGui::TreePop(); \
            } \
        }

#define VARIANT_END() \
        ImGui::PushID("_type"); \
        ImGui::Text("Type"); \
        ImGui::SameLine(); \
        if (ImGui::BeginCombo("", selectedIndex < typesInfo.size() ? typesInfo[selectedIndex].name.c_str() : "", 0)) \
        { \
            for (int n = 0; n < (int)typesInfo.size(); ++n) \
            { \
                const bool selected = (selectedIndex == n); \
                if (ImGui::Selectable(typesInfo[n].name.c_str(), selected)) \
                    value._index = typesInfo[n]._index; \
                /* Set the initial focus when opening the combo (scrolling + keyboard navigation focus) */ \
                if (selected) \
                    ImGui::SetItemDefaultFocus(); \
            } \
            ImGui::EndCombo(); \
        } \
        ImGui::PopID(); \
        ImGui::PopID(); \
	}

// Built in types

void ShowUI(uint8_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (uint8_t)v;
}

void ShowUI(uint16_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (uint16_t)v;
}

void ShowUI(uint32_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (uint32_t)v;
}

void ShowUI(uint64_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (uint64_t)v;
}

void ShowUI(int8_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (int8_t)v;
}

void ShowUI(int16_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (int16_t)v;
}

void ShowUI(int32_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (int32_t)v;
}

void ShowUI(int64_t& value)
{
    int v = (int)value;
    if (ImGui::InputInt("", &v))
        value = (int64_t)v;
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
