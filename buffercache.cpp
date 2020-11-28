#include "buffercache.h"

const int blocksPerBucket = CACHE_SIZE / BUCKET_COUNT;

BufferCache::BufferCache()
{
    m_evictIndex = 0;
}

void BufferCache::blockRead(char *x, int blockNumber)
{
    int i, count;
    int bucketIndex = bucketBoundaries(i, count, blockNumber);

    // Lock corresponding bucket before accessing it
    lock_guard<mutex> lock(m_bucketMutex[bucketIndex]);

    for (; i < count; ++i) {
        // Loop through cache and find block with corresponding number
        if (m_cache[i].number == blockNumber) {
            x = m_cache[i].data;
            return;
        }
    }

    // If we didn't find block, fetch from disk instead of evicted entry

    // We use simplest eviction algorithm that selects next entry circularly
    m_evictIndex = (m_evictIndex + 1) % CACHE_SIZE;
    CacheBlock *evictedBlock = &m_cache[m_evictIndex];

    // If block is modified, we first have to write it to disk
    if (evictedBlock->isModified) {
        diskBlockWrite(evictedBlock->data, evictedBlock->number);
    }

    // Then we just read needed block from disk and store it in the evicted entry
    diskBlockRead(evictedBlock->data, blockNumber);
    evictedBlock->number = blockNumber;
    evictedBlock->isModified = false;
}

void BufferCache::blockWrite(char *x, int blockNumber)
{
    int i, count;
    int bucketIndex = bucketBoundaries(i, count, blockNumber);

    lock_guard<mutex> lock(m_bucketMutex[bucketIndex]);

    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (m_cache[i].number == blockNumber) {
            m_cache[i].data = x;
            m_cache[i].isModified = true;
            return;
        }
    }

    m_evictIndex = (m_evictIndex + 1) % CACHE_SIZE;
    CacheBlock *evictedBlock = &m_cache[m_evictIndex];

    if (evictedBlock->isModified) {
        diskBlockWrite(evictedBlock->data, evictedBlock->number);
    }

    evictedBlock->number = blockNumber;
    evictedBlock->data = x;
    evictedBlock->isModified = true;
}

void BufferCache::diskBlockRead(char *x, int blockNumber)
{
    sleep(1); // Simulate block read
}

void BufferCache::diskBlockWrite(char *x, int blockNumber)
{
    sleep(1); // Simulate block write
}

/**
 * Returns bucket index and sets begin and end indices
 */
int BufferCache::bucketBoundaries(int &begin, int &end, const int &blockNumber)
{
    // First we're hashing block number to decide
    // wich bucket might own it
    int bucketIndex = blockNumber % BUCKET_COUNT;

    // Then we calculate index of first element of that bucket
    begin = bucketIndex * blocksPerBucket;

    // and index of last element of that bucket
    end = begin + blocksPerBucket;

    return bucketIndex;
}

void BufferCache::printCache()
{
    for (int i = 0; i < CACHE_SIZE; ++i)
        cout << "[" << m_cache[i].number << "]";

    cout << endl;
}
