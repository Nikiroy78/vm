#include "stack.h"
#include <iostream>

int bytesToInt (vector<vector<std::byte>> bytes) {
    // (!) Сделать потом
    return 0;
}

Stack::Stack() {
    this->stackStorage.clear();
    this->stackPointer = -1;
}
Stack::~Stack () {
    //delete this->stackStorage;
}

vector<byte> Stack::get () {
    if (this->stackStorage.size() == 0) return {};
    vector<byte> result = this->stackStorage[this->stackPointer];
    if (this->stackLinker[this->stackPointer] != -1) {
        if (
            this->stackLinker.size() < bytesToInt(this->stackStorage[this->stackPointer])
        ) {
            // (!) Выдать ошибку: такого элемента не существует
        }
        else if (
            bytesToInt(this->stackStorage[this->stackPointer]) == this->stackPointer
        ) {
            // (!) Выдать ошибку: ссылочный элемент не может ссылаться на самого себя
        }
        else {
            this->stackPointer = bytesToInt(this->stackStorage[this->stackPointer]);
            return this->get();
        }
    }
    else {
        return result;
    }
}

void Stack::push (vector<byte> data) {
    this->stackStorage.push_back(data);
    this->stackLinker.push_back(-1);
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
        this->stackLinker.pop_back();
        if (this->stackStorage.size() <= this->stackPointer) {
            this->stackPointer--;
        }
    }
}

int Stack::size () {
    return this->stackStorage.size();
}
