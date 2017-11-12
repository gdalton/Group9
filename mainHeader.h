//  CS300 - Group 9
//  Filename: mainHeader.h


//General Include
#include "standardHeader.h"


//-----------------------------
//  File System Class
//  - reads/writes to/from the file system
//-----------------------------
class fileSystem{
    public:
        
        //Constructor and Destructor
        fileSystem();
        ~fileSystem();
        
        //Read out to a file
        bool write(const char* dataToReadOut, const char* filename);
        
        //Read in from a file
        bool read(char* & allData, int length, const char* fileName);
    
        //Test Function to run the class's test suite 
        bool testFileSystem();
    
    private:
    
};

