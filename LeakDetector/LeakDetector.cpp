#include "LeakDetector.h"
#include <iostream>
#include <cstring>

// ????? _DEBUG_NEW_ ?, 
// ???????????????? new ???, 
// ????????
#define __NEW_OVERLOAD_IMPLEMENTATION__


struct MemoryList {
    MemoryList* next;
    MemoryList* prev;
    size_t     size;   
    bool    isArray;   
    char* file;     
    unsigned int line;
};

static unsigned long memoryAllocated = 0;    
static MemoryList root = { nullptr,nullptr,0,false,nullptr,0 };

unsigned int LeakDetector::callCount = 0;

//
//  LeakDetector.cpp
//  LeakDetector
//
void* AllocateMemory(size_t size, bool array, char* file, unsigned line) {

    size_t newSize = sizeof(MemoryList) + size;

    // ?? new ???????????? malloc ?????
    MemoryList* newElem = (MemoryList*)malloc(newSize);

    newElem->next = root.next;
    newElem->prev = &root;
    newElem->size = size;
    newElem->isArray = array;
    newElem->file = NULL;

    // ?????????????
    if (file) {
        newElem->file = (char*)malloc(strlen(file) + 1);
        strcpy(newElem->file, file);
    }
    // ????
    newElem->line = line;

    // ????
    root.next->prev = newElem;
    root.next = newElem;

    // ??????????
    memoryAllocated += size;

    // ????????? newElem ??? char* ????????? +1 ????? byte
    return (char*)newElem + sizeof(MemoryList);
}