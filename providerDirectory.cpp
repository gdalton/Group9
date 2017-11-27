
/* filename: providerDirectory.cpp
* Programmers: (Add your name here)
* Class Number: CS-300
* Date: 22NOV17
* Purpose: The Provider Directory class will manage the list of services that
  providers are able to bill ChocAn for. This information contained in this
  class will be viewable by both managers and providers, however only manger’s
  will have the ability to manage the data contained by the class. The Provider
  Directory will contain the service’s ID number, name, and fee as well as all
  the functions to manage this data.
*/

#include "mainHeader.h"
	

/** Constructs the object.
 */
providerDirectory :: providerDirectory ( void ) {}

/** Constructs the object.
 * @param      toCopy  To copy
 */
providerDirectory :: providerDirectory ( const providerDirectory & toCopy ) {

}

/** Destroys the object.
 */
providerDirectory :: ~providerDirectory ( void ) {}

/** Returns a list of services providers have that agreed to perform for ChocAn
 * members.
 * @return     The directory.
 */
list < Service > providerDirectory :: getDirectory ( void ) {

}

/** Takes a Service struct as input and adds it to the linear linked of services
 * ChocAn provides. It returns true if the services was successfully added,
 * otherwise it returns false.
 * @param      addedService  The added service
 * @return     True if the service was added, false otherwise
 */
bool providerDirectory :: addService ( Service addedService) {

}

/** Takes a 6-digit long int as input and removes the corresponding service from
 * the linear linked list if it exists. It returns true if the service is
 * successfully removed, otherwise it returns false.
 * @param      serviceID  The service id
 * @return     True if the service was removed, false otherwise
 */
bool providerDirectory :: removeService ( int serviceID) {

}

/** Takes a 6-digit long int as input and displays the corresponding service and
 * all of its information to the terminal. It returns true if the service
 * entered is found and displayed, otherwise the function returns false.
 * @param      serviceID  The service id
 * @return     True if the service was displayed, false otherwise (Why is this a
 *             bool?)
 */
bool providerDirectory :: displayService ( int serviceID) {

}

/** Takes a 6-digit long int, and a float up to 999.99 as input and updates the
 * service fee of the corresponding service if it exists within the directory.
 * It returns true if the fee is successfully updated, or false if it is not.
 * @param      serviceID  The service id *
 * @param      newFee     The new fee
 * @return     True if the service fee was updated, false otherwise
 */
bool providerDirectory :: updateFee ( int serviceID, float newFee) {

}