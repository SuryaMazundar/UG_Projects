/*Program Name: PPM Manipulation
 * Name: Surya Teja Mazundar
 * Professor: Dr. Jens Gregor
 * NetID: smazunda
 * Student ID: 000718553
 * Sources: Cplusplus.com, handouts, class resources
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Support.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;

int main(int argc, char *argv[]) {
	// determines image processing chunk size
	int block_size = 512;
	int K = 1;
	// controls lens effect
	float rho = 1.5;

	string filename;
	bool agray = false, aflip = false, adraw = false, alens = false;

	// Loops through command line arguments to set the respective flags and values
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-gray") agray = true;
		else if (arg == "-flip") aflip = true;
		else if (arg == "-draw" && i + 1 < argc) adraw = true, K = atoi(argv[++i]);
		else if (arg == "-lens" && i + 1 < argc) alens = true, rho = atof(argv[++i]);
		else if (arg == "-bs" && i + 1 < argc) block_size = atoi(argv[++i]);
		else filename = arg;
	}

	if (filename.empty()) {
		cerr << "Error: No file name provided!\n";
		return 1;
	}
	if (K < 1) {
		cerr << "Error: K must be greater than 1!\n";
		return 1;
	}

	// Sees to it that rho is within the range 
	if (rho <= 1.0 || rho > 2.0) {
		cerr << "Error: rho must be in the range (1.0, 2.0]!\n";
		return 1;
	}

	ppm image;
	// Sets block size
	image.set_bs(block_size);
	image.read(filename);

	// Based off the command, the respective will implement
	if (agray) gray(image);
	if (aflip) flip(image);
	if (adraw) draw(image, K);
	if (alens) lens(image, rho);

	image.write(filename);
	return 0;
}
