#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <numeric>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " ";
	std::cout << std::endl;
}

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
	long int result = 0;
	for (int i = 0; i < batteries.size(); ++i) {
		// first scan to find maximum
		int index = 0;
		int maximum = batteries[i][0];
		batteries[i][0] = 0;
		for (int j = 0; j < batteries[i].size() - 1; ++j)
			if (batteries[i][j] > maximum) {
				maximum = batteries[i][j];
				batteries[i][j] = 0;
				index = j;
			}
		
		// update result
		result += 10 * maximum;

		// second scan to find maximum
		maximum = batteries[i][index];
		for (int j = index; j < batteries[i].size(); ++j)
			if (batteries[i][j] > maximum) {
				maximum = batteries[i][j];
				batteries[i][j] = 0;
			}

		// update result
		result += maximum;
	}
	std::cout << "Result: " << result << std::endl;

	return 0;
}
