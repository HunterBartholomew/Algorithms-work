/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Hunter Bartholomew
 * Version     : 1.0
 * Date        :11/2/16
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that i have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long inv_count = 0;
	//nested for loop, comparing i to each element after it
	for (int i = 0; i < length - 1; i++)
		for (int j = i+1; j < length; j++)
			if (array[i] > array[j])
				inv_count++;

	  return inv_count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	//create new scratch array
	int* scratch = new int[length];
	return mergesort(array, scratch, 0, length-1);
}

static long mergesort(int array[], int scratch[], int low, int high) {
	long inv_count = 0;
	if(low < high){
		int mid = (low + high)/2;
		//recursive calls on each half
		inv_count += mergesort(array, scratch, low, mid);
		inv_count += mergesort(array, scratch, mid+1, high);
		int L = low;
		int H = mid + 1;
		for(int k = low; k <= high; ++k){
			if(L <= mid && (H > high || array[L] <= array[H])){
				scratch[k] = array[L];
				++L;
			}
			else{
				scratch[k] = array[H];
				++H;
				//increase count when merging
				inv_count += mid - L + 1;
			}
		}
		for(int j = low; j <= high; ++j){
			array[j] = scratch[j];
		}
	}
	return inv_count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

	if(argv[1] != NULL){
		string slow = argv[1];
		if(argc > 2){
			cout << "Usage: ./inversioncounter [slow]" << endl;
			return 0;
		}
		if(slow != "slow"){
			cout << "Error: Unrecognized option '" << slow << "'." << endl;
			return 0;
				}
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    //checks if there are no numbers entered
    if(values.size() == 0){
    	cout << "Error: Sequence of integers not received."; return 0;
    }

    //runs either the slow or fast version
    if(argv[1] != NULL)
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    else
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;

    return 0;
}
