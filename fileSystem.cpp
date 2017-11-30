
/* filename: fileSystem.cpp
 * Programmers: Dmitri Murphy, (Add your name here)
 * Class Number: CS-300
 * Date: 22NOV17
 * Purpose:
 * @todo
 */

#include "mainHeader.h"

//Constructor and Destructor
fileSystem::fileSystem()
{
    
}
fileSystem::~fileSystem()
{
    
}

//Read out to a file, deletes anything previously in the file
bool fileSystem::write(const char* dataToReadOut, const char* filename)
{
    ofstream fileOut; //Var to read out to file
    
    //Open the filestream
    fileOut.open(filename);
    
    //Read out to the file
    
    //Checking the connection to the file
    if(fileOut)
    {
        //Read out the data
        fileOut<<dataToReadOut;
        
        //Close the file
        fileOut.close();
        
        return true;
    }
    
    return false;
}

//Read out to a file, deletes anything previously in the file
bool fileSystem::writeSTR(string & dataToReadOut, string & filename)
{
    ofstream fileOut; //Var to read out to file
    
    //Open the filestream
    fileOut.open(filename.c_str());
    
    //Read out to the file
    
    //Checking the connection to the file
    if(fileOut)
    {
        //Read out the data
        fileOut<<dataToReadOut;
        
        //Close the file
        fileOut.close();
        
        return true;
    }
    
    return false;
}


bool fileSystem::read(char* & allData, int length, const char* fileName){
    ifstream fileIn;
//    char toCheck [101];
//    char next = 'a';
    
    //Initialize File Stream
    fileIn.open(fileName);
    
    //Stop if fileOpen failed
    if(!fileIn){ return false; }
    
    //Get a single line from the data file
    fileIn.get(allData, length, '\0');
    
    fileIn.close();
    return true;
}


bool fileSystem::testFileSystem(){
    bool toReturn = false;
    
    
    return toReturn;
}







