#include <iostream>
#include <thread>

#include "buffercache.h"

using namespace std;


BufferCache bufferCache;
void testLoop();

int main()
{
    thread t1(testLoop);
    thread t2(testLoop);
    t1.join();
    t2.join();
    return 0;
}

void testLoop()
{
    for (int i = 0; i < 1000; ++i) {
        bufferCache.blockRead(nullptr, rand() % 60);
        bufferCache.blockWrite(nullptr, rand() % 60);
    }
}
