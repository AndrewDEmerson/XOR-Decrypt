#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
float freq(string);

// CHANGE THESE VARIBLES
const char* input_file = "Data.txt";
const int results_to_show = 10;

int main()
{
	ifstream input;
	input.open(input_file);
	if (input.fail()) {
		cerr << "ERROR: Failed to open file, Aborting program" << endl;
		return -1;
	}
	// Vector of all permuations of xor that fit criteria
	vector<string> legal_permutations;
	vector <float> legal_permutations_ratings;
	// Line loaded in from input file
	string input_string;
	while (getline(input, input_string)) {
		// Convert string of hexidecimal values into an array of 8-bit values.
		vector<uint8_t> data_array;
		for (int i = 0; i < (input_string.length() / 2); i++) {
			char hex_string[3] = { '\0' };
			hex_string[0] = input_string[2 * i];
			hex_string[1] = input_string[(2 * i) + 1];
			data_array.push_back((uint8_t)strtol(hex_string, NULL, 16));
		}

		// XOR the data with every possible value
		for (uint8_t p = 0; p < 254; p++) {
			vector<uint8_t> test_array = data_array;
			for (int i = 0; i < test_array.size(); i++) {
				test_array[i] ^= p;
			}

			std::string str(test_array.begin(), test_array.end());
			legal_permutations.push_back(str);
			legal_permutations_ratings.push_back(freq(str));
		}
	}

	// Print out the most likley correct results, sorted by letter frequency
	for (int i = 0; i < results_to_show; i++) {
		float best_score = 0;
		float best_index = 0;
		for (int i = 0; i < legal_permutations.size(); i++) {
			if (legal_permutations_ratings.at(i) > best_score) {
				best_score = legal_permutations_ratings.at(i);
				best_index = i;
			}
		}
		if (best_score == 0) {
			break;
		}
		else {
			cout << legal_permutations.at(best_index) << endl;
			legal_permutations_ratings[best_index] = 0;
		}
	}
	return 0;
}

float freq(string str) {
	// frequinces of the letters A-Z
	const float char_frequencies[] = {
		0.081670, 0.149200, 0.027820, 0.042530,
		0.127020, 0.022280, 0.020150, 0.060940,
		0.060940, 0.001530, 0.007720, 0.040250,
		0.024060, 0.067490, 0.075070, 0.019290,
		0.000950, 0.059870, 0.063270, 0.090560,
		0.027580, 0.009780, 0.023600, 0.001500,
		0.01974 , 0.00074 };
	//' ' = .13000
	float sum = 0;
	for (int c = 0; c < str.length(); c++) {
		if ((toupper(str.at(c)) - 'A') < 0 || (toupper(str.at(c)) - 'A') > 26) {
			// account for space
			if (str.at(c) == ' ') sum += 0.13000;
		}
		else {
			sum += char_frequencies[toupper(str.at(c)) - 'A'];
		}
	}
	return sum;
}
