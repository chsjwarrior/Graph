#pragma once
#include <iostream>
#include <limits>

namespace Scanner {
	void writeVertex(const int& vertex) {
		if (vertex > -1) {
			std::cout << 'V';
			if (vertex < 99)
				std::cout << "0";
			if (vertex < 9)
				std::cout << "0";
			std::cout << vertex + 1;
		} else
			std::cout << "nil ";
	}

	void writeEdge(const int& edge) {
		if (edge > -1) {
			std::cout << "E";
			if (edge < 99)
				std::cout << "0";
			if (edge < 9)
				std::cout << "0";
			std::cout << edge + 1;
		} else
			std::cout << "nil ";
	}

	void writeValue(const int& value) {
		if (value < 1000) {
			if (value < 100)
				std::cout << " ";
			std::cout << value;
			if (value < 10)
				std::cout << " ";
			if (value >= 0)
				std::cout << " ";
		} else
			std::cout << "inf ";
	}

	template<typename T>
	void writeErr(T arg) {
		std::cerr << arg << std::endl;
	}

	template<typename T>
	void write(T arg) {
		std::cout << arg;
	}

	template<typename T, typename... Types>
	void write(T arg, Types... args) {
		std::cout << arg << " ";
		write(args...);
	}

	template<typename T>
	void writeln(T arg) {
		std::cout << arg << std::endl;
	}

	template<typename T, typename... Types>
	void writeln(T arg, Types... args) {
		std::cout << arg << std::endl;
		writeln(args...);
	}

	template<typename... Types>
	int read(Types... args) {
		int value = NULL;
		writeln(args...);
		std::cin >> value;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");
			value = NULL;
		}
		return value;
	}
};
