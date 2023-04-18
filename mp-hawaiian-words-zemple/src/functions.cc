#include "functions.hpp"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;


bool WhetherHawaiian (string input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        
        if (input[i] != 'a' && input[i] != 'e' && input[i] != 'i' && input[i] != 'o' && input[i] != 'u' && input [i] != 'w' && input[i] != 'p' && input[i] != 'k' 
        && input[i] != 'h' && input[i] != 'l' && input[i] != 'm' && input[i] != 'n' && input[i] != ' ' && input[i] != '\'') {
            return false;
        }
    }
    return true;
}

string HelperA(string input, unsigned int i) {
    string output;

    if (input[i + 1] == 'e' || input[i + 1] == 'i') {
        output += "eye-";
    }
    else if (input[i + 1] == 'o' || input[i + 1] == 'u') {
        output += "ow-";
    }
    else if (i == input.length() - 1 || input[i+1] == ' ' || input[i+1] == '\'') {
        output += "ah";
    }
    else {
        output += "ah-";
    }
    return output;
}

string HelperE(string input, unsigned int i) {
    string output;

    if (input[i + 1] == 'i') {
        output += "ay-";
    }
    else if (input[i + 1] == 'u') {
        output += "eh-oo-";
    }
    else if (input[i+1] == ' ' && isalpha(input[i+2]) != 0) {
        output += "eh";
    }
    else {
        output += "eh-";
    }
    return output;
}

string HelperI(string input, unsigned int i) {

    string output;
    
    if (i == 0 || (input [i-1] != 'a' && input [i-1] != 'e' && input [i+1] != 'u' )) {
        output += "ee-";
    }
    else if (input[i+1] == 'u') {
        output += "ew-";
    }
    else if (input[i-1] == 'a' || input[i-1] == 'e') {
        output += "";
    }          
    return output;
}
string HelperO(string input, unsigned int i) {
    string output;

    if (input[i + 1] == 'i') {
        output += "oy-";
    }
    else if (input[i + 1] == 'u') {
        output += "ow-";
    }
    else if (input[i+1] == ' ' && isalpha(input[i+2]) != 0) {
        output += "oh";
    }
    else {
        output += "oh-";
    }
    return output;
}


string Hawaiian(string str) {
    string output;
    string input;
    for (unsigned int i = 0; i < str.length(); i++) {
        input += (char)tolower(str[i]);
    }
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == 'p' || input[i] == 'k' || input[i] == 'h' || input[i] == 'l' || input[i] == 'm' || input[i] == 'n' || input[i] == ' ' || input[i] == '\'') {
            output.push_back(input[i]);
        }
        if (input[i] == 'w') {
            if (i != 0 && (input[i - 1] == 'i' || input[i - 1] == 'e')) {
                output.push_back('v');
            }
            else {
                output.push_back('w');
            }
        }
        if (input[i] == 'a') {output += HelperA(input,i);}
        if (input[i] == 'e') {output += HelperE(input,i);}
        if (input[i] == 'i') {output += HelperI(input,i);}
        if (input[i] == 'o') {output += HelperO(input,i);}
        
        if (input[i] == 'u') {
            if (input[i-1] == 'a') {
                continue;
            }
            else if (input[i + 1] == 'i') {
                output += "ooey-";
            }
            else {
                output += "oo-";
            }
        }
    }
    return output;
}

void Result(string str) {
    string input;

    for (unsigned int i = 0; i < str.length(); i++) {
        input += (char)tolower(str[i]);
    } 
    if (!WhetherHawaiian(input)) {
        std::cout << input << " contains a character not a part of the Hawaiian language." << std::endl;
    }
    else {
        std::cout << Hawaiian(input) << std::endl;
    }
}