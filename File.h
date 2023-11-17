//
// Created by wastard on 11/17/23.
//

#ifndef CLIENT_FILE_H
#define CLIENT_FILE_H


#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "util.h"


class File {
    protected: int descriptor = -1;
    protected: void *pointer = nullptr;
    protected: struct stat statistic {};

    public: void openFile() {
        std::string path = enterPath();
        descriptor = open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if(descriptor < 0) {
            std::cout << "Incorrect path, try again!" << std::endl;
            openFile();
        } else {
            std::cout << "File opened successful!" << std::endl;
            fstat(descriptor, &statistic);
        }
    }

    public: void projectFile() {
        pointer = mmap(nullptr, statistic.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
        if (pointer == MAP_FAILED) {
            perror("mmap");
            closeFile();
        }
    }

    public: void unprojectFile() {
        if (munmap(pointer, statistic.st_size) == -1) {
            perror("munmap");
            closeFile();
        }
    }

    public: void closeFile() {
        close(descriptor);
    }

    public: static std::string enterPath() {
        std::string path = readFilePath();
        return path;
    }

    public: static std::string readFilePath(const std::string& message = "\nEnter file path: ") {
        return readConsole(message);
    };
};


#endif //CLIENT_FILE_H
