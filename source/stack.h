#ifndef STACK_H
#define STACK_H

#include "vector"
using std::byte;
using std::vector;

class Stack {
public:
    Stack();
    ~Stack();
    /* Stack commands */
    void push (vector<byte> data);
    void rm   (byte removeMode = byte(0x00));
    void ed   ();
    void repl ();
    vector<byte> get ();
    int size ();
private:
    int stackPointer = -1;
    int stackSize = 0;
    vector<vector<byte>> stackStorage = {};
};

#endif // STACK_H
