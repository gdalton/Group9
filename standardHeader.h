//  CS300 - Group 9
//  Filename: main.cpp

//Include the necessary files
#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <cmath>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include "list" //http://www.cplusplus.com/reference/list/list/
#include "string" //http://www.cplusplus.com/reference/string/string/
#include <sstream> // stringstream http://www.cplusplus.com/reference/sstream/stringstream/

using namespace std;

//General UI Functions//


//Checks if input is correct type - numeric/char
//Returns bool, true if it is not correct, false if it is correct
bool incorrect_input();

//Read in a string of charachters to a variable
void read(const char* prompt, char* &read_into);

//Read in a int to a variable
void read_num(const char* prompt, int & num);

//Read in a float to a variable
void read_num(const char* prompt, float & num);

//Asks user if they would like to do something again, returns a bool
//True if yes, false if no
bool again(const char* prompt);

//Copies one array into another one
void copyArray(char* & arrayTo, const char* arrayFrom);

//A function to print a line that is "length" long
void printLine(int length);

//Prompts and waits for the user to press enter
void waitForEnter();

//Returns a string with the current date and time
string currentDateTime();

//Integer to String Converter - for systems earlier than C++11
string toString(int convertToString);



//Can probably delete this later... if we use a list library
//Standard Node Class

//This class is intended to be a standard node class that any obj.
//can be derived from when Linked List functionality is needed
class standardNode
{
    
public:
    //Constructor and Destructor
    standardNode();
    ~standardNode();
    
    //Constructor with arguments
    standardNode(standardNode* nextNode);
    
    //Copy constructor
    standardNode(const standardNode & toCopy);
    
    //Assignment operator for a standard node
    standardNode& operator = (const standardNode & toCopy);
    
    //Function to return next
    standardNode* & goForward();
    
    //Function to set the next node
    void setNext(standardNode* nextIn);
    
    
protected:
    
    //Pointer to the next node
    standardNode* next;
};







