/*
    Created by YSP on 2025-05-05.
*/
#pragma once
#include <sstream>
#include <string>
namespace ysp {
    class Object {
    public:
        Object() = default;
        virtual bool Equals(const Object& other) const;
        virtual std::string ToString() const ;
    };
}



