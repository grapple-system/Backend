#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include <cstdint>
#include "../utilities/globalDefinitions.hpp"

class LRUCache
{
    list<pair<string,int8_t>> dl;
    std::unordered_map<string,decltype(dl.begin())> hm;
    int csize;
public:
    LRUCache(int);
    int8_t get(string);
    void put(string, int8_t);
};

#endif
