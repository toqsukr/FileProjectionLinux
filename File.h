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
    private: std::string path;
    private: const int FILESIZE = 4096;

    public: File()=default;

    private: virtual void makeOperation() = 0;

    public: void start() {
        openFile();
        projectFile();
        makeOperation();
        unprojectFile();
        closeFile();
    }

    private: void openFile() {
        path = enterPath();
        descriptor = open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if(descriptor < 0) {
            std::cout << "Incorrect path, try again!" << std::endl;
            openFile();
        } else {
            std::cout << "File opened successful!" << std::endl;
            fstat(descriptor, &statistic);
        }
    }

    private: void projectFile() {
        if (ftruncate(descriptor, FILESIZE) == -1) {
            perror("ftruncate");
            exit(EXIT_FAILURE);
        }
        pointer = mmap(nullptr, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
        if (pointer == MAP_FAILED) {
            perror("mmap");
            closeFile();
        }
    }

    private: void unprojectFile() {
        if (munmap(pointer, FILESIZE) == -1) {
            perror("munmap");
            closeFile();
        }
    }

    private: void closeFile() {
        close(descriptor);
        unlink(path.c_str());
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
