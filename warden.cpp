
/* filename: warden.cpp
 * Programmers: Matthew Greenlaw, (Add your name here)
 * Class Number: CS-300
 * Date: 22NOV17
 * Purpose: The Warden class encapsulates the security functionality of the
   system into one discrete object. Warden primarily interacts with the UI and
   File System classes. Warden’s three main tasks are validation / system locks,
   timeouts, and logging.
*/

#include "mainHeader.h"

/** Constructs the object.
 */
Warden :: Warden ( void ) { //@todo

}

/** Constructs the object.
 * @param      toCopy  To copy
 */
Warden :: Warden ( const Warden & toCopy ) { //@todo

}

/** Destroys the object.
 */
Warden :: ~Warden ( void ) { //@todo

}

/** Adds a credential to systemCredentials.
 * @param      newUsername  The new username
 * @param      newPassword  The new password
 * @return     True if the cred was added, false otherwise
 */
bool Warden :: addCredential ( string newUsername, string newPassword) { //@todo
    bool toReturn = false;
    
    return toReturn;
}

/** Updates a credential in systemCredentials.
 * @param      newUsername  The new username
 * @param      newPassword  The new password
 * @return     True if the cred was updated, false otherwise
 */
bool Warden :: updateCredential ( string newUsername, string newPassword) { //@todo
    bool toReturn = false;
    
    return toReturn;
}

/** Deletes a credential from systemCredentials.
 * @param      newUsername  The new username
 * @param      newPassword  The new password
 * @return     True if the cred was deleted, false otherwise
 */
bool Warden :: deleteCredential ( string newUsername, string newPassword) { //@todo
    bool toReturn = false;
    
    return toReturn;
}

/** Returns true if there is a match between the userID / userPassword pair and a
 * pair in the systemCredentials list
 * @param      checkedUsername  The checked username
 * @param      checkedPassword  The checked password
 * @return     True if the username/passowrd match, false otherwise.
 */
bool Warden :: validateLogin ( string checkedUsername, string checkedPassword) { //@todo
    bool toReturn = false;
    
    return toReturn;
}

/** Returns true if login attempts < 3.
 * @param      userID  The user id
 * @return     Returns true if login attempts < 3, false otherwise
 */
bool Warden :: checkLoginAttempts ( int userID) { //@todo
    bool toReturn = false;
    
    return toReturn;
}


/** Returns true if the logEntry is successfully entered in the logFile.
 * @param      logToAdd  The log to add
 * @return     Returns true if the logEntry is successfully entered in the
 *             logFile, false otherwise.
 */
bool Warden :: addLog ( string logToAdd) { //@todo
    bool toReturn = false;
    
    return toReturn;
}


/** Checks if the difference between currentTime and referenceTime is <5min
 * @return     Returns true if the difference between currentTime and
 *             referenceTime is <5min, false otherwise
 */
bool Warden :: checkActive ( void ) { //@todo
    bool toReturn = false;
    
    return toReturn;
}
