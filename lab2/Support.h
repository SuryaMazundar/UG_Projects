#ifndef SUPPORT_H
#define SUPPORT_H

#include <string> 
using namespace std;

struct location {
	string city;
	string state;
	string geocode;

	// Overloads to compare locations
	bool operator<(const location &n_station) const;
	
	// Overloads to compare locations in same state
	bool operator==(const location &n_station) const;
};

struct data {
	int month;
	float precipitation;
	int temparature;
};

// Linked list of weather info
class list {

	// Shows that node is in linked list
	struct node {

		// Constructor and deconstructor of node
		node(const location &n_station=location(), const data &weather = data());
		~node();

		void print_station();
		void print_data();

		// Data members for node
		location station;
		data weather;		

		int *month_counter;

		float *monthly_precipitation;
		float *max_precipitation;
		float *min_precipitation;

		int *monthly_temparature;
		int *max_temparature;
		int *min_temparature;
		
		// Pointer to next node
		node *next;
	};

	public:

	// Constructor and deconstructor of list
	list();
	~list();

	void insert(const location &, const data &);
	void print(const char *);

	private:
	node *head;
};

#endif
