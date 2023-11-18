//
// Created by wastard on 11/17/23.
//

#ifndef CLIENT_READPROJECTFILE_H
#define CLIENT_READPROJECTFILE_H

#include <iostream>
#include <fcntl.h>
#include <sys/select.h>
#include <csignal>
#include <unistd.h>
#include <fstream>
#include "../File.h"


class ReadProjectFile: public File {
    private: int initDescriptor() override {
        return open(path.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    }

    private: void printOperation() override {
        std::cout << "Read data\t---->\t2" << std::endl;
    }

    private: void makeOperation() override {
        redraw();

        if(pointer) {
            fd_set readFileDescriptorSet;
            struct timeval timeout{};

            FD_ZERO(&readFileDescriptorSet);
            FD_SET(descriptor, &readFileDescriptorSet);

            timeout.tv_sec = 10;  // timeout (seconds)

            int ready = select(descriptor + 1, &readFileDescriptorSet, nullptr, nullptr, &timeout);
            if (ready == -1) {
                std::cerr << "Using select() error\n";
            } else if (ready == 0) {
                std::cout << "Time is up\n";
            } else {
                if (FD_ISSET(descriptor, &readFileDescriptorSet)) {
                    // Access allowed

                    std::cout << "Read data:\n" << (char*)pointer << std::endl;

                    std::cout << "\nFile has been read\n";
                }
            }
        } else std::cout << "File is not projected!" << std::endl;
    }
};


#endif //CLIENT_READPROJECTFILE_H
