#ifndef LAYER_H
#define LAYER_H
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <string>

// define layer, each layer contain n neurals, 
// layers can perform their own forward, backward and update weight function
class Layer{
public:
	Layer(int, int);
	~Layer();
	std::vector<double> feedForward();
	std::vector<double> derivatedVector();
	std::vector<double> middleDerivatedValue(std::vector<double>);
	std::vector<double> layerDelta(std::vector<double>);
	void updateWeight(std::vector<double>, double);
	std::string weightToString() const;
	void setInput(std::vector<double>);
	void setLearningRate(double r) { this->learningRate = r; }
	
private:
	double activated(double);
	double derivated(double);
	std::vector<double> input;
	int neuralNum;
	double learningRate;
	Matrix *weight;
};
#endif