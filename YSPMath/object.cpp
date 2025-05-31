/*
    Created by YSP on 2025-05-05.
*/
#include "object.h"
namespace ysp {
    //打印类
    std::string Object::ToString() const {
        std::stringstream ss;
        ss << static_cast<const void*>(this);
        return ss.str();
    }

    bool Object::Equals(const Object &other) const {
        return this == &other;
    }
}
