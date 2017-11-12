//  CS300 - Group 9
//  Filename: main.cpp


#include "mainHeader.h"

int main(int argc, const char * argv[]) {

    printLine(45);
    cout<<"         Welcome to the ChocAn HCS "<<endl;
    printLine(45);
    
    //Test of the file system
    fileSystem fileSys;
    char* testString = new char[100];
    
    fileSys.write("This is a test!\n\n Another Line! \n", "test.txt");
    fileSys.read(testString, 100, "test.txt");
    
    cout<<endl<<testString<<endl;
    
    delete [] testString;

    
    
    return 0;
}
