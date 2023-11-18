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
    protected: std::string path;
    protected: const int FILESIZE = 4096;

    public: File()=default;

    private: virtual int initDescriptor() = 0;

    private: virtual void makeOperation() = 0;

    private: virtual void printOperation() = 0;

    public: void start() {
        openFile();
        int mode = printMenu();
        while(mode) {
            switch (mode) {
                case 1:
                    projectFile();
                    break;
                case 2:
                    makeOperation();
                    break;
                default:
                    std::cout << "Entered incorrect mode. Try again!" << std::endl;
                    break;
            }
            redraw();
            mode = printMenu();
        }
        unprojectFile();
        closeFile();
    }

    private: int printMenu() {
        int value;
        std::cout << "Project file\t---->\t1" << std::endl;
        printOperation();
        std::cout << "Exit\t\t---->\t0" << std::endl;
        std::cout << "\nEnter mode: ";
        std::cin >> value;
        return value;
    }


    private: void openFile() {
        path = enterPath();
        descriptor = initDescriptor();
        if(descriptor < 0) {
            std::cout << "Incorrect path, try again!" << std::endl;
            openFile();
        } else {
            std::cout << "File opened successful!" << std::endl;
            fstat(descriptor, &statistic);
        }
    }

    private: void projectFile() {
        redraw();
        if(!pointer) {
            std::cout << "File projected successful!" << std::endl;
            if (ftruncate(descriptor, FILESIZE) == -1) {
                perror("ftruncate");
                exit(EXIT_FAILURE);
            }
            pointer = mmap(nullptr, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, descriptor, 0);
            if (pointer == MAP_FAILED) {
                perror("mmap");
            }
        } else {
            std::cout << "The file has already project!" << std::endl;
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
