/* Program Name: Arithmetic
 * Name: Surya Teja Mazundar
 * Professor Name: Dr. Jens Gregor
 * NetID: smazunda
 * StudentID: 000718553
 * Sources: cplusplus.com, notes (canvas), searched to understand the logics
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

// Global flags for controlling program behavior
bool success = false; // if at least one valid solution was found
bool findall = false; // sees if it has to find all solutions or stop after the first
bool verbose = false; // prints out every step
//string mode = "inorder"; 
int target = 0;
string anyorder = ""; // all the permutations of the numbers are computed
string inorder = "";  // only the original sequence
string mode = "";

// Shows the sequence of operations in different modes.	
void show_solution(vector<int> &numbers, vector<int> &operations) {
	string signs = "*/+-";
	string ops; 

	// Verbose mode for detailed calculations
	if (verbose){
		int result = numbers[0]; // Starts with the first number
		cout << numbers[0];

		// Convert operations to symbols
		for (size_t i = 0; i < operations.size(); ++i) {
			if (operations[i] == 0) {
				cout <<	"*"; // Multiplication
			} else if (operations[i] == 1) {
				cout <<	"/"; // Division
			} else if (operations[i] == 2) {
				cout <<	"+"; // Addition
			} else if (operations[i] == 3) {
				cout <<	"-"; // Subtraction
			}

			// Print the operation and the next number
			cout << numbers[i + 1];

			// Evalutes step by step
			if (operations[i] == 0) {
				result *= numbers[i + 1];
			} else if (operations[i] == 1) {
				result /= numbers[i + 1];
			} else if (operations[i] == 2) {
				result += numbers[i + 1];
			} else if (operations[i] == 3) {
				result -= numbers[i + 1];
			}
		}

		// Final output
		cout << "=" << target << " ";
	}

	// Takes the operations used to print it beside the output
	for (size_t i = 0; i < operations.size(); ++i) {
		ops += signs[operations[i]];
	}
	// Operations used
	cout << ops << endl;
}

// Recursion to find a sequence of operations that results in target value
bool find_solution(vector<int> &numbers, vector<int> &operations, int k=0, int fvalue=0) {

	if (k == 0) { // Resets and starts recursion
		operations.clear(); // Reset the operations vector
		if (numbers.empty()) { // if there are no numbers
			return false;
		}
		return find_solution(numbers, operations, 1, numbers[0]); // Starts with the first number
	}

	// When last number is reached 
	if ((size_t)k == numbers.size() - 1) {
		if (fvalue == target) { // If arrived at target value
			show_solution(numbers, operations);
			success = true;
			if (findall) { 
				return false; // Continue searching for more solutions
			} else {
				return true; // Stop after finding one solution
			}
		}
		return false; // If no solution found 
	}

	// Next number
	int next = numbers[k];

	// Arithmetic Operations
	for (int sign = 0; sign < 4; ++sign) {
		int result = fvalue;
		if (sign == 0) {
			result *= next; // Multiplication
		} else if (sign == 1) {
			result /= next; // Division
		} else if (sign == 2) {
			result += next; // Addition
		} else if (sign == 3) {
			result -= next; // Subtraction
		}

		// Add the above operation to the operations vector
		operations.push_back(sign);

		// Recursive call to process the next number
		bool foundSolution = find_solution(numbers, operations, k + 1, result);
		if (foundSolution && !findall) { // Stops if only one solution is needed
			return true;
		}
		// Removes the last operation to find other possibilities
		operations.pop_back();
	}
	return false; 
}

int main(int argc, char *argv[]) {
	vector<int> numbers, operations; // Vectors to store input numbers and operations

	if (argc < 2) {
		cerr << "Usage: ./Prog6 -inorder|anyorder -1|N [-verbose] < numbers.txt" << endl;
		return 1;
	}

	int argin = 1;

	// Parse command line flags
	while (argin < argc && argv[argin][0] == '-') {
		string flag = argv[argin];

		if (flag == "-N") { // -all
			findall = true;
		} else if (flag == "-verbose") {
			verbose = true;
		} else if (flag == "-inorder") {
			mode = "inorder";
		} else if (flag == "-anyorder") {
			mode = "anyorder";
		} else if (flag == "-1") {
			findall = false;
		} else {
			cerr << "Unknown option: " << flag << endl;
			return 1;
		}
		argin++;
	}

	// Read numbers 
	while (argin < argc) {
		numbers.push_back(atoi(argv[argin]));
		argin++;
	}

	if (numbers.empty()) {
		int val;
		while (cin >> val) {
			numbers.push_back(val);
		}
	}

	// Checks if tjere are at least two numbers (operand and target value)
	if (numbers.size() < 2) {
		cerr << "Error: Need at least two numbers (operands and target)" << endl;
		return 1;
	}

	// Extracts the target value
	target = numbers.back();
	numbers.pop_back();

	// Evaluates based on selected mode
	if (mode == "inorder") {
		numbers.push_back(target); // Pushes back the target value to numbers vector
		find_solution(numbers, operations); // Finds a solution

	} else if (mode == "anyorder") {
		sort(numbers.begin(), numbers.end()); // Sorts for permutation

		do {
			success = false; // Resets for permutation
			operations.clear(); // Clears vector for each permutation
			numbers.push_back(target); // Pushes back the target value to numbers vector
			find_solution(numbers, operations) && !findall; // Finds solution
			numbers.pop_back(); // Remove the target value for the next loop.
		} while (next_permutation(numbers.begin(), numbers.end())); // Permutation
	}else {
		cerr << "Use -inorder or -anyorder" << endl;
		return 1;
	}

	return 0;
}
