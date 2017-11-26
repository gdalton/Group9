
/* filename: warden.cpp
 * Programmers: Matthew Greenlaw, (Add your name here)
 * Class Number: CS-300
 * Date: 22NOV17
 * Purpose:
 * @todo
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
    
    /** Adds a credential.
     * @param      newUsername  The new username
     * @param      newPassword  The new password
     * @return     Adds a username/password pair to the list of credentials
     */
    bool Warden :: addCredential ( string newUsername, string newPassword) { //@todo

    }
    
    /** Validates a login.
     * @param      checkedUsername  The checked username
     * @param      checkedPassword  The checked password
     * @return     True if the username/passowrd match
     */
    bool Warden :: validateLogin ( string checkedUsername, string checkedPassword) { //@todo

    }
    
    /** Checks how many times a user has failed logins
     * @param      userID  The user id
     * @return     True if the user has not exceeded their login attempts, false
     *             otherwise
     */
    bool Warden :: checkLoginAttempts ( int userID) { //@todo

    }
    
    /**
     * Adds a log.
     * @param      logToAdd  The log to add
     * @return     True if the log was added, false otherwise
     */
    bool Warden :: addLog ( string logToAdd) { //@todo

    }
    
    /**
     * Checks if a user is active
     * @return     True if the user is active, false otherwise
     */
    bool Warden :: checkActive ( void ) { //@todo

    }
