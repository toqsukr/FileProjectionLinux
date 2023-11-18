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
    private: int serverPID = -1;
    private: void makeOperation() override {
        fd_set readFileDescriptorSet;
        struct timeval timeout{};

        std::ifstream pid_file("../server_pid.txt");
        pid_file >> serverPID;
        pid_file.close();

        FD_ZERO(&readFileDescriptorSet);
        FD_SET(descriptor, &readFileDescriptorSet);

        timeout.tv_sec = 20;  // timeout (seconds)

        int ready = select(descriptor + 1, &readFileDescriptorSet, nullptr, nullptr, &timeout);
        if (ready == -1) {
            std::cerr << "Using select() error\n";
        } else if (ready == 0) {
            std::cout << "Time is up\n";
        } else {
            if (FD_ISSET(descriptor, &readFileDescriptorSet)) {
                // Access allowed
                char buffer[1024];

                ssize_t bytesRead = read(descriptor, buffer, sizeof(buffer));
                if (bytesRead == -1) {
                    std::cerr << "File reading error\n";
                }

                std::cout << buffer << std::endl;

                kill(serverPID, SIGUSR1);

                std::cout << "File has been read\n";
            }
        }
    }
};


#endif //CLIENT_READPROJECTFILE_H
