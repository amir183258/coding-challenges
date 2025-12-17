#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <set>
#include <map>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << std::setw(4) << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<int> &x, std::vector<int> &y, std::vector<int> &z) {
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
		x.push_back(std::stoi(number));

		std::getline(ss, number, ',');
		y.push_back(std::stoi(number));

		std::getline(ss, number, ',');
		z.push_back(std::stoi(number));
	}
}

void find_minimum_distance(std::vector<std::vector<double>> &distance, int &i, int &j) {
	double minimum = distance[0][0];
	for (int r = 0; r < distance.size(); ++r)
		for (int c = 0; c < distance[r].size(); ++c)
			if (distance[r][c] < minimum) {
				minimum = distance[r][c];
				i = r;
				j = c;

			}
	distance[i][j] = std::numeric_limits<double>::infinity();
	distance[j][i] = std::numeric_limits<double>::infinity();
}

int main() {
	// read data
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> z;

	std::string data_file = "./adventofcode.com_2025_day_8_input.txt";
	read_data(data_file, x, y, z);

	// show data
	/*
	print_vector(x);
	print_vector(y);
	print_vector(z);
	*/

	// solution
	std::vector<std::vector<double>> distance(x.size(), std::vector<double>(x.size(),
				std::numeric_limits<double>::infinity()));

	for (int i = 0; i < x.size(); ++i)
		for (int j = 0; j < x.size(); ++j)
			if (i != j)
				distance[i][j] = std::sqrt(std::pow(x[j] - x[i], 2) +
						std::pow(y[j] - y[i], 2) +
						std::pow(z[j] - z[i], 2));

	std::set<std::set<int>> circuits;
	for (int i = 0; i < x.size(); ++i)
		circuits.insert({i});

	int number_of_connections = 1000;
	int i;
	int j;
	for (int noc = 0; noc < number_of_connections; ++noc) {
		find_minimum_distance(distance, i, j);

		std::set<int> first_group;
		std::set<int> second_group;

		for (auto c: circuits) {
			if (c.find(i) != c.end())
				first_group = c;
			if (c.find(j) != c.end())
				second_group = c;
		}

		circuits.erase(first_group);
		circuits.erase(second_group);

		first_group.merge(second_group);

		circuits.insert(first_group);
	}

	std::map<int, int> subset_stats;
	for (auto c: circuits) {
		if (subset_stats.find(c.size()) == subset_stats.end())
			subset_stats[c.size()] = 1;
		else
			subset_stats[c.size()] += 1;
	}

	for (auto s: subset_stats)
		std::cout << s.first << ": " << s.second << std::endl;

	long int result = 1;

	auto it = subset_stats.rbegin();

	result *= it->first;
	++it;

	result *= it->first;
	++it;

	result *= it->first;

	std::cout << "Result: " << result << std::endl;
	
	return 0;
}
