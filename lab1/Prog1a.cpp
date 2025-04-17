#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

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

void extract_values(string &line, location &location, data &data) {

	// Replace Spaces with underscore

	// Replace comas with spaces

	for (size_t i = 0; i < (int)line.size(); ++i) {
		if (line[i] == ' ') {
			line[i] = '_';
		}

		else if (line[i] == ',') {
			line[i] = ' ';
		}
	} 

	istringstream ss(line);
	ss >> data.month; 
	ss >> location.city; 
	ss >> location.state; 
	ss >> location.geocode; 
	ss >> data.precip; 
	ss >> data.temp;

}

int main() {
	ifstream inputFile("weather_TN.csv");
	string line;

	while (getline(inputFile, line)) {
		location location;
		data data;
		extract_values(line, location, data);

		cout << data.month << " ";
		cout << location.city << " ";
		cout << location.state << " ";
		cout << location.geocode << " ";
		cout << fixed << setprecision(2) << data.precip << " "; 
		cout << data.temp << endl;
	}

	inputFile.close();

	return 0;
}
