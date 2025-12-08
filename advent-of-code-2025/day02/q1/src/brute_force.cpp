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

void read_data(const std::string& file_name, std::vector<std::pair<long long int, long long int>>& ranges) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string range_str;

		// Split line by commas
		while (std::getline(ss, range_str, ',')) {
			// Find the position of the dash to separate the two numbers
			size_t dash_pos = range_str.find('-');
			if (dash_pos != std::string::npos) {
				long long int start = std::stoll(range_str.substr(0, dash_pos));  // Number before dash
				long long int end = std::stoll(range_str.substr(dash_pos + 1));   // Number after dash

				// Add the range as a pair to the vector
				ranges.push_back({start, end});
			}
		}
	}
}

int main() {
	// read data
	std::vector<std::pair<long long int, long long int>> ranges;

	std::string data_file = "./adventofcode.com_2025_day_2_input.txt";
	read_data(data_file, ranges);

	// solution
	std::unordered_set<long long int> invalids;
	for (int i = 0; i < ranges.size(); ++i) {
		std::cout << ranges[i].first << "-" << ranges[i].second << std::endl;
		for (long long j = ranges[i].first; j <= ranges[i].second; ++j) {
			std::string str = std::to_string(j);
			if (str.size() % 2 != 0)
				continue;

			int mid = str.size() / 2;

			std::string first_part = str.substr(0, mid);
			std::string second_part = str.substr(mid, str.size());

			if (first_part == second_part)
				invalids.insert(std::stoll(first_part + second_part));
		}

		/*

		std::string lower_bound = std::to_string(ranges[i].first);
		int mid = lower_bound.size() / 2;

		long long int prefix;
		if (mid == 0)
			prefix = 1;
		else
			prefix = std::stoll(lower_bound.substr(0, mid));

		long long int number = std::stoll(std::to_string(prefix) + std::to_string(prefix));
		while (number <= ranges[i].second) {
			if (number >= ranges[i].first) {
				if (invalids.find(number) != invalids.end())
					std::cout << "hi" << std::endl;
				invalids.insert(number);
			}

			//std::cout << number << std::endl;

			++prefix;
			number = std::stoll(std::to_string(prefix) + std::to_string(prefix));
		*/
	}

	std::cout << "Result: " << std::accumulate(invalids.begin(), invalids.end(), 0LL) << std::endl;
	//std::cout << "Result: " << sum << std::endl;

	return 0;
}
