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

	explicit Cell() = default;
	~Cell() { value.clear(); }

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
	enum class HeaderOrientation : bool { NONE, COLUMN, ROW };

	PageTable(const PageTable&) = delete;
	PageTable operator=(const PageTable&) = delete;
	PageTable(const PageTable&&) = delete;
	PageTable operator=(const PageTable&&) = delete;

	PageTable() : HEADER_ORIENTATION(HeaderOrientation::COLUMN) {}

	explicit PageTable(const std::string descriptions[], const size_t& size, const HeaderOrientation& headerOrientation) :
		HEADER_ORIENTATION(headerOrientation) {
		addHeader(descriptions, size);
	}

	explicit PageTable(const std::initializer_list<std::string>& descriptions, const HeaderOrientation& headerOrientation) :
		HEADER_ORIENTATION(headerOrientation) {
		addHeader(descriptions);
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
		if (HEADER_ORIENTATION == HeaderOrientation::NONE)
			throw std::invalid_argument("Error - Header Orientation is NONE.");

		header.push_back(description);
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN) {
			resizeColumnsWidth(header.size() + 1);
			updateColumnWidth(header.size(), description.size());
		} else {//if (HEADER_ORIENTATION == HeaderOrientation::ROW)
			resizeColumnsWidth(1);
			updateColumnWidth(0, header.back().size());
		}
	}

	void addHeader(const std::string descriptions[], const size_t& size) {
		if (HEADER_ORIENTATION == HeaderOrientation::NONE)
			throw std::invalid_argument("Error - Header Orientation is NONE.");

		resizeColumnsWidth(HEADER_ORIENTATION == HeaderOrientation::COLUMN ? size + 1 : 1);

		for (size_t i = 0; i < size; ++i) {
			header.push_back(descriptions[i]);
			if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
				updateColumnWidth(header.size() + 1, descriptions[i].size());
			else//if (HEADER_ORIENTATION == HeaderOrientation::ROW)
				updateColumnWidth(0, header.back().size());
		}
	}

	void addHeader(const std::initializer_list<std::string>& descriptions) {
		if (HEADER_ORIENTATION == HeaderOrientation::NONE)
			throw std::invalid_argument("Error - Header Orientation is NONE.");

		resizeColumnsWidth(HEADER_ORIENTATION == HeaderOrientation::COLUMN ? descriptions.size() + 1 : 1);

		for (auto s = descriptions.begin(); s != descriptions.end(); ++s) {
			header.push_back(*s);
			if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
				updateColumnWidth(header.size() + 1, header.back().size());
			else//if (HEADER_ORIENTATION == HeaderOrientation::ROW)
				updateColumnWidth(0, header.back().size());
		}
	}

	void addRow(size_t columnsCount) {
		if (columnsCount == 0)
			columnsCount = columnsWidth.size() - 1;
		else
			resizeColumnsWidth(columnsCount + 1);
		data.emplace_back(columnsCount);
		Row& newRow = data.back();

		for (auto c = newRow.begin(); c != newRow.end(); ++c)
			*c = std::make_unique<Cell>();
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<typename std::remove_pointer<T>::type>::value>>
	void addRow(const T& row, const size_t& size) {
		data.emplace_back(size);
		resizeColumnsWidth(size + 1);
		Row& newRow = data.back();

		for (size_t i = 0; i < size; ++i) {
			newRow.at(i) = std::make_unique<Cell>();
			*newRow.at(i) = row[i];
			updateColumnWidth(i + 1, newRow.at(i)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void addRow(const std::initializer_list<T>& row) {
		data.emplace_back(row.size());
		resizeColumnsWidth(row.size() + 1);
		Row& newRow = data.back();

		for (size_t i = 0; i < row.size(); ++i) {
			newRow.at(i) = std::make_unique<Cell>();
			*newRow.at(i) = *(row.begin() + i);
			updateColumnWidth(i + 1, newRow.at(i)->value.size());
		}
	}

	template<class T, class = typename std::enable_if<std::is_arithmetic<T>::value>>
	void setValueAt(const size_t& row, const size_t& column, const T& value) {
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
		updateColumnWidth(column + 1, dRow.at(column)->value.size());
	}

	void setColumnMaxWidth(const size_t& index, const size_t& width) {
		if (index >= columnsWidth.size() - 1)
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth[index + 1].first = true;
		columnsWidth[index + 1].second = width;
	}

	void clearColumns(const size_t& index) {
		if (index >= columnsWidth.size() - 1)
			throw std::out_of_range("Error - column index is out of range.");

		columnsWidth[index + 1].first = false;
		columnsWidth[index + 1].second = 0;
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN)
			updateColumnWidth(index + 1, header[index].size());
		for (const Row& row : data)
			if (index < row.size())
				updateColumnWidth(index + 1, row[index]->value.size());
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

	const size_t getRowCount() const {
		return data.size();
	}

	const size_t getColumnCount() const {
		return columnsWidth.size() - 1;
	}

	void print() const {
		size_t numPages = (columnsWidth.size() - 1) / columnsPage;
		for (size_t i = 0; i <= numPages; ++i)
			printPage(i);
	}

private:
	const HeaderOrientation HEADER_ORIENTATION;

	struct BorderSide {
		const unsigned char left, middle, right;
	};
	struct Border {
		const BorderSide top{218, 194, 191};
		const BorderSide middle{195, 197, 180};
		const BorderSide botton{192, 193, 217};
		const unsigned char horizontal = 196;
		const unsigned char vertical = 179;
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

	inline void resizeColumnsWidth(const size_t& size) {
		if (size == columnsWidth.size() + 1)
			columnsWidth.emplace_back(false, 0);
		else if (size > columnsWidth.size())
			columnsWidth.resize(size, std::pair<bool, size_t>(false, 0));
	}

	inline void updateColumnWidth(const size_t& index, const size_t& width) {
		if (columnsWidth.at(index).second == 0 || columnsWidth.at(index).first == false)
			columnsWidth[index].second = std::max(columnsWidth[index].second, width);
	}

	inline void printFill(const char& value, const size_t& lenght) const {
		for (size_t i = 0; i < lenght; i++)
			std::cout << value;
	}

	void printBorderSide(const size_t& startIndex, const size_t& endIndex, const BorderSide& side) const {
		std::cout << side.left;

		if (columnsWidth.front().second > 0) {
			printFill(border.horizontal, columnsWidth.front().second);
			std::cout << side.middle;
		}
		for (size_t i = 1 + startIndex; i < endIndex; ++i) {
			printFill(border.horizontal, columnsWidth.at(i).second);
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

	void printRow(const size_t& startIndex, const size_t& endIndex, const Row& row) const {
		std::cout << border.vertical;

		for (size_t c = startIndex; c < endIndex; ++c) {
			if (c < row.size())
				printCell(row[c]->value, columnsWidth[c + 1].second);
			else
				printFill(' ', columnsWidth[c + 1].second);

			std::cout << border.vertical;
		}

		std::cout << std::endl;
	}

	void printPage(const size_t& page) const {
		size_t startIndex = page * columnsPage;
		size_t endIndex = std::min(startIndex + columnsPage, columnsWidth.size() - 1);

		if (startIndex >= columnsWidth.size() - 1)
			return;

		//0==============================TITLE============================================0
		if (page == 0 && title.empty() == false) {
			size_t fill = endIndex - startIndex - 1;
			if (columnsWidth.front().second > 0)
				fill += columnsWidth.front().second + 1;
			for (size_t i = 1 + startIndex; i < endIndex + 1; ++i)
				fill += columnsWidth.at(i).second;

			if (fill < title.size()) {
				size_t newWidth = endIndex - startIndex - 1;
				if (newWidth) {
					newWidth /= title.size();
					for (size_t i = 1 + startIndex; i < endIndex + 1; ++i)
						columnsWidth[i].second = newWidth;
				} else
					columnsWidth[1].second = newWidth;
			}

			printBorderSide(startIndex, endIndex + 1, {border.top.left, border.horizontal, border.top.right});
			std::cout << border.vertical << title;

			fill = endIndex - startIndex - 1;
			if (columnsWidth.front().second > 0)
				fill += columnsWidth.front().second + 1;
			for (size_t i = 1 + startIndex; i < endIndex + 1; ++i)
				fill += columnsWidth.at(i).second;
			printFill(' ', fill - title.size());

			std::cout << border.vertical << std::endl;
			printBorderSide(startIndex, endIndex + 1, {border.middle.left,border.top.middle,border.middle.right});
		} else
			printBorderSide(startIndex, endIndex + 1, border.top);

		//0=============================COLUMN+HEADER=====================================0
		if (HEADER_ORIENTATION == HeaderOrientation::COLUMN && header.empty() == false) {
			std::cout << border.vertical;

			for (size_t c = startIndex; c < endIndex; ++c) {
				if (c < header.size())
					printCell(header[c], columnsWidth[c + 1].second);
				else
					printFill(' ', columnsWidth[c + 1].second);

				std::cout << border.vertical;
			}

			std::cout << std::endl;
			if (data.empty() == false)
				printBorderSide(startIndex, endIndex + 1, border.middle);
		}

		//0==================================ROWS=========================================0
		for (size_t r = 0; r < data.size(); ++r) {
			if (HEADER_ORIENTATION == HeaderOrientation::ROW) {
				if (r < header.size()) {
					std::cout << border.vertical;
					printCell(header[r], columnsWidth.front().second);
				} else if (header.empty() == false) {
					std::cout << border.vertical;
					printFill(' ', columnsWidth.front().second);
				}
			}

			printRow(startIndex, endIndex, data[r]);
			if (r < data.size() - 1)
				printBorderSide(startIndex, endIndex + 1, border.middle);
		}

		printBorderSide(startIndex, endIndex + 1, border.botton);
	}
};