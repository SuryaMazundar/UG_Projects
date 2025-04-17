/* Program Name: Weather Forecaster
 * Name: Surya Teja Mazundar
 * Professor: Dr. Jens Gregor
 * NetID: smazunda
 * Student ID: 000718553
 * */

#include <iostream>
#include <sstream>
#include <string>
#include "Support.h" // Header for info related to location, data and list

using namespace std;

void extract_values(string &line, location &n_station, data &n_data) {
	
	// Replace spaces with underscores and commas with spaces.
	for (size_t i = 0; i < line.size(); ++i) {
		if (line[i] == ' ') {
			line[i] = '_';
		}

		else if (line[i] == ',') {
			line[i] = ' ';
		}
	}

	// Extracts values from a line
	istringstream ss(line);
	ss >> n_data.month;
	ss >> n_station.city;
	ss >> n_station.state;
	ss >> n_station.geocode;
	ss >> n_data.precipitation;
	ss >> n_data.temparature;

}

int main(int argc, char *argv[]) {

	if (argc != 1 && argc != 2) {
		cerr << "usage: " << argv[0] << " [location] < datafile\n";
		return 1;
	}
	
	// Pointer to store location argument if entered
	char *target_location = NULL;
	if (argc == 2) {
		target_location = argv[1]; 
	}
	
	// Weather Data of different locations 
	list city_list;

	// Stores input, location and weather data
	string n_line;
	location n_station;
	data n_data;

	// Reads each line and inserts into list
	while (getline(cin, n_line)) {
		extract_values(n_line, n_station, n_data);
		city_list.insert(n_station, n_data);
	}
	
	// Prints weather data
	city_list.print(target_location);

	return 0;
}
