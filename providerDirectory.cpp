
/* filename: providerDirectory.cpp
* Programmers: Dalton Gray
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
providerDirectory :: providerDirectory ( void ) {
	loadDirectory();
}

/** Constructs the object.
 * @param      toCopy  To copy
 */
providerDirectory :: providerDirectory ( const providerDirectory & toCopy ) {
	directory = toCopy.directory;
}

/** Destroys the object.
 */
providerDirectory :: ~providerDirectory ( void ) {
	writeDirectory();
}

/** Returns a list of services providers have that agreed to perform for ChocAn
 * members.
 * @return     The directory.
 */
list < Service > providerDirectory :: getDirectory ( void ) {
	return directory;
}

/** Takes a Service struct as input and adds it to the linear linked of services
 * ChocAn provides. It returns true if the services was successfully added,
 * otherwise it returns false.
 * @param      addedService  The added service
 * @return     True if the service was added, false otherwise
 */
bool providerDirectory :: addService (Service addedService) {
        if(directory.empty()) {
            directory.push_front(addedService);
            return true;
        }
        else {
            list < Service > :: iterator it = directory.begin(); 
	    for(it; it != directory.end(); ++it) {
                if(it -> name >= addedService.name) {
                    directory.insert(it, addedService);
                    return true;
                }
            }
        }
        directory.push_back(addedService);
            return true;
}

/** Takes a 6-digit long int as input and removes the corresponding service from
 * the linear linked list if it exists. It returns true if the service is
 * successfully removed, otherwise it returns false.
 * @param      serviceID  The service id
 * @return     True if the service was removed, false otherwise
 */
bool providerDirectory :: removeService (string serviceID) {
	if(directory.empty())
            return false;//Nothing was there to remove
        else {
            list < Service > :: iterator it = directory.begin(); 
            for(it; it != directory.end(); ++it) {
                if(it -> serviceID == serviceID) {
                    /*
                        This stuff is breaking things.
                        -- This should work now. - Dalton
                    */ 
                    it = directory.erase(it);
                    if(it -> serviceID == serviceID)
                        return false;
                    else
                        return true;
                }
            }
        }
        return true;
}
                    
/** Takes a 6-digit long int as input and displays the corresponding service and
 * all of its information to the terminal. It returns true if the service
 * entered is found and displayed, otherwise the function returns false.
 * @param      serviceID  The service id
 * @return     True if the service was displayed, false otherwise (Why is this a
 *             bool?)
 */
bool providerDirectory :: displayService (string serviceID) {
	if(directory.empty())
            return false;
        else {
            list < Service > :: iterator it = directory.begin(); 
            for(it; it != directory.end(); ++it) {
                if(it -> serviceID == serviceID) {
                    cout << "\nService ID: " << it -> serviceID << "\nName: " << it -> name << "\nService Fee: $" << it -> fee << endl;
                    return true;
                }
            }
        }
        return false;
}

/** Takes a 6-digit long int, and a float up to 999.99 as input and updates the
 * service fee of the corresponding service if it exists within the directory.
 * It returns true if the fee is successfully updated, or false if it is not.
 * @param      serviceID  The service id *
 * @param      newFee     The new fee
 * @return     True if the service fee was updated, false otherwise
 */
bool providerDirectory :: updateFee (string serviceID, float newFee) {
	if(directory.empty())
            return false;
        else {
            list < Service > :: iterator it = directory.begin();
            for(it; it != directory.end(); ++it) {
                if(it -> serviceID == serviceID) {
                    it -> fee = newFee; 
                    if(it -> fee == newFee)
                        return true;
                    else
                        return false;
                }
            }
        }
        return false;
}

void providerDirectory :: displayAll() {
	if(directory.empty())
            cout << "\nDirectory is empty!" << endl;
        else {
            list < Service > :: iterator it = directory.begin(); 
            for(it; it != directory.end(); ++it) {
                cout << "\nService ID: " << it -> serviceID << "\nName: " 
                     << it -> name << "\nService Fee: $" << it -> fee << endl;
            }
        }
}

bool providerDirectory :: checkID(string serviceID) {
	if(directory.empty())
            return false;
        else {
            list < Service > :: iterator it = directory.begin(); 
            for(it; it != directory.end(); ++it) {
                if(it -> serviceID == serviceID)
                    return true;
            }
        }
        return false;
}

void providerDirectory :: loadDirectory() {

	ifstream toLoad;
        Service toAdd;
        char temp[21];
        int i = 0;
        
	toLoad.open("directory.txt");
        
        while(toLoad) {
            toLoad.get(temp, 7, '^');
            toLoad.get();
             
            if(toLoad.eof())
                break;
            else {
                toAdd.serviceID = temp;
                toLoad.get(temp, 21, '^');
                toLoad.get();
                toAdd.name = temp;
                toLoad >> toAdd.fee;
                toLoad.get();
            }
            addService(toAdd);
        }
}

void providerDirectory :: writeDirectory() {

	ofstream toWrite;

        toWrite.open("directory.txt");

        list < Service > :: iterator it = directory.begin(); 
        for(it; it != directory.end(); ++it) {
            toWrite << it -> serviceID << "^" << it -> name << "^" << it -> fee << "\n";
        }

        toWrite.close();
}
