//
// Created by YSP on 25-5-5.
//
#pragma once
#include <sstream>
#include <string>
namespace ysp {
    class Object {
    public:
        Object() = default;
        virtual bool Equal(const Object& other) const;
        virtual std::string Print() const ;
    };
}



