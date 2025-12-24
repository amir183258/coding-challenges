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

void read_data(const std::string& file_name, std::vector<std::string> &devices, std::vector<std::vector<std::string>> &targets) {
	std::ifstream file {file_name};
	if (!file.is_open()) {
		std::cerr << "Error: cannot open file!\n";
		exit(1);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::string device;
		std::stringstream ss {line};

		std::getline(ss, device, ':');
		devices.push_back(device);

		std::vector<std::string> temp;
		std::string target;
		ss.ignore(); // to ignore the first white space
		while (std::getline(ss, target, ' '))
			temp.push_back(target);
		targets.push_back(temp);
	}
}

int main() {
	// read data
	std::vector<std::string> devices;
	std::vector<std::vector<std::string>> targets;
	
	std::string data_file = "./adventofcode.com_2025_day_11_input.txt";

	read_data(data_file, devices, targets);

	// show data
	std::cout << "Devices: " << std::endl;
	print_vector(devices);

	std::cout << "Targets: " << std::endl;
	for (const auto &t: targets)
		print_vector(t);

	// solution
	std::unordered_map<std::string, std::vector<std::string>> table;
	for (int i = 0; i < devices.size(); ++i)
		table[devices[i]] = targets[i];

	std::vector<std::string> outputs;
	outputs.push_back("you");

	long int result = 0;
	while (!outputs.empty()) {
		std::vector<std::string> new_outputs;

		for (int i = 0; i < outputs.size(); ++i)
			if (outputs[i] == "out")
				++result;
			else
				for (int j = 0; j < table[outputs[i]].size(); ++j)
					new_outputs.push_back(table[outputs[i]][j]);
		outputs = new_outputs;
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}
