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
#include <cstring>
#include "../File.h"
#include "util.h"


class WriteProjectFile: public File {
    public: void writeData(const std::string& text) {
        if (pointer != MAP_FAILED) {
            std::cout << "File projected successful!" << std::endl;
            std::memcpy(pointer, text.c_str(), text.size());
            std::cout << "Data has been written to the memory-mapped file." << std::endl;
        } else {
            std::cerr << "File projecting error D:"  << std::endl;
        }
    }
};


#endif //FILEPROJECTIONLINUX_FILE_H
