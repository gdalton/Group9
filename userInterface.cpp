/* filename: userInterface.cpp
* Programmers: Matthew Greenlaw, Katie Loveland
* Class Number: CS-300
* Date: 22NOV17
* Purpose:The User Interface (UI) class manages all input from the user and all
  output to the user, as well as enforcing the proper access levels for each
  user. This entails providing the user with menu’s, accepting their
  selections/data, and passing this data on to other classes to consume. The UI
  class will also query deeper level classes (such as the Account Manager or
  Report Manager) in order to provide information to the user, if the user
  selects a menu option that requires such action. The UI class will utilize the
  Warden class to determine the security clearance of each user and will present
  menu options to them based on that clearance.
*/

#include "mainHeader.h"


/** Constructs the object.
 */

UserInterface :: UserInterface () {

}

/** Constructs the object.
 * @param      toCopy  To copy
 */
UserInterface :: UserInterface ( const UserInterface & toCopy ) {
	currentUser = string(toCopy.currentUser);
}

/** Destroys the object.
 */
UserInterface :: ~UserInterface ( void ) {
}

/** Starts up the whole system and runs the UI.
 * @return     True if the user exits normally, false otherwise
 */
bool UserInterface :: runSystem ( void ) {
    bool toReturn = false;
    
    int selection = 0;
    
    //Welcome the user and explain the program
    printLine(50);
    cout<<"           Welcome to the ChocAn HCS"<<endl;
    printLine(50);
    cout<<endl<<endl;
    
    //Login Function here
    
    do
    {
        //Get the user's selection
        selection = userSelection();
        switch(selection)
        {
            case 1:
                //Some function call...
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 2:
                //Some function call...
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 3:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 4:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 5:
                
                //Wait for the user to continue
                waitForEnter();
                break;
                
            case 9:
                //Close the program
                cout<<"Program closed... Thank you!"<<endl;
                break;
                
            default:
                cout<<"An unknown error occured!"<<endl;
                
        }
    }while(selection<=8);

    
    return toReturn;
}


//Function to allow the user to select a number for the switch statement
int UserInterface::userSelection()
{
    int userSelection=0;
    
    do
    {
        cout<<"************************************************"<<endl;;
        cout<<"            ChocAn Manager Menu"<<endl;;
        cout<<"************************************************"<<endl;
        
        //Print out the menu options
        cout<<"1. Add a Account"<<endl;
        cout<<"2. Run Reports"<<endl;
        cout<<"3. Set member status"<<endl;
        cout<<"9. Exit program."<<endl;
        
        read_num("\nPlease make a selection:", userSelection);
        
    }while(userSelection<1 || userSelection>9);
    
    return userSelection;
}

/** Runs the provider menu system. It presents the provider with a series of
 * commands for the provider to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runProviderMenu ( void ) {
	//@todo
    bool toReturn = false;
    
    return toReturn;
}

/** Runs the manager menu system. It presents the manager with a series of
 * commands for the manger to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runManagerMenu ( void ) {
	//@todo
    bool toReturn = false;
    
    return toReturn;
}
