#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <cctype>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::string> &data) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	// first get operators with their extra spaces 
	std::string line;
	while (std::getline(file, line)) {
		line += '\n';				// add last character, we need this
		data.push_back(line);
	}
}

int main() {
	// read data
	std::vector<std::string> data;

	std::string data_file = "./adventofcode.com_2025_day_6_input.txt";
	read_data(data_file, data);

	// show data
	print_vector(data);

	// solution
	long int result = 0;
	long int col_result;
	char op;
	for (int c = 0; c < data[0].size(); ++c) {
		if (data[data.size() - 1][c] == '*') {
			op = data[data.size() - 1][c];
			col_result = 1;
		}
		else if (data[data.size() - 1][c] == '+') {
			op = data[data.size() - 1][c];
			col_result = 0;
		}

		std::string number = "";
		for (int r = 0; r < data.size(); ++r)
			if (std::isdigit(data[r][c]))
				number += data[r][c];

		std::cout << number << std::endl;

		if (number == "")
			result += col_result;
		else if (op == '*') {
			col_result *= std::stol(number);
			std::cout << col_result << std::endl;
		}
		else if (op == '+') {
			col_result += std::stol(number);
			std::cout << col_result << std::endl;
		}
	}
	std::cout << "Result: " << result << std::endl;
	
	return 0;
}
