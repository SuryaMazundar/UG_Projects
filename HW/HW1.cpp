#include <iostream>
using namespace std;

int strlen(char* a) {
	int length = 0;
	while (*a != '\0') {
		length++;
		a++;
	}
	return length;
}

int main(int argc, char* argv[]) {
	cout << "Num args = " << argc << endl;

	for (int i = 0; i < argc; ++i) {
		cout << "argv[" << i << "] = " << argv[i] << " " << argv[i] << " (strlen=" << strlen(argv[i]) << ")" << endl;
	}

	return 0;
}
