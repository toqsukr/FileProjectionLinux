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

volatile sig_atomic_t flag = 0;

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        flag = 1;
    }
}


class WriteProjectFile: public File {
    private: void makeOperation() override {
        if (pointer != MAP_FAILED) {
            int server_pid = getpid();
            std::ofstream pid_file("../server_pid.txt");
            pid_file << server_pid << std::endl;
            pid_file.close();

            std::string text = "Client lox";
            std::cout << "File projected successful!" << std::endl;
            std::memcpy(pointer, text.c_str(), text.size());
            std::cout << "Data has been written to the memory-mapped file." << std::endl;

            signal(SIGUSR1, signal_handler);

            while (!flag) {
                usleep(1000);
            }

        } else {
            std::cerr << "File projecting error D:"  << std::endl;
        }
    }
};


#endif //FILEPROJECTIONLINUX_FILE_H
