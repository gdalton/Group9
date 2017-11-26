
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
    reportManager :: reportManager ( const reportManager & toCopy ) {}
    
    /** Destroys the object.
     */
    reportManager :: ~reportManager ( void ) {}

    /** Allows the user to make changes to an existing report
     * @return     True if the changes were made, false otherwise
     * @todo This is a change from the original design and may need some extra
     * attention.
     */
    bool reportManager :: updateReport ( void ) {

    }
    
    /** Generates a new provider report
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     True if the report was generated, false otherwise
     */
    bool reportManager :: providerReport ( string reportDetails, providerRecord * newReport) {

    }

    /** Generates a new member report
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     True if the report was generated, false otherwise
     */
    bool reportManager :: memberReport ( string reportDetails, memberRecord * newReport) {

    }

    /** Generates all reports for a provider
     * @param      providerTree  The provider tree
     * @param      theProvider   The provider
     * @return     True if the reports were generated, false otherwise
     */
    bool reportManager :: providerAllReports ( map < string, Provider > providerTree, Provider * theProvider) {

    }

    /** Generates all reports for a member
     * @param      memberTree  The member tree
     * @param      theMember   The member
     * @return     True if the reports were generated, false otherwise
     */
    bool reportManager :: memberAllReports ( map < string, Member > memberTree, Member * theMember) {

    }

    /** Generates an EFT
     * @param      newEFT     The new eft
     * @param      trasferee  The trasferee
     * @return     True if the EFT was generated, false otherwise
     */
    bool reportManager :: generateEFT ( eft * newEFT, Account * trasferee) {

    }