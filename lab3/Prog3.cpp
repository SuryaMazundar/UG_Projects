/* Program Name: Prime Number Calculator
 * Name: Surya Teja Mazundar
 * Professor: Dr. Jens Gregor
 * NetID: smazunda
 * Student ID: 000718553
 * Sources: TA Sydney, TA Zac
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Support.h"

using namespace std;

int main(int argc, char* argv[]) {

	// Determines output
	bool sort_output = false;
	bool unique_output = false; 
	bool verbose_mode = false;

	// For command line arguements which enables if that particular command is provided
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];

		if (arg == "-sorted") {
			sort_output = true;
		}

		if (arg == "-unique") {
			unique_output = true;
		}

		if (arg == "-verbose") {
			verbose_mode = true;
		}
	}

	// Object of isprime class for verbose mode
	isprime prime_checker(verbose_mode);

	// Vector to store inputs and prime numbers
	vector<int> numbers, primes;

	int num;
	// Reads input and stores each number into the vector
	while (cin >> num) {
		numbers.push_back(num);
	}

	// Checks if numbers are prime and stores
	for (size_t i = 0; i < numbers.size(); i++) {
		if (prime_checker(numbers[i])) {
			primes.push_back(numbers[i]);
		}
	}

	// Removes duplicate primes
	if (unique_output) {
		sort(primes.begin(), primes.end());
		primes.erase(unique(primes.begin(), primes.end()), primes.end());
	}

	// Sorts prime numbers
	if (sort_output) {
		sort(primes.begin(), primes.end());
	}

	for (size_t i = 0; i < primes.size(); i++) {
		if (i % 20 == 0) {
			// First number of each line uses setw(4)
			cout << right << setw(4) << primes[i];
		} else {
			// Subsequent numbers use setw(5)
			cout << right << setw(5) << primes[i];
		}

		// Move to the next line after every 20 numbers
		if ((i + 1) % 20 == 0) {
			cout << endl;
		}
	}

	// Ensure the last line is properly terminated if it doesn't have exactly 20 numbers
	if (primes.size() % 20 != 0) {
		cout << endl;
	}

	/*	// Prints with formatting
		for (size_t i = 0; i < primes.size(); i++) {
	//if(primes.size() > 20) {
	//}
	cout << right << setw(4) << primes[i];

	if ((i + 1) % 20 == 0) {
	cout << endl;
	}
	}

	// Ensure the last line is properly terminated if it doesn't have exactly 20 numbers
	if (primes.size() % 20 != 0) {
	cout << endl;
	}
	*/
	return 0;
}

