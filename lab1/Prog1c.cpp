/* Program Name: Weather Forecast
Name: Surya Teja Mazundar
Professor Name: Dr. Jens Gregor
Net ID: smazunda
Student ID: 000718553
Source: TA Nicholas, TA Zach, TA Diego
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Support.h" // Header file consisting of functions and classes

using namespace std;

// Checks if a particular geocode is valid
bool isgeocode(const string &pass) {
	if (pass.size() != 3) {
		return false;
	}
	for (size_t i = 0; i < pass.size(); ++i) {
		if (!isupper(pass[i])) {
			return false;
		}
	}
	return true;
}

// Replaces spaces with underscores and commas with spaces
void extract_values(string &line, location &location, data &data) {
	
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			line[i] = '_';
		}

		else if (line[i] == ',') {
			line[i] = ' ';
		}
	}

	// Creates objects to extract values
	istringstream ss(line);
	ss >> data.month;
	ss >> location.city;
	ss >> location.state;
	ss >> location.geocode;
	ss >> data.precipitation;
	ss >> data.temparature;

}

int main(int argc, char* argv[]) {
	
	string line;
	
	// Checks for command line arguments or displays an error if more than expected
	if (argc > 2) {
		cerr << "usage: ./Prog1c [geocode] < datafile" << endl;
		return 1;
	}

	string geocode;
	
	// Checks if the geocode is valid in the command line else displays an error
	if (argc == 2) {
		geocode = argv[1];
		if (!isgeocode(geocode)) {
			cerr << "Invalid geocode: " << geocode << endl;
			cerr << "Usage: ./Prog1c [geocode] < datafile" << endl;
			return 1;
		}

	}

	// New station object which is only used when it is not equal to location
//	summary stat(location);	

	// Vector to store each unique geocode
	vector<summary> stations; 


	// Reads each line
	while (getline(cin, line)) {
		location location;
		data data;

		// Calls to extract values
		extract_values(line, location, data);

		bool found = false;
		
		// Loops through current stations to check if the current location's geocode already exists
		for (size_t i = 0; i < stations.size(); i++) {
			if (stations[i].get_station() == location) { 
				found = true;
				// Transfers the new data to the current station's final info
				stations[i].incorporate_data(data); 
				break;

			}
		}
		
		// Creates a new summary object if not found
		if (!found) {
			summary stat(location);
			// Again, transfers the new data to the curent station's final info
			stat.incorporate_data(data);  
			// Appends the new data to the vector
			stations.push_back(stat);
		}

	}

	// Prints the summaries 
	for (size_t i = 0; i < stations.size(); i++) {
		// A check to see if that station has respective info
		if (!stations[i].empty()) {
			if (stations.empty() || stations[i].get_station().geocode == geocode) { 
				stations[i].print_station();
				stations[i].print_data();
			}
		}
	}
	return 0;
}
