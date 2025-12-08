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

int compute_prefix_digits(int prefix) {
	int digits = 0;
	while (prefix > 0) {
		prefix /= 10;
		++digits;
	}

	return digits;
}

int main() {
	// read data
	std::vector<std::pair<long long int, long long int>> ranges;

	std::string data_file = "./adventofcode.com_2025_day_2_input.txt";
	read_data(data_file, ranges);

	// solution
	std::unordered_set<long long int> invalids;
	for (int i = 0; i < ranges.size(); ++i) {
		std::string lower_bound = std::to_string(ranges[i].first);
		std::string higher_bound = std::to_string(ranges[i].second);

		std::cout << "lower_bound: " << lower_bound << std::endl;

		// prefix
		int prefix = 1;
		int prefix_digits = 1 ;
		while (prefix_digits < higher_bound.size() / 2 + 1) {
			std::string repeated_pattern = std::to_string(prefix); 
			while (std::stoll(repeated_pattern) < ranges[i].first)
				repeated_pattern += std::to_string(prefix);
			while (repeated_pattern.size() > 1 && std::stoll(repeated_pattern) <= ranges[i].second) {
				std::cout << "* inavlid: " << repeated_pattern << std::endl;

				invalids.insert(std::stoll(repeated_pattern));

				repeated_pattern += std::to_string(prefix);
			}

			++prefix;
			prefix_digits = compute_prefix_digits(prefix);
		}

		std::cout << "higher_bound: " << higher_bound << std::endl;
	}

	std::cout << "Result: " << std::accumulate(invalids.begin(), invalids.end(), 0LL) << std::endl;

	return 0;
}
