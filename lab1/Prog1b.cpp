/* Name: Surya Teja Mazundar
Professor: Dr. Jens Gregor
Sources: TA Jack and Sydney

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

// Initializes data objects
struct location {
	string city;
	string state;
	string geocode;
};

struct data {
	int month;
	float precip;
	int temp;
};

class summary {
	public:
		summary() {
			N = 0;
			total_precip = 0.0;
			max_precip = 0;
			min_precip = 20000;
			total_temp = 0;
			max_temp = 0;
			min_temp = 10000;
		}

		bool empty() {
			return station.geocode.empty();
		}

		void set_station(const location &location){
			station = location;
		}

		void incorporate_data(const data &data){
			N++;
			total_precip += data.precip;
			max_precip = max(max_precip, data.precip);
			min_precip = min(min_precip, data.precip);
			total_temp += data.temp;
			max_temp = max(max_temp, data.temp);
			min_temp = min(min_temp, data.temp);

		}

		void print_station() {
			cout << station.city << ", " << station.state << " (" << station.geocode << ")" << endl;
		}
		void print_data() {

			cout.precision(2);
				
			cout << ">>>  " << left << setw(2) << total_precip << "  ";
			cout << fixed << left << setw(2) << (total_precip) / (N) << "  ";
			cout << fixed << left << setw(2) << max_precip << "  ";
			cout << fixed << left << setw(2) << fixed << min_precip << "  "; 
			cout << fixed << left << setw(2) << ":";
			cout << fixed << left << setw(2) << (total_temp) / (N) << "  ";
			cout << fixed << left << setw(2) << max_temp << "  ";
			cout << fixed << left << setw(2) << min_temp << endl;

		}

	private:
		location station;

		int N;

		float total_precip;
		float max_precip;
		float min_precip;

		int total_temp;
		int max_temp;
		int min_temp;
};

int geocode_to_index(const string &geocode) {
	return (geocode[0] - 'A') + 26 * (geocode[1] - 'A') + 676 * (geocode[2] - 'A'); 
}


// Replaces mentioned characters by checking each line of the file
void extract_values(string &line, location &location, data &data) {

	// Spaces with underscore
	// Comas with spaces
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
	ss >> data.precip;
	ss >> data.temp;

}

int main() {
	string line;
	int index;

	vector<summary> stations(17576);

	// Reads each line 
	while (getline(cin, line)) {
		location location;
		data data;

		// Function is called to extract values
		extract_values(line, location, data);

		index = geocode_to_index(location.geocode);
		if (stations[index].empty()) {
			stations[index].set_station(location);
		}

		stations[index].incorporate_data(data);
	}

	for (size_t i = 0; i < stations.size(); i++) {
		if (!stations[i].empty()) {

			stations[i].print_station();
			stations[i].print_data();
		}
	}

	return 0;
}
