#include <iostream>
#include <iomanip>
#include <string>
#include "Support.h" // Header for info related to location, data and list

using namespace std;

// Compares two locations based off state and city
bool location::operator<(const location &n_station) const{
	if((state < n_station.state) || (state == n_station.state && city < n_station.city)) {
		return true;
	}
	return false;
}

// Overloads to sort by state and if states are equal, sorts by city 
bool location::operator==(const location &n_station) const{
	if ((n_station.state == state && n_station.city == city) || n_station.state == state) {
		return true;
	}
	return false;

}

// Constructor initializing weather data arrays
list::node::node(const location &n_station, const data &weather) {

	station = n_station;
	
	// Dynamically allocates arrays for weather info and initializes to 0
	monthly_precipitation = new float[12]();
	max_precipitation = new float[12]();
	min_precipitation = new float[12]();
	monthly_temparature = new int[12]();
	max_temparature = new int[12]();
	min_temparature = new int[12]();

	// Keeps track of month
	month_counter = new int[12]();

	next = NULL;

}

// Deallocates memory used by weather arrays
list::node::~node(){
	delete[] month_counter;
	delete[] monthly_precipitation;
	delete[] max_precipitation;
	delete[] min_precipitation;
	delete[] monthly_temparature;
	delete[] max_temparature;
	delete[] min_temparature;
}

// Initializes head to a new node
list::list() {
	head = new node();
}

// Deallocates nodes and their data
list::~list() {
	node *temp = head;
	while (temp != NULL) {
		node *next_node = temp->next;
		delete temp;
		temp = next_node;
	}

}

// Inserts a new weather entry into the list while maintaining sorted order
void list::insert(const location &n_station, const data &weather) {

	node *before = head;
	node *current;
	if (head != NULL) {
		current = head->next;
	} else {
		current = NULL;
	}
	
	// Finds position to insert node
	while (current && current->station < n_station) {
		before = current;
		current = current->next;
	}

	if (current && current->station == n_station) {
		int month = weather.month - 1;

		current->month_counter[month]++;

		current->monthly_precipitation[month] += weather.precipitation;

		if (weather.precipitation > current->max_precipitation[month]) {
			current->max_precipitation[month] = weather.precipitation;
		}

		if (current->month_counter[month] == 1) {
			current->min_precipitation[month] = weather.precipitation;
		} else if (weather.precipitation < current->min_precipitation[month]) {
			current->min_precipitation[month] = weather.precipitation;
		}

		current->monthly_temparature[month] += weather.temparature;

		if (weather.temparature > current->max_temparature[month]) {
			current->max_temparature[month] = weather.temparature;
		}

		if (current->month_counter[month] == 1) {
			current->min_temparature[month] = weather.temparature;
		} else if (weather.temparature < current->min_temparature[month]) {
			current->min_temparature[month] = weather.temparature;
		}

	} else {

		// Create a new node for the new station.
		node *newStation = new node(n_station, weather);
		newStation->next = current;

		if (before) {
			before->next = newStation;
		} else {
			// Inserts at beginning of list
			head = newStation;
		}

		int month = weather.month - 1;
		newStation->month_counter[month] = 1;
		newStation->monthly_precipitation[month] = weather.precipitation;
		newStation->max_precipitation[month] = weather.precipitation;
		newStation->min_precipitation[month] = weather.precipitation;
		newStation->monthly_temparature[month] = weather.temparature;
		newStation->max_temparature[month] = weather.temparature;
		newStation->min_temparature[month] = weather.temparature;
	}
}

// Prints station info
void list::node::print_station() {

	cout << "------------------------------------------" << endl;
	cout << station.city << ", " << station.state << " (" << station.geocode << ")" << endl;
	cout << "------------------------------------------" << endl;
}

// Prints weather info for a particular station
void list::node::print_data() {

	string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	for (size_t i = 0; i < 12; ++i) {

		cout.precision(2);

		cout << months[i] << ": ";

		if (month_counter[i] > 0) {
			cout << fixed << right << setw(5) << setprecision(2) << monthly_precipitation[i] << " ";
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

//Prints weather info for a specific given location or all locations
void list::print(const char *target_location) {

	bool found = false;
	
	// Iterate through the list, starting from the first actual data node
	for (node *temp = head->next; temp != NULL; temp = temp->next) { 
		
		// Print all if target_location is NULL
		if (target_location == NULL) { 

			// Prints all data
			temp->print_station();
			temp->print_data();
			found = true; 
		} else if (temp->station.city == target_location || temp->station.state == target_location || temp->station.geocode == target_location) {
			
			// Prints data of a specific given location
			temp->print_station();
			temp->print_data();
			found = true;
		}
	}

	if (!found && target_location != NULL) {
		cout << "No data found for location: " << target_location << endl;
	}
}
