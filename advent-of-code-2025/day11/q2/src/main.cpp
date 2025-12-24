#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <tuple>

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

std::unordered_map<std::string, std::vector<std::string>> table;
std::unordered_map<std::string, long int> memo;

long int solve(std::string origin, std::string destination) {
	if (origin == destination)
		return 1;
	if (origin == "out")
		return 0;

	long int sum = 0;
	for (int i = 0; i < table[origin].size(); ++i) {
		std::string new_origin = table[origin][i];
		if (memo.contains(new_origin))
			sum += memo[new_origin];
		else
			sum += solve(new_origin, destination);
	}

	memo[origin] = sum;
	return sum;
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
	for (int i = 0; i < devices.size(); ++i)
		table[devices[i]] = targets[i];

	long long int path_1= 1;

	path_1 *= solve("svr", "fft");
	memo.clear();

	path_1 *= solve("fft", "dac");
	memo.clear();

	path_1 *= solve("dac", "out");
	memo.clear();

	long long int path_2= 1;

	path_2 *= solve("svr", "dac");
	memo.clear();

	path_2 *= solve("dac", "fft");
	memo.clear();

	path_2 *= solve("fft", "out");
	memo.clear();

	std::cout << "Result: " << path_1 + path_2 << std::endl;

	return 0;
}
