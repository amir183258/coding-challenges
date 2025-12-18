#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cmath>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << std::setw(3) << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<long int> &x, std::vector<long int> &y) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss {line};
		std::string number;

		std::getline(ss, number, ',');
		x.push_back(std::stoi(number));

		std::getline(ss, number, ',');
		y.push_back(std::stoi(number));
	}
}

long int find_max(std::vector<std::vector<long int>> &areas) {
	long int maximum = areas[0][0];
	for (int i = 0; i < areas.size(); ++i)
		for (int j = 0; j < areas[i].size(); ++j)
			if (areas[i][j] > maximum)
				maximum = areas[i][j];

	return maximum;
}

int main() {
	// read data
	std::vector<long int> x;
	std::vector<long int> y;

	std::string data_file = "./adventofcode.com_2025_day_9_input.txt";

	read_data(data_file, x, y);

	// show data
	print_vector(x);
	print_vector(y);

	// solution
	std::vector<std::vector<long int>> areas(x.size(), std::vector<long int>(x.size(), 0));

	// comupte areas
	for (int i = 0; i < areas.size(); ++i)
		for (int j = 0; j < areas[i].size(); ++j)
			areas[i][j] = (std::abs(x[j] - x[i]) + 1) * (std::abs(y[j] - y[i]) + 1);

	for (int i = 0; i < areas.size(); ++i)
		print_vector(areas[i]);

	// find maximum area
	long int result;
	result = find_max(areas);

	std::cout << "Result: " << result << std::endl;
	
	return 0;
}
