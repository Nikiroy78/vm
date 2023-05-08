#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include "vector"
#include "stack.h"

using std::vector;
using std::byte;

class CommandExecutor
{
public:
    CommandExecutor(vector<byte> bytes, Stack globalStack);
    Stack globalStack;
    Stack insiderStack;
    bool isCommandDefined;
    bool isEnded;
    vector<vector<byte>> commands;
    vector<byte> bytes;
    void execute ();
private:
    bool isCorrectionSyntax ();
};

#endif // COMMANDEXECUTOR_H
