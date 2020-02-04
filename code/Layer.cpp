#include "Layer.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

// initialize layer
Layer::Layer(int numPreOutput, int neuralNum){
	this->neuralNum = neuralNum;
	this->weight = new Matrix(numPreOutput + 1, neuralNum);
}

// calculate activated function sigmoid
double Layer::activated(double val){
	return 1 / (1 + exp(-val));
}

// calculate derivative of activated function
double Layer::derivated(double val){
	return activated(val) * (1 - activated(val));
}

// one layer feed forward
vector<double> Layer::feedForward(){
	vector<double> res;
	res = this->weight->vectorMultiply(this->input);
	for (int i = 0; i < res.size(); ++i){
		res[i] = activated(res[i]);
	}
	return res;
}

// calculate layer derivative of sigmoid
vector<double> Layer::derivatedVector(){
	vector<double> res;

	res = this->weight->vectorMultiply(this->input);
	for (int i = 0; i < res.size(); ++i){
		res[i] = derivated(res[i]);
	}
	return res;
}

// calculate layer's derivative before sigmoid to update weight
vector<double> Layer::middleDerivatedValue(vector<double> nextLayerDelta){
	vector<double> res;
	vector<double> currDerivated = derivatedVector();

	for (int i = 0; i < currDerivated.size(); ++i){
		res.push_back(currDerivated[i] * nextLayerDelta[i]);
	}
	return res;
}

// calculate layer's derivative to pass to the former layer
vector<double> Layer::layerDelta(vector<double> nextLayerDelta){
	vector<double> middleDelta = middleDerivatedValue(nextLayerDelta);
	vector<double> res;
	for (int i = 0; i < weight->getNumRows(); ++i){
		double temp = 0.0;
		for (int j = 0; j < weight->getNumCols(); ++j){
			temp += weight->getValue(i, j) * middleDelta[j];
		}
		res.push_back(temp);
	}
	return res;
}

// use middleDelta, learning rate and current layer input to update weight
void Layer::updateWeight(vector<double> nextLayerDelta, double lr){
	learningRate = lr;
	vector<double> middleDelta = middleDerivatedValue(nextLayerDelta);
	for (int i = 0; i < weight->getNumRows(); ++i){
		for (int j = 0; j < weight->getNumCols(); ++j){
			weight->setValue(i, j, weight->getValue(i, j) - learningRate * middleDelta[j] * input[i]);
		}
	}
}

// transform format output string
string Layer::weightToString() const{
	return this->weight->toString();
}

// add bias 1 at the end of input data
void Layer::setInput(vector<double> v){
	v.push_back(1);
	this->input = v;
}