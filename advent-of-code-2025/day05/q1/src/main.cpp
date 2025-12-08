#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::string>& grid) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line))
		grid.push_back(line);
}

bool is_valid(int r, int c, int i, int j) {
	if (i < 0 || j < 0 || i >= r || j >= c)
		return false;
	return true;
}

int main() {
	// read data
	std::vector<std::string> grid;

	std::string data_file = "./adventofcode.com_2025_day_4_input.txt";
	read_data(data_file, grid);

	// show data
	print_vector(grid);

	// solution
	int result = 0;
	
	int r = grid.size();
	int c = grid[0].size();
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			if (grid[i][j] == '@') {
				int rolls_around = -1;			// the center of window is a roll
				for (int m = -1; m <= 1; ++m)
					for (int n = -1; n <= 1; ++n)
						if (is_valid(r, c, i + m, j + n) && grid[i + m][j + n] == '@')
							++rolls_around;
				if (rolls_around < 4)
					++result;
			}

	std::cout << "Result: " << result << std::endl;

	return 0;
}
