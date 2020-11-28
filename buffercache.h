#ifndef BUFFERCACHE_H
#define BUFFERCACHE_H

#include <unistd.h>
#include <iostream>
#include <mutex>

using namespace std;

#define CACHE_SIZE 50
#define BUCKET_COUNT 5

struct CacheBlock
{
    int number = -1;
    char *data = nullptr;
    bool isModified = false;
};

class BufferCache
{
public:
    BufferCache();

    void blockRead(char *x, int blockNumber);
    void blockWrite(char *x, int blockNumber);

private:
    void diskBlockRead(char *x, int blockNumber);
    void diskBlockWrite(char *x, int blockNumber);
    int bucketBoundaries(int &begin, int &end, const int &blockNumber);
    void printCache();

    CacheBlock m_cache[CACHE_SIZE];
    int m_evictIndex;
    mutex m_bucketMutex[BUCKET_COUNT];
};

#endif // BUFFERCACHE_H
