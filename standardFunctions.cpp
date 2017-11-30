//  CS300 - Group 9
//  Filename: "standardFunctions.cpp"

#include "standardHeader.h"

/*
 This is the implimentation file for all of my standard functions. They help with some
 very basic functionality that is useful program wide... 
 */

//General UI Functions//

//Checks if input is correct type - numeric/char
//Returns bool, true if it is not correct, false if it is correct
bool incorrect_input()
{
    //If the input buffer is in a fail state
    if(!cin)
    {
        //Restore the input buffer
        cin.clear();
        
        //Print an error message
        cout<<"Invalid Data!!! Please enter it correctly!"<<endl;
        
        //Clear the input buffer
        while(cin.get()!='\n');
        
        //Since the input was not correct
        return true;
    }
    
    //If the input is correct
    else
        return false;
}


//Read in a string of charachters to a variable
void read(const char* prompt, char* &read_into)
{
    //Temp variable to hold the response
    char* temp = new char [500];
    
    //Read in the information
    do
    {
        //Print out the prompt
        cout<<"\n"<<prompt;
        
        //Read in the data
        cin.get(temp, 500, '\n');

       
        //Clear our the input buffer
        while(cin.get()!='\n');
    
    //Repeat this until the user gives the correct input
    }while(incorrect_input());
       
	 //Dynamically allocate the memory
        read_into = new char [strlen(temp)+1];
    
        //Copy the data into the variable
        strcpy(read_into, temp);
    
    //Release memory
    delete [] temp;
 }



//Read in a int to a variable
void read_num(const char* prompt, int & num)
{
    //Read in the information
    do
    {
        //Print out the prompt
        cout<<"\n"<<prompt;
        
        //Read in the data
        cin>>num;
        
        //Repeat this until the user gives the correct input
    }while(incorrect_input());
    
    //Ignore any extra input
    while(cin.get()!='\n');
}



//Read in a float to a variable
void read_num(const char* prompt, float & num)
{
    //Read in the information
    do
    {
        //Print out the prompt
        cout<<"\n"<<prompt;
        
        //Read in the data
        cin>>num;
        
        //Repeat this until the user gives the correct input
    }while(incorrect_input());
    
    //Ignore any extra input
    while(cin.get()!='\n');
}



//Asks user if they would like to do something again, returns a bool
//True if yes, false if no
bool again(const char* prompt)
{
    //Variable for the response
    char response = 'o';
    
    //Variable for the return value
    bool again = false;
    
    //Print out the prompt
    cout<<"\n"<<prompt;
    
    //Read in the reponse
    cin.get(response);
    
    //Ignore extra charachters
    while(cin.get()!='\n');
    
    //Make sure the reponse is in the correct format
    response = tolower(response);
    
    //Check to see if it is a 'y'
    if(response == 'y')
        again = true;
    
    //Return the bool value
    return again;
}



//Copies one array into another one
void copyArray(char* & arrayTo, char* arrayFrom)
{
    arrayTo = new char [strlen(arrayFrom)+1];
    
    strcpy(arrayTo, arrayFrom);
    
}



//A function to print a line that is "length" long
void printLine(int length)
{
    //Print the line specified
    for(int i= 0; i!=length; ++i)
    {
        cout<<"-";
    }
    
    //Print out a newline at the end
    cout<<"\n";
}



//A function to prompt and wait until the user presses enter
void waitForEnter()
{
    cout<<"Press enter to continue..."<<endl;
    
    //Ignore extra charachters and wait for \n
    while(cin.get()!='\n');
}




///----------------///
//Node Class implimentaition
//Constructor and Destructor
standardNode::standardNode()
{
    //Set the variables to NULL
    next = NULL;
}



//Destructor 
standardNode::~standardNode()
{
    //Reset the variable to NULL
    next = NULL;
}


//Constructor with arguments
standardNode::standardNode(standardNode* nextNode)
{
    next = nextNode;
}


//Copy constructor
standardNode::standardNode(const standardNode & toCopy)
{
    //Check if NULL
    if(toCopy.next == NULL)
        next = NULL;
    else
        //Copy the data over
        next = toCopy.next;
}


//Assignment operator for a standard node
standardNode& standardNode::operator = (const standardNode & toCopy)
{
    //Check for self assignmemt
    if(this == &toCopy)
        return *this; //Just return ourselves
    
    //Copy over the data
    next = toCopy.next;
    
    //Return oursleves
    return *this;
}



//Function to return next
standardNode* & standardNode::goForward()
{
    //Return the next node
    return next;
}


//Function to set the next node
void standardNode::setNext(standardNode* nextIn)
{
    //Set the next pointer
    next = nextIn;
}

/**
 * Returns a string with the current time and date
 * @return     Current time and date
 */
string currentDateTime () {
  time_t raw;
  struct tm * timeStruct;
  char buffer [20];

  time (&raw);
  timeStruct = localtime (&raw);

  strftime (buffer,20,"_%d-%m-%Y_%I%M%S",timeStruct);
  string theTime(buffer);

  return theTime;
}


/**
 * Returns a string of whatever number was passed in
 * @return     String
 */
string toString(int convertToString)
{
    stringstream aStringStream;
    aStringStream << convertToString;
    return aStringStream.str();
}

string toString(float convertToString)
{
    stringstream aStringStream;
    aStringStream << convertToString;
    return aStringStream.str();
}
