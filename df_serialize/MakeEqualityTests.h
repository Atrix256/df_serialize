// This makes member wise equality testing

#pragma once

#include "_common.h"

#define ENUM_BEGIN(_NAMESPACE, _NAME)

#define ENUM_ITEM(_NAME, _DESCRIPTION)

#define ENUM_END()

#define SCHEMA_BEGIN(_NAMESPACE, _NAME) \
    bool operator == (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B); \
    bool operator != (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B) \
    { \
        return !(A==B); \
    } \
    bool operator == (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B) \
    {

#define SCHEMA_INHERIT_BEGIN(_NAMESPACE, _NAME, _BASE) \
    bool operator == (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B); \
    bool operator != (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B) \
    { \
        return !(A==B); \
    } \
    bool operator == (const _NAMESPACE::_NAME& A, const _NAMESPACE::_NAME& B) \
    { \
        if (*(const _BASE*)&A != *(const _BASE*)&B) \
            return false;

#define SCHEMA_FIELD(_TYPE, _NAME, _DEFAULT, _DESCRIPTION) \
        if (A._NAME != B._NAME) \
            return false;

#define SCHEMA_ARRAY(_TYPE, _NAME, _DESCRIPTION) \
        if (A._NAME.size() != B._NAME.size()) \
            return false; \
        for (size_t index = 0; index < A._NAME.size(); ++index) \
        { \
            if (A._NAME[index] != B._NAME[index]) \
                return false; \
        }

#define SCHEMA_END() \
        return true; \
    }
