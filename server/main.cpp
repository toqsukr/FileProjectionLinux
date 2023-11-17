#include <iostream>
#include "File.h"

int main() {
    File *file = new File();
    file->openFile();
    std::cout << "File size: " << file->getStatistic().st_size << " bytes" << std::endl;
    file->projectFile();
    file->unprojectFile();
    file->closeFile();
    return 0;
}
