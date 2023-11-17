#include <iostream>
#include "File.h"

int main() {
    File *file = new File();
    file->openFile();
    file->projectFile();
    file->writeData("Projection test");
    std::cout << "File address: " << file->getPointer() << std::endl;
    getchar();
    file->unprojectFile();
    file->closeFile();
    return 0;
}
