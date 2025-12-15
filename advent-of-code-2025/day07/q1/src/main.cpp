#include <iostream>
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

int update(std::vector<std::string> &map, std::set<std::pair<int, int>> &beams) {
	int r = map.size();
	int c = map[0].size();

	std::set<std::pair<int, int>> new_beams {};

	int collision_count = 0;
	for (auto beam: beams) {
		int i = beam.first;
		int j = beam.second;

		if (map[i + 1][j] == '^') {
			++collision_count;
			if (is_valid(i + 1, j - 1, r, c) && map[i + 1][j - 1] == '.') {
				map[i + 1][j - 1] = '|';
				new_beams.insert({i + 1, j - 1});
			}

			if (is_valid(i + 1, j + 1, r, c) && map[i + 1][j + 1] == '.') {
				map[i + 1][j + 1] = '|';
				new_beams.insert({i + 1, j + 1});
			}
		}
		else if (map[i + 1][j] == '.') {
			map[i + 1][j] = '|';
			new_beams.insert({i + 1, j});
		}
	}

	beams = new_beams;

	return collision_count;
}

int main() {
	// read data
	std::vector<std::string> map;		// beams map
	std::set<std::pair<int, int>> beams;	// beams positions

	std::string data_file = "./adventofcode.com_2025_day_7_input.txt";
	read_data(data_file, map, beams);

	// show data
	print_vector(map);
	for (auto beam: beams)
		std::cout << beam.first << ", " << beam.second << std::endl;

	// solution
	int result = 0;
	for (int i = 2; i < map.size(); ++i) {
		result += update(map, beams);
		//print_vector(map);
	}

	std::cout << "Result: " << result << std::endl;
	
	return 0;
}
