/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Hunter Bartholomew
 * Date        : 9/20/16
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that i have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

bool is_all_lowercase(const string &s) {

	//iterates through the string checking if each index is both a letter and lowercase
	for(unsigned i = 0; i < s.size(); ++i){
    	if(isalpha(s[i]) == 0 || islower(s[i]) == 0){
    		return false;
    	}
    }

	return true;
}
bool all_unique_letters(const string &s) {

	//initialize bit string
    unsigned bit_string = 0;

    for(unsigned i = 0; i < s.size(); ++i){
    	//subtract 'a' from letter in s, shift the bitstring that many bits, and it with 1, if its 1 then the letter has been seen before
    	if(((bit_string >> (s[i] - 'a')) & 1) == 1){
    		return false;
    	}

    	else{
    		//set new bitstring as 1, shift it to align with its index in the main bitstring
    		unsigned n = 1;
    		n = n << (s[i] - 'a');
    		//OR them so that the main bitstring now has a 1 in that index
    		bit_string |= n;
    	}
    }

    return true;
}

int main(int argc, char * const argv[]) {

	//if theres more than 2 args, throw error
	if (argc != 2) {
			cerr << "Usage: " << argv[0] << " <string>" << endl;
			return 0;
		}

	//if the string isnt all lowercase letters, throw error
	if(is_all_lowercase(argv[1]) == false){
    	cout << "Error: String must contain only lowercase letters." << endl;
    	return 0;
    }

	//check if letters are unique
    if(all_unique_letters(argv[1]) == true){
    	cout << "All letters are unique." << endl;
    }

    else{
    	cout << "Duplicate letters found." << endl;
    }

    return 0;
}
