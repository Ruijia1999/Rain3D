#pragma once
//
//  LeakDetector.hpp
//  LeakDetector
//
#ifndef RAIN_LEAK_DETECTOR
#define RAIN_LEAK_DETECTOR

void* operator new(size_t _size, char* _file, unsigned int _line);
void* operator new[](size_t _size, char* _file, unsigned int _line);

#ifndef NEW_OVERLOAD_IMPLEMENTATION
#define new    new(__FILE__, __LINE__)
#endif

class LeakDetector
{
public:
    static unsigned int callCount;
    LeakDetector() noexcept {
        ++callCount;
    }
    ~LeakDetector() noexcept {
        if (--callCount == 0)
            LeakDetect();
    }
private:
    static unsigned int LeakDetect() noexcept;
};
static LeakDetector _exit_counter;
#endif