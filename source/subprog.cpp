#include "vm-src.h"
#include "command-exec.h"
#include "stack.h"

Subprog::Subprog (vector<byte> id, byte mode, vector<vector<byte>> commandBytes) {
    this->id = id;
    this->mode = mode;
    this->commandBytes = commandBytes;
    //this->stack;
}

void Subprog::execute () {
    for (vector<byte> com : commandBytes) {
        CommandExecutor execCur(com, this->stack);
        execCur.execute();
        while (execCur.insiderStack.size() != 0) {
            vector<byte> bytes = execCur.insiderStack.get();
            this->stack.push(bytes);
            execCur.insiderStack.rm();
        }
    }
}
