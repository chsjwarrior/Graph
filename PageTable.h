#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//0====================CELL_CLASS====================0
class Cell {
private:
	std::string value;
	friend class PageTable;

public:
	Cell(const Cell&) = delete;
	Cell& operator=(const Cell&) = delete;
	Cell(const Cell&&) = delete;
	Cell& operator=(const Cell&&) = delete;

	explicit Cell() = default;
	~Cell() { value.clear(); }

	/*this function works for std::vector<std::string>*/
	Cell& operator=(const std::string& s) {
		value = s;
		return *this;
	}

	/*this function works for std::initializer_list<char*>*/
	Cell& operator=(const char* c) {
		value = c;
		return *this;
	}

	/*this function works for char[]*/
	Cell& operator=(const char& c) {
		value = std::string(1, c);
		return *this;
	}

	Cell& operator=(const bool b) {
		value = b ? "true" : "false";
		return *this;
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>::type>
	Cell& operator=(const T& t) {
		value = std::to_string(t);
		return *this;
	}
};

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

	void resizeColumnsWidth(const size_t size) {
		if (columnsWidth.empty())
			columnsWidth.push_back(0);
		if (size > columnsWidth.size())
			columnsWidth.resize(size, 0);
	}

	inline void updateColumnWidth(const size_t index, const size_t width) {
		columnsWidth[index] = std::max(columnsWidth[index], width);
	}

	inline void ifAutoResizingColumnsUpdateColumnWidth(const size_t index, const size_t width) {
		if (columnsWidth[index] == 0 || autoResizeColumns)
			updateColumnWidth(index, width);
	}

	inline void printFill(const char value, const size_t lenght) const {
		for (size_t i = 0; i < lenght; i++)
			std::cout << value;
	}

	void printBorderSide(const size_t startIndex, const size_t endIndex, const BorderSide& side) const {
		std::cout << side.left;

		if (columnsWidth.front() > 0) {
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

	void printCell(const std::string& value, size_t cellWidth) const {
		std::cout << value;
		if (value.size() <= cellWidth)
			cellWidth = cellWidth - value.size();
		printFill(' ', cellWidth);
	}

	void printRow(const size_t startIndex, const size_t endIndex, const Row& row) const {
		std::cout << border.vertical;

		for (size_t c = startIndex, fill; c < endIndex; ++c) {
			if (c < row.size())
				printCell(row[c]->value, columnsWidth.at(c + 1));
			else
				printFill(' ', columnsWidth[c + 1]);

			std::cout << border.vertical;
		}

		std::cout << std::endl;
	}

	void printPage(const size_t page) {
		size_t startIndex = page * columnsPage;
		size_t endIndex = std::min(startIndex + columnsPage, columnsWidth.size() - 1);

		if (startIndex >= columnsWidth.size() - 1)
			return;

		//0==============================TITLE============================================0
		if (page == 0 && title.empty() == false) {
			printBorderSide(startIndex, endIndex + 1, {border.top.left, border.horizontal, border.top.right});
			std::cout << border.vertical << title;

			size_t fill = endIndex - startIndex;
			for (size_t i = startIndex; i < endIndex + 1; ++i)
				fill += columnsWidth.at(i);
			if (rowHeader.empty())
				fill++;
			printFill(' ', fill - title.size());

			std::cout << border.vertical << std::endl;
			printBorderSide(startIndex, endIndex + 1, {border.middle.left,border.top.middle,border.middle.right});
		} else
			printBorderSide(startIndex, endIndex + 1, border.top);

		//0=============================COLUMN+HEADER=====================================0
		if (columnHeader.empty() == false) {
			if (rowHeader.empty() == false) {
				std::cout << border.vertical;
				printCell(rowHeader[0], columnsWidth.front());
			}
			//igual a print row mas com lista string
			std::cout << border.vertical;

			for (size_t c = startIndex; c < endIndex; ++c) {
				if (c < columnHeader.size())
					printCell(columnHeader[c], columnsWidth[c + 1]);
				else
					printFill(' ', columnsWidth[c + 1]);

				std::cout << border.vertical;
			}

			std::cout << std::endl;
			//igual a print row mas com lista string

			if (data.empty() == false)
				printBorderSide(startIndex, endIndex + 1, border.middle);
		}

		//0==================================ROWS=========================================0
		size_t rHeader = columnHeader.empty() ? 0 : 1;
		for (size_t r = 0; r < data.size(); ++r) {
			if (rHeader < rowHeader.size()) {
				std::cout << border.vertical;
				printCell(rowHeader[rHeader++], columnsWidth.front());
			} else if (rowHeader.empty() == false) {
				std::cout << border.vertical;
				printFill(' ', columnsWidth.front());
			}

			printRow(startIndex, endIndex, data[r]);

			if (r < data.size() - 1)
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
		resizeColumnsWidth(1);
		ifAutoResizingColumnsUpdateColumnWidth(0, description.size());
	}

	void addColumnHeader(const std::string& description) {
		columnHeader.emplace_back(description);
		resizeColumnsWidth(columnHeader.size() + 1);
		ifAutoResizingColumnsUpdateColumnWidth(columnHeader.size(), description.size());
	}

	void removeColumn(const size_t index) {
		if (index >= columnsWidth.size() - 1)
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth.erase(columnsWidth.cbegin() + index + 1);
		if (index < columnHeader.size())
			columnHeader.erase(columnHeader.cbegin() + index);
		for (auto r = data.begin(); r != data.end();) {
			if (index < r->size())
				r->erase(r->cbegin() + index);
			if (r->empty())
				r = data.erase(r);
			else
				r++;
		}
	}

	void addRow(size_t columnsCount = 0) {
		if (columnsCount == 0)
			columnsCount = columnsWidth.size() - 1;
		else
			resizeColumnsWidth(columnsCount);
		data.emplace_back(columnsCount);
		Row& newRow = data.back();

		for (auto c = newRow.begin(); c != newRow.end(); ++c)
			*c = std::make_unique<Cell>();
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void addRow(const T row, const size_t size) {
		data.emplace_back(size);
		resizeColumnsWidth(size + 1);
		Row& newRow = data.back();

		for (size_t i = 0; i < size; ++i) {
			newRow.at(i) = std::make_unique<Cell>();
			*newRow.at(i) = row[i];
			ifAutoResizingColumnsUpdateColumnWidth(i + 1, newRow.at(i)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void addRow(const std::initializer_list<T>& row) {
		data.emplace_back(row.size());
		resizeColumnsWidth(row.size() + 1);
		Row& newRow = data.back();

		for (size_t i = 0; i < row.size(); ++i) {
			newRow.at(i) = std::make_unique<Cell>();
			*newRow.at(i) = *(row.begin() + i);
			ifAutoResizingColumnsUpdateColumnWidth(i + 1, newRow.at(i)->value.size());
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
				for (const auto& h : rowHeader)
					updateColumnWidth(0, h.size());
		}

		if (index < data.size()) {
			data[index].clear();
			data.erase(data.cbegin() + index);

			size_t columnsCount = 0;
			for (const Row& r : data) {
				if (columnsCount < r.size())
					columnsCount = r.size();
				if (autoResizeColumns)
					for (size_t c = 0; c < r.size(); ++c)
						updateColumnWidth(c + 1, r.at(c)->value.size());
			}
			if (columnsCount < columnsWidth.size() - 1)
				removeColumn(columnsCount + 1);
			if (autoResizeColumns)
				for (size_t c = 0; c < columnHeader.size(); ++c)
					updateColumnWidth(c + 1, columnHeader.at(c).size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_fundamental<T>::value>>
	void setValueAt(const size_t row, const size_t column, const T value) {
		if (row >= data.size())
			throw std::out_of_range("Error - row index is out of range.");
		if (column >= columnsWidth.size() - 1)
			throw std::out_of_range("Error - column index is out of range.");

		Row& dRow = data.at(row);

		if (column >= dRow.size()) {
			dRow.reserve(columnsWidth.size() - 1);
			for (size_t i = dRow.size(); i < columnsWidth.size() - 1; ++i)
				dRow.emplace_back(new Cell());
		}
		*dRow[column] = value;
	}

	void print() {
		size_t numPages = (columnsWidth.size() - 1) / columnsPage;
		for (size_t i = 0; i <= numPages; ++i)
			printPage(i);
	}
};