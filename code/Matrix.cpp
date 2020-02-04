#include "Matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// random initialize matrix
Matrix::Matrix(int r, int c): rows(r), columns(c){
	for (int i = 0; i < this->rows; ++i){
		vector<double> colValues;
		for (int j = 0; j < this->columns; ++j){
			colValues.push_back(rand() % 10000000 / double(10000000));
		}
		this->vals.push_back(colValues);
	}
}

// output format string
string Matrix::toString() const{
	ostringstream output;
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < columns; ++j){
			output << "Neural " << (j+1) << " : ";
			output << fixed << setprecision(4) << setw(10) << this->vals.at(i).at(j) << "\t";
		}
		output << endl;
	}
	output << endl;
	return output.str();
}

// calculate vector muliply matrix
vector<double> Matrix::vectorMultiply(vector<double> v){
	if (v.size() != this->getNumRows()){
		cerr << "Matrix not match!" << endl;
		assert(false);		
	}
	vector<double> res;
	for (int i = 0; i < this->getNumCols(); ++i){
		double p = 0.0;
		for (int j = 0; j < v.size(); ++j){
			p += v[j] * this->getValue(j, i);
		}
		res.push_back(p);
		p = 0.0;
	}
	return res;
}