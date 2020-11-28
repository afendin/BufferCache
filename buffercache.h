/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
