//
// Created by YSP on 25-5-5.
//

#include "object.h"
namespace ysp {
//打印类
std::string Object::Print() const {
    std::stringstream ss;
    ss << static_cast<const void*>(this);
    return ss.str();
}

bool Object::Equal(const Object &other) const {
    return this == &other;
}
}
