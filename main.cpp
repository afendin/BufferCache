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
