#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <map>

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
	// create an ordererd map
	std::map<long long int, std::pair<long long int, long long int>> table;
	for (int i = 0; i < ranges.size(); ++i) {
		if (table.find(ranges[i].first) == table.end())
			table[ranges[i].first] = ranges[i];
		else {
			if (table[ranges[i].first].second < ranges[i].second)
				table[ranges[i].first] = ranges[i];
		}
	}

	// show map
	/*
	for (auto &pair: table)
		std::cout << pair.first << ", " << pair.second.first << ", " << pair.second.second << std::endl;
	*/

	long long int result = 0;
	long long int start = 0;
	long long int end = 0;
	for (auto &pair: table) {
		std::pair<long long int, long long int> range = pair.second;
		if (end < range.first)
			result += range.second - range.first + 1;
		else if (range.second > end)
			result += range.second - end;

		start = range.first;
		end = range.second;
	}
	std::cout << "Result: " << result << std::endl;

	return 0;
}
