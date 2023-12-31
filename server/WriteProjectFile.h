//
// Created by wastard on 11/16/23.
//

#ifndef FILEPROJECTIONLINUX_FILE_H
#define FILEPROJECTIONLINUX_FILE_H

#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "../File.h"


class WriteProjectFile: public File {
    int initDescriptor() override {
        return open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    }

    private: void printOperation() override {
        std::cout << "Write data\t---->\t2" << std::endl;
    }

    private: void makeOperation() override {
        redraw();

        if (pointer && pointer != MAP_FAILED) {
            std::string text;
            text = readConsole("Enter text:\n");
            memset(pointer, 0, FILESIZE);
            std::memcpy(pointer, text.c_str(), text.size());
            std::cout << "Data has been written to the memory-mapped file." << std::endl;
        } else {
            std::cout << "File is not projected!"  << std::endl;
        }
    }
};


#endif //FILEPROJECTIONLINUX_FILE_H
