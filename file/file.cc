#include <fstream> 
#include <iostream>
#include <vector>
#include "file.h"
#include "../tools/tools.h"

using namespace std;

vector<char> File::getFileContent(string path){
    vector<char> output;
    string line;
    string templine;
    // init input file stream
    ifstream file(path);

    if (file.is_open()){
        if (getline(file, line)) {
            templine = line.c_str();
            // load string templine in vector
            for(int i =0; i < templine.size(); i++){
                output.push_back(templine[i]); 
            }
        }
        file.close();
    }else{
         cout << "unable to open file "<< path <<" : CHECK FILE NAME error handling in file.cc line about 25"<< endl;
    }

    // if (file.is_open()) {
    //     while (getline(file, line)) {
    //         templine = line.c_str();
    //         output.push_back(templine); 
    //     }
    //     file.close();
    // }else{
    //     cout << "unable to open file:" << path << endl;
    // }

    // print file content
    //for(char i : fileContent){
    //    cout << i << " ";
    //}
    //cout << endl;
    
    return output;
}

bool File::fileCheck(string path){
    ifstream file(path);
    return file.is_open();
}

void File::makeFile(string path){
    ofstream outfile;
    outfile.open(path);

    // creating a string and copy all chars to be able to write in the file
    string abc = "";
    vector<char> standardTemplate = this->standardTemplate();
    const int SIZE = standardTemplate.size();
    for(int i = 0 ; i< SIZE ; i++){
        abc += standardTemplate[i];
    }

    outfile << abc << endl;
    outfile.close();

    // ./DATA/ 7 chars
    string newFileName;
    for(int i = 7; i < path.size(); i++){
        newFileName+= path[i];
    }

    // ADD NEW FILE TO PATHNAMES FILE
    string filename = PATH; filename+="FILENAMES.txt";    
    string fileNamesContent = vecToStr( getFileContent(filename) );

    bool fileExists = fileCheck(filename);
    // try if file research and pronting works
    if(!fileExists){
        makeFile(path);
    }
    // write new file in FILENAMES file
    fileNamesContent += newFileName+" ";
    outfile.open(filename);
    outfile << fileNamesContent;
    outfile.close();
}


// nicer would be with array.. but as..
vector<char> File::standardTemplate(){
    vector<char> standardTemplate;
    // begin  n char rel begin n rel
    // 000000 000000 000000    000
    // ... file content ...
    string beginString = "007686";
    
    for(int i = 0 ; i< 366 ; i++){
        // position of begin string
        for(int i = 0 ; i< MAX_N_DIGITS ; i++){
            standardTemplate.push_back(beginString[i]);
        }
        // string length
        for(int i = 0 ; i< MAX_N_DIGITS ; i++){
            standardTemplate.push_back('0');
        }
        //begin relations.. if nothing in same as begin string
        for(int i = 0 ; i< MAX_N_DIGITS ; i++){
            standardTemplate.push_back(beginString[i]);
        }
        // no relations .. 0 chars
        for(int i = 0 ; i< 3 ; i++){
            standardTemplate.push_back('0');
        }
    }
    return standardTemplate;
}

string File::vecToStr(vector<char> content){
    string str = "";
    const int SIZE = content.size();
    for(int i = 0 ; i< SIZE ; i++){
        str += content[i];
    }
    return str;
} 

vector<char> File::getIndex(vector<char> content){
    vector<char> index;
        for(int i = 0 ; i< INDEXSIZE ; i++){
        index.push_back(content[i]);
    }
    return index;
}

vector<string> File::dataOfDay(string date , vector<char> index){
    vector<string> data;
    vector<char> strings;
    string tempString;

    Tools tools;
    // search begin index
    // count day, get n of day from 01/01
    const int DAYCOUNT = dayCount(date);

    // format is:
    // begin  n char rel begin n rel
    // 000000 000000 000000    000
    const int FORMATSIZE = 21;

    // get begin of data
    int charBegin = (DAYCOUNT - 1) * FORMATSIZE;
    string charBeginStr = tools.itos(charBegin);
    data.push_back(charBeginStr);

    for(int i = 0; i < FORMATSIZE; i++){
        strings.push_back(index[charBegin+i]);
    }

    // for(int i = 0; i < strings.size(); i++){
    //     cout << strings[i] << endl;
    // }
    
    // split strings and add to vector and return
    for(int i = 0; i < 3; i++){
        for(int j = i*MAX_N_DIGITS; j < i*MAX_N_DIGITS + MAX_N_DIGITS; j++){
            tempString += strings[j];
        }
        data.push_back(tempString);
        tempString ="";
    }

    // last 3
    for(int i = 18; i < 21; i++){
        tempString += strings[i];
    }
    data.push_back(tempString);
    return data;
}

int File::dayCount(string date){
    int count = 0;
    
    //get day and mont from date as integer
    string strday; strday+= date[0]; strday += date[1];
    string strmonth; strmonth += date[2]; strmonth += date[3];
    const int DAY = stoi(strday);
    const int MONTH = stoi(strmonth);

    const int calender [12] = {31,29,31,30,31,30,31,31,30,31,30,31};

    for(int i = 0; i < MONTH -1; i++){
        count += calender[i];
    }
    count += DAY;

    return count;
}


void File::insertInDate(string date , string newContent , string relations){
    Tools tools;
    // get path from date
    string path = PATH;
    for(int i = 4; i < 8 ; i++){
        path += date[i];
    }
    path += ".txt";

    //get day and mont from date
    string day; day+= date[0]; day += date[1];
    string month; month += date[2]; month += date[3];

    const string DATE = day + month;
    const vector<char> CONTENT = getFileContent(path);

    // get index from CONTENT vector
    vector<char> INDEX = getIndex(CONTENT);

    // returns vector with: pos beagin index, pos begin char, n chars, pos begin relation, N relations
    vector<string> DATA = dataOfDay(DATE , INDEX);
    // format is:
    // begin  n char rel begin n rel
    // 000000 000000 000000    000

    // ACHTUNG!! WHEN 999 999 chars !!!

        // take index and change all the next data
        int newContentLength = newContent.length();
        int newRelationsLength = relations.length();

        // difference between the old char num and the new
            // new - old
        //  is the quantity of chars to move all the data
        // in DATA[2] is stored the old num of chars
        int contentCharsDifference = newContentLength - stoi(DATA[2]);
        int relationsCharsDifference = newRelationsLength - stoi(DATA[4]);

        // from position of begin index change the data of this date
        string beginIndex  = DATA[0]; 
        string positionOfString = DATA[1]; 
        string numberOfChars = DATA[2]; 
        string positionOfRelations  = DATA[3]; 
        string numberRelations  = DATA[4]; 

        int newRelationsPosition = stoi(positionOfRelations) + contentCharsDifference;
        string newRelationsPos = tools.padString(tools.itos(newRelationsPosition),MAX_N_DIGITS );
        string newDataForIndex = positionOfString + tools.padString(tools.itos(newContentLength),MAX_N_DIGITS) + newRelationsPos + tools.padString(tools.itos(newRelationsLength),3);
        
        // UPDATE CURRENT INDEX WITH DATA SAVED BEFORE
        int dayIndexBegin = stoi(beginIndex);
        for(int i = 0; i< 21; i++){
            INDEX[dayIndexBegin+i] = newDataForIndex[i];   
        }

        //#######################################################
        //MAYBE THAT NOT NEEDED..................................
        //
        // new position of relations
        //
        //// needs to be 
        // 31 12 has position of last char..
        // find the last char in the index
        // index, of the index
        int lastIndexRecord = (INDEXSIZE - FORMATSIZE);
        string beginRelationZ;
        cout << lastIndexRecord << endl;
        for(int i = lastIndexRecord; i < lastIndexRecord + CHARSOFNUMBER ; i++){
            beginRelationZ += INDEX[i];
         }
        // last got is the last char in the file
        cout << beginRelationZ << endl;
        int beginOfRelations = stoi( beginRelationZ );
        //
        //
        //
        //MAYBE UNTIL HERE NOT NEEDED..............................
        //#########################################################
        
        // CHANGE ALL THE OTHER INDEXES ACCORDING TO THE NEW INFO

        // place for all..
        vector<string> tempDataOfDay;
        int tempPositionOfString; //= DATA[1];  
        int tempPositionOfRelations;//  = DATA[3]; 
        int newPositionOfTempString;
        int newPositionOfTempRelations;
        string newTempDataForIndex;
        string tempBeginIndex;
        int tempBeginIndexInt;
        string tempMonth;
        string generateDatum;
        int dayConunter=1;

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
                tempDataOfDay = dataOfDay(generateDatum , INDEX);

                // get old data
                tempPositionOfString= stoi( tempDataOfDay[1] );
                tempPositionOfRelations = stoi (tempDataOfDay[3] );

                //IF MONTH LESS, CHANGE ONLY POSITION OF RELATIONS
                // IF MORE , POSITION OF STRING AND ALSO RELATIONS
                if(i <= stoi(month) && dayConunter <= stoi(day)  ){
                    newPositionOfTempRelations = beginOfRelations+contentCharsDifference;
                    newPositionOfTempString = tempPositionOfString;
                }else{
                    newPositionOfTempString = tempPositionOfString + contentCharsDifference;
                    newPositionOfTempRelations = tempPositionOfRelations + contentCharsDifference + relationsCharsDifference;
                }

                //create new string for index
                newTempDataForIndex = tools.padString(tools.itos(newPositionOfTempString),MAX_N_DIGITS) + tempDataOfDay[2] + tools.padString(tools.itos(newPositionOfTempRelations),MAX_N_DIGITS) + tempDataOfDay[4];
                
                // get position of begin index char
                tempBeginIndexInt = stoi(tempDataOfDay[0]);
                for(int i = 0; i< 21; i++){
                    INDEX[tempBeginIndexInt+i] = newTempDataForIndex[i];   
                }
                dayConunter++;
                generateDatum="";
            }
            dayConunter = 1;
        }
        // UPDATE THE CURRENT DAY 
        //             !!!        AGAIN       !!!
        //                               AFTER ALL DAYS
        dayIndexBegin = stoi(beginIndex);
        for(int i = 0; i< 21; i++){
            INDEX[dayIndexBegin+i] = newDataForIndex[i];   
        }
        // day stuff is been ovewritten in the previous loop...

        // SPLIT ALL PARTS FROM CONTENT AND CREATE NEW CONTENT
        vector<char> indexToPhrase;
        vector<char> newPhrase;
        vector<char> endOldPhraseToRelations;
        vector<char> newRelations;
        vector<char> endNewRelationsToEndFile;
        
        for(int i= INDEX.size(); i < stoi(positionOfString); i++ ){
            indexToPhrase.push_back(CONTENT[i]);
        }

        for(int i=0; i < newContent.size(); i++ ){
            newPhrase.push_back(newContent[i]);
        }

        for(int i= stoi(positionOfString) + stoi(numberOfChars) ; i < stoi(positionOfRelations); i++ ){
            endOldPhraseToRelations.push_back(CONTENT[i]);
        }

        for(int i=0; i < relations.size(); i++ ){
            newRelations.push_back(relations[i]);
        }

        for(int i=stoi(positionOfRelations) + stoi(numberRelations); i < CONTENT.size(); i++ ){
            endNewRelationsToEndFile.push_back(CONTENT[i]);
        }

        //create array of all vector for looping throught
        const vector<char> newCompleteFile [6] = { INDEX, indexToPhrase, newPhrase, endOldPhraseToRelations, newRelations, endNewRelationsToEndFile};
        // WRITE IN FILE BACK
        ofstream outfile;
        outfile.open(path);
        for (int i = 0; i < 6; i++){
            for(int j = 0; j < newCompleteFile[i].size(); j++){
                outfile << newCompleteFile[i][j];
            }   
        }
        outfile << endl;
        outfile.close();
}
