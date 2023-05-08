#include "command-exec.h"
#include "command.h"

bool isMatchedCommand (vector<byte> compareValue, vector<vector<byte>> comparingArr) {
    for (vector<byte> command : comparingArr) {
        if (command[0] == compareValue[0] && command[1] == compareValue[1]) {
            return true;
        }
    }
    return false;
}

bool CommandExecutor::isCorrectionSyntax () {
    if (this->isCommandDefined) {
        switch (this->bytes.at(0)) {
            case byte(0x00):  // Работа с функциями
                switch (this->bytes[1]) {
                    case byte(0x00): { // Заголовок функции
                        VOID_HEADER vh(this->bytes, this->globalStack);
                        return vh.checkCorrectSyntax();
                    }
                    case byte(0x01): { // Концевик функции
                        VOID_ENDER ve(this->bytes, this->globalStack);
                        return ve.checkCorrectSyntax();
                    }
                }
            case byte(0x01):  // Работа со стэком
                switch (this->bytes.at(1)) {
                    case byte(0x01):  // Добавить значение в стек
                        STACK_PUSH sp(this->bytes, this->globalStack);
                        return sp.checkCorrectSyntax();
                }
            case byte(0x04): // Системный ввод-вывод
                switch (this->bytes.at(1)) {
                    case byte(0x00):  // Вывод в консоль
                        STDOUT so(this->bytes, this->globalStack);
                        return so.checkCorrectSyntax();
                }
            default:
                return false;
        }
    }
    else return false;
}

void CommandExecutor::execute () {
    if (this->isCommandDefined) {
        switch (this->bytes.at(0)) {
            case byte(0x00):  // Работа с функциями
                switch (this->bytes[1]) {
                    case byte(0x00): { // Заголовок функции
                        VOID_HEADER vh(this->bytes, this->globalStack);
                        vh.exec();
                        while (vh.localStack.size() != 0) {
                            vector<byte> bytes = vh.localStack.get();
                            this->insiderStack.push(bytes);
                            vh.localStack.rm();
                        }
                    }
                    case byte(0x01): { // Концевик функции
                        VOID_ENDER ve(this->bytes, this->globalStack);
                        ve.exec();
                        while (ve.localStack.size() != 0) {
                            vector<byte> bytes = ve.localStack.get();
                            this->insiderStack.push(bytes);
                            ve.localStack.rm();
                        }
                    }
                }
            case byte(0x01):  // Работа со стэком
                switch (this->bytes.at(1)) {
                    case byte(0x01):  // Добавить значение в стек
                        STACK_PUSH sp(this->bytes, this->globalStack);
                        sp.exec();
                        while (sp.localStack.size() != 0) {
                            vector<byte> bytes = sp.localStack.get();
                            this->insiderStack.push(bytes);
                            sp.localStack.rm();
                        }
                }
            case byte(0x04): // Системный ввод-вывод
                switch (this->bytes.at(1)) {
                    case byte(0x00):  // Вывод в консоль
                        STDOUT so(this->bytes, this->globalStack);
                        so.exec();
                        while (so.localStack.size() != 0) {
                            vector<byte> bytes = so.localStack.get();
                            this->insiderStack.push(bytes);
                            so.localStack.rm();
                        }
                }
        }
    }
}

CommandExecutor::CommandExecutor (vector<byte> bytes, Stack globalStack) {
    this->bytes = bytes;
    this->globalStack = globalStack;
    this->commands = {
        // Functions
        {byte(0x00), byte(0x00)},  // void_header
        {byte(0x00), byte(0x01)},  // void_ender
        // Stack
        {byte(0x01), byte(0x01)},
        // Stdout-Stdin
        {byte(0x04), byte(0x00)}
    };
    this->isCommandDefined = isMatchedCommand(
        {
            bytes[0], bytes[1]
        }, this->commands
    );
    this->isEnded = this->isCorrectionSyntax();
}
