#include <iostream>
#include "WriteProjectFile.h"
#include "WriteProjectFile.h"

int main() {
    auto file = new WriteProjectFile();
    file->openFile();
    file->projectFile();
    file->writeData("Projection test");
    getchar();
    file->unprojectFile();
    file->closeFile();
    return 0;
}
