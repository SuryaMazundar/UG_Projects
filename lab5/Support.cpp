#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Support.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;
using std::min;
using std::swap;

ppm::ppm() {
	// Ensures to be in binary format
	magicid = "P6";
	Nrow = 0;
	Ncol = 0;
	maxvalue = 255;
	block_size = 256;
	img = NULL;	
}

// Constructor that duplicates an existing item
ppm::ppm(const ppm &other) {
	magicid = other.magicid;
	Nrow = other.Nrow;
	Ncol = other.Ncol;
	maxvalue = other.maxvalue;
	block_size = other.block_size;

	if (other.img) {
		// Allocate memory for new image
		img = new RGB[Nrow * Ncol];

		for (int i = 0; i < Nrow * Ncol; ++i) {
			// Copies pixel data
			img[i] = other.img[i];
		}
	} else {
		img = NULL;
	}
} 

// Destructor releases memory allocated for image
ppm::~ppm() {
	delete[] img;
} 

// Modifies the block size, which determines the amount of data read at a time. 
// I believe it is useful for large images so that its just easier to read in smaller chunks.
void ppm::set_bs(int blockS) {
	block_size = blockS;
}

// To access rows of an image and returns a pointer to the row
RGB *ppm::operator[](int row) {
	return img + row * Ncol;
}

// Reads a PPM image file and stores its data in the object. 
// As in, if the image is valid, it deletes the space created for the next image. 
// It then reads data in chunks of 256 bytes and stores it in buffer as it checks the error cases.
void ppm::read(const string &inputFile) {
	ifstream file(inputFile.c_str(), ios::binary);
	if (!file.is_open()) {
		cerr << "Error: Could not open file " << inputFile << endl;
		return;
	}

	file >> magicid >> Ncol >> Nrow >> maxvalue;
	file.ignore(); 

	// Validate PPM format and max pixel value
	if (magicid != "P6") {
		cerr << "Error: Invalid PPM magic identifier." << endl;
		return;
	}
	if (maxvalue != 255) {
		cerr << "Error: Unsupported max pixel value." << endl;
		return;
	}

	delete[] img;
	img = new RGB[Nrow * Ncol];

	// Total number of bytes for further usage
	int pixel = Nrow * Ncol * 3;
	int byteCount = 0;

	// Read image data in chunks
	while(byteCount < pixel) {

		// Holds image data
		char buffer[256];  

		int byteR;
		if (pixel - byteCount > 256) {
			byteR = 256;
		} else {
			byteR = pixel - byteCount;
		}

		for (int i = 0; i < byteR; i++) {
			char bytes;
			if (file.get(bytes)) {  
				buffer[i] = bytes;
			} else {
				cerr << "Error: Failed to read expected RGB data." << endl;

				delete[] img;
				img = NULL;

				return;
			}
		}

		// Copy buffer data to image
		for (int i = 0; i < byteR; i++) {
			int index = byteCount + i;
			int pixelIndex = index / 3;
			if (index % 3 == 0) {
				img[pixelIndex].R = buffer[i];
			} else if (index % 3 == 1) {
				img[pixelIndex].G = buffer[i];
			} else {
				img[pixelIndex].B = buffer[i];
			}
		}

		byteCount += byteR;
	}

	file.close();
}

// Generates two output .ppm files with names _mod.ppm and _solution.ppm to be able to compare each other for errors. 
// In case writing the file fails, it gives an errors message.
void ppm::write(const string &outputfile) {

	// Generates a modified file name
	string outputFile = outputfile;
	size_t pos = outputFile.rfind(".ppm");

	if (pos != string::npos) {
		outputFile.insert(pos, "_mod");
	} else {
		outputFile += "_mod.ppm";
	}

	ofstream file(outputFile.c_str(), ios::binary);
	if (!file) {
		cerr << "Error: Could not create file " << outputFile << endl;
		return;
	}

	file << magicid << "\n" << Ncol << " " << Nrow << "\n" << maxvalue << "\n";

	// Write image pixel data
	for (int i = 0; i < Nrow * Ncol; ++i) {
		file << img[i].R;
		file << img[i].G;
		file << img[i].B;
	}

	if (!file) {
		cerr << "Error: Failed to write RGB data." << endl;
		return;
	}

	file.close();
}

// Converts the image to grayscale by taking the average of RGB values for each pixel. 
// Since, the conversion is the same for all the pixels, RGB are set equal to the average value.
void gray(ppm &img) {

	int Nrow = img.get_Nrow();
	int Ncol = img.get_Ncol();

	for (int i = 0; i < Nrow; ++i) {
		for (int j = 0; j < Ncol; ++j) {
			RGB &pixel = img[i][j];
			byte gray_value = (pixel.R + pixel.G + pixel.B) / 3;
			pixel.R = pixel.G = pixel.B = gray_value;
		}
	}
}

// Flips image left-to-right.
// Iterates over each line or row and swaps pixels. 
void flip(ppm &img) {

	int Nrow = img.get_Nrow();
	int Ncol = img.get_Ncol();

	// Swaps pixels
	for (int i = 0; i < Nrow; ++i) {
		for (int j = 0; j < Ncol / 2; ++j) {
			swap(img[i][j], img[i][Ncol - j - 1]);
		}
	}
}

// Applies a drawing effect by enhancing contrast based on neighboring pixel intensities
void draw(ppm &img, int K) {
	int Nrow = img.get_Nrow();
	int Ncol = img.get_Ncol();

	// Create a copy to avoid modifying original image while processing
	ppm img_copy = img; 

	for (int i = 0; i < Nrow; ++i) {
		for (int j = 0; j < Ncol; ++j) {
			int Y_max = 0;

			// Scan neighboring pixels in a KxK window
			for (int di = -K; di <= K; ++di) {
				for (int dj = -K; dj <= K; ++dj) {
					int ni = i + di;
					int nj = j + dj;
					if (ni >= 0 && ni < Nrow && nj >= 0 && nj < Ncol) {
						RGB &sidePixel = img_copy[ni][nj];
						int Y = (sidePixel.R + sidePixel.G + sidePixel.B) / 3;
						if (Y > Y_max) {
							Y_max = Y;
						}
					}
				}
			}

		}
	}
}

// Applies a lens effect to the image.
// Uses the arithmetic given in the writeup.
void lens(ppm &img, float rho) {
	int Nrow = img.get_Nrow();
	int Ncol = img.get_Ncol();
	int ci = Nrow / 2, cj = Ncol / 2;
	int rmax = min(Nrow / 2, Ncol / 2);
	ppm img_copy = img; 

	for (int i = 0; i < Nrow; ++i) {
		for (int j = 0; j < Ncol; ++j) {
			int di = i - ci, dj = j - cj;
			float r = sqrt(di * di + dj * dj);

			if (r < rmax) {
				float z = sqrt(rmax * rmax - r * r);
				float dzi = di / sqrt(di * di + z * z);
				float dzj = dj / sqrt(dj * dj + z * z);
				float bi = (1.0 - 1.0 / rho) * asin(dzi);
				float bj = (1.0 - 1.0 / rho) * asin(dzj);
				int ip = (int)(i - z * tan(bi) + 0.5);
				int jp = (int)(j - z * tan(bj) + 0.5);
				img[i][j] = img_copy[ip][jp];
			}
		}
	}
}
