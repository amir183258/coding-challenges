#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <set>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << std::endl;;
}

void read_data(const std::string& file_name, std::vector<std::string> &map, std::set<std::pair<int, int>> &beams) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	// import data to map
	std::string line;
	while (std::getline(file, line))
		map.push_back(line);

	// add the first beam to the beams
	for (int i = 0; i < map[1].size(); ++i) // second row of the map contains the first beam
		if (map[0][i] == 'S') {
			map[1][i] = '|';
			beams.insert({1, i});
		}
}

// is i, j valid in the map
bool is_valid(int i, int j, int r, int c) {
	if (i < 0 || i >= r || j < 0 || j >= c)
		return false;
	return true;
}

void update(std::vector<std::string> &map, std::set<std::pair<int, int>> &beams, std::vector<std::vector<long long int>> &timelines) {
	int r = map.size();
	int c = map[0].size();

	std::set<std::pair<int, int>> new_beams {};

	int time_lines = 1;
	for (auto beam: beams) {
		int i = beam.first;
		int j = beam.second;

		if (map[i + 1][j] == '^') {
			if (is_valid(i + 1, j - 1, r, c)) {
				map[i + 1][j - 1] = '|';
				new_beams.insert({i + 1, j - 1});
				timelines[i + 1][j - 1] += timelines[i][j];
			}

			if (is_valid(i + 1, j + 1, r, c)) {
				map[i + 1][j + 1] = '|';
				new_beams.insert({i + 1, j + 1});
				timelines[i + 1][j + 1] += timelines[i][j];
			}
		}
		else {
			map[i + 1][j] = '|';
			new_beams.insert({i + 1, j});
			timelines[i + 1][j] += timelines[i][j];
		}
	}

	beams = new_beams;
}

int main() {
	// read data
	std::vector<std::string> map;		// beams map
	std::set<std::pair<int, int>> beams;	// beams positions

	std::string data_file = "./adventofcode.com_2025_day_7_input.txt";
	read_data(data_file, map, beams);

	// show data
	/*
	print_vector(map);
	for (auto beam: beams)
		std::cout << beam.first << ", " << beam.second << std::endl;
	*/

	// solution
	std::vector<std::vector<long long int>> timelines(map.size(), std::vector<long long int>(map[0].size(), 0));
	for (auto beam: beams)
		timelines[beam.first][beam.second] = 1;

	for (int i = 2; i < map.size(); ++i) {
		update(map, beams, timelines);
		//print_vector(map);
	}

	// printing timelines matrix
	/*
	for (int i = 0; i < timelines.size(); ++i) {
		for (int j = 0; j < timelines[i].size(); ++j)
			if (timelines[i][j] != 0)
				std::cout << timelines[i][j] << ",";
		std::cout << std::endl;
	}
	*/

	std::cout << "Result: " << std::accumulate(timelines.back().begin(), timelines.back().end(), 0LL) << std::endl;
	
	return 0;
}
