#ifndef STACK_H
#define STACK_H

#include "vector"
using std::byte;
using std::vector;

int bytesToInt (vector<vector<byte>> bytes);

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
    int bytesToInt (vector<byte> bytes);
    //int bytesToInt (vector<std::byte, allocator<std::byte>> bytes);

    int stackPointer = -1;
    int stackSize = 0;
    vector<vector<byte>> stackStorage = {};
    // Link: -1 - Not Link; 0 - Link to stack; 1 - Link to heap
    vector<int> stackLinker = {};
};

#endif // STACK_H
