#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "vector"
#include "stack.h"

using std::byte;
using std::vector;

class Subprog {
public:
    Subprog                            (vector<byte> id, byte mode, vector<vector<byte>> commandBytes);
    vector<byte>         id;
    byte                 mode;
    vector<vector<byte>> commandBytes;
    Stack                stack;
    void                 execute       ();
};

class VirtualMachine {
public:
    VirtualMachine                      (bool isDebugModeOn);
    void                 bindStopPoints (int* stopPoints);
    void                 includeVoid    (Subprog subprog);
    vector<vector<byte>> parseCommands  (byte* allByteCode, int byteCodeLength);

    vector<Subprog>      subprogs;
    // Registers
    // [16-bit (4 bytes)]
    // General
    byte EAX[4];
    byte EBX[4];
    byte ECX[4];
    byte EDX[4];
    // [32-bit (8 bytes)]
    // General
    byte AX[8];
    byte BX[8];
    byte CX[8];
    byte DX[8];
    // [64-bit (16 bytes)]
    // General
    byte RAX[16];
    byte RBX[16];
    byte RCX[16];
    byte RDX[16];
    // [128-bit (32 bytes)]
    byte BAX[32];
    byte BBX[32];
    byte BCX[32];
    byte BDX[32];
private:
    bool isDebugging;
    void debugModeOutput ();
};

#endif // VIRTUALMACHINE_H
