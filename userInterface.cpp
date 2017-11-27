/* filename: userInterface.cpp
* Programmers: Matthew Greenlaw, (Add your name here)
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
UserInterface :: UserInterface ( void ) {
	//@todo
}

/** Constructs the object.
 * @param      toCopy  To copy
 */
UserInterface :: UserInterface ( const UserInterface & toCopy ) {
	//@todo
}

/** Destroys the object.
 */
UserInterface :: ~UserInterface ( void ) {
	//@todo
}

/** Starts up the whole system and runs the UI.
 * @return     True if the user exits normally, false otherwise
 */
bool UserInterface :: runSystem ( void ) {
	//@todo
}

/** Runs the provider menu system. It presents the provider with a series of
 * commands for the provider to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runProviderMenu ( void ) {
	//@todo
}

/** Runs the manager menu system. It presents the manager with a series of
 * commands for the manger to use.
 * @return     True if the user exits  normally, false otherwise
 */
bool UserInterface :: runManagerMenu ( void ) {
	//@todo
}