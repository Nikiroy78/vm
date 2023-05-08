#ifndef COMMAND_H
#define COMMAND_H

#include "stack.h"
#include "vector"
#include <iostream>
using std::vector;
using std::byte;

/*class Command
{
public:
    // Command();
    virtual ~Command () {
        delete this->virtualStack;
    }
    virtual bool checkCorrectSyntax ();
    virtual void exec               ();
private:
    vector<byte> bytes;
    Stack* virtualStack;
}; */

class VOID_HEADER {
public:
    // From all command
    VOID_HEADER (vector<byte> bytes, Stack globalStack);
    virtual bool checkCorrectSyntax ();
    virtual void exec               ();
    Stack globalStack;
    Stack localStack;
private:
    // From all command
    vector<byte> bytes;
};

class VOID_ENDER {
public:
    // From all command
    VOID_ENDER (vector<byte> bytes, Stack globalStack);
    virtual bool checkCorrectSyntax ();
    virtual void exec               ();
    Stack globalStack;
    Stack localStack;
private:
    // From all command
    vector<byte> bytes;
};

class STACK_PUSH {
public:
    // From all command
    STACK_PUSH (vector<byte> bytes, Stack globalStack);
    virtual bool checkCorrectSyntax ();
    virtual void exec               ();
    Stack globalStack;
    Stack localStack;
private:
    // From all comand
    vector<byte> bytes;
};

class STDOUT {
public:
    // From all command
    STDOUT (vector<byte> bytes, Stack globalStack);
    virtual bool checkCorrectSyntax ();
    virtual void exec               ();
    Stack globalStack;
    Stack localStack;
private:
    // From all comand
    vector<byte> bytes;
    byte mode;
};

#endif // COMMAND_H
