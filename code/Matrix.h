#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <string>

// define matrix to perform like neurals in one layer
class Matrix{
public:
	Matrix(int, int);
	~Matrix();
	// set and get Matrix column and row
	void setValue(int r, int c, double v) { this->vals.at(r).at(c) = v; }
	double getValue(int r, int c) { return this->vals.at(r).at(c); }

	int getNumRows() { return this->rows; }
	int getNumCols() { return this->columns; }

	std::vector<double> vectorMultiply(std::vector<double>);

	std::string toString() const;
private:
	int columns;
	int rows;
	std::vector< std::vector<double> > vals;
};

#endif