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
		std::cout << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::vector<bool>> &diagrams, std::vector<std::vector<int>> &buttons,
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
		std::vector<int> buttons_temp;
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

				long int button = 0;
				while (std::getline(ss2, number, ','))
					button += (1 << std::stoi(number));
				buttons_temp.push_back(button);
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

int main() {
	// read data
	std::vector<std::vector<bool>> diagrams;
	std::vector<std::vector<int>> buttons;
	std::vector<std::vector<int>> joltages;

	std::string data_file = "./adventofcode.com_2025_day_10_input.txt";

	read_data(data_file, diagrams, buttons, joltages);

	// show data
	std::cout << "Diagrams: " << std::endl;
	for (int i = 0; i < diagrams.size(); ++i)
		print_vector(diagrams[i]);

	std::cout << "Buttons: " << std::endl;
	for (int i = 0; i < buttons.size(); ++i)
		print_vector(buttons[i]);

	std::cout << "Joltages: " << std::endl;
	for (int i = 0; i < joltages.size(); ++i)
		print_vector(joltages[i]);

	// solution
	// convert diagrams to plain integer
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

	std::cout << "Targets: " << std::endl;
	print_vector(targets);

	int result = 0;
	for (int i = 0; i < targets.size(); ++i) {
		int min_buttons = 1000;

		for (int mask = 0; mask < (1 << buttons[i].size()); ++mask) {
			int number_of_buttons = 0;

			int m = mask;
			int output = 0;
			int j = 0;
			while (m > 0) {
				int first_bit = 1 & m;
				m >>= 1;

				if (first_bit) {
					output ^= buttons[i][j];
					++number_of_buttons;
				}
				j++;
			}

			if (output == targets[i])
				if (number_of_buttons < min_buttons)
					min_buttons = number_of_buttons;
		}
		result += min_buttons;
	}

	std::cout << "Result: " << result << std::endl;
	

	return 0;
}
