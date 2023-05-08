#include "stack.h"
#include <iostream>

Stack::Stack() {
    this->stackStorage.clear();
    this->stackPointer = -1;
}
Stack::~Stack () {
    //delete this->stackStorage;
}

vector<byte> Stack::get () {
    if (this->stackStorage.size() == 0) return {};
    else return this->stackStorage[this->stackPointer];
}

void Stack::push (vector<byte> data) {
    this->stackStorage.push_back(data);
    this->stackPointer = this->stackStorage.size() - 1;
    /*if (this->readMode) {
        // (!) Выдать ошибку: стек открыт только для чтения
    }
    else {
        //std::cout << "We add to stack: " << data.size() << " bytes\n";

    }*/
}

void Stack::rm (byte removeMode) {
    if (this->stackStorage.size() == 0) {
        if (removeMode == byte(0xFF)) {
            // (!) Выдать ошибку: стек пуст.
        }
    }
    else {
        // (!) Вот тут очистить по индексу
        this->stackStorage.pop_back();
        if (this->stackStorage.size() <= this->stackPointer) {
            this->stackPointer--;
        }
    }
}

int Stack::size () {
    return this->stackStorage.size();
}
