#include <iostream>
#include "crypt.h"

using namespace std;

// !! IMPORTANT !!
// FIRST SHUFFLE THE NEW ALPHABET WITH PASSWORD,
// cripted text will be created from the new shuffled alphabet
// then crypt.. or decrypt..

// string newAlphabet = crypt.shuffle(passwd, abc);
// string crypted = crypt.encrypt(input);
// cout << crypted << endl;
// cout << crypt.decrypt(crypted) << endl;

int Crypt::findex(const char toSearch, string where){
    int ind;
        // searching indexes
        for (int j = 0; j < where.size(); j++){
            //cout << where[j] << endl;
            if (toSearch == where[j]){
                // save index
                ind = j;
            }
        }
    return ind;
}

string Crypt::invert(string str){
    string reverse="";
    for (int i = str.size()-1; i>=0; i--){
        reverse += str[i];
    }
    return reverse;
}

string Crypt::shuffle(string password){
    string shuffled = "";
    // shuffle alphabet
    string half1 ="";
    string half2 ="";
    shuffled = ABC;
    int index;
    for (int i = 0; i < password.size(); i++){
        // take from shuffled index found until end and add to half1
        index = findex(password[i],shuffled);
        cout << shuffled[index] <<' '<< index << endl;
        //loop the string from the letter until the end
        for (int j = index; j < ABC.size(); j++){
            // and add to half1, the second half
            half1 += shuffled[j];
        }
        //loop the string from the begin until the letter
        for (int k = 0; k < index; k++){
            // and add to half2, the first half
            half2 += shuffled[k];
        }
        // take from begin shuffled to index and add to half2
        shuffled = half1 + invert(half2);
        half1 = "";
        half2 = "";
        // cout << "  " << endl;
        // cout << " status of new alphabet...  " << endl;
        // cout << shuffled << endl;
    }
    newAlphabet = shuffled;
    return shuffled;
}

string Crypt::encrypt(string input){
    int indexInput;
    string crypted = input;
    for (int i = 0; i < input.size(); i++){
        //find the index of the letter input in old dictionary
        indexInput = findex(input[i],ABC);
        //knowing the index in standard dictionary, change with new
        crypted[i]= newAlphabet[indexInput];
    }
    return crypted;
}

string Crypt::decrypt(string crypted){
    int indexCrypted;
    string decryptd = crypted;
    for (int i = 0; i < crypted.size(); i++){
        //find the index of the letter crypted in old dictionary
        indexCrypted = findex(crypted[i],newAlphabet);
        //knowing the index in standard dictionary, change with new
        decryptd[i]= ABC[indexCrypted];
    }
    return decryptd;
}
