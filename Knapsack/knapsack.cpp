/*
 * knapsack.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: hunter
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Item {
	unsigned int item_number, weight, value;
	string description;
	explicit Item(const unsigned int item_number,
			const unsigned int weight,
			const unsigned int value,
			const string &description) :
		 item_number(item_number),
		 weight(weight),
		 value(value),
		 description(description) { }
	friend std::ostream& operator<<(std::ostream& os, const Item &item) {
		os << "Item " << item.item_number << ": " << item.description
				<< " (" << item.weight
				<< (item.weight == 1 ? " pound" : " pounds") << ", $"
				<< item.value << ")";
		os.flush();
		return os;
	}
};

void display_inv(int cap, vector<Item> inv){

	cout << "Candidate items to place in knapsack:" << endl;

	for (unsigned int i = 0; i < inv.size(); i++) {
		cout << "   " << inv[i] << endl;
	}

    cout << "Capacity: " << cap;
    if (cap == 1)
        cout << " pound";
    else
        cout << " pounds";
    cout << endl;

}
//Displays Used Items
void display_used(vector<Item> used){

	unsigned int weight = 0, value = 0;
	//if nothing can be placed in the knapsack
	if(used.size() == 0)
		cout << "Items to place in knapsack: None" << endl;

	else{
		cout << "Items to place in knapsack:" << endl;

		for (int i = used.size() - 1; i >= 0; i--) {
			weight += used[i].weight;
			value += used[i].value;
			cout << "   " << used[i] << endl;
		}
	}

	cout << "Total weight: " << weight;

    if (weight == 1)
        cout << " pound";
    else
        cout << " pounds";

    cout << endl;
	cout << "Total value : $" << value << endl;


}

//Finds Used Items
void find_used(int cap, vector<Item> inv, int** arr){

	int i = inv.size(), j = cap;
	vector<Item> used;

	while (i > 0 && j > 0) {
		if (arr[i][j] != arr[i - 1][j]) {
			used.push_back(inv[i - 1]);
			j -= inv[i - 1].weight;
			i--;
		}
		else
			i--;
	}

	display_used(used);

}

//Solves the problem dynamically
void solve(int capacity, vector<Item> inventory) {

	unsigned int cap = capacity;
	int **array = new  int*[inventory.size() + 1];

	for (unsigned int i = 0; i < inventory.size() + 1; i++) {

		array[i] = new  int[capacity + 1];

		for (unsigned int j = 0; j < cap + 1; j++) {

			if (j == 0 || i == 0)
				array[i][j] = 0;

			else {

				if (j < inventory[i-1].weight)
					array[i][j] = array[i-1][j];

				else {

					int use_it = inventory[i - 1].value + array[i - 1][j - inventory[i - 1].weight];
					int lose_it = array[i-1][j];

					if (use_it > lose_it) {
						array[i][j] = use_it;
					}
					else {
						array[i][j] = lose_it;
					}
				}
			}
		}
	}

	find_used(capacity, inventory, array);

	for (unsigned int k = 0; k < inventory.size() + 1; k++) {
		delete [] array[k];
	}

	delete [] array;
}

int main(int argc, char * const argv[]){

	//error checking
		if (argc != 3) {
			cerr << "Usage: " << argv[0] << " <capacity> <filename>" << endl;
			return 0;
		}

		istringstream iss;
		int cap;
		iss.str(argv[1]);

		//checks if the argument is a positive int
		if (!(iss >> cap) || cap < 0){
			cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
			return 0;
		}

		//check if file exists
		string filename = argv[2];
		ifstream file(filename.c_str());
		if (!file){
			cout << "Error: Cannot open file '" << argv[2] << "'." << endl;
			return 0;
		}

		//get each line of the text file
    	vector<string> result;
		std::string str;
		    while (std::getline(file, str)){
		    	std::stringstream ss(str);
		    	while(ss.good()){
		    	    string substr;
		    	    getline( ss, substr, '\n' );
		    	    result.push_back(substr);
		    	}
		    }

		    vector<Item> items;
		    unsigned int item_num = 1;

		    for(unsigned i=0; i < (result.size()); i++){
		    	int weight, value;
		    	string name, weightString, valueString;
		    	string line = result.at(i);
	    		int count = 0;

		    	for(unsigned int j = 0; j < line.length(); ++j){
		    		if(line[j] == ','){
		    			count ++;
		    		}
		    	}
		    	//make sure each line has 3 values
		    	if(count != 2){
		    		cout << "Error: Line number " << i+1 << " does not contain 3 fields." << endl;
		    		return 0;
		    	}
		    	vector<string> info;
		    	std::stringstream myStream(result.at(i));
		    	while(myStream.good()){
		    		string substr;
		    		getline(myStream, substr, ',' );
		    		info.push_back(substr);
		    	}
		    	name = info[0];

		    	//check for invalid weights and values
		    	istringstream iss;
		    	iss.str(info[1]);
		    	if((!(iss >> weight)) || weight < 0){
		    		cout << "Error: Invalid weight '" << info[1] << "' on line number " << item_num << "." << endl;
		    		return 0;

		    	}
		    	istringstream iss2;
		    	iss2.str(info[2]);
		    	if((!(iss2 >> value)) || value < 0){
		    		cout << "Error: Invalid value '" << info[2] << "' on line number " << item_num << "." << endl;
		    		return 0;
		    	}

		    	items.push_back(Item(item_num, weight, value, name));
		    	item_num++;
		    }

		    display_inv(cap, items);
		    solve(cap, items);
		    return 0;
	}
