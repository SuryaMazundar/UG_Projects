/* Program Name: Hashtable Generator
 * Name: Surya Teja Mazundar
 * Professor: Dr. Jens Gregor
 * NetID: smazunda
 * Student ID: 000718553
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

typedef unsigned long ulong;

// Structure to hold user credentials (salt and password hash)
struct credentials {

	void set_salt(string &username);
	void set_hash(string &password);

	void operator=(const credentials &other);
	bool operator==(const credentials &other);

	string salt;
	ulong password_hash;
};

// Computes a cyclic shift hash of a string
ulong cyclic_shift_hash(const string &s) {
	ulong hash = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		char c = s[i];
		//Shift
		hash = (hash << 5) | (hash >> 27);
		// Adds character value
		hash += c;
	}
	return hash;
}

// Sets the salt based on username
void credentials::set_salt(string &username) {
	salt = "Kn0xVi113"; // Base Value
	for (size_t i = 0; i < salt.size(); ++i) {
		// Gets a character from the username
		char user_char = username[i % username.size()];
		// Gets a character from the base salt
		char salt_char = salt[i];
		// Modify the salt character
		char new_char = salt_char + (user_char & 0x7);

		// Ensures its printable
		if (!isprint(new_char)) {
			new_char = '*'; 
		}
		salt[i] = new_char; // Updates
	}
}

// Compute and set the password hash
void credentials::set_hash(string &password) {
	string combined = salt + password;
	password_hash = cyclic_shift_hash(combined);

}

// Assignment Operator
void credentials::operator=(const credentials &other) {
	salt = other.salt;
	password_hash = other.password_hash;
}

// Equality Operator
bool credentials::operator==(const credentials &other) {
	return salt == other.salt && password_hash == other.password_hash;
}

// Overloads input operator ofr credentials
istream &operator>>(istream &in, credentials &login) {
	in >> setw(10) >> login.salt >> hex >> login.password_hash >> dec;
	return in;

}

// Overloads output operator for credentials
ostream &operator<<(ostream &out, const credentials &login) {
	out << setw(10) << login.salt << " " << hex << login.password_hash << dec;
	return out;

}

typedef unordered_map<string,credentials> hashtable;

// Writes the hashtable to a file
void write_hashtable(hashtable &H, bool verbose) {
	string username, password;
	size_t prev_bucket_count = H.bucket_count();
	// Initialize number of entries to 0
	size_t N = 0;
	// Initial bucket count
	size_t I = H.bucket_count();

	if (verbose) {
		cout << "** S = " << setw(4) << N << " N = " << setw(4) << I
			<< " : load = " << fixed << setprecision(2) << H.load_factor() << endl;
	}

	while (cin >> username >> password) { // Read username and password
		credentials login;
		login.set_salt(username);
		login.set_hash(password);
		H[username] = login; // Inserts username and credentials into the hash table
		N++;

		size_t S = H.bucket_count(); // Current Bucket
		if (verbose && (S != prev_bucket_count || N == 1)) {
			cout << "** S = " << setw(4) << N
				<< " N = " << setw(4) << S
				<< " : load = " << fixed << setprecision(2) << H.load_factor()
				<< endl;
		}
	}

	ofstream out("passwd.txt");
	if (!out) {
		cerr << "Error: Could not open passwd.txt for writing." << endl;
		exit(1);
	}

	// Iterate through the hash table and writes
	for (hashtable::iterator it = H.begin(); it != H.end(); ++it) {
		out << setw(10) << it->first << " " << it->second << endl;
	}

	out.close();

	if (verbose) {
		cout << endl;

		// Loops through each bucket and by iterating through the beginning and the end of the bucket
		for (size_t i = 0; i < H.bucket_count(); ++i) {

			hashtable::local_iterator it = H.begin(i); 
			hashtable::local_iterator end = H.end(i);

			cout << setw(6) << i << " " << setw(4) << H.bucket_size(i);
			
			while (it != end) {
				cout << " " << it->first;
				++it;
			}

			cout << endl;
		}
	}
}

// Reads the hashtable from a file
void read_hashtable(hashtable &H, bool verbose) {
	ifstream in("passwd.txt");
	if (!in) {
		cerr << "Error: Could not open passwd.txt for reading." << endl;
		exit(1);
	}

	string username;
	credentials login;

	size_t N = H.size(); 
	size_t I = H.bucket_count();

	if (verbose) {
		cout << "** S = " << setw(4) << N
			<< " N = " << setw(4) << I
			<< " : load = " << fixed << setprecision(2) << H.load_factor()
			<< endl;
	}

	while (in >> username >> login) {
		H[username] = login;
		
		if (verbose) {
			cout << "** S = " << setw(4) << H.size()
				<< " N = " << setw(4) << H.bucket_count()
				<< " : load = " << fixed << setprecision(2) << H.load_factor()
				<< endl;
		}

	}

	in.close();

	//size_t prev_bucket_count = H.bucket_count();
	if (verbose) {
		cout << endl;
		for (size_t i = 0; i < H.bucket_count(); ++i) {

			hashtable::local_iterator it = H.begin(i); 
			hashtable::local_iterator end = H.end(i);

			cout << setw(6) << i << " " << setw(4) << H.bucket_size(i);
			while (it != end) {
				cout << " " << it->first;
				++it;
			}

			cout << endl;
		}
	}


}

int main(int argc, char *argv[]) {
	// Creates hastable
	hashtable H;

	// Flags
	bool createMode = false;
	bool checkMode = false;
	bool verbose = false;
	float load_factor = 1.0;
	string username, password;

	// Command line arguments
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "-create") {
			createMode = true;
		} else if (arg == "-check") {
			checkMode = true;
		} else if (arg == "-verbose") {
			verbose = true;
		} else if (arg == "-load" && i + 1 < argc) {
			load_factor = atof(argv[++i]);
		} else {
			cerr << "usage: ./sprog4 -create|check [-load Z] [-verbose] <logins.txt" << arg << "'." << endl;
			return 1;
		}
	}

	// Checks invalid arguments
	if (createMode && checkMode) {
		cerr << "Error: Cannot specify both -create and -check." << endl;
		return 1;
	}

	if (!createMode && !checkMode) {
		cerr << "Error: Must specify either -create or -check." << endl;
		return 1;
	}
	
	// Sets maximum load factor
	H.max_load_factor(load_factor);

	if (createMode) {
		write_hashtable(H, verbose);
	} else if (checkMode) {
		read_hashtable(H, verbose);

		string username, password;
		while (cin >> username >> password) {

			hashtable::iterator it = H.find(username);
			
			// Could not find username
			if (it == H.end()) {
				cout << username << " bad username" << endl;
				continue;
			}
	
			credentials stored = it->second;

			credentials input;

			input.set_salt(username);
			input.set_hash(password);

			if (input.password_hash == stored.password_hash) {
				cout << username << " access granted" << endl;
			} else {
				cout << username << " bad password" << endl;
			}
		}
	}

	return 0;
}

