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
