#include "lrucache.h"

LRUCache::LRUCache(int csize) { this->csize = csize; }

int8_t LRUCache::get(string key)
{
    auto it = hm.find(key);
    if(it == hm.end()) return -1;
    dl.splice(dl.begin(), dl, it->second);
    it->second = dl.begin();
    return it->second->second;
}

void LRUCache::put(string key, int8_t val)
{
    dl.push_front(std::make_pair(key,val));
    hm.insert(std::make_pair(key,dl.begin()));
    while(hm.size() > csize) {
        auto it_last = dl.end(); it_last--;
        hm.erase(it_last->first);
        dl.pop_back();
    }
}
