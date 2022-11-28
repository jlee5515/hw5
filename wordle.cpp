// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper (std::string& in, string& gray, size_t loc, const std::set<std::string>& dict, size_t blanks, std::set<std::string>& words){ 
    if(blanks < gray.length()){ 
        return;
    }
    if(loc == in.length()){
        if( (gray == "") && ( dict.find(in)!= dict.end()) ){
            words.insert(in);
        }
        return;
    }
    if(in[loc] == '-'){
        for(char temp = 'a'; temp <= 'z'; temp++){ //iterate throught the alphabets
            if(gray.find(temp) != string::npos){
                in[loc] = temp;
                gray.erase(gray.find(temp),1);
                wordleHelper(in, gray, loc + 1, dict, blanks - 1, words);
                in[loc] = '-';
                gray += temp;
            }
            else if(gray.find(temp == string::npos)){ //alphabet not found; error because unsigned int and char
                in[loc] = temp;
                wordleHelper(in, gray, loc + 1, dict, blanks - 1, words);
                in[loc] = '-';
            }
        }
    }
    else if(in[loc] != '-'){
        wordleHelper(in, gray, loc + 1, dict, blanks, words);
        return;
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    int blanks = 0;
    std::set<std::string> words;
    for(unsigned int i = 0; i < in.length(); i ++){
        if(in[i] == '-'){ //has to be '-'
            blanks += 1;
        }
    }
    std::string tempGray = floating;
    std::string tempIn = in;
    wordleHelper(tempIn, tempGray, 0, dict, blanks, words);
    return words;
}

// Define any helper functions here
//pass in dictionary
//pass in set of answers
//pass in number of dashes and decrease every time you use one