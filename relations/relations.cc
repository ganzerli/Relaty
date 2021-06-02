#include <vector>
#include <string>
#include <iostream>
#include <fstream> 

#include "relations.h"
#include "../file/file.h"
#include "../crypt/crypt.h"
#include "../tools/tools.h"
#include "../search/search.h"

using namespace std;
    
void Relations::addRelation(string relationsAndConcepts){
    File file;
    ofstream outfile;
    // open file and add relation
    // get first as relation, second as relation name, other as concepts
    string relations = file.vecToStr( file.getFileContent( PATH ));
    string toWrite = relations + relationsAndConcepts + "!";
    // write back
    outfile.open(PATH);
    outfile << toWrite << endl;
    outfile.close();
}


vector<string> Relations::relFileToVector(){
    File file;

    string FILERELATIONS = file.vecToStr( file.getFileContent(PATH) );
    vector<string> fileRelationsVec;

    string tempString;
    char tempChar;

    if(FILERELATIONS != ""){
        // split FILERELATIONS in vector
        for(int i = 0 ; i < FILERELATIONS.size(); i++){
            tempChar = FILERELATIONS[i];
            if(tempChar == '!'){
                // put name in vector
                fileRelationsVec.push_back(tempString);
                tempString = ""; 
            }else{
                tempString += FILERELATIONS[i];
            }
        }
    }else{
        cout << "getting relations NO FILE EXISTING YET.. create ./DATA/RELATIONS.txt" << endl;
    }
    return fileRelationsVec;
}

// add or remove a concept from one relation
// find the relation, if the relation exists
    // if the something is found, replace with 3rd string
    // if not, add.. and ignore the 3rd string
        // 7 mai

vector<string> Relations::updateConcept(string relation, string newConcept, string value, string replacement){
// vector new file content
    vector<string> relStrings;
    vector<string> relSplit;

    bool go = false;
    char tempChar;
    char tempChar2;
    string tempString;
    string concept;
    int relStringsIndex = 999999;
    int index;

    // save the relations whole as string
    relStrings = relFileToVector();

    for(int z = 0; z < relStrings.size(); z++ ){

        tempString = relStrings[z];
        cout << tempString <<endl;
        // get vector of ONE relation wih concepts
        relSplit = relStringToVector(tempString);

        // get the NAME of the relation
        tempString = relSplit[1];

        // find the right relation from the NAME
        if(relation == tempString){
            // relation is found
            // check for the concepts
            tempString = "";
            for(int i = 2; i < relSplit.size(); i++){
                concept = relSplit[i];
                //get the value away from the concept
                // make another string without the last char
                for(int j = 0 ; j < concept.size() - 1 ; j++  ){
                    tempString += concept[j];
                }
                // concept - last chat == new concept
                if(newConcept == tempString){
                    //cout << newConcept << endl;
                    go = true;
                    // save the index and exit loop
                    index = i;
                    break;
                }else{
                    go = false;
                }
                // empty fo rthe next concept in the list of this relation
                tempString = "";
            }

            // if found
            if(go){
                // replace
                cout << "replace" << endl;
                // check if empty?????????
                relSplit[index] = replacement + value;
                if(replacement == "" ||replacement == " "){
                    concept = "to delete";    
                }
                relStringsIndex = z;
                break;
            }else{
                // add
                cout << "add" << endl;
                relSplit.push_back(newConcept + value);
                relStringsIndex = z;
                break;
            }

        }else{
            tempString = "";
        }
    }// end loop of relations

    // relString index is set if somewhere to find or replace
    if(relStringsIndex != 999999){
        // relation found
        // pack in a string together the relSplit vec
        tempString = relSplit[0]+"="+relSplit[1]+ "=";
        for(int i = 2; i < relSplit.size(); i++){
            // LAST CHAR CANNOT BE A SPACE !!!
            if(i == relSplit.size()-1){
                if(concept != "to delete"){
                // if the last one is empty dont add anything    
                    tempString += relSplit[i];
                }
            }else{
                if(concept == "to delete" && i == relSplit.size()-2){
                    tempString += relSplit[i];
                }else{
                    tempString += relSplit[i] + " ";
                }
            }
            
        }

        // replace the new relation in relStrings
        relStrings[relStringsIndex] = tempString;

        // pack in a string together the NEW FILE CONTENT
        tempString = "";
        for(int i = 0; i < relStrings.size(); i++){
            tempString += relStrings[i]+"!";
        }

        // WRITE BACK
        ofstream outfile;
        outfile.open(PATH);
        outfile << tempString << endl;
        outfile.close();

        cout << "found!!" << endl;
    }else{
        // relation not there
    }

    return relStrings;
}


vector<string> Relations::relStringToVector(string rel){
    vector<string> vec;
    char tempChar;  
    string tempString;
    int index;

    tempString += rel[0];

    // get the simbol first
    vec.push_back(tempString);

    tempString = "";

    // ge the relation name
    for(int i = 2; i < 30; i++){
        tempChar = rel[i];
        if(tempChar == '='){
            vec.push_back(tempString);
            tempString="";
            //save index and avoid the =
            index = i+1;
            break;
        }else{
            tempString += tempChar;
        }
    }

    // from 3rd char, after '=', get the name, and then the concepts
    for(int i = index; i < rel.size(); i++){
        tempChar = rel[i];
        
        if(tempChar == ' '){
            vec.push_back(tempString);
            tempString="";
        }else{
            // after check avoid " "
            tempString += tempChar;
        }
    }
    
    // push last word
    vec.push_back(tempString);
    return vec;
}

// find relations and concepts related with same concept
vector<vector<string>> Relations::getRelationsFromConcept(string concept){
    
    vector<vector<string>> related;
    vector<string> relationConcepts;
    vector<string> relStrings;
    string tempString;

    relStrings = relFileToVector();

    //loop throught all relations
    for(int i = 0; i < relStrings.size(); i++){
        relationConcepts = relStringToVector(relStrings[i]);

        // get NAME
        tempString = relationConcepts[1];
        // compare the name
        if(tempString == concept){
            //found concept as relation
            related.push_back(relationConcepts);
        }
        tempString = "";

        // compare all the rest
        for(int j = 2; j < relationConcepts.size(); j++){

            // cut out the value for the coparison
            for(int k = 0 ; k < relationConcepts[j].size() - 1 ; k++ ){
                tempString += relationConcepts[j][k];
            }
            // compare the name
            if(tempString == concept){
                //found concept as relation
                related.push_back(relationConcepts);
                break;
            }
            tempString = "";
        }
    }
    return related;
}

//having text find the relations from words contained
string Relations::findRelationsToText(string record){
string result;

    Tools tools;

    // SKIP PUNKTUATIONS, MAYBE CREATING ANOTHER STRING WITHOUT,
    // AND THEN MAKE A VECTOR
    string unpunktuatedText;
    vector<string> text;
    vector<string> relations = relFileToVector();
    vector<vector<string>> splittedTempRelation;
    const char punktuationz[4] = {',','.',':',';'};
    char tempChar;
    char punktChar;

    bool pass = true;

    // check the record to cancel all punktuation
    for(int i = 0 ; i < record.size(); i++){
        tempChar = record[i];
        // for every char check if is a punktuation
        for(int j = 0 ; j < 4; j++){
            punktChar = punktuationz[j];
            if(tempChar == punktChar){
                pass = false;
                break;
            }
        }
        if(pass){
            unpunktuatedText += tempChar;
        }
        pass = true;
    }
    
    // TEXT VECTOR
    text = tools.strToVec(unpunktuatedText,' ');

    // check if the word is present somewhere in relations
    for(int i = 0 ; i < text.size(); i++){
        // skip the words smaller than 2 chars
        if(text[i].size() > 2){
            // getting all relations with this word
           splittedTempRelation = getRelationsFromConcept(text[i]);

           if(splittedTempRelation.size() > 0){
               // add relations to the result string
               for(int j = 0 ; j < splittedTempRelation.size(); j++){
                    result += splittedTempRelation[j][0];
               }
           }
        }
    }

    // avoid repetitions
    result = tools.trimRepetitions(result);

    return result;
}




