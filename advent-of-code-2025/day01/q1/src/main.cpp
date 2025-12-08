#include <iostream>
#include <string>
#include <fstream>
#include <vector>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name,
	       std::vector<char>& directions,
	       std::vector<int>& numbers)
{
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	char dir;
	int num;
	while (file >> dir >> num) {
		directions.push_back(dir);
		numbers.push_back(num);
	}
}

int main() {
	// read data
	std::vector<char> directions;
	std::vector<int> numbers;

	std::string data_file = "./adventofcode.com_2025_day_1_input.txt";
	read_data(data_file, directions, numbers);

	// solution
	int start = 50;
	int counter = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		int sign = 1;
		if (directions[i] == 'L')
			sign = -1;

		start += sign * numbers[i];

		if (start < 0)
			start = 100 - (-start % 100);

		start %= 100;

		if (start == 0)
			++counter;

		//std::cout << directions[i] << numbers[i] << ": " << start << std::endl;
	}
	std::cout << "Result: " << counter << std::endl;

	return 0;
}
