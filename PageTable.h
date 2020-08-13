#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
//0====================CELL_CLASS=====================0
class Cell {
private:
	std::string value;
	friend class PageTable;

public:
	Cell(const Cell&) = delete;
	Cell& operator=(const Cell&) = delete;
	Cell(const Cell&&) = delete;
	Cell& operator=(const Cell&&) = delete;

	explicit Cell() {
		std::cout << "Cell()" << std::endl;
	}
	~Cell() {
		value.clear();
		std::cout << "~Cell()" << std::endl;
	}

	//this function works for setValueAt
	Cell& operator=(const std::string& s) {
		value = s;
		return *this;
	}

	//this function works for std::initializer_list<char*>
	Cell& operator=(const char* c) {
		value = c;
		return *this;
	}

	//this function works for char[]
	Cell& operator=(const char& c) {
		value = std::string(1, c);
		return *this;
	}

	Cell& operator=(const bool& b) {
		value = b ? "true" : "false";
		return *this;
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	Cell& operator=(const T& t) {
		value = std::to_string(t);
		return *this;
	}
};
//0====================TABLE_CLASS====================0
class PageTable {
public:
	enum class HeaderOrientation {
		NONE, COLUMN, ROW
	};

	PageTable(const PageTable&) = delete;
	PageTable operator=(const PageTable&) = delete;
	PageTable(const PageTable&&) = delete;
	PageTable operator=(const PageTable&&) = delete;

	PageTable() : HEADER_ORIENTATION(HeaderOrientation::NONE) {}

	explicit PageTable(const HeaderOrientation& headerOrientation) :
		HEADER_ORIENTATION(headerOrientation) {}

	explicit PageTable(const size_t& rowCount, const size_t& columnCount, const HeaderOrientation& headerOrientation = HeaderOrientation::NONE) :
		HEADER_ORIENTATION(headerOrientation) {
		setRowCount(rowCount);
		setColumnCount(columnCount);
	}

	explicit PageTable(const std::string& title, const size_t& rowCount, const size_t& columnCount, const HeaderOrientation& headerOrientation = HeaderOrientation::NONE) :
		title(title), HEADER_ORIENTATION(headerOrientation) {
		setRowCount(rowCount);
		setColumnCount(columnCount);
	}

	explicit PageTable(const std::string& title, const HeaderOrientation& headerOrientation = HeaderOrientation::NONE) :
		title(title), HEADER_ORIENTATION(headerOrientation) {}

	~PageTable() {
		title.clear();
		columnsWidth.clear();
		header.clear();
		while (data.empty() == false) {
			data.back().clear();
			data.pop_back();
		}
	}

	void addHeader(const std::string& description) {
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN) {
			setColumnCount(getColumnCount() + 1);
			header.back() = description;
			updateColumnWidth(header.size(), description.size());
		}
		else if (HEADER_ORIENTATION == HeaderOrientation::ROW) {
			setRowCount(getRowCount() + 1);
			header.back() = description;
			updateColumnWidth(0, description.size());
		}
		else //if (HEADER_ORIENTATION == HeaderOrientation::NONE) 
			throw std::invalid_argument("Error - header orientation is set to NONE.");
	}

	void addHeader(const std::string descriptions[], const size_t& size) {
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
			setColumnCount(getColumnCount() + size);
		else if (HEADER_ORIENTATION == HeaderOrientation::ROW)
			setRowCount(getRowCount() + size);
		else //if (HEADER_ORIENTATION == HeaderOrientation::NONE) 
			throw std::invalid_argument("Error - header orientation is set to NONE.");

		for (size_t i = 0, j = header.size() - size; i < size; ++i, ++j) {
			header[j] = descriptions[i];
			if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
				updateColumnWidth(j + 1, header[j].size());
			else if (HEADER_ORIENTATION == HeaderOrientation::ROW)
				updateColumnWidth(0, header[j].size());
		}
	}

	void addHeader(const std::initializer_list<std::string>& descriptions) {
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
			setColumnCount(getColumnCount() + descriptions.size());
		else if (HEADER_ORIENTATION == HeaderOrientation::ROW)
			setRowCount(getRowCount() + descriptions.size());
		else //if (HEADER_ORIENTATION == HeaderOrientation::NONE) 
			throw std::invalid_argument("Error - header orientation is set to NONE.");

		for (size_t i = 0, j = header.size() - descriptions.size(); i < descriptions.size(); ++i, ++j) {
			header[j] = *(descriptions.begin() + i);
			if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
				updateColumnWidth(j + 1, header[j].size());
			else if (HEADER_ORIENTATION == HeaderOrientation::ROW)
				updateColumnWidth(0, header[j].size());
		}
	}

	void updateHeaderAt(const size_t& index, const std::string& description) {
		if (HEADER_ORIENTATION == HeaderOrientation::NONE)
			throw std::invalid_argument("Error - header orientation is set to NONE.");
		if (index >= header.size())
			throw std::out_of_range("Error - header index is out of range.");

		header.at(index) = description;
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
			updateColumnWidth(index + 1, description.size());
		else//if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
			updateColumnWidth(0, description.size());
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value>>
	void addRow(const T& row, const size_t& size) {
		setRowCount(getRowCount() + 1);
		updateRowAt(getRowCount() - 1, row, size);
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void addRow(const std::initializer_list<T>& row) {
		setRowCount(getRowCount() + 1);
		updateRowAt(getRowCount() - 1, row);
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value>>
	void updateRowAt(const size_t& index, const T& row, const size_t& size) {
		if (index >= getRowCount())
			throw std::out_of_range("Error - row index is out of range.");

		Row& cRow = data.at(index);
		const size_t columnCount = getColumnCount();
		for (size_t c = 0; c < columnCount && size; ++c) {
			*cRow.at(c) = row[c];
			updateColumnWidth(c + 1, cRow.at(c)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void updateRowAt(const size_t& index, const std::initializer_list<T>& row) {
		if (index >= getRowCount())
			throw std::out_of_range("Error - row index is out of range.");

		Row& cRow = data.at(index);
		const size_t columnCount = getColumnCount();
		for (size_t c = 0; c < columnCount && row.size(); ++c) {
			*cRow.at(c) = *(row.begin() + c);
			updateColumnWidth(c + 1, cRow.at(c)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value>>
	void addColumn(const T& column, const size_t& size) {
		setColumnCount(getColumnCount() + 1);
		updateColumnAt(getColumnCount() - 1, column, size);
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void addColumn(const std::initializer_list<T>& column) {
		setColumnCount(getColumnCount() + 1);
		updateColumnAt(getColumnCount() - 1, column);
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value>>
	void updateColumnAt(const size_t& index, const T& column, const size_t& size) {
		if (index >= getColumnCount())
			throw std::out_of_range("Error - column index is out of range.");

		const size_t rowCount = getRowCount();
		for (size_t r = 0; r < rowCount && r < size; ++r) {
			*data.at(r).at(index) = column[r];
			updateColumnWidth(index + 1, data.at(r).at(index)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void updateColumnAt(const size_t& index, const std::initializer_list<T>& column) {
		if (index >= getColumnCount())
			throw std::out_of_range("Error - column index is out of range.");

		const size_t rowCount = getRowCount();
		for (size_t r = 0; r < rowCount && r < column.size(); ++r) {
			*data.at(r).at(index) = *(column.begin() + r);
			updateColumnWidth(index + 1, data.at(r).at(index)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void updateValueAt(const size_t& row, const size_t& column, const T& value) {
		if (row >= getRowCount())
			throw std::out_of_range("Error - row index is out of range.");
		if (column >= getColumnCount())
			throw std::out_of_range("Error - column index is out of range.");

		*data.at(row).at(column) = value;
		updateColumnWidth(column + 1, data.at(row).at(column)->value.size());
	}

	const size_t getRowCount() const {
		return data.size();
	}

	void setRowCount(const size_t& size) {
		//0=========================ROW=HEADER=========================0
		if (HEADER_ORIENTATION == HeaderOrientation::ROW) {
			while (header.size() < size) {
				header.push_back("row " + std::to_string(header.size() + 1));
				updateColumnWidth(0, header.back().size());
			}
			while (header.size() > size)
				header.pop_back();
		}//0=========================ROW=HEADER=========================0

		if (data.size() < size) {
			do {
				data.emplace_back(getColumnCount());
				for (auto c = data.back().begin(); c != data.back().end(); ++c)
					*c = std::unique_ptr<Cell>(new Cell);
			} while (data.size() < size);
		}
		else
			while (data.size() > size) {
				data.back().clear();
				data.pop_back();
			}
	}

	const size_t getColumnCount() const {
		if (columnsWidth.empty())
			return 0;
		return columnsWidth.size() - 1;
	}

	void setColumnCount(size_t size) {
		size++;
		while (columnsWidth.size() < size)
			columnsWidth.emplace_back(false, 0);
		while (columnsWidth.size() > size)
			columnsWidth.pop_back();
		size--;

		//0======================COLUMN=HEADER=========================0
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN) {
			while (header.size() < size) {
				header.push_back("column " + std::to_string(header.size() + 1));
				updateColumnWidth(header.size(), header.back().size());
			}
			while (header.size() > size)
				header.pop_back();
		}//0======================COLUMN=HEADER=========================0

		for (Row& row : data)
			if (row.size() < size) {
				do
					row.emplace_back(new Cell);
				while (row.size() < size);
			}
			else
				while (row.size() > size)
					row.pop_back();
	}

	void setColumnMaxWidth(size_t index, const size_t& width) {
		if (index >= getColumnCount())
			throw std::out_of_range("Error - column index is out of range.");

		index++;
		columnsWidth[index].first = true;
		columnsWidth[index].second = width;
	}

	void clearColumnMaxWidth(size_t index) {
		if (index >= getColumnCount())
			throw std::out_of_range("Error - column index is out of range.");

		index++;
		columnsWidth[index].first = false;
		columnsWidth[index].second = 0;
		for (const Row& row : data)
			if (index < row.size())
				updateColumnWidth(index, row[index - 1]->value.size());
	}

	const size_t getColumnsForPage() const {
		return columnsPage;
	}

	void setColumnsForPage(const size_t& columnsPage) {
		this->columnsPage = columnsPage;
	}

	void setTitle(const std::string& title) {
		this->title = title;
	}

	const std::string getTitle() const {
		return title;
	}

	void print() const {
		size_t numPages = getColumnCount() / columnsPage;
		for (size_t i = 0; i <= numPages; ++i)
			printPage(i);
	}

private:
	const HeaderOrientation HEADER_ORIENTATION;

	struct BorderSide {
		const unsigned char LEFT, MIDDLE, RIGHT;
	};
	struct Border {
		const BorderSide TOP{218, 194, 191};
		const BorderSide MIDDLE{195, 197, 180};
		const BorderSide BOTTON{192, 193, 217};
		const unsigned char HORIZONTAL = 196;
		const unsigned char VERTICAL = 179;
		const unsigned char EMPTY = 32;
	} border;

	size_t columnsPage = 10;
	std::string title;
	mutable std::vector<std::pair<bool, size_t>> columnsWidth;
	/*
	pair.first == true, indica que o tamanho da coluna não pode ser alterado.
	pair.second, indica o tamanho da coluna.
	o elemento columnsWidth[0] indica a largura do header como linha.
	*/
	std::vector<std::string> header;
	typedef std::vector<std::unique_ptr<Cell>> Row;
	std::vector<Row> data;

	inline void updateColumnWidth(size_t index, const size_t& width) const {
		if (columnsWidth.at(index).second == 0 || columnsWidth.at(index).first == false)
			columnsWidth[index].second = std::max(columnsWidth[index].second, width);
	}

	inline void printFill(const unsigned char& value, const size_t& lenght) const {
		for (size_t i = 0; i < lenght; i++)
			std::cout << value;
	}

	void printBorderSide(const size_t& startColumn, const size_t& endColumn, const BorderSide& side) const {
		std::cout << side.LEFT;

		if (HEADER_ORIENTATION == HeaderOrientation::ROW) {
			printFill(border.HORIZONTAL, columnsWidth.front().second);
			std::cout << side.MIDDLE;
		}

		for (size_t i = startColumn; i < endColumn; ++i) {
			printFill(border.HORIZONTAL, columnsWidth[i + 1].second);
			if (i != endColumn - 1)
				std::cout << side.MIDDLE;
		}

		std::cout << side.RIGHT << std::endl;
	}

	void printCell(const std::string& value, size_t cellWidth) const {
		std::cout << value;
		if (value.size() <= cellWidth)
			cellWidth = cellWidth - value.size();
		printFill(border.EMPTY, cellWidth);
	}

	void printRow(const size_t& startColumn, const size_t& endColumn, const Row& row) const {
		std::cout << border.VERTICAL;
		for (size_t c = startColumn; c < endColumn; ++c) {
			printCell(row[c]->value, columnsWidth[c + 1].second);
			std::cout << border.VERTICAL;
		}
		std::cout << std::endl;
	}

	void printPage(const size_t& page) const {
		size_t startColumn = page * columnsPage;
		size_t endColumn = std::min(startColumn + columnsPage, getColumnCount());

		if (startColumn >= getColumnCount())
			return;
		//0==============================TITLE============================================0
		if (page == 0 && title.empty() == false) {
			size_t fill = endColumn - startColumn;
			fill += columnsWidth.front().second;
			for (size_t i = startColumn; i < endColumn; ++i)
				fill += columnsWidth.at(i + 1).second;

			if (fill < title.size()) {
				fill = endColumn - startColumn;
				fill = title.size() / fill;//divide by zero?
				for (size_t i = startColumn; i < endColumn; ++i)
					updateColumnWidth(i + 1, fill);
				fill = 0;
			}

			printBorderSide(startColumn, endColumn, {border.TOP.LEFT, border.HORIZONTAL, border.TOP.RIGHT});
			std::cout << border.VERTICAL;

			if (fill == 0) {
				fill = endColumn - startColumn;
				fill += columnsWidth.front().second;
				for (size_t i = startColumn; i < endColumn; ++i)
					fill += columnsWidth.at(i + 1).second;
			}
			if (HEADER_ORIENTATION != HeaderOrientation::ROW)
				fill--;
			printCell(title, fill);

			std::cout << border.VERTICAL << std::endl;
			printBorderSide(startColumn, endColumn, {border.MIDDLE.LEFT,border.TOP.MIDDLE,border.MIDDLE.RIGHT});
		}
		else
			printBorderSide(startColumn, endColumn, border.TOP);

		//0=============================COLUMN+HEADER=====================================0		
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN) {
			for (size_t c = startColumn; c < endColumn; ++c) {
				std::cout << border.VERTICAL;
				printCell(header[c], columnsWidth[c + 1].second);
			}

			std::cout << border.VERTICAL << std::endl;
			if (data.empty() == false)
				printBorderSide(startColumn, endColumn, border.MIDDLE);
		}
		//0==================================ROWS=========================================0
		for (size_t r = 0; r < data.size(); ++r) {
			if (HEADER_ORIENTATION == HeaderOrientation::ROW) {
				std::cout << border.VERTICAL;
				printCell(header[r], columnsWidth.front().second);
			}

			printRow(startColumn, endColumn, data[r]);
			if (r < data.size() - 1)
				printBorderSide(startColumn, endColumn, border.MIDDLE);
		}

		printBorderSide(startColumn, endColumn, border.BOTTON);
	}
};