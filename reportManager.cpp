
/* filename: reportManager.cpp
 * Programmers: Matthew Greenlaw (Add your name here)
 * Class Number: CS-300
 * Date: 22NOV17
 * Purpose: The Report Manager (RM) class will contain all of the functions
   necessary to create all of the reports required by ChocAn, their members, and
   their Providers. This class will generate reports for the aforementioned
   parties weekly, as well as provide functionality for ChocAn managers to
   generate reports on-demand.
*/

#include "mainHeader.h"

	/** Constructs the object.
	 */
	reportManager :: reportManager ( void ) {}
    
    /** Constructs the object.
     * @param      toCopy  To copy
     */
    //reportManager :: reportManager ( const reportManager & toCopy ) {}
    
    /** Destroys the object.
     */
    reportManager :: ~reportManager ( void ) {}

    /** Finds every provider that has provided a service during
     * the week and list them, along with the number of services they provided
     * during the week, and the total fee owed to them. It will also add up the
     * overall total fee owed by ChocAn for the week. This will be stored and
     * returned via a manager’s report struct.
     * @return     True if the changes were made, false otherwise
     */
    bool reportManager :: managerReport ( map < string, Provider > providerTree ) {

        //loop over providers {
        //  Display there stuff
        //  add up total fee
        // }
        //  display total fee

        float providerFee = 0;
        float totalFees = 0;

        for ( map < string, Provider > :: iterator i = providerTree.begin (); i != providerTree.end (); ++i ) {
            if( i->second.getNumMembersSeen () != 0) {
                cout << "Provider: " << endl;
                i->second.display ();
                cout << "Members seen: " << i -> second.getNumMembersSeen () << endl;

                list < providerRecord > * copyServiceRecord = i -> second.getServiceRecord ();
                
                for ( list < providerRecord > :: iterator j = copyServiceRecord -> begin (); j != copyServiceRecord -> end (); ++j ) {
                    providerFee += j -> serviceFee;
                }

                cout << "Fees due: " << providerFee << endl;

            }

            totalFees += providerFee;
            providerFee = 0;
        }

        cout << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;
        cout << "Total fees due: " << totalFees << endl;
        cout << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;

    }
    
    /** Reads in a 9-digit provider ID and generate an individual provider report
     * for a ChocAn manager if the provider ID input exists. The report will be
     * returned via provider report pointer provided in the arguments list. If
     * the report is successfully created the function will return true,
     * otherwise it will return false.
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     True if the report was generated, false otherwise
     */
    bool reportManager :: providerReport ( string reportDetails, providerRecord * newReport) {

    }

    /** Reads in a 9-digit member ID and generate an individual member report for
     * a ChocAn manager if the member ID input exists. The report will be
     * returned via the member report pointer provided in the arguments list. If
     * the report is successfully created the function will return true,
     * otherwise it will return false.
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     True if the report was generated, false otherwise
     */
    bool reportManager :: memberReport ( string reportDetails, memberRecord * newReport) {

    }

    /** Reads in a tree of providers and cycle through all of the ChocAn
     * providers creating a linear linked list of provider reports. A node in
     * the list will represent a report and each provider that has rendered a
     * service during the week will have a node. The completed list will be
     * returned via the the Provider Report pointer in the arguments list for
     * use by the file system. The function will return true if the list is
     * completed, or false if there is an error in the process.
     * @param      providerTree  The provider tree
     * @param      theProvider   The provider
     * @return     True if the reports were generated, false otherwise
     */
    bool reportManager :: providerAllReports ( map < string, Provider > providerTree, Provider * theProvider) {

    }

    /** Reads read in a tree of members and cycle through all of the ChocAn
     * members creating a linear linked list of member reports. A node in the
     * list will represent a report and each member that has received a service
     * during the week will have a node. The completed list will be returned via
     * the the Member Report pointer in the arguments list for use by the file
     * system. The function will return true if the list is completed, or false
     * if there is an error in the process.
     * @param      memberTree  The member tree
     * @param      theMember   The member
     * @return     True if the reports were generated, false otherwise
     */
    bool reportManager :: memberAllReports ( map < string, Member > memberTree, Member * theMember) {

    }

    /** Reads read in a tree of providers and cycle through all of the ChocAn
     * providers creating a linear linked list of providers and total fees owed
     * to them. The completed list will be returned via the eft pointer for use
     * by the file system. The function will return true if the list is
     * completed, or false if there is an error in the process.
     * @param      newEFT     The new eft
     * @param      trasferee  The trasferee
     * @return     True if the EFT was generated, false otherwise
     */
    bool reportManager :: generateEFT ( eft * newEFT, Account * trasferee) {

    }