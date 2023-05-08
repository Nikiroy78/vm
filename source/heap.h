#ifndef HEAP_H
#define HEAP_H

#include "byteType.h"


class Heap {
public:
    Heap       ();
    /* Heap commands */
    void init  ();
    void alloc ();
    void push  ();
};

#endif // HEAP_H
