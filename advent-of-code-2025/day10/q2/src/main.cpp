#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <unordered_map>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::vector<bool>> &diagrams, std::vector<std::vector<std::vector<int>>> &buttons,
		std::vector<std::vector<int>> &joltages) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::string expression;
		std::stringstream ss {line};
		std::vector<std::vector<int>> buttons_temp;
		while (std::getline(ss, expression, ' ')) {
			if (expression[0] == '[') {
				std::vector<bool> temp;
				for (int i = 1; i < expression.size() - 1; ++i) // ignore the first '[' and the last ']'
					if (expression[i] == '.')
						temp.push_back(false);
					else if (expression[i] == '#')
						temp.push_back(true);
				diagrams.push_back(temp);

			}
			else if (expression[0] == '(') {
				expression.erase(expression.find('('), 1);
				expression.erase(expression.find(')'), 1);

				std::string number;
				std::stringstream ss2 {expression};

				std::vector<int> temp;
				while (std::getline(ss2, number, ','))
					temp.push_back(std::stoi(number));
				buttons_temp.push_back(temp);
			}
			else if (expression[0] == '{') {
				std::vector<int> temp;

				expression.erase(expression.find('{'), 1);
				expression.erase(expression.find('}'), 1);

				std::string number;
				std::stringstream ss2 {expression};

				while (std::getline(ss2, number, ','))
					temp.push_back(std::stoi(number));
				joltages.push_back(temp);

				buttons.push_back(buttons_temp);
				buttons_temp.clear();
			}
		}
	}
}

std::vector<long int> convert_diagrams_to_integer(std::vector<std::vector<bool>> &diagrams)  {
	std::vector<long int> targets;
	for (int i = 0; i < diagrams.size(); ++i) {
		long int target = 0;
		int pow = 1;
		for (int j = 0; j < diagrams[i].size(); ++j) {
			target += diagrams[i][j] * pow;
			pow <<= 1;
		}
		targets.push_back(target);
	}
	return targets;
}

std::vector<int> number_of_minimum_buttons_for_target(std::string target, const std::vector<std::vector<int>> &buttons) {
	std::vector<int> masks;
	for (int mask = 0; mask < (1 << buttons.size()); ++mask) {
		int m = mask;
		std::string output(target.size(), '0');
		int j = 0;
		while (m > 0) {
			int first_bit = 1 & m;
			m >>= 1;

			if (first_bit)
				for (const auto &b: buttons[j])
					if (output[b] == '0')
						output[b] = '1';
					else if (output[b] == '1')
						output[b] = '0';
			j++;
		}

		if (output == target)
			masks.push_back(mask);
	}
	return masks;
}

int count_buttons_in_mask(int mask) {
	int i = 0;
	while (mask > 0) {
		if (mask & 1)
			++i;
		mask >>= 1;
	}
	return i;
}

std::vector<int> apply_button(std::vector<int> button, std::vector<int> &joltages) {
	for (const auto &b: button)
		joltages[b] -= 1;
	return joltages;
}

std::vector<int> apply_mask(int mask, std::vector<int> joltages, std::vector<std::vector<int>> buttons) {
	int i = 0;
	while (mask > 0) {
		bool use_button = mask & 1;
		if (use_button)
			apply_button(buttons[i], joltages);
		++i;
		mask >>= 1;
	}
	for (auto &j: joltages)
		j >>= 1;
	return joltages;
}

std::unordered_map<std::string, long int> cache;

std::string make_cache_key(std::vector<int> joltages) {
	std::string key = "";
	for (auto &j: joltages)
		key += std::to_string(j) + ",";
	return key;
}

long int number_of_minimum_buttons_for_joltage(std::vector<int> joltages, std::vector<std::vector<int>> &buttons) {
	if (std::all_of(joltages.begin(), joltages.end(), [](int j) { return j == 0; }))
		return 0;
	if (std::any_of(joltages.begin(), joltages.end(), [](int j) { return j < 0; }))
		return 1000000;

	// make joltage diagram here
	std::string target(joltages.size(), '0');
	for (int i = 0; i < joltages.size(); ++i)
		if (joltages[i] % 2 == 1)
			target[i] = '1';

	// resolving masks for target
	std::vector<int> masks;
	masks = number_of_minimum_buttons_for_target(target, buttons);

	// check if masks are empty
	if (masks.empty())
		return 1000000;

	int minimum_count = 100000;
	for (int i = 0; i < masks.size(); ++i) {
		std::vector<int> new_joltages = apply_mask(masks[i], joltages, buttons);

		int count;
		if (cache.find(make_cache_key(new_joltages)) != cache.end())
			count = count_buttons_in_mask(masks[i]) + 2 * cache[make_cache_key(new_joltages)];
		else
			count = count_buttons_in_mask(masks[i]) + 2 * number_of_minimum_buttons_for_joltage(new_joltages, buttons);

		if (count < minimum_count)
			minimum_count = count;
	}
	cache[make_cache_key(joltages)] = minimum_count;
	return minimum_count;
}

int main() {
	// read data
	std::vector<std::vector<bool>> diagrams;
	std::vector<std::vector<std::vector<int>>> buttons;
	std::vector<std::vector<int>> joltages;

	std::string data_file = "./adventofcode.com_2025_day_10_input.txt";

	read_data(data_file, diagrams, buttons, joltages);

	// show data
	/*
	std::cout << "Diagrams: " << std::endl;
	for (int i = 0; i < diagrams.size(); ++i)
		print_vector(diagrams[i]);
	*/

	for (int i = 0; i < buttons.size(); ++i) {
		std::cout << "Buttons " + std::to_string(i) + ": " << std::endl;
		for (int j = 0; j < buttons[i].size(); ++j)
			print_vector(buttons[i][j]);
	}

	std::cout << "Joltages: " << std::endl;
	for (int i = 0; i < joltages.size(); ++i)
		print_vector(joltages[i]);

	// solution
	long int result = 0;
	for (int i = 0; i < joltages.size(); ++i) {
		result += number_of_minimum_buttons_for_joltage(joltages[i], buttons[i]);
		//std::cout << number_of_minimum_buttons_for_joltage(joltages[i], buttons[i]) << std::endl;
		cache.clear();
	}
	std::cout << "Result: " << result << std::endl;

	return 0;
}
