#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << std::endl;
}

void read_data(const std::string& file_name, std::vector<long long int> &nums, std::vector<std::pair<long long int, long long int>> &ranges) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.find('-') != std::string::npos) {
			std::stringstream ss {line};
			std::string range_str;

			long long int start;
			std::getline(ss, range_str, '-');
			start = std::stoll(range_str);

			long long int end;
			std::getline(ss, range_str);
			end = std::stoll(range_str);

			ranges.push_back(std::make_pair(start, end));
		}
		else if (line != "")
			nums.push_back(std::stoll(line));
	}
}


int main() {
	// read data
	std::vector<long long int> nums;
	std::vector<std::pair<long long int, long long int>> ranges;

	std::string data_file = "./adventofcode.com_2025_day_5_input.txt";
	read_data(data_file, nums, ranges);

	// show data
	for (int i = 0; i < ranges.size(); ++i)
		std::cout << ranges[i].first << "-" << ranges[i].second << std::endl;
	print_vector(nums);

	// solution
	int result = 0;
	for (int i = 0; i < nums.size(); ++i)
		for (int j = 0; j < ranges.size(); ++j)
			if (nums[i] >= ranges[j].first && nums[i] <= ranges[j].second) {
				++result;
				break;
			}
	std::cout << "Result: " << result << std::endl;

	return 0;
}
