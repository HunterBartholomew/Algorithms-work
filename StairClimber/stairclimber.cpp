/*Hunter Bartholomew
 * 9/27/16
 * i pledge my honor that i have abided by the stevens honor system
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;
vector< vector<int> > out;
vector<int> in;

vector< vector<int> > get_ways(int num_stairs) {
	//stairclimber algorithm
	    if (num_stairs <= 0) {
	        out.push_back(in);
	    }
	    if (num_stairs >= 1) {
	        in.push_back(1);
	        get_ways(num_stairs-1);
	        in.pop_back();
	    }
	    if (num_stairs >= 2) {
	        in.push_back(2);
	        get_ways(num_stairs-2);
	        in.pop_back();
	    }
	    if (num_stairs >= 3) {
	        in.push_back(3);
	        get_ways(num_stairs-3);
	        in.pop_back();
	    }

	    return out;
	}

void display_ways(const vector< vector<int> > &ways) {
	//gets the number of digits in the size of the vector of ways
	int length = 1, num = ways.size();
	while(num > 10){
		num /= 10;
		++length;
	}

    for (unsigned int i = 0; i < ways.size(); i++) {
    	//right aligns the numbers in the output
    	cout << right << setw(length) << i+1 << ". " << "[";
    	//prints out the elements of the vector
    	for (unsigned int j = 0; j < ways[i].size(); j++) {
            if (j != ways[i].size()-1)
                cout << ways[i][j] << ", ";
            else
                cout << ways[i][j];
        }
        cout << "]" << endl;
    }
}
int main(int argc, char * const argv[]) {

	vector< vector<int> > ways;
	istringstream iss;
	int m;

	//checks if theres more or less than 2 arguments
	if (argc != 2) {
				cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
				return 0;
			}
	iss.str(argv[1]);

	//checks if the argument is an int
	if (!(iss >> m)){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 0;
	}

	//checks if the argument is a positive int
	if(m < 0){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 0;
	}

	ways = get_ways(m);

	//make sure we're using proper grammar
	if(ways.size() == 1)
		cout << ways.size() << " way to climb " << argv[1] << " stair." << endl;

	else
		cout << ways.size() << " ways to climb " << argv[1] << " stairs." << endl;

	display_ways(ways);
	return 0;
}
