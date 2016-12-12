/*Hunter Bartholomew
 * 9/15/16
 * I pledge my honor that i have abided by the stevens honor system
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
    	//run the sieve
        sieve();
        num_primes_ = count_num_primes();
        display_primes();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
    	//find the width of the max prime and how many primes fit on a row
    	const int max_prime_width = num_digits(max_prime_),
    			primes_per_row = 80 / (max_prime_width + 1);
    	int count = 0;
    	cout << endl;
    	cout << "Number of primes found: " << num_primes() << endl;
    	cout << "Primes up to " <<  limit_ << ":" << endl;

    	//output formatting
    	for(int i = 2; i <= limit_; i++){
    		if(num_primes() <= 25 && is_prime_[i] && i == max_prime_) {
    			cout << i;
    			return;
    		}
    		else if(num_primes() <= 25 && is_prime_[i]){
    			cout << i << " ";
    		}
    		else if(count == primes_per_row - 1 && is_prime_[i]){
    			std::cout << std::setw(max_prime_width);
    			cout << i << endl;
    			count = 0;
    		}
    		else if(i == max_prime_){
    			std::cout << std::setw(max_prime_width);
    			cout << i << endl;
    			return;
    		}

    		else if(is_prime_[i]){
    			count++;
    			std::cout << std::setw(max_prime_width);
    			cout << i << " ";
    		}
    	}
    	cout << endl;
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
    	//counts the number of primes found
    	int numprimes = 0;
    	for(int i = 0; i <= limit_; i++){
    		if(is_prime_[i]){
    			numprimes++;
    		}
    	}
    	return numprimes;
    }

    int num_digits(int num) const {
    	//counts number of digits in the largest prime
    	int count = 0;
    	for(int i = num; i>=1; i /= 10){
    		count++;
    	}
    	return count;
    }

    void sieve() {
    	//set 0 and 1 to false
    	is_prime_[0] = 0;
    	is_prime_[1] = 0;

    	//set every other value to true
    	for(int i = 2; i <= limit_; i++){
    		is_prime_[i] = 1;
    	}

    	//checks if number is prime, if it isn't, set its value to false
    	for (int i = 2; i <= sqrt(double(limit_)); i++){
    		if(is_prime_[i]){
    			for(int j = pow(double(i),2.0);  j <= limit_ ;j += i){
    				is_prime_[j] = 0;
    			}
    		}
    	}

    	//find the largest prime by starting at the end of the array and working backwards
    	for(int i = limit_; i >= 2; --i){
    		if(is_prime_[i]){
    			max_prime_ = i;
    			break;
    		}
    	}
    }
};

int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    //run the sieve and print output
    PrimesSieve((int)limit);
    return 0;
}
