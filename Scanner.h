#pragma once
#include <iostream>
#include <string>

namespace Scanner {
	void writeVertex(const unsigned int& vertex) {
		if (vertex != UINT_MAX)
			std::cout << "V" + std::to_string(vertex + 1);
		else
			std::cout << "nil";
		/*
		if (vertex != UINT_MAX) {
			std::cout << 'V';
			if (vertex < 99)
				std::cout << '0';
			if (vertex < 9)
				std::cout << '0';
			std::cout << vertex + 1;
		} else
			std::cout << "nil ";
			*/
	}

	void writeEdge(const unsigned int& edge) {
		if (edge != UINT_MAX)
			std::cout << "E" + std::to_string(edge + 1);
		else
			std::cout << "nil";
		/*
		if (edge != UINT_MAX) {
			std::cout << 'E';
			if (edge < 99)
				std::cout << '0';
			if (edge < 9)
				std::cout << '0';
			std::cout << edge + 1;
		} else
			std::cout << "nil ";
			*/
	}

	void writeValue(const int& value) {
		if (value > -10000 && value < 10000)
			std::cout << value;
		else
			std::cout << "inf";
		/*
		if (value < 10000 && value > -10000) {
			if (value < 100)
				std::cout << ' ';
			std::cout << value;
			if (value < 10)
				std::cout << ' ';
			if (value >= 0)
				std::cout << ' ';
		} else
			std::cout << "inf ";
			*/
	}

	template<typename T>
	void writeErr(T arg) {
		std::cerr << arg << std::endl;
	}

	template<typename T, typename... Types>
	void writeErr(T arg, Types... args) {
		std::cerr << arg << ' ';
		writeErr(args...);
	}

	template<typename T>
	void write(T arg) {
		std::cout << arg;
	}

	template<typename T, typename... Types>
	void write(T arg, Types... args) {
		std::cout << arg << ' ';
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
	unsigned int uRead(Types... args) {
		unsigned int value = NULL;
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

	template<typename... Types>
	int iRead(Types... args) {
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