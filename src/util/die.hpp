#pragma once
#include <cstdio>

template<typename... S> 
void die(const S... str) {
    std::fprintf(stderr, str...);
    std::fprintf(stderr, "\n");
    std::abort();
}