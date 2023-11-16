//
// Created by wastard on 11/16/23.
//

#ifndef FILEPROJECTIONLINUX_FILE_H
#define FILEPROJECTIONLINUX_FILE_H

#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "util.h"


class File {
    private: int descriptor = -1;
    private: void *pointer = nullptr;
    private: struct stat statistic {};

    public: int getDescriptor() const {return  descriptor;}

    public: struct stat getStatistic() {return statistic;}

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
        if(pointer) std::cout << "File projected successful!";
        else    std::cout << "File projecting error D:" << std::endl;
    }

    public: void unprojectFile() {
        munmap(pointer, statistic.st_size);
        if(pointer) std::cout << "Memory released!";
        else    std::cout << "Memory releasing error D:" << std::endl;
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


#endif //FILEPROJECTIONLINUX_FILE_H
