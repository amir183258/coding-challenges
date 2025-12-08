#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " "; std::cout << std::endl; }

void read_data(const std::string& file_name, std::vector<std::vector<int>>& batteries) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> temp;
		for (int i = 0; i < line.size(); ++i)
			temp.push_back(line[i] - '0');
		batteries.push_back(temp);
	}
}
void print_data(std::vector<std::vector<int>>& batteries) {
	for (int i = 0; i < batteries.size(); ++i)
		print_vector(batteries[i]);
}

int main() {
	// read data
	std::vector<std::vector<int>> batteries;

	std::string data_file = "./adventofcode.com_2025_day_3_input.txt";
	read_data(data_file, batteries);

	// show data
	//print_data(batteries);

	// solution
	long long int result;
	for (int i = 0; i < batteries.size(); ++i) {
		int free_space = batteries[i].size() - 12 + 1;				// be careful; main data line size is different from demo data
		auto start = batteries[i].begin();
		int j = 0;
		long long int number = 0;
		while (j < 12) {
			auto maximum = std::max_element(start, start + free_space);

			number = number * 10 + *maximum;

			free_space -= (maximum - start);

			start = maximum + 1;
			++j;
		}
		std::cout << "Number: " << number << std::endl;
		result += number;
	}
	std::cout << "Result: " <<  result << std::endl;

	return 0;
}
