//
// Created by wastard on 11/17/23.
//

#ifndef CLIENT_UTIL_H
#define CLIENT_UTIL_H

#include <string>
#include <iostream>

std::string readConsole(const std::string& message = "\nEnter value: ") {
    std::string value;
    std::cout << message;
    std::getline(std::cin, value);

    // Удаляем пробелы с обоих концов строки
    size_t firstNonSpace = value.find_first_not_of(" \t");
    size_t lastNonSpace = value.find_last_not_of(" \t");

    if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
        value = value.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    } else {
        // Если строка состоит только из пробелов, обнуляем строку
        value.clear();
    }
    return value;
};

#endif //CLIENT_UTIL_H
