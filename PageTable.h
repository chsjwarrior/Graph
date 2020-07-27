#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

/*
Essa classe deve montar uma matriz no console e
deve mostrar os valores divididos em páginas.
*/
//0====================CELL_CLASS====================0
class Cell {
private:
	std::string value;

public:
	Cell(const Cell&) = delete;
	Cell& operator=(const Cell&) = delete;
	Cell(const Cell&&) = delete;
	Cell& operator=(const Cell&&) = delete;

	explicit Cell() = default;
	~Cell() { value.clear(); }

	/*this function works for std::vector<std::string>*/
	Cell& operator=(const std::string& v) {
		value = v;
		return *this;
	}

	/*this function works for std::initializer_list<char*>*/
	Cell& operator=(const char* v) {
		value = v;
		return *this;
	}

	/*this function works for char[]*/
	Cell& operator=(const char& v) {
		value = std::string(1, v);
		return *this;
	}

	Cell& operator=(const bool v) {
		value = v ? "true" : "false";
		return *this;
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>::type>
	Cell& operator=(const T& v) {
		value = std::to_string(v);
		return *this;
	}

	void clear() { value.clear(); }

	const size_t getSize() const { return value.size(); }

	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
};

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	std::cout << cell.value;
	return os;
}

//0====================TABLE_CLASS====================0
class PageTable {
private:
	typedef std::vector<std::unique_ptr<Cell>> Row;
	bool autoResizeColumns = true;
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
	std::vector<Row> data;

	void resizeColumnsWidth(const size_t index) {
		if (columnsWidth.empty())
			columnsWidth.push_back(0);
		if (index > columnsWidth.size())
			columnsWidth.resize(index, 0);
		if (index == columnsWidth.size())
			columnsWidth.push_back(0);
	}

	inline void updateColumWidth(const size_t index, const size_t width) {
		columnsWidth[index] = std::max(columnsWidth[index], width);
	}

	inline void ifAutoResizingColumnsUpdateColumWidth(const size_t index, const size_t width) {
		if (columnsWidth[index] == 0 || autoResizeColumns)
			updateColumWidth(index, width);
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

	void printRow(const size_t startIndex, const size_t endIndex, const Row& row) const {
		std::cout << border.vertical;

		for (size_t c = startIndex; c < endIndex; ++c) {
			if (c < row.size()) {
				std::cout << *row[c];
				if (row[c]->getSize() <= columnsWidth[c + 1])
					printFill(' ', columnsWidth[c + 1] - row[c]->getSize());
			} else
				printFill(' ', columnsWidth[c + 1]);

			if (c != endIndex - 1)
				std::cout << border.vertical;
		}

		std::cout << border.vertical << std::endl;
	}

	void printPage(const size_t page) {
		size_t startIndex = page * columnsPage;

		size_t endIndex = std::min(startIndex + columnsPage, columnsWidth.size() - 1);
		//0==========================================================================0

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

			/*igual a print row mas com lista string*/
			std::cout << border.vertical;

			for (size_t c = startIndex; c < endIndex; ++c) {
				if (c < columnHeader.size()) {
					std::cout << columnHeader[c];
					printFill(' ', columnsWidth[c + 1] - columnHeader[c].size());
				} else
					printFill(' ', columnsWidth[c + 1]);

				//if (c != endIndex - 1)
				std::cout << border.vertical;
			}
			//std::cout << border.vertical << std::endl;
			std::cout << std::endl;
			/*igual a print row mas com lista de string*/

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
		for (auto r = data.begin(); data.empty() == false; r = data.erase(r))
			r->clear();
	}

	const bool isAutoResizeColumns() const { return autoResizeColumns; }
	void setAutoResizeColumns(const bool autoResizeColumns) { this->autoResizeColumns = autoResizeColumns; }
	const size_t getColumnsOfPage() const { return columnsPage; }
	void setColumnsOfPage(const size_t columnsPage) { this->columnsPage = columnsPage; }
	void setTitle(const std::string& title) { this->title = title; }
	const std::string getTitle() const { return title; }

	void setColumnWidth(const size_t index, const size_t width) {
		if (index >= columnsWidth.size())
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth[index] = width;
	}

	void addRowHeader(const std::string& description) {
		rowHeader.emplace_back(description);
		resizeColumnsWidth(0);
		ifAutoResizingColumnsUpdateColumWidth(0, description.size());
	}

	void addColumnHeader(const std::string& description) {
		columnHeader.emplace_back(description);
		resizeColumnsWidth(columnHeader.size());
		ifAutoResizingColumnsUpdateColumWidth(columnHeader.size(), description.size());
	}

	void removeColumn(const size_t index) {
		if (index + 1 >= columnsWidth.size())
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth.erase(columnsWidth.cbegin() + index + 1);
		if (columnHeader.empty() == false)
			columnHeader.erase(columnHeader.cbegin() + index);
		for (auto& r : data)
			if (index < r.size())
				r.erase(r.cbegin() + index);
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void addRow(const T row, const size_t size) {
		data.emplace_back(size);
		resizeColumnsWidth(size);
		auto& newRow = data.back();

		for (size_t i = 0; i < size; i++) {
			newRow[i] = std::make_unique<Cell>();
			*newRow[i] = row[i];
			ifAutoResizingColumnsUpdateColumWidth(i + 1, newRow.at(i)->getSize());
		}
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void addRow(const std::initializer_list<T>& row) {
		data.emplace_back(row.size());
		resizeColumnsWidth(row.size());
		auto& newRow = data.back();

		for (size_t i = 0; i < row.size(); i++) {
			newRow[i] = std::make_unique<Cell>();
			*newRow[i] = *(row.begin() + i);
			ifAutoResizingColumnsUpdateColumWidth(i + 1, newRow.at(i)->getSize());
		}
	}

	/*esse metodo precisa ser verificado*/
	void removeRow(const size_t index) {
		if (index >= rowHeader.size() && index >= data.size())
			throw std::out_of_range("Error - row index is out of range.");

		if (index < rowHeader.size()) {
			rowHeader.erase(rowHeader.cbegin() + index);
			if (rowHeader.empty())
				columnsWidth.front() = 0;
			else if (autoResizeColumns)
				for (const auto& s : rowHeader)
					updateColumWidth(0, s.size());
		}

		if (index < data.size()) {
			data[index].clear();
			data.erase(data.cbegin() + index);

			size_t columnsCount = 0;
			for (const auto& r : data) {
				if (autoResizeColumns)
					for (size_t c = 0; c < r.size(); ++c)
						updateColumWidth(c + 1, r.at(c)->getSize());
				if (columnsCount < r.size())
					columnsCount = r.size();
			}
			if (columnsCount < columnsWidth.size() - 1)
				columnsWidth.pop_back();
			if (autoResizeColumns)
				for (size_t c = 0; c < columnHeader.size(); ++c)
					updateColumWidth(c + 1, columnHeader.at(c).size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void setValueAt(const size_t row, const size_t column, const T value) {
		if (row >= data.size())
			throw std::out_of_range("Error - row index is out of range.");
		if (column >= columnsWidth.size() - 1)
			throw std::out_of_range("Error - column index is out of range.");

		auto& dRow = data.at(row);

		if (column >= dRow.size()) {
			dRow.reserve(columnsWidth.size() - 1);
			for (size_t i = dRow.size(); i < columnsWidth.size() - 1; ++i)
				dRow.emplace_back(new Cell());
		}
		*dRow[column] = value;
	}

	void show() {
		size_t numPages = (columnsWidth.size() - 1) / columnsPage;
		for (size_t i = 0; i <= numPages; ++i) {
			printPage(i);
			std::cout << std::endl;
		}
	}
};