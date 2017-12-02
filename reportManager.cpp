
/* filename: reportManager.cpp
 * Programmers: Matthew Greenlaw, Dalton Gray (Add your name here)
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

    /** Finds every provider that has provided a service during
     * the week and list them, along with the number of services they provided
     * during the week, and the total fee owed to them. It will also add up the
     * overall total fee owed by ChocAn for the week. This will be stored and
     * returned via a manager’s report struct.
     * @return     True if the changes were made, false otherwise
     */
    managersReport * reportManager :: managerReport ( const map < string, Account* > * providerTree ) {

        float providerFee = 0;
        float totalFees = 0;
        int totalProviders = 0;
        int totalConsults = 0;
        Provider* theAccount;

        managersReport * record = new managersReport;
        map < int, float > data;

        if ( providerTree ) {
            //Loop over providers
            for ( map < string, Account*  > :: const_iterator i = providerTree->begin (); i != providerTree->end (); ++i ) {

                theAccount = static_cast<Provider*>(i->second);
                
                //If they saw anyone this week
                if( theAccount->getNumMembersSeen () != 0) {
                    ++totalProviders;
                if( theAccount->getNumMembersSeen () != 0) {

                    //loop over who they saw and record the fees
                    list < providerRecord > * providerServiceRecord = theAccount->getServiceRecord ();

                    for ( list < providerRecord > :: const_iterator j = providerServiceRecord -> begin (); j != providerServiceRecord -> end (); ++j ) {
                        providerFee += j -> serviceFee;
                        ++totalConsults;
                    }
                    
                    //Free memory
                    delete providerServiceRecord;

                    //store the data
                    data.insert ( pair < int, float > ( theAccount->getNumMembersSeen (), providerFee));

                    //add the provider and their data
                    record -> providerDetails.insert ( pair < string, map < int, float > > ( i -> first, data));
                }

                //tie up the bits
                totalFees += providerFee;
                providerFee = 0;
            }
            record -> totalProviders = totalProviders;
            record -> totalConsults = totalConsults;
            record -> totalFees = totalFees;
        }

        return record;
    }
}

    /** Reads in a 9-digit provider ID and generate an individual provider report
     * for a ChocAn manager if the provider ID input exists. The report will be
     * returned via provider report pointer provided in the arguments list. If
     * the report is successfully created the function will return true,
     * otherwise it will return false.
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     providersReport *  if the report was generated, NULL otherwise
     */
    providersReport * reportManager :: providerReport ( const Provider & theProvider ) const {

        float totalFees = 0;
        int totalConsults = 0;
        providersReport * newReport = NULL;

        if( &theProvider ){
            //Static stuff
            newReport = new providersReport;
            infoStruct * providerInfo = theProvider . getInfo();
            list < providerRecord > * providerServiceRecord = theProvider . getServiceRecord ();

            newReport -> providerName = providerInfo -> name;//no get name
            newReport -> providerID = providerInfo -> ID;//invalid from string* to char
            newReport -> theAddress = providerInfo -> theAddress;//No get address
            newReport -> serviceRecord = *providerServiceRecord;
            
            //Dynamic stuff
            for ( list < providerRecord > :: iterator j = providerServiceRecord -> begin (); j != providerServiceRecord -> end (); ++j ) {
                totalFees += j -> serviceFee;
                ++totalConsults;
            }

            newReport -> consultations = totalConsults;
            newReport -> weekFee = totalFees;
            
            //Free memory
            delete providerServiceRecord; 
        }
        
        return newReport;
    }

    /** Reads in a 9-digit member ID and generate an individual member report for
     * a ChocAn manager if the member ID input exists. The report will be
     * returned via the member report pointer provided in the arguments list. If
     * the report is successfully created the function will return true,
     * otherwise it will return false.
     * @param      reportDetails  The report details
     * @param      newReport      The new report
     * @return     membersReport * if the report was generated, NULL otherwise
     */
    membersReport * reportManager :: memberReport ( const Member & theMember ) {

        membersReport * newReport = NULL;

        if( &theMember ){

            newReport = new membersReport;
            infoStruct * memberInfo = theMember . getInfo ();

            newReport -> memberName = memberInfo -> name;
            newReport -> memberID = memberInfo -> ID;
            newReport -> theAddress = memberInfo -> theAddress;
            newReport -> serviceRecord = * theMember.getServiceRecords ();
        }

        return newReport;
    }

    /**
     * Generates a members's Service Record
     * @return     Pointer to a memberRecord
     */
    memberRecord * reportManager :: generateMemberServiceRecord ( string * providerName, string * serviceName ) {
            return new memberRecord ( new string ( currentDateTime()), providerName, serviceName);
    }

    /**
     * Generates a provider's Service Record
     * @return     Pointer to a providerRecord
    */
    providerRecord * reportManager :: generateProviderServiceRecord ( string * newDateOfService, string * newMemberName, string * providerID, string * serviceID, string * memberID, string * comments, float serviceFee ){        
        return new providerRecord ( new string ( currentDateTime()), newDateOfService, newMemberName, providerID, serviceID, memberID, comments, serviceFee);
    }


    /** Reads in a tree of providers and cycle through all of the ChocAn
     * providers creating a linear linked list of providers and total fees owed
     * to them. The completed list will be returned via the eft pointer for use
     * by the file system. The function will return true if the list is
     * completed, or false if there is an error in the process.
     * @param      newEFT     The new eft
     * @param      trasferee  The trasferee
     * @return     True if the EFT was generated, false otherwise
     */
    eft * reportManager :: generateEFT ( const Provider * transferee) {

        eft * retEFT = NULL;
        infoStruct * providerInfo = NULL;
        providersReport * theProviderReport = NULL;

        if ( transferee ) {
            retEFT = new eft;
            providerInfo = transferee -> getInfo();
            theProviderReport = providerReport( * transferee ) ;

            retEFT -> providerName = providerInfo -> name ;
            retEFT -> providerID = providerInfo -> ID;
            retEFT -> totalFee = theProviderReport -> weekFee;
        }

        return retEFT;
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
    list < providersReport >  * reportManager :: providerAllReports ( const map < string, Account* > * providerTree) {

        list < providersReport > * providerReports = NULL;
        Provider* theAccount;

        if ( providerTree ) {//Can't remember if I need this if statment or not
            providerReports = new list < providersReport >;

            for ( map < string, Account* > :: const_iterator i = providerTree -> begin (); i != providerTree -> end (); ++i ) {
                
                theAccount = static_cast<Provider*>(i->second);
                providerReports -> push_back ( *providerReport ( *theAccount ) );
            }
        }

        

        return providerReports;
        
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
    list < membersReport > * reportManager :: memberAllReports ( const map < string, Account* > * memberTree) {
        list < membersReport > * memberReports = NULL;
        Member* theAccount;

        if ( memberTree ) {//Can't remember if I need this if statment or not
            memberReports = new list < membersReport >;

            for ( map < string, Account* > :: const_iterator i = memberTree -> begin (); i != memberTree -> end (); ++i ) {

                theAccount = static_cast<Member*>(i->second);
                memberReports -> push_back ( *memberReport ( *theAccount ) );
            }
        }

        return memberReports;
    }



    

    /**
     PARKING LOT
     **
        
        //Save to file version 0
        void reportManager :: managerReport ( map < string, Provider > providerTree ) {

        //Generate report filename
        string sFilename = "managerReport" + currentDateTime();
        const char * filename = sFilename.c_str();

        //Open file for appen
        ofstream record;
        record.open(filename, fstream :: app);//Closes once out of scope

        float providerFee = 0;
        float totalFees = 0;

        for ( map < string, Provider > :: iterator i = providerTree.begin (); i != providerTree.end (); ++i ) {
            if( i->second.getNumMembersSeen () != 0) {
                record << "Provider: " + i -> first << endl;
                record << "Members seen: " << i -> second.getNumMembersSeen () << endl;

                list < providerRecord > * providerServiceRecord = i -> second.getServiceRecord ();
                
                for ( list < providerRecord > :: iterator j = providerServiceRecord -> begin (); j != providerServiceRecord -> end (); ++j ) {
                    providerFee += j -> serviceFee;
                }

                record << "Fees due: " << providerFee << endl;

            }

            totalFees += providerFee;
            providerFee = 0;
        }

        record << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;
        record << "Total fees due: " << totalFees << endl;
        record << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;

    }

        
        //Save to file version 1
        void reportManager :: managerReport ( map < string, Provider > providerTree ) {

        float providerFee = 0;
        float totalFees = 0;
        stringstream record;
        string completedRecord;
        fileSystem fs; 

        //Generate report filename
        string filename = "managerReport" + currentDateTime();

        for ( map < string, Provider > :: iterator i = providerTree.begin (); i != providerTree.end (); ++i ) {
            if( i->second.getNumMembersSeen () != 0) {
                record << "Provider: " + i -> first << endl;
                record << "Members seen: " << i -> second.getNumMembersSeen () << endl;

                list < providerRecord > * providerServiceRecord = i -> second.getServiceRecord ();
                
                for ( list < providerRecord > :: iterator j = providerServiceRecord -> begin (); j != providerServiceRecord -> end (); ++j ) {
                    providerFee += j -> serviceFee;
                }

                record << "Fees due: " << providerFee << endl;

            }

            totalFees += providerFee;
            providerFee = 0;
        }

        record << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;
        record << "Total fees due: " << totalFees << endl;
        record << "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << endl;

        completedRecord = record.str();
        fs.write(completedRecord.c_str(), filename.c_str());
     */

