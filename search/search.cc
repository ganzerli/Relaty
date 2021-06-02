#include <iostream>
#include <string>
#include <vector>


#include "search.h"
#include "../file/file.h"
#include "../tools/tools.h"

#include "../relations/relations.h"



using namespace std;

    // POSITION OF BEGIN RELATIONS
    //int lastIndexRecord = (INDEXSIZE - FORMATSIZE);
    //string beginRelationZ;
    //cout << lastIndexRecord << endl;
    //for(int i = lastIndexRecord; i < lastIndexRecord + CHARSOFNUMBER ; i++){
    //    beginRelationZ += INDEX[i];
    // }
    // last got is the last char in the file
    //cout << beginRelationZ << endl;
    //int beginOfRelations = stoi( beginRelationZ );


void Search::loadContentAndIndexFromPath(string year){
    File file;
    string path = file.PATH + year +".txt";
    CONTENT = file.getFileContent(path);
    INDEX = file.getIndex(CONTENT);
}

vector<string> Search::searchRelations(string relations){
    vector<string> result;
    // code here

    //
    return result;
}

vector<string> Search::searchDate(string date){ 
vector<string> result;
    // init class entity
    string content;
    string relations;

    File file;
    Tools tools;
    string year;
    for(int i = 4; i < 8 ; i++){
        year += date[i];
    }
    // date and index need to be loaded in this class
    loadContentAndIndexFromPath(year);

    //get day and mont from date
    string day; day+= date[0]; day += date[1];
    string month; month += date[2]; month += date[3];
    const string DATE = day + month;

    vector<string> DATA = file.dataOfDay(DATE , INDEX);
    ///////////////////////////////////////////////////
    // find in content
    string beginIndex  = DATA[0]; 
    string positionOfString = DATA[1]; 
    string numberOfChars = DATA[2]; 
    string positionOfRelations  = DATA[3]; 
    string numberRelations  = DATA[4]; 
    // print content of date
    for(int i=stoi(positionOfString); i < stoi(positionOfString) + stoi(numberOfChars); i++ ){
        content += CONTENT[i];
    }
    cout << content << endl;

    for(int i=stoi(positionOfRelations); i < stoi(positionOfRelations) + stoi(numberRelations); i++ ){
        relations += CONTENT[i];

    }
    cout << relations << endl;

    result.push_back(content);
    result.push_back(relations);
    
    return result;
}

vector<vector<string>> Search::fromRelations(string relations){
    Tools tools;
    File file;
    Relations rel;

    vector<vector<string>> result;
    vector<string> emptyVector;
    vector<string> collectConceptsResult;
    vector<string> collectTextRels;
    vector<string> collectResult;

    string tempSearchedConcepts;
    
    string text;
    string rels;

    vector<vector<string>> relsFromSearchedConcept;
    vector<string> foundSearchedConcepts;

    bool conceptFound;

    // fun must
    char tempChar;
    char tempChar2;

    string relationsFound;

    // get vector of relations..
    vector<string> allRelations = tools.strToVec(relations,' ');
    //

    // CHECK IF CONCEPTS HAS RELATED RELATIONS
    for(int i = 0; i < allRelations.size(); i++){
        // for every relation searched, get it from related concepts
        relsFromSearchedConcept = rel.getRelationsFromConcept(allRelations[i]);
        if( relsFromSearchedConcept.size() > 0 ){
            // get relationS from one concept
            for(int j = 0; j < relsFromSearchedConcept.size(); j++){
                // MAKE A VECTOR WITH [0] SEARCHED CONCEPT, AND RELATION INFO AFTER[][][]
                // and fill a vector with searched concept[0] relations...[1][2]
                tempSearchedConcepts += allRelations[i] +" ";
                for(int k = 0; k < relsFromSearchedConcept[j].size(); k++){
                    tempSearchedConcepts += relsFromSearchedConcept[j][k] + " ";
                }
                foundSearchedConcepts.push_back(tempSearchedConcepts);
                tempSearchedConcepts="";
            }
            // add concept related relations to main vector
        }           
    }

    const string PATH = file.PATH;

    // check files
    string FILENAMES = file.vecToStr( file.getFileContent(PATH + "FILENAMES.txt") );
    vector<string> fileNamesVec = tools.strToVec(FILENAMES,' ');
    // first name is RELATIONS.txt
    for(int i = 1; i < fileNamesVec.size(); i++){
        // open file, get index
        const vector<char> CONTENT = file.getFileContent(PATH + fileNamesVec[i]);

        // get index from CONTENT vector
        vector<char> INDEX = file.getIndex(CONTENT);

        // GENERATE A DATUM
        string tempMonth;
        string generateDatum;
        int dayConunter=1;
        int tempPositionOfString;
        int tempPositionOfRelations;
        int tempLenghtOfRelations;
        int tempLengthOfString;

        vector<string> tempDataOfDay;

        // get data of day of all the remainings days
        // instread to use day count.. we generate the datums from this month
        const int calender [1 + 12] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
        // the loop does not work so good with the last calender[11].. then the 0 index

        for(int i = 1; i <= 12; i++ ){
            while(dayConunter <= calender[i]){
                // generate a date string
                if(i < 10){
                    tempMonth = "0"+tools.itos(i);
                }else{
                    tempMonth = tools.itos(i);
                }                

                if(dayConunter < 10){
                    generateDatum = "0"+tools.itos(dayConunter) + tempMonth;
                }else{
                    generateDatum += tools.itos(dayConunter ) + tempMonth;
                }
                tempDataOfDay = file.dataOfDay(generateDatum , INDEX);

                // get old data
                tempPositionOfString = stoi( tempDataOfDay[1] );
                tempLengthOfString = stoi( tempDataOfDay[2] );
                tempPositionOfRelations = stoi ( tempDataOfDay[3] );
                tempLenghtOfRelations = stoi ( tempDataOfDay[4] );

                if(tempLenghtOfRelations > 0){
                    // check in vector if the relation SIMBOL 
                    // compare with that in the frase

                    // 
                    for(int i = 0; i < foundSearchedConcepts.size(); i++ ){
                        // CHECK IN STRING OF FOUD POSSIBLE RELATIONS 
                        for(int j = 0; j < foundSearchedConcepts[i].size(); j++ ){

                            tempChar = foundSearchedConcepts[i][j];
                            if(tempChar == ' '){
                                // WE NEED THE CHAR AFTER.. THERE IS STORED THE SYMBOL OF THE RELATION

                                // RELATION TO CHECK IS IN [i][j] + 1;
                                tempChar = foundSearchedConcepts[i][j+1];

                                // FROM TEXT GET THE ACTUAL RELATIONS
                                for(int i = 0; i < tempLenghtOfRelations; i++ ){
                                    tempChar2 = CONTENT[tempPositionOfRelations + i];
                                    if ( tempChar2 == tempChar ){
                                       conceptFound = true;
                                    }  
                                }
                            //exit the string loop after first found
                            // the relation symbol is after the first " " char
                            break;
                            }
                        }

                        if(conceptFound){
                            collectConceptsResult.push_back(foundSearchedConcepts[i]);
                        }
                        conceptFound = false;
                        // IF FOUND GET ALL TEXT AND ALSO WHERE FOUND
                    }

                    if ( collectConceptsResult.size() > 0 ){

                        // first text, then relations, then all found concepts
                        // collect text
                        for(int i = 0; i < tempLengthOfString; i++ ){
                            text += CONTENT[i+tempPositionOfString];
                        }
        
                        // collect relations
                        for(int i = 0; i < tempLenghtOfRelations ; i++ ){
                            rels += CONTENT[i+tempPositionOfRelations];
                        }
        
                        // FILL FIRST TEXT AND RELATIONS
                        collectResult.push_back(text);
                        text = "";
                        collectResult.push_back(rels);
                        rels = "";
        
                        // PUSH OTHER FULL RELATIONS FOUND FROM CONCEPTS
                        for(int i = 0; i < collectConceptsResult.size(); i++ ){
                            collectResult.push_back(collectConceptsResult[i]);
                        }
                        collectResult.push_back(generateDatum);
        
                        // fill result
                        result.push_back(collectResult);
        
                        // empty vectors
                        collectConceptsResult = emptyVector;
                        collectResult = emptyVector;
                    }

                }

                dayConunter++;
                generateDatum="";
            }
            dayConunter = 1;
        }
        
    }
    return result;
}

vector<string> Search::searchWord(string word){
    vector<string> result;
    // code here

    //
    return result;
}

// given an input of research for concept, filter with given word
vector<vector<string>> Search::wordInConceptRel(string word, vector<vector<string>> input){
    
    vector<vector<string>> result;
    Tools tools;
    vector<string> stringVec;
    string tempString;
    bool found = false;
    // code here
    for(int i = 0; i < input.size(); i++ ){
        // the text is stored in [0]
        stringVec = tools.strToVec(input[i][0],' ');
        for(int j = 0; j < stringVec.size(); j++ ){
            tempString = stringVec[j];
            if(word == tempString){
                result.push_back(input[i]);
                break;
            }
        }
    }

    for(int i = 0; i < result.size(); i++ ){
        cout << result[i][1] << endl;
    }
    //
    return result;
}
