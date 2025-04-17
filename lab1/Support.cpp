#include <cctype> // For isupper()
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Support.h"

bool location::empty() {
	// Checks if location is empty
	return geocode.empty();
}

bool location::operator == (const location &check) const{
	// Checks if both have same geocode by overloading
	return geocode == check.geocode;
}

// Checks if summary is empty
bool const summary::empty() {
	return station.geocode.empty();
}

// Sets station to allocated location
void summary::set_station(const location &location){
	station = location;
}

// Appends weather data into summary
void summary::incorporate_data(const data &data){
	int month = data.month-1;
	
	// Increments the count of the number of times recurs for that month
	month_counter[month]++; 
		
	// Holds precipitation info
	monthly_precipitation[month] += data.precipitation;

	// Updates max precip for that particular month
	if (data.precipitation > max_precipitation[month]) {
		max_precipitation[month] = data.precipitation;
	}
	
	// Updates min precip for that particular month
	if (data.precipitation < min_precipitation[month]) {
		min_precipitation[month] = data.precipitation;
	}
	
	// Holds temparature info
	monthly_temparature[month] += data.temparature;
		
	// Updates max temp for that particular month
	if (data.temparature > max_temparature[month]) {
		max_temparature[month] = data.temparature;
	}
	
	// Updates min temp for that particular month
	if (data.temparature < min_temparature[month]) {
		min_temparature[month] = data.temparature;
	}
}

// Prints summarized station data
void const summary::print_station() {

	cout << "------------------------------------------" << endl;
	cout << station.city << ", " << station.state << " (" << station.geocode << ")" << endl;
	cout << "------------------------------------------" << endl;

}

// Checks while it loops on months and prints summarized weather data for each month
void summary::print_data() {

string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

for (size_t i = 0; i < 12; ++i) {
	
	// Common for decimal outputs
	cout.precision(2);

	cout << months[i] << ": ";

	if (month_counter[i] > 0) {
	    cout << fixed << right << setw(5) << monthly_precipitation[i] << " "; 
		cout << fixed << right << setw(5) << (monthly_precipitation[i] / month_counter[i]) << " "; 
		cout << fixed << right << setw(5) << max_precipitation[i] << " ";
		cout << fixed << right << setw(5) << min_precipitation[i] << " ";
		cout << fixed << right << setw(1) << ":" << " ";
	}

	if (monthly_temparature[i] > 0) {
		cout << fixed << right << setw(3) << (monthly_temparature[i] / month_counter[i]) << " ";
		cout << fixed << right << setw(3) << max_temparature[i] << " ";
		cout << fixed << right << setw(3) << min_temparature[i] << endl;
	}

}
}

// Initializes member variables
summary::summary() {
	
	// Since min precipitation or temparature cannot exceed a certain number, assuming max value as 100000 gives us an advantage to be accurate.
	station = location();
	monthly_precipitation.resize(12,0.0);
	max_precipitation.resize(12,0.0);
	min_precipitation.resize(12,10000.0);
	monthly_temparature.resize(12,0.0);
	max_temparature.resize(12,0.0);
	min_temparature.resize(12,10000.0);	

	}

// When location is the input
summary::summary(const location &location) {
	station = location;
	monthly_precipitation.resize(12, 0.0);
    max_precipitation.resize(12, 0.0);
    min_precipitation.resize(12, 10000.0); 
    monthly_temparature.resize(12, 0.0);
    max_temparature.resize(12, 0.0);
    min_temparature.resize(12, 10000.0); 
    month_counter.resize(12, 0);
}

// Returns that station's information along with the summary
const location summary::get_station() { 
	return station; 
}

