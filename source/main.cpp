#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include "vm-src.h"
#include "boot-code.h"

using std::byte;
using std::cout;
using std::string;
using std::vector;

bool itemCharFound (char* array[], int length, const char* foundingItem) {
    string item;
    for (int i = 0; i < length; i++) {
        item = string(array[i]);
        if (item == foundingItem) {
            return true;
        }
    }
    return false;
}

string getByteText (byte b) {
    string bytes[256] = {"0x00 ","0x01 ","0x02 ","0x03 ","0x04 ","0x05 ","0x06 ","0x07 ","0x08 ","0x09 ","0xa ","0xb ","0xc ","0xd ","0xe ","0xf ","0x10 ","0x11 ","0x12 ","0x13 ","0x14 ","0x15 ","0x16 ","0x17 ","0x18 ","0x19 ","0x1a ","0x1b ","0x1c ","0x1d ","0x1e ","0x1f ","0x20 ","0x21 ","0x22 ","0x23 ","0x24 ","0x25 ","0x26 ","0x27 ","0x28 ","0x29 ","0x2a ","0x2b ","0x2c ","0x2d ","0x2e ","0x2f ","0x30 ","0x31 ","0x32 ","0x33 ","0x34 ","0x35 ","0x36 ","0x37 ","0x38 ","0x39 ","0x3a ","0x3b ","0x3c ","0x3d ","0x3e ","0x3f ","0x40 ","0x41 ","0x42 ","0x43 ","0x44 ","0x45 ","0x46 ","0x47 ","0x48 ","0x49 ","0x4a ","0x4b ","0x4c ","0x4d ","0x4e ","0x4f ","0x50 ","0x51 ","0x52 ","0x53 ","0x54 ","0x55 ","0x56 ","0x57 ","0x58 ","0x59 ","0x5a ","0x5b ","0x5c ","0x5d ","0x5e ","0x5f ","0x60 ","0x61 ","0x62 ","0x63 ","0x64 ","0x65 ","0x66 ","0x67 ","0x68 ","0x69 ","0x6a ","0x6b ","0x6c ","0x6d ","0x6e ","0x6f ","0x70 ","0x71 ","0x72 ","0x73 ","0x74 ","0x75 ","0x76 ","0x77 ","0x78 ","0x79 ","0x7a ","0x7b ","0x7c ","0x7d ","0x7e ","0x7f ","0x80 ","0x81 ","0x82 ","0x83 ","0x84 ","0x85 ","0x86 ","0x87 ","0x88 ","0x89 ","0x8a ","0x8b ","0x8c ","0x8d ","0x8e ","0x8f ","0x90 ","0x91 ","0x92 ","0x93 ","0x94 ","0x95 ","0x96 ","0x97 ","0x98 ","0x99 ","0x9a ","0x9b ","0x9c ","0x9d ","0x9e ","0x9f ","0xa0 ","0xa1 ","0xa2 ","0xa3 ","0xa4 ","0xa5 ","0xa6 ","0xa7 ","0xa8 ","0xa9 ","0xaa ","0xab ","0xac ","0xad ","0xae ","0xaf ","0xb0 ","0xb1 ","0xb2 ","0xb3 ","0xb4 ","0xb5 ","0xb6 ","0xb7 ","0xb8 ","0xb9 ","0xba ","0xbb ","0xbc ","0xbd ","0xbe ","0xbf ","0xc0 ","0xc1 ","0xc2 ","0xc3 ","0xc4 ","0xc5 ","0xc6 ","0xc7 ","0xc8 ","0xc9 ","0xca ","0xcb ","0xcc ","0xcd ","0xce ","0xcf ","0xd0 ","0xd1 ","0xd2 ","0xd3 ","0xd4 ","0xd5 ","0xd6 ","0xd7 ","0xd8 ","0xd9 ","0xda ","0xdb ","0xdc ","0xdd ","0xde ","0xdf ","0xe0 ","0xe1 ","0xe2 ","0xe3 ","0xe4 ","0xe5 ","0xe6 ","0xe7 ","0xe8 ","0xe9 ","0xea ","0xeb ","0xec ","0xed ","0xee ","0xef ","0xf0 ","0xf1 ","0xf2 ","0xf3 ","0xf4 ","0xf5 ","0xf6 ","0xf7 ","0xf8 ","0xf9 ","0xfa ","0xfb ","0xfc ","0xfd ","0xfe ","0xff "};
    return bytes[int(b)];
}

string showBytes (vector<byte> bytes) {
    string showTxt = "";
    for (byte b : bytes) {
        // showTxt += char(b);
        showTxt += getByteText(b);
    }
    return showTxt;
}

bool isEqualId (vector<byte> idA, vector<byte> idB) {
    /*std::cout << showBytes(idA) << ";\n";
    std::cout << showBytes(idB) << ";\n--\n";*/
    return  (
        idA.at(0) == idB.at(0) &&
        idA.at(1) == idB.at(1) &&
        idA.at(2) == idB.at(2) &&
        idA.at(3) == idB.at(3)
    );
}

int execFunct (VirtualMachine vmCur, vector<byte> id) {
    vector<byte> mainFunctId = {};
    mainFunctId.insert(mainFunctId.begin(), 4, byte(0x00));
    vmCur.subprogs;

    for (Subprog funct : vmCur.subprogs) {
        if (isEqualId(funct.id, id)) {
            if (isEqualId(funct.id, mainFunctId) && funct.mode != byte(0x00)) {
                // (!) Выдать ошибку: MAIN не может быть кэшируемой.
            }
            else {
                funct.execute();
                return 0;
            }
        }
    }
    // (!) Вызвать ошибку: функция  '<идентификатор>' не найдена.
    return -1;
}

/*int getCurrentTime () {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();
    int currentTimeMillis = static_cast<int>(value);
    return currentTimeMillis;
}*/

int main(int argc, char* argv[]) {
    bool isShowRuntime = itemCharFound(argv, argc, "--show-runtime");  /* Проверим, чтобы флаг --show-runtime был в параметрах */
    //isShowRuntime = true;  /* Отладка */
    auto startedTime = std::chrono::steady_clock::now(); // запоминаем время начала
    bool isDebugMode = itemCharFound(argv, argc, "--debug");  /* Проверим, чтобы флаг --debug был в параметрах */
    int stopPoints[] = {};
    VirtualMachine vmCur(isDebugMode);
    if (isDebugMode) {
        vmCur.bindStopPoints(stopPoints);
    }
    // Прочитать весь байткод
    vector<byte> allByteCode = bootFrom("standartInputWithOut"); /*{
        byte(0x00), byte(0x00), byte(0x00), byte(0x00), byte(0x00), byte(0x00), byte(0x00),
        byte(0x01), byte(0x01), byte(0x0D), byte(0x48), byte(0x65), byte(0x6C), byte(0x6C), byte(0x6F), byte(0x2C), byte(0x20), byte(0x77), byte(0x6F), byte(0x72), byte(0x6C), byte(0x64), byte(0x21),
        byte(0x04), byte(0x00), byte(0x0E),
        byte(0x00), byte(0x01), byte(0x00), byte(0x00), byte(0x00), byte(0x00)
    };*/
    /* 1. Прогоняем все подпрограммы */
    vector<vector<byte>> parsedBytecode = vmCur.parseCommands(allByteCode, allByteCode.size());

    // Найдём все подпрограммы
    bool subprogParseIsStarted = false;
    vector<vector<byte>> subprogBytes = {};
    vector<byte> functId;
    byte functMode = byte(0x00);
    int commandPointer = 0;
    for (vector<byte> command : parsedBytecode) {
        //cout << showBytes(command) << "\n";  // Вывод команд (Отладка)
        if (
            command.at(0) == byte(0x00) &&
            command.at(1) == byte(0x00)
        ) {
            if (!subprogParseIsStarted) {
                subprogParseIsStarted = true;
                //functMode = byte(command.at(commandPointer + 1));
                functMode = byte(command.at(1));
                functId = {
                    /*byte(command[commandPointer + 2]),
                    byte(command[commandPointer + 3]),
                    byte(command[commandPointer + 4]),
                    byte(command[commandPointer + 5])*/
                    byte(command.at(2)),
                    byte(command.at(3)),
                    byte(command.at(4)),
                    byte(command.at(5))
                };
            }
            else {
                // (!) Выдать ошибку: нельзя объявлять функцию в функции.
                return -1;
            }
        }
        else if (
            command.at(0) == byte(0x00) &&
            command.at(1) == byte(0x01)
        ) {
            if (!subprogParseIsStarted) {
                // (!) Выдать ошибку: ошибка синтаксиса: обнаружен концевик без объявления начала функции
            }
            else if (!(
                /*command[commandPointer + 1] == functId.at(1) &&
                command[commandPointer + 2] == functId.at(2) &&
                command[commandPointer + 3] == functId.at(3) &&
                command[commandPointer + 4] == functId.at(4)*/
                command.at(2) == functId.at(0) &&
                command.at(3) == functId.at(1) &&
                command.at(4) == functId.at(2) &&
                command.at(5) == functId.at(3)
            )) {
                // (!) Выдать ошибку: идентификатор подпрограммы в концевике не соответствует идентификатору подпрограммы в заголовке.
                /*std::cout << "\n" << showBytes(functId) << "\n";
                std::cout << showBytes({command.at(2), command.at(3), command.at(4), command.at(5)}) << "\n";*/
            }
            else {
                Subprog funct(
                    functId,
                    functMode,
                    subprogBytes
                );
                vmCur.includeVoid(funct);

                subprogParseIsStarted = false;
                subprogBytes.clear();
                functId = {
                    byte(0x00),
                    byte(0x00),
                    byte(0x00),
                    byte(0x00)
                };
                functMode = byte(0x00);
            }
        }
        else if (subprogParseIsStarted) {
            //std::cout << "pushCom: " << showBytes(command) << ";\n";
            subprogBytes.push_back(command);
        }
        else {
            // (!) Выдать ошибку: команда вне функции.
            return -1;
        }

        commandPointer++;
    }
    // Исполняем код
    vector<byte> mainFunctId = {};
    mainFunctId.insert(mainFunctId.begin(), 4, byte(0x00));
    auto execTime = std::chrono::steady_clock::now();
    execFunct(vmCur, mainFunctId);
    auto endTime = std::chrono::steady_clock::now();
    if (isShowRuntime) {
        int executeTimeDebug = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - execTime).count();
        int bootTimeDebug = std::chrono::duration_cast<std::chrono::milliseconds>(execTime - startedTime).count();
        int totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startedTime).count();
        cout << "\n========================\nExecute time: " << executeTimeDebug << " ms\nBoot time: " << bootTimeDebug << " ms\nTotal: " << totalTime << " ms";
    }
}
