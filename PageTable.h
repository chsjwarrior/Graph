#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip> 

class Cell {
public:
	Cell(const Cell&) = delete;
	Cell& operator=(const Cell&) = delete;
	Cell(const Cell&&) = delete;
	Cell& operator=(const Cell&&) = delete;

	Cell() {}
	~Cell() {}

	Cell& operator=(const std::string& v) {
		value = v;
		return *this;
	}

	Cell& operator=(const char* v) {
		value = v;
		return *this;
	}

	Cell& operator=(const char& v) {
		value = std::string(1, v);
		return *this;
	}

	Cell& operator=(const bool v) {
		value = v ? "true" : "false";
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	Cell& operator=(const T& v) {
		value = std::to_string(v);
		return *this;
	}

	const size_t size() const { return value.size(); }

	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
private:
	std::string value;
};

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	std::cout << cell.value;
	return os;
}

class PageTable {
private:
	bool columnsAutoResize = true;
	size_t columnsPage = 10;

	struct BorderSide {
		const unsigned char left, middle, right;
	};
	struct Border {
		const BorderSide top{218, 194, 191};
		const BorderSide middle{195, 197, 180};
		const BorderSide botton{192, 193, 217};
		const unsigned char horizontal = 196;
		const unsigned char vertical = 179;
	};

	Border border;
	std::string title;
	std::vector<size_t> columnsWidth;
	std::vector<std::string> rowHeader, columnHeader;
	std::vector<std::vector<std::string>> data;
	std::vector<Cell*> cells;

	void columnsWidthResize(const size_t index) {
		if (columnsWidth.empty())
			columnsWidth.push_back(0);
		if (index > columnsWidth.size())
			columnsWidth.resize(index, 0);
		if (index == columnsWidth.size())
			columnsWidth.push_back(0);
	}

	inline void updateColumsWidth(const size_t index, const size_t width) {
		if (columnsWidth[index] == 0 || columnsAutoResize)
			columnsWidth[index] = std::max(columnsWidth[index], width);
	}

	inline void printFill(const char value, const size_t lenght) const {
		for (size_t i = 0; i < lenght; i++)
			std::cout << value;
	}

	void printBorderSide(const size_t startIndex, const size_t endIndex, const BorderSide& side) const {
		std::cout << side.left;

		if (columnsWidth[0] > 0) {
			printFill(border.horizontal, columnsWidth[0]);
			std::cout << side.middle;
		}

		for (size_t i = 1 + startIndex; i < endIndex; ++i) {
			printFill(border.horizontal, columnsWidth[i]);
			if (i != endIndex - 1)
				std::cout << side.middle;
		}

		std::cout << side.right << std::endl;
	}

	void printRow(const size_t startIndex, const size_t endIndex, const std::vector < std::string> row) const {
		std::cout << border.vertical;

		for (size_t c = startIndex; c < endIndex; ++c) {
			if (c < row.size()) {
				std::cout << row[c];
				printFill(' ', columnsWidth[c + 1] - row[c].size());
			} else
				printFill(' ', columnsWidth[c + 1]);

			if (c != endIndex - 1)
				std::cout << border.vertical;
		}

		std::cout << border.vertical << std::endl;
	}

public:
	PageTable(const PageTable&) = delete;
	PageTable operator=(const PageTable&) = delete;
	PageTable(const PageTable&&) = delete;
	PageTable operator=(const PageTable&&) = delete;

	explicit PageTable() {}

	explicit PageTable(const std::string title) : title(title) {}

	~PageTable() {
		title.clear();
		columnsWidth.clear();
		rowHeader.clear();
		columnHeader.clear();
		for (auto r = data.begin(); data.empty() == false; r = data.erase(r)) {
			r->clear();
		}
	}

	const bool getColumnsAutoResize() const { return columnsAutoResize; }
	void setColumnsAutoResize(const bool columnsAutoResize) { this->columnsAutoResize = columnsAutoResize; }
	const size_t getColumnsOfPage() const { return columnsPage; }
	void setColumnsOfPage(const size_t columnsPage) { this->columnsPage = columnsPage; }
	void setTitle(const std::string& title) { this->title = title; }
	const std::string getTitle() const { return title; }

	void setColumWidth(const size_t index, const size_t width) {
		if (index >= columnsWidth.size())
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth[index] = width;
	}

	void setRowHeader(const size_t index, const std::string& description) {
		if (index >= columnsWidth.size())
			throw std::out_of_range("Error - row index is out of range.");

		rowHeader[index] = description;
		updateColumsWidth(0, description.size());
	}

	void addRowHeader(const std::string& description) {
		rowHeader.emplace_back(description);
		columnsWidthResize(0);
		updateColumsWidth(0, description.size());
	}

	void setColumnHeader(const size_t index, const std::string& description) {
		if (index >= columnsWidth.size())
			throw std::out_of_range("Error - column index is out of range.");

		columnHeader[index] = description;
		updateColumsWidth(index + 1, description.size());
	}

	void addColumnHeader(const std::string& description) {
		columnHeader.emplace_back(description);
		columnsWidthResize(columnHeader.size());
		updateColumsWidth(columnHeader.size(), description.size());
	}

	void addRow(const std::vector<std::string>& row) {
		data.emplace_back(row.size());
		columnsWidthResize(row.size());

		for (size_t i = 0; i < row.size(); i++) {
			data.back()[i] = row[i];
			updateColumsWidth(i + 1, data.back()[i].size());
		}
	}

	void addRow(const std::string row[], const size_t size) {
		data.emplace_back(size);
		columnsWidthResize(size);

		for (size_t i = 0; i < size; i++) {
			data.back()[i] = row[i];
			updateColumsWidth(i + 1, data.back()[i].size());
		}
	}

	void addRow(const std::initializer_list<std::string>& row) {
		data.emplace_back(row.size());
		columnsWidthResize(row.size());

		for (size_t i = 0; i < row.size(); i++) {
			data.back()[i] = *(row.begin() + i);
			updateColumsWidth(i + 1, data.back()[i].size());
		}
	}
	
	void printPage(const size_t page) {
		size_t startIndex = page * columnsPage;

		size_t endIndex = std::min(startIndex + columnsPage, columnsWidth.size() - 1);

		//==========================================================================\\

		if (title.empty() == false) {
			printBorderSide(startIndex, endIndex + 1, {border.top.left, border.horizontal, border.top.right});
			std::cout << border.vertical << title;

			size_t count = columnsWidth.size();
			for (size_t i = startIndex; i < endIndex; ++i)
				count += columnsWidth[i];
			printFill(' ', count - title.size());

			std::cout << border.vertical << std::endl;
			printBorderSide(startIndex, endIndex + 1, {border.middle.left,border.top.middle,border.middle.right});
		} else
			printBorderSide(startIndex, endIndex + 1, border.top);

		if (columnHeader.empty() == false) {
			if (rowHeader.empty() == false) {
				std::cout << border.vertical;

				std::cout << rowHeader[0];
				printFill(' ', columnsWidth[0] - rowHeader[0].size());
			}

			printRow(startIndex, endIndex, columnHeader);

			if (data.empty() == false)
				printBorderSide(startIndex, endIndex + 1, border.middle);
		}

		size_t rHeader = columnHeader.empty() ? 0 : 1;
		for (size_t r = 0; r < data.size(); ++r, ++rHeader) {
			if (r < rowHeader.size()) {
				std::cout << border.vertical;

				std::cout << rowHeader[rHeader];
				printFill(' ', columnsWidth[0] - rowHeader[rHeader].size());
			}
			printRow(startIndex, endIndex, data[r]);

			if (r != data.size() - 1)
				printBorderSide(startIndex, endIndex + 1, border.middle);
		}

		printBorderSide(startIndex, endIndex + 1, border.botton);
	}
	/*
	void show() {
		
	}
	*/
};