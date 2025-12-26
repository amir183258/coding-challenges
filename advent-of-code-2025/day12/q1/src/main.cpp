#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <unordered_map>

template <class T>
void print_vector(const std::vector<T>& vec) {
	for (const T element : vec)
		std::cout << element << " ";
	std::cout << std::endl;
}

void read_data(const std::string& file_name, std::vector<std::vector<std::string>> &blocks,
		std::vector<std::vector<int>> &dimensions,
		std::vector<std::vector<int>> &required_blocks) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> block;
		if (line[0] == '#' || line[0] == '.') {
			// first line of block
			block.push_back(line);

			// second line of block
			std::getline(file, line);
			block.push_back(line);

			// third line of block
			std::getline(file, line);
			block.push_back(line);

			blocks.push_back(block);
		}
		else if (line.find('x') != std::string::npos) {
			std::vector<int> dimension;

			std::stringstream ss {line};
			std::string number;

			// first dimension
			std::getline(ss, number, 'x');
			dimension.push_back(std::stoi(number));

			// second dimension
			std::getline(ss, number, ':');
			dimension.push_back(std::stoi(number));

			dimensions.push_back(dimension);

			// ignore first space character
			ss.ignore();

			// required blocks
			std::vector<int> required;

			while (std::getline(ss, number, ' '))
				required.push_back(std::stoi(number));
			required_blocks.push_back(required);
		}
	}
}

int main() {
	// read data
	std::vector<std::vector<std::string>> blocks;
	std::vector<std::vector<int>> dimensions;
	std::vector<std::vector<int>> required_blocks;

	std::string data_file = "./adventofcode.com_2025_day_12_input.txt";

	read_data(data_file, blocks, dimensions, required_blocks);

	// show data
	std::cout << "Blocks: " << std::endl;
	for (int i = 0; i < blocks.size(); ++i)
		print_vector(blocks[i]);

	std::cout << "Dimensions: " << std::endl;
	for (int i = 0; i < dimensions.size(); ++i)
		print_vector(dimensions[i]);

	std::cout << "Required Blocks: " << std::endl;
	for (int i = 0; i < required_blocks.size(); ++i)
		print_vector(required_blocks[i]);

	// solution
	// compute each block size
	std::vector<int> blocks_sizes;
	for (int i = 0; i < blocks.size(); ++i) {
		int size = 0;
		for (int j = 0; j < blocks[i].size(); ++j)
			for (int k = 0; k < blocks[i][j].size(); ++k)
				if (blocks[i][j][k] == '#')
					++size;
		blocks_sizes.push_back(size);
	}

	// check if number of tiles in each block less than total grid tiles
	int result = 0;
	for (int i = 0; i < dimensions.size(); ++i) {
		int total_grid_size = dimensions[i][0] * dimensions[i][1];

		int total_blocks_size = 0;
		for (int j = 0; j < required_blocks[i].size(); ++j)
			total_blocks_size += required_blocks[i][j] * blocks_sizes[j];

		if (total_blocks_size * 1.3 < total_grid_size) // 1.3 is just a guess
			++result;
	}
	std::cout << "Result: " << result << std::endl;

	return 0;
}
