#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <numbers>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << std::setw(3) << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<long long int> &x, std::vector<long long int> &y) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss {line};
		std::string number;

		std::getline(ss, number, ',');
		x.push_back(std::stoll(number));

		std::getline(ss, number, ',');
		y.push_back(std::stoll(number));
	}
}

bool is_valid_rectangle(int i, int j, std::vector<long long int> &x, std::vector<long long int> &y) {
	if (x[i] == x[j] || y[i] == y[j])
		return true;

	// (x[i], y[i]) and (x[j], y[j]) are in the area
	// (x[j], y[i]) and (x[i], y[j]) should be checked
	long long int x_rect_1 = x[j];
	long long int y_rect_1 = y[i];

	long long int x_rect_2 = x[i];
	long long int y_rect_2 = y[j];

	// define a slope (not 0, 90, 180, 270)
	double m = std::numbers::pi;

	int collisions_1 = 0;
	int collisions_2 = 0;
	for (int k = 0; k < x.size() - 1; ++k) {
		if (x[k] == x[k + 1]) {
			double collision_y;
			collision_y = m * (x[k] - x_rect_1) + y_rect_1;

			if (collision_y > y_rect_1)
				continue;

			if ((collision_y <= y[k] && collision_y >= y[k + 1]) || 
				(collision_y >= y[k] && collision_y <= y[k + 1]))
				++collisions_1;
		}
		else {
			double collision_x;
			collision_x = (y[k] - y_rect_1) / m + x_rect_1;

			if (collision_x > x_rect_1)
				continue;

			if ((collision_x <= x[k] && collision_x >= x[k + 1]) || 
				(collision_x >= x[k] && collision_x <= x[k + 1]))
				++collisions_1;
		}
	}

	for (int k = 0; k < x.size() - 1; ++k) {
		if (x[k] == x[k + 1]) {
			double collision_y;
			collision_y = m * (x[k] - x_rect_2) + y_rect_2;

			if (collision_y > y_rect_2)
				continue;

			if ((collision_y <= y[k] && collision_y >= y[k + 1]) || 
				(collision_y >= y[k] && collision_y <= y[k + 1]))
				++collisions_2;
		}
		else {
			double collision_x;
			collision_x = (y[k] - y_rect_2) / m + x_rect_2;

			if (collision_x > x_rect_2)
				continue;

			if ((collision_x <= x[k] && collision_x >= x[k + 1]) || 
				(collision_x >= x[k] && collision_x <= x[k + 1]))
				++collisions_2;
		}
	}

	if (collisions_1 != collisions_2)
		return false;

	if (collisions_1 % 2 == 1 && collisions_2 % 2 == 1)
		return true;
	
	return false;
}

long long int find_max(std::vector<std::vector<long long int>> &areas) {
	long long int maximum = areas[0][0];
	int r = 0;
	int c = 0;
	for (int i = 0; i < areas.size(); ++i)
		for (int j = 0; j < areas[i].size(); ++j)
			if (areas[i][j] > maximum) {
				maximum = areas[i][j];
				r = i;
				c = j;
			}

	std::cout << r << " and " << c << std::endl;

	return maximum;
}

int main() {
	// read data
	std::vector<long long int> x;
	std::vector<long long int> y;

	std::string data_file = "./adventofcode.com_2025_day_9_input.txt";

	read_data(data_file, x, y);

	// show data
	print_vector(x);
	print_vector(y);

	// solution
	std::vector<std::vector<long long int>> areas(x.size(), std::vector<long long int>(x.size(), 0));

	for (int i = 0; i < areas.size(); ++i)
		for (int j = 0; j < areas[i].size(); ++j)
			if (is_valid_rectangle(i, j, x, y) && y[i] > 48550 && y[j] > 48550)
				areas[i][j] = (std::abs(x[j] - x[i]) + 1) * (std::abs(y[j] - y[i]) + 1);
			else
				areas[i][j] = 0;

	std::cout << std::endl;
	std::cout << "Result: " << find_max(areas) << std::endl;

	return 0;
}
