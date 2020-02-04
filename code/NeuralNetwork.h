#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "Layer.h"
#include <vector>
#include <string>
#include <iostream>
class NeuralNetwork{
public:
	NeuralNetwork();
	~NeuralNetwork();
	// set parameters functions
	void setLayers(std::vector<int> n) {this->neuralsInLayers = n;}
	void setLearningRate(double r) {this->learningRate = r;}
	void setLossToleration(double l) {this->lossToleration = l;}
	void setMaxLoops(int loops) {this->maxLoops = loops;}

	// train predict score function
	void training(std::vector<std::vector<double> >, std::vector<std::vector<double> >);
	std::vector<double> predict(std::vector<double>);
	void score(std::vector<std::vector<double> >, std::vector<std::vector<double> >);

	// output string function
	std::string toString() const;

private:
	// initial weight function
	void initialWeight(std::vector<std::vector<double> >);
	// feedforward function
	void feedForward(std::vector<double>, std::vector<double>);
	// backward function
	void backward();	
	std::vector<std::vector<double> > target;
	std::vector<std::vector<double> >input;
	std::vector<Layer*> layers;
	double learningRate;
	double lossToleration;
	int maxLoops;
	double L2Loss;
	std::vector<double> currLoss;
	std::vector<int> neuralsInLayers;
};

#endif