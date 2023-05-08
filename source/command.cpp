#include "command.h"

// 0x00 0x00 void_header
VOID_HEADER::VOID_HEADER (vector<byte> bytes, Stack globalStack) {
    this->bytes = bytes;
    this->globalStack = globalStack;
}

bool VOID_HEADER::checkCorrectSyntax () {
    int byteRequired = 7;
    for (byte commandByte : this->bytes) {
        byteRequired--;
        if (byteRequired == 0) {
            return true;
        }
    }
    return false;
}

void VOID_HEADER::exec () {}

// 0x00 0x01 void_ender
VOID_ENDER::VOID_ENDER (vector<byte> bytes, Stack globalStack) {
    this->bytes = bytes;
    this->globalStack = globalStack;
}

bool VOID_ENDER::checkCorrectSyntax () {
    int byteRequired = 6;
    for (byte commandByte : this->bytes) {
        byteRequired--;
        if (byteRequired == 0) {
            return true;
        }
    }
    return false;
}

void VOID_ENDER::exec () {}

// 0x01 0x01 stack_push
STACK_PUSH::STACK_PUSH (vector<byte> bytes, Stack globalStack) {
    this->bytes = bytes;
    this->globalStack = globalStack;
}

bool STACK_PUSH::checkCorrectSyntax () {
    int byteRequired = 3;
    int byteRegistered = 0;
    for (byte commandByte : this->bytes) {
        byteRequired--;
        byteRegistered++;
        if (byteRegistered == 3) {
            byteRequired += int(commandByte);
        }
        else if (byteRequired == 0) {
            return true;
        }
    }
    return false;
}

void STACK_PUSH::exec () {
    if (this->checkCorrectSyntax()) {
        //std::cout << "Add to stack: " << this->bytes.size() << " bytes " << "\n";
        this->localStack.push(this->bytes);
    }
}

// 0x04 0x00 stdout
STDOUT::STDOUT (vector<byte> bytes, Stack globalStack) {
    this->bytes = bytes;
    this->globalStack = globalStack;
    if (this->checkCorrectSyntax()) this->mode = bytes[2];
}

bool STDOUT::checkCorrectSyntax () {
    int byteRequired = 3;
    int byteRegistered = 0;
    for (byte commandByte : this->bytes) {
        byteRequired--;
        byteRegistered++;
        if (byteRequired == 0) {
            if (byteRegistered == 3) {
                switch (commandByte) {  // Getting mode
                    case byte (0x0E):   // Получить значение из вершины стэка
                        return true;
                    default:
                        std::cout << "Unknown read mode";
                        return false;
                        // (!) Вызвать ошибку: неизвестный режим чтения
                }
            }
        }
    }
    return false;
}

std::string getTextFromBytes (vector<byte> bytes) {
    std::string text = "";
    for (byte symbol : bytes) {
        text += char(symbol);
    }
    return text;
}

void STDOUT::exec () {
    vector<byte> stdoutData;
    switch (this->mode) {
        case byte(0x0E) : // Получить значение из вершины стэка
            stdoutData = this->globalStack.get();
            break;
    }
    //std::cout << int(this->mode) << "\n";
    std::cout << getTextFromBytes(stdoutData);
    //std::cout << ":" << getTextFromBytes(stdoutData);
}
