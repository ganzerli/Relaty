#include "tools.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string Tools::itos(int num){
    const char table[] ={'0','1','2','3','4','5','6','7','8','9'};
    int num_ = num;
    string strNum;
    while(num_/10 > 0){
        strNum += table[num_%10];
        num_ /= 10;
    }
    // concat remaining
    strNum += table[num_%10];
    string reverse;
    // regverse string 
    for (int i = strNum.size()-1; i>=0; i--){
        reverse += strNum[i];
    }
    return reverse;
}

string Tools::invert(string str){
    string reverse="";
    for (int i = str.size()-1; i>=0; i--){
        reverse += str[i];
    }
    return reverse;
}

string Tools::padString(string str, int num){
    string pad;
    for(int i =0; i< num; i++){
        pad+= "0";
    }
    int rest = pad.size()-str.size();
    for(int i = str.size(); i>=0; i--){
        pad[i + rest] = str[i];
    }
    return pad;
}

int Tools::stoi9(string num){
    const char table[] ={'0','1','2','3','4','5','6','7','8','9'};
    const int decimal[] ={1,10,100,1000,10000,100000,1000000,10000000,100000000};

    int maxNum = 999999999;

    for(int i = 0; i< num.size(); i++){
        ///
    }

    // int can have 9 digits
    return 12345;
}

vector<string> Tools::strToVec(string frase, char divisor){
    vector<string> strings;
    string tempString;

    for(int i = 0; i < frase.size(); i++){
        if(frase[i] == divisor ){
            strings.push_back(tempString);
            tempString = "";
        }else if(i == frase.size()-1){
            tempString += frase[i];
            strings.push_back(tempString);
            tempString = "";
        }else{
            tempString+=frase[i];
        }

    }
    return strings;
}

string Tools::trimRepetitions(string str){
    string result;
    string already = "";
    char tempChar;
    char alreadyTempChar;

    bool notThere = true;

    for(int i = 0; i < str.size(); i++){
        tempChar = str[i];

        for(int j = 0; j < already.size(); j++){
            alreadyTempChar = already[j];
            if(tempChar == alreadyTempChar){
                notThere = false;
                break;
            }
        }
        if(notThere){
            // add it
            result += tempChar;
            already += tempChar;
        }
        notThere = true;
    }
    return result;
}

bool Tools::isNum(string strNum){
    bool isNum = true;
    bool pass = false;

    const char table[10] ={'0','1','2','3','4','5','6','7','8','9'};
    char tempChar;
    char tempTableChar;

    // IF ONCE IS NOT A NUMBER THEN FLAG AS FALSE
    for(int i =0; i< strNum.size(); i++){
        tempChar = strNum[i];
        // find if the temp char is a number
        for(int j =0; j < 10; j++){
            tempTableChar = table[j];
            if(tempChar == tempTableChar){
                pass = true;
                break;
            }
        }
        // ever been a not NUMBER??
        if(!pass){
            isNum = false;
            break;
        }
        pass = false;
    }
    return isNum;
}

// FORMAT dd mm yyyy
bool Tools::isDatum(string strNum){
    bool isDatum = false;
    if(strNum.size() == 8 &&  isNum(strNum)){
        // better check also if 
            // first2 are < then 31,
            // month < then 12.. but for now..
            isDatum = true;
    }
    return isDatum;
}

vector<vector<string>> Tools::filterVecVec(vector<vector<string>> vecVec, int index, string logicGate, string possibilities){
    vector<vector<string>> filtered;
    Tools tools;

    bool pass = false;
    vector<string> poss = tools.strToVec(possibilities, ' ');
    vector<string> takenResults;
    int counter = 0;

    string tempString;
    string tempString2;

    if(logicGate == "and"){
        // if it has all the requirements add
        for(int i = 0 ; i < vecVec.size(); i++){
            // for every record in the vecVec, check if in possibilities
            // get the possibilities from the RESULT, present vector
            tempString = vecVec[i][index];
            takenResults = tools.strToVec(tempString, ' ');

            for(int j = 0 ; j < poss.size() ; j++){
                tempString = poss[j];

                for(int k = 0 ; k < takenResults.size() ; k++){
                    // check if in the results there is a possibility
                    tempString2 = takenResults[k];
                    if(tempString == tempString2){
                        // set true if appears a possibilitiy
                        //  pass = true;
                        counter ++;
                        break;
                    }
                }

                // if all possibilities found
                if(counter == poss.size()){
                    filtered.push_back(vecVec[i]);
                }

            }   
            counter = 0;
        }

    }else if(logicGate == "or"){
        // add at avery requirement found
        for(int i = 0 ; i < vecVec.size(); i++){
            // for every record in the vecVec, check if in possibilities
            // get the possibilities from the RESULT, present vector
            tempString = vecVec[i][index];
            takenResults = tools.strToVec(tempString, ' ');

            for(int j = 0 ; j < poss.size() ; j++){
                tempString = poss[j];

                for(int k = 0 ; k < takenResults.size() ; k++){
                    // check if in the results there is a possibility
                    tempString2 = takenResults[k];

                    if(tempString == tempString2){
                        // set true if appears a possibilitiy
                        pass = true;
                        break;
                    }
                }

                if(pass){
                    break;
                }
            }   

            // if all possibilities found
            if(pass){
                filtered.push_back(vecVec[i]);
                pass = false;
            }
        }
       

    }else if(logicGate == "not"){
        // add if no one of possibilities
        for(int i = 0 ; i < vecVec.size(); i++){
            // for every record in the vecVec, check if in possibilities
            // get the possibilities from the RESULT, present vector
            tempString = vecVec[i][index];
            takenResults = tools.strToVec(tempString, ' ');

            for(int j = 0 ; j < poss.size() ; j++){
                tempString = poss[j];
                for(int k = 0 ; k < takenResults.size() ; k++){
                    // check if in the results there is a possibility
                    tempString2 = takenResults[k];
                    if(tempString == tempString2){
                        // set true if appears a possibilitiy
                        pass = true;
                        break;
                    }
                }
                if(pass){
                    break;
                }
            }   

            // if all possibilities found
            if(!pass){
                filtered.push_back(vecVec[i]);
            }else{
                pass = false;
            }
        }

    }

    return filtered;
}
