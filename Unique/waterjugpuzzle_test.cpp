/*
 * water_jug.cpp
 *
 *  Created on: Oct 4, 2016
 *      Author: hunter
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iterator>


using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;

    vector<string> directions;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

bool operator==(const State& s1, const State& s2)
{
	if(s1.a == s2.a && s1.b == s2.b && s1.c == s2.c)
		return true;
	return false;
}

bool dupe(State current, vector<State> states){
	for (unsigned i = 0; i < states.size(); i++){
			if (current == states[i]){
				return false;
			}
		}
	return true;
}
State clone_state(const State& state){
	State temp(int(state.a), int(state.b), int(state.c));
	return temp;
}


vector<State> final;

void get_steps(State current, State goal, vector<string> steps, vector<State> states, State caps, int level){

	if(current == goal){
		if(final.size() == 0)
			final = states;
		if(states.size() < final.size()){
			final = states;
			return;
		}

	}

	State temp_current = clone_state(current);

	//C to A
	if(caps.a != temp_current.a && temp_current.c != 0){
		if(temp_current.c + temp_current.a > caps.a){
			//if(dupe(State(caps.a, current.b, temp_current.c - (caps.a- temp_current.a)), states))
				//states.push_back(State(caps.a, temp_current.b, temp_current.c - (caps.a- temp_current.a)));
				//get_steps( State(caps.a, temp_current.b, temp_current.c - (caps.a- temp_current.a)), goal, steps, states, caps, level + 1);
			temp_current.c = temp_current.c - (caps.a- temp_current.a);
			temp_current.a = caps.a;
		}
		else {
			//if(dupe(State(temp_current.a + temp_current.c, temp_current.b, 0), states)){
			//states.push_back(State(temp_current.a + temp_current.c, temp_current.b, 0));
			//get_steps( State(temp_current.a + temp_current.c, current.b, 0), goal, steps, states, caps, level + 1);
			temp_current.a = temp_current.a + temp_current.c;
			temp_current.c = 0;
		}
		steps.push_back("C");
		steps.push_back("A");
		if(dupe(temp_current, states)){
				states.push_back(temp_current);
				get_steps(temp_current, goal, steps, states, caps, level + 1);
				}

	}

	temp_current = clone_state(current);
	//B to A
	if(caps.a != temp_current.a && temp_current.b != 0){
		if(temp_current.b + temp_current.a > caps.a){
			if(dupe(State(caps.a, temp_current.b - (caps.a- temp_current.a), temp_current.c), states))
				states.push_back(State(caps.a, temp_current.b - (caps.a- temp_current.a), temp_current.c));
				get_steps( State(caps.a, temp_current.b - (caps.a- temp_current.a), temp_current.c), goal, steps, states, caps, level + 1);
			//temp_current.b = temp_current.b - (caps.a- temp_current.a);
			//temp_current.a = caps.a;
		}
		else{
			//temp_current.a = temp_current.a + temp_current.b;
			temp_current.b = 0;
		}
		steps.push_back("B");
		steps.push_back("A");
		//cout << temp_current.to_string() << endl;
		if(dupe(temp_current, states)){
					states.push_back(temp_current);
					get_steps(temp_current, goal, steps, states, caps, level + 1);

				}
		else
			states.pop_back();
	}

	temp_current = clone_state(current);

	//C to B
	if(caps.b != temp_current.b && temp_current.c != 0){
		if(temp_current.c + temp_current.b > caps.b){
			temp_current.c = temp_current.c - (caps.b - temp_current.b);
			temp_current.b = caps.b;
		}
		else{
			temp_current.b = temp_current.b + temp_current.c;
			temp_current.c = 0;
		}
		steps.push_back("C");
		steps.push_back("B");

		if(dupe(temp_current, states)){

			states.push_back(temp_current);

			get_steps(temp_current, goal, steps, states, caps, level + 1);

		}
	}

	temp_current = clone_state(current);
	//A to B
	if(caps.b != temp_current.b && temp_current.a != 0){
		if(temp_current.a + temp_current.b > caps.b){
			temp_current.a = temp_current.a - (caps.b - temp_current.b);
			temp_current.b = caps.b;
		}
		else{
			temp_current.b = temp_current.b + temp_current.a;
			temp_current.a = 0;
		}
		steps.push_back("A");
		steps.push_back("B");
		if(dupe(temp_current, states)){
					states.push_back(temp_current);

					get_steps(temp_current, goal, steps, states, caps, level + 1);

				}
	}


	temp_current = clone_state(current);
	//B to C
	if(caps.c != temp_current.c && temp_current.b != 0){
		if(temp_current.b + temp_current.c > caps.c){
			temp_current.b = temp_current.b - (caps.c - temp_current.c);
			temp_current.c = caps.c;
		}
		else{
			temp_current.c = temp_current.c + temp_current.b;
			temp_current.b = 0;
		}
		steps.push_back("B");
		steps.push_back("C");
		if(dupe(temp_current, states)){
							states.push_back(temp_current);

							get_steps(temp_current, goal, steps, states, caps, level + 1);

						}
	}

	temp_current = clone_state(current);
	//A to C
	if(caps.c != temp_current.c && temp_current.a != 0){
		if(temp_current.a + temp_current.c > caps.c){
			temp_current.a = temp_current.a - (caps.c - temp_current.c);
			temp_current.c = caps.c;
		}
		else{
			temp_current.c = temp_current.c + temp_current.a;
			temp_current.a = 0;
		}
		steps.push_back("A");
		steps.push_back("C");
		//cout << temp_current.to_string() << endl;
		if(dupe(temp_current, states)){
					states.push_back(temp_current);

					get_steps(temp_current, goal, steps, states, caps, level + 1);

				}
	}
}


int main(int argc, char * const argv[]) {
	string letters[7] = {"", "A", "B", "C", "A", "B", "C"};


	if (argc != 7) {
				cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
				return 0;
			}

	for(int i = 1; i <= 3; ++i){
		istringstream iss;
		int m;
		iss.str(argv[i]);
		if (!(iss >> m) || m <= 0){
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letters[i] << "." << endl;
			return 0;
		}
	}

	for(int i = 4; i <= 6; ++i){
		istringstream iss;
		int m;
		iss.str(argv[i]);
		if (!(iss >> m) || m < 0){
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letters[i] << "." << endl;
			return 0;
		}
	}

	vector <int> values;

	for(int i = 1; i <= 6; ++i){
		istringstream iss;
		int m;
		iss.str(argv[i]);
		iss >> m;
		values.push_back(m);
	}

	for (int i = 0; i < 3; ++ i){
		if(values[i+3] > values[i]){
			cerr << "Error: Goal cannot exceed capacity of jug " << letters[i+1] << "." << endl;
			return 0;
		}
	}

	if((values[3] + values[4] + values[5]) != values[2]){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 0;
	}

	/*if(5 == 6){
		//to do
		return 0;
	}
	else{
		cout << "No solution." << endl;
		return 0;
	}*/

	State current(0, 0, values[2]);
	State goal(values[3], values[4], values[5]);
	vector<State> states;
	vector<string> steps;
	State caps(values[0], values[1], values[2]);

	int level = 0;

	get_steps(current, goal, steps, states, caps, level);
	if(final.size() == 0){
		cout << "No solution.";
		return 0;
	}
	for(unsigned i = 0; i < final.size(); i++){

					cout << final[i].to_string() << endl;
						}

	return 0;
}
