#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Support.h"

using namespace std;

// Vectore to store prime numbers
vector<int> known_primes;

// For verbose mode
bool verbose;

// Constructor for isprime class initializing known primes and verbose mode
isprime::isprime(bool v) {
	verbose = v;

	// First prime is always 2
	known_primes.push_back(2); 
}

// Overloading to check if a number is prime
bool isprime::operator()(int N) {
	if (N < 2) {
		return false;
	}

	// If N is larger, expands the list of primes
	if (N > known_primes.back()) {
		expand_known_primes(N);
	}

	// Checks if N is in the known primes list
	if (binary_search(known_primes.begin(), known_primes.end(), N)) {
		return true;
	} else {
		return false;
	}

}

// Appends the known prime list upto N
void isprime::expand_known_primes(int N) {
	// Gets to last known prime
	int P = known_primes.back();

	// Modulus checker
	int counter = 0;
	int Q;

	// Ensures Q starts at next odd number
	if (P % 2 == 0) {
		Q = P + 1;
		counter++;
	} else {
		Q = P + 2;
		counter++;
	}

	if (verbose) {
		cout << "updating " << N << endl;
	}

	// Finds and adds new primes found on the way to N
	while (known_primes.back() < N || Q <= N ) {

		bool is_prime = true;

		// Limits divisibility check to numbers upto sqrt(Q)
		int limit = sqrt(Q);

		// Checks divisibility
		for (int i = 3; i <= limit; i+=2) {
			counter++;	
			
			// If divisible Q is not prime
			if (Q % i == 0) {
				is_prime = false;
				break;
			}

		}

		// Appends to known primes if prime
		if (is_prime) {

			known_primes.push_back(Q);

			if (verbose) {
				cout << "** adding " << Q << " (N=" << counter << ")" << endl;
			}
	
			// Reset counter for next number
			counter = 0;
		}

		// Moves to next odd number for testing
		Q += 2;

	}


}

