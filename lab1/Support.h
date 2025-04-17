#ifndef Support_h
#define Support_h

#include <string>
#include <vector>

using namespace std;

// Shows the location attributes
struct location {
	string city;
	string state;
	string geocode;
	
	// Fucntion to check if geocode is empty
	bool empty(); 

	//Overloading to compare two location objects
	bool operator == (const location& location) const;

};

// Shows weather data attributes
struct data {
	int month;
	float precipitation;
	int temparature;
};

// Summarizes weather data for a particular location
class summary {
	
	// Initializes class members
	public:
		summary();
		summary(const location& location); 
		const location get_station(); 
		bool const empty(); 
		void set_station(const location& location);
		void incorporate_data(const data& data);
		void const print_station();
		void print_data();

	private:
		location station;

		// Stores the respective info for each month
		vector<float> monthly_precipitation;
        vector<float> max_precipitation;
        vector<float> min_precipitation;
        vector<int> monthly_temparature;
        vector<int> max_temparature;
        vector<int> min_temparature;
		vector<int> month_counter;
};

// Initializes to check if a geocode is valid
bool isgeocode(const string& pass);

#endif
