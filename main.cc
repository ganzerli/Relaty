#include <iostream>
#include <vector>
#include <fstream> 

#include "file/file.h"
#include "crypt/crypt.h"
#include "tools/tools.h"
#include "search/search.h"
#include "relations/relations.h"

using namespace std;

string ask(string question){
    string answer;
    cout << question << endl;
    getline(cin, answer);
    return answer;
}

int main (){
    //  define data folder
    const string FOLDER ="./DATA/";

    // init path
    string path = FOLDER;

    // useful variables
    string tempString;
    string tempString2;
    vector<string> stringVector;
    vector<vector<string>> vecVec;
    vector<string> emptyVector;
    vector<vector<string>> emptyVector2;



    // init objects of class files
    File file;
    Crypt crypt;
    Search search;
    ofstream outfile;
    Relations rel;
    Tools tools;

    rel.findRelationsToText("hello we are living very good, or at least hope to");

    //rel.updateConcept("bad-day","concept-1","5","");
    //rel.getRelationsFromConcept("concept-1");

    //tools.strToVec("have better day", ' ');

    // INTRO AND WELCOME
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                        @" << endl;    
    cout << "@    WELCOME TO RELATY   @" << endl;
    cout << "@                        @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << endl;
    
    const string PASSWORD = ask(" DECRIPTING FILES, insert password: ");

    // ################### DECRYPT ##############################
    //decrypt all files present in filenames file ANY
     string FILENAMES = file.vecToStr( file.getFileContent(FOLDER+"FILENAMES.txt") );
    // vector<string> fileNamesVec;
    // //string tempString;
     char tempChar;

    // if(FILENAMES != ""){
    //     // split filenames in vector
    //     for(int i = 0 ; i < FILENAMES.size(); i++){
    //         tempChar = FILENAMES[i];
    //         if(tempChar == ' '){
    //             // put name in vector
    //             fileNamesVec.push_back(tempString);
    //             tempString = ""; 
    //         }else{
    //             tempString += FILENAMES[i];
    //         }
    //     }
    // }else{
    //     cout << "decrypting.. NO FILE EXISTING YET.." << endl;
    // }

    // // loop throught filenames vector
    // tempString="";
    // for(int i = 0 ; i < fileNamesVec.size(); i++){
    //     //cout << fileNamesVec[i] << endl;
    //     // OPEN FILES, DECRIPT AND WRITE BACK
    //     tempString = file.vecToStr( file.getFileContent(FOLDER+fileNamesVec[i]) );
    //     outfile.open(FOLDER+fileNamesVec[i]);
    //     // decrypt content
    //     crypt.shuffle(PASSWORD);
    //     tempString = crypt.decrypt(tempString);
    //     // write back
    //     outfile << tempString << endl;
    //     outfile.close();
    // }
    // tempString="";
//     // ################### DECRYPT END  #########################


    //search.fromRelations("relation-1 relation-abc");

    
    //          ####################################
    //  menu                O P T I O N S
    //          ####################################

    // menu or useful variables
    bool pass = true;
    bool fileExists = false;
    string date;
    int userAction;

    //case 2 
    string relations;
    string text;
    string q;

    // LOOP START
    while(pass){
        q = ask(
            "Select action, NUMBER: \n1)INSERT record\n2)SEARCH record\n3)UPDATE record\n4)DELETE record\n5)ADD RELATION\n6)UPDATE CONCEPT\n7)SEARCH FROM CONCEPTS/RELATIONS\n8)SEARCH PRECISE WORD GIVEN CONCEPT\n9)LIST RELATIONS\n10)\n11)\n12)\n13)\n14)\n15)ENCRYPT AND EXIT\n"
        );
        if(q == "1"||q == "2"||q == "3"||q == "4"||q == "5"||q == "6"||q == "7"||q == "8"||q == "9"||q == "10"||q == "11"||q == "12"||q == "13"||q == "14"||q == "15" /* POSSIBLE EXITS */ || q == "exit" || q == "quit" || q == "EXIT"|| q == "QUIT"|| q == "Q"){
            if(q == "exit" || q == "quit" || q == "EXIT"|| q == "QUIT"|| q == "Q"){
                userAction = 15;
                q = "15";
            }
            userAction = stoi(q);

        //  SWITCH
            switch(userAction){
            case 1:
            cout << "########################"<<endl;
            cout << "#                      #"<<endl;
            cout << "#    INSERT A RECORD   #"<<endl;
            cout << "#                      #"<<endl;
            cout << "########################"<<endl;
                // get user input date
                path = FOLDER;
                date = ask("insert datum in format ddmmyyyy\nIf the datum is in the wrong format will not work");
                for(int i = 4; i < 8 ; i++){
                    path += date[i];
                }
                path += ".txt";

                fileExists = file.fileCheck(path);
                // try if file research and pronting works
                if(!fileExists){
                    cout << "file "<< path <<" does not exist" <<endl;
                    // ask if making file
                    string answ = ask("making file in folder DATA? y or n");
                    if(answ =="y" || answ =="Y") {
                        file.makeFile(path);
                        cout << "new file created in DATA folder" << endl;
                    }else{
                        cout << "ok nada... no file crated.." << endl;
                    }
                }

                // INSERT IN DATE    
                text = ask("insert text");
                // if...
                // relations = rel.findRelationsToText(text);
                relations = ask("insert relations");
                file.insertInDate(date, text, relations);

            break;
            case 2:
            // SEARCH RECORD IN A DATE
               cout << "########################"<<endl;
               cout << "#                      #"<<endl;
               cout << "#    SEARCH IN DATE    #"<<endl;
               cout << "#                      #"<<endl;
               cout << "########################"<<endl;

                //########### chack if file exists #########
                path = FOLDER;
                date = ask("insert datum, format; ddmmyyyy");
                // GET THE YEAR
                for(int i = 4; i < 8 ; i++){
                    path += date[i];
                }
                path += ".txt";
                fileExists = file.fileCheck(path);
                //###########################################
                if(fileExists){
                    search.searchDate(date);
                }else{
                    cout << "file " << path <<" does not exist, first insert a record accordingly" <<endl;
                    cout << "choose option  >> 1 << and create a record" <<endl;
                }            
            
            break;
            case 3:
                // CHANGE RECORD
                cout << "########################"<<endl;
                cout << "#                      #"<<endl;
                cout << "#    CHANGE RECORD     #"<<endl;
                cout << "#                      #"<<endl;
                cout << "########################"<<endl;

                //########### chack if file exists #########
                path = FOLDER;
                date = ask("insert datum, format; ddmmyyyy");
                // GET THE YEAR
                for(int i = 4; i < 8 ; i++){
                    path += date[i];
                }
                path += ".txt";
                fileExists = file.fileCheck(path);
                //##########################################
                if(fileExists){
                    cout << "TIPP: a good approach is to search the record in this date and copy the text, or the record will be completely overwritten, when an option to use atext editor would be an easier option, would be like that.. but our igenieure are working on the core framework of the program then this option is not been given as efficient in the development of the prototype of this kind of rational database.. we invite to understand, beeing an open source project A LOSS OF DATA IS NOT ADDRESSABLE TO THE DEVELOPERS OF THE PROJECT." <<endl;
                    text = ask("insert text");
                    relations = ask("insert relations");
                    // if...
                    // relations = rel.findRelationsToText(text);
                    file.insertInDate(date, text, relations);
                }else{
                    cout << "file " << path <<" does not exist, first insert a record accordingly" <<endl;
                    cout << "choose option  >> 1 << and create a record" <<endl;
                }    
            break;

            case 4:
                // DELETE A RECORD
                cout << "########################"<<endl;
                cout << "#                      #"<<endl;
                cout << "#    DELETE RECORD     #"<<endl;
                cout << "#                      #"<<endl;
                cout << "########################"<<endl;

                //########### chack if file exists #########
                path = FOLDER;
                date = ask("insert datum, format; ddmmyyyy");
                // GET THE YEAR
                for(int i = 4; i < 8 ; i++){
                    path += date[i];
                }
                path += ".txt";
                fileExists = file.fileCheck(path);
                //##########################################
                if(fileExists){
                    date = ask("DELETE FROM WHICH DATUM datum 00112021");
                    if(ask("DELETING RECORD.. SHORE TO DELETE RECORD in date "+date)== "y"){
                        file.insertInDate(date,"","");
                    }else{
                        cout << "record NOT deleted" << endl;
                    }
                }else{
                    cout <<"file for " << path << " does not exist" << endl;
                }

            break;

            case 5:
                // ADD RELATION
                cout << "########################"<<endl;
                cout << "#                      #"<<endl;
                cout << "#    ADD RELATION      #"<<endl;
                cout << "#                      #"<<endl;
                cout << "########################"<<endl;
 
                tempString = ask("select a SYMBOL for your relation");
                tempString += "=" + ask("select a NAME for your relation");
                tempString += "=" + ask("list related concepts with added value,\n 1 to 5 \n divided by spaces\nFORMAT: aaaa2 bbbb4 cccc1");
                
                // save relations 
                rel.addRelation(tempString);
                tempString ="";

                stringVector = rel.relFileToVector();
                cout << stringVector[0] << endl;
                stringVector = emptyVector;

            break;

            case 6:
                cout << "########################"<< endl;
                cout << "#                      #"<< endl;
                cout << "#    UPDATE CONCEPT    #"<< endl;
                cout << "#                      #"<< endl;
                cout << "########################"<< endl;
                
                // list relations
                stringVector = rel.relFileToVector();
                for(int i = 0; i < stringVector.size(); i++ ){
                    cout << stringVector[i] << endl;
                }
                stringVector = emptyVector;

                tempString = ask("select the relation");
                stringVector.push_back(tempString);

                tempString = ask("select a NEW CONCEPT for your relation, leave EMPTY to delete , select present to update");
                stringVector.push_back(tempString);
                
                tempString = ask("select a value for the concept 1 - 5");
                stringVector.push_back(tempString);
                
                tempString = ask("select a replacement if wanted , leave empty to delete");
                stringVector.push_back(tempString);
                
                rel.updateConcept(stringVector[0], stringVector[1], stringVector[2], stringVector[3]);

                // list relations
                stringVector = rel.relFileToVector();
                for(int i = 0; i < stringVector.size(); i++ ){
                    cout << stringVector[i] << endl;
                }
                stringVector = emptyVector;

            break;

            case 7:
                cout << "#############################"<< endl;
                cout << "#                           #"<< endl;
                cout << "#    SEARCH FROM CONCEPT    #"<< endl;
                cout << "#                           #"<< endl;
                cout << "#############################"<< endl;

                tempString = ask("select concept to search in records, divided by spaces ex.:abc defg");
                vecVec = search.fromRelations(tempString);

                //vecVec = tools.filterVecVec(vecVec,0,"not","dahin");

                cout << " " << endl;    
                cout << "# searching  " << tempString << endl;

                for(int i = 0; i < vecVec.size(); i++){
                                    
                cout << " >>> record n" << i+1 <<" )" <<  endl;   
                cout << " " << endl;  
                    cout << vecVec[i][0] << endl;
                    cout << "# from relations and concepts of: " << endl;
                    cout << " relations >> " << vecVec[i][1] <<" << abut this text" <<endl;
                    cout << " relations >> " << vecVec[i][2] <<" << abut this text" <<endl;
                    cout << " relations >> " << vecVec[i][3] <<" << abut this text" <<endl;


                cout << " " << endl;   
                }

                if(vecVec.size() < 1){
                    cout << "NO record found with: >> " << tempString << " << in searched concepts" << endl;
                }
                
                cout << " " << endl;   
                cout << " " << endl;   

                tempString = "";
                vecVec = emptyVector2;
            break;

            case 8:
                cout << "#############################"<< endl;
                cout << "#                           #"<< endl;
                cout << "# SEARCH WORD FROM RELATION #"<< endl;
                cout << "#                           #"<< endl;
                cout << "#############################"<< endl;
                
                tempString = ask("select concept to search in records, divided by spaces ex.:abc defg");
                vecVec = search.fromRelations(tempString);
                tempString = ask("select one word to search int the text");
                vecVec = search.wordInConceptRel(tempString , vecVec);

                cout << " " << endl;   

                for(int i = 0; i < vecVec.size(); i++){
                cout << " >>> record n" << i+1 <<" )" <<  endl;   
                cout << " " << endl;  
                    cout << "# searching  " << tempString << " with " <<tools.strToVec(vecVec[i][2],' ')[0]  << " ..." << endl;
                    cout << vecVec[i][0] << endl;
                    cout << "# from relations and concepts of: " << endl;
                    cout << vecVec[i][2] << endl;   
                    cout << " relations >> " << vecVec[i][1] <<" << abut this text" <<endl;
                    cout << " word >> " << tempString <<" << to search" <<endl;
                cout << " " << endl;  
                }
                if(vecVec.size() < 1){
                    cout << "NO record found with: >> " << tempString << " << in searched concepts" << endl;
                }
                
                cout << " " << endl;   
                cout << " " << endl;   

                tempString = "";
                vecVec = emptyVector2;

            break;

            case 9:

                cout << "#############################"<< endl;
                cout << "#                           #"<< endl;
                cout << "#       LIST RELAITONS      #"<< endl;
                cout << "#                           #"<< endl;
                cout << "#############################"<< endl;
                cout << ""<< endl;
                

                stringVector = rel.relFileToVector();

                for(int i = 0; i < stringVector.size(); i++){
                    cout << stringVector[i] << endl;
                }              
                cout << ""<< endl;



            break;
            
            case 10:
                cout << "OPTION NOT IMPLEMENTED YET .. ROTE <3" << userAction << endl;
            break;
            
            case 11:
                cout << "OPTION NOT IMPLEMENTED YET .. ROTE <3" << userAction << endl;
            break;
            
            case 12:
                cout << "OPTION NOT IMPLEMENTED YET .. ROTE <3" << userAction << endl;
            break;
            
            case 13:
            // OPTION NOT REALLY NEEDED IN THE PROGRAM
            userAction = 0;
            while(userAction < 50000){
                cout << "  V I R U S  "<< endl;
                cout << "                       <3 <  <3 <3 <3    <3  <3 < "<< endl;
                cout << "                       #                           #"<< endl;
                cout << "                       #        V I R U S          #"<< endl;
                cout << "                       <3                           #"<< endl;
                cout << "                       #        ---------          #"<< endl;
                cout << "                      <3        | 0   0 |          #"<< endl;
                cout << "                       #         !  V  /            #"<< endl;
                cout << "                      #            |||             #"<< endl;
                cout << "                       #                           <3"<< endl;
                cout << "                       #                           #"<< endl;
                cout << "                       <3 <3    <3 <3 <3 <  <3 <3   "<< endl;
                cout << " "<< endl;
                cout << " "<< endl;
                cout << "  V I R U S  "<< endl;
                cout << " "<< endl;
                cout << " "<< endl;
                cout << "  <3 <  <3 <3 <3    <3  <3 < "<< endl;
                cout << "  #                           #"<< endl;
                cout << "  #        V I R U S          #"<< endl;
                cout << "  <3                           #"<< endl;
                cout << "  #        ---------          #"<< endl;
                cout << " <3        | 0   0 |          #"<< endl;
                cout << "  #         !  V  /            #"<< endl;
                cout << " #            |||             #"<< endl;
                cout << "  #                           <3"<< endl;
                cout << "  #                           #"<< endl;
                cout << "  <3 <3    <3 <3 <3 <  <3 <3   "<< endl;
                cout << " "<< endl;
                cout << " "<< endl;
                cout << "                       V I R U S  "<< endl;
                cout << " "<< endl;
                cout << " QOOOK CPU ... QUUUK ...."<< endl;

            userAction += 1;
            }
                
            break;
            
            case 14:
                cout << "OPTION NOT IMPLEMENTED YET .. ROTE <3" << userAction << endl;
            break;

            case 15:
                cout << "ENCRYPT WIT PASSWORD "<< PASSWORD << " and EXIT" << endl;

                //#####################    ENCRYPT   ########################
                // ENCRUPT all files present in filenames file ANY
                FILENAMES = file.vecToStr( file.getFileContent(FOLDER+"FILENAMES.txt") );
                vector<string> fileNamesVec_;

                if(FILENAMES != ""){
                    // split filenames in vector
                    for(int i = 0 ; i < FILENAMES.size(); i++){
                        tempChar = FILENAMES[i];
                        if(tempChar == ' '){
                            // put name in vector
                            fileNamesVec_.push_back(tempString);
                            tempString = ""; 
                        }else{
                            tempString += FILENAMES[i];
                        }
                    }
                }else{
                    cout << "decrypting.. NO FILE EXISTING YET.." << endl;
                }

                // loop throught filename vector
                // tempString="";
                // for(int i = 0 ; i < fileNamesVec_.size(); i++){
                //     // GET FILE CONTENT
                //     tempString = file.vecToStr( file.getFileContent(FOLDER+fileNamesVec_[i]) );

                //     outfile.open(FOLDER+fileNamesVec_[i]);
                    
                //     // ENCRYPT CONTENT
                //     crypt.shuffle(PASSWORD);
                //     tempString = crypt.encrypt(tempString);
                    
                //     // WRITE BACK
                //     outfile << tempString << endl;
                //     outfile.close();
                // }
                // tempString="";
                //###########################################################
                // EXIT LOOP.. exit program
                pass = false;
            break;
            }   

            if(userAction != 15){
                ask("\n\n\n---------------------------------\npress enter for MENU");
            }

        }else{
        ///////////////////////////////
            cout << "######################################################################"<<endl;
            cout << "#  ERROR: Answer >> "<<q<<" << not valid, insert a possible option number  #" <<endl;
            cout << "######################################################################"<<endl;
        }
        //
        // IF NO CORRECT ANSWER THE PROGRAM CAN END HERE AND GO LOOPING..
        //
    }

}// END MAIN


