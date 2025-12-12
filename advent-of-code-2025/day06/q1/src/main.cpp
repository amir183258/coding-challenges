#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::vector<int>> &nums, std::vector<char> &operators) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss {line};
		if (line.find('*') == std::string::npos) {

			std::vector<int> temp;
			int number;
			while (ss >> number)
				temp.push_back(number);
			nums.push_back(temp);
		}
		else {
			char op;
			while (ss >> op)
				operators.push_back(op);
		}
	}
}

int main() {
	// read data
	std::vector<std::vector<int>> nums;
	std::vector<char> operators;

	std::string data_file = "./adventofcode.com_2025_day_6_input.txt";
	read_data(data_file, nums, operators);

	// show data
	for (int i = 0; i < nums.size(); ++i)
		print_vector(nums[i]);
	print_vector(operators);

	// solution
	long int result = 0;
	for (int i = 0; i < nums[0].size(); ++i) {
		long int col_result;
		if (operators[i] == '*')
			col_result = 1;
		else
			col_result = 0;

		for (int j = 0; j < nums.size(); ++j) {
			if (operators[i] == '*')
				col_result *= nums[j][i];
			else
				col_result += nums[j][i];
		}

		result += col_result;
	}

	std::cout << "Result: " << result << std::endl;
	
	return 0;
}
