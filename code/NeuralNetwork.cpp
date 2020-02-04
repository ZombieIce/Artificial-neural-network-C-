#include "NeuralNetwork.h"
#include "Layer.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

NeuralNetwork::NeuralNetwork(){};

void NeuralNetwork::initialWeight(std::vector<std::vector<double> > data){
	layers.clear();
	// according to the input size decide first hidden layer size
	int inputNeurals = data[0].size();
 	vector<int>::iterator it = neuralsInLayers.begin();
 	neuralsInLayers.insert(it, inputNeurals);

 	// generate hidden layers
	for (int i = 0; i < neuralsInLayers.size() - 1; ++i){
		Layer *layer = new Layer(neuralsInLayers[i], neuralsInLayers[i+1]);
		layers.push_back(layer);
	}
}

void NeuralNetwork::feedForward(vector<double> currInput, vector<double> target){
	vector<double> temp = currInput;

	// feedforward
	for (int i = 0; i < layers.size(); ++i){
		layers[i]->setInput(temp);
		temp = layers[i]->feedForward();
	}
	L2Loss = 0.0;
	vector<double> tempLoss;

	// calculate error and loss derivative
	for (int i = 0; i < temp.size(); ++i){
		double lossDelta = target[i] - temp[i];
		tempLoss.push_back(-2 * lossDelta);
		L2Loss += lossDelta * lossDelta; 
	}
	currLoss.clear();
	currLoss = tempLoss;
}

void NeuralNetwork::backward(){
	vector<double> nextLayerDelta;
	nextLayerDelta = currLoss;
	vector<double> currLayerDelta;
	// calculate delta layer and update weight
	for (int i = layers.size() - 1; i >= 0 ; --i){
		currLayerDelta = layers[i]->layerDelta(nextLayerDelta);
		layers[i]->updateWeight(nextLayerDelta, learningRate);
		nextLayerDelta = currLayerDelta;
	}
}

std::vector<double> NeuralNetwork::predict(vector<double> currInput){
	vector<double> temp = currInput;
	for (int i = 0; i < layers.size(); ++i){
		layers[i]->setInput(temp);
		temp = layers[i]->feedForward();
	}
	// set 0.5 shreshold to get prediction label
	for (int i = 0; i < temp.size(); ++i){
		if (temp[i] > 0.5){
			temp[i] = 1;
		}else{
			temp[i] = 0;
		}
	}
	return temp;
}

void NeuralNetwork::score(vector<vector<double> > inputs, vector<vector<double> > yTrue){
	int numOfFail = 0;
	// sum up wrong prediction number
	for (int i = 0; i < inputs.size(); ++i){
		vector<double> yPred = predict(inputs[i]);
		if (yPred != yTrue[i]){
			numOfFail++;
			continue;
		}
	}
	// calculate score
	double score = 1 - numOfFail / (static_cast<double>(inputs.size()));
	cout << "The accuracy score is : " << score << endl;
}

void NeuralNetwork::training(vector<vector<double> >data, vector<vector<double> > t){
	// initialize weight, set train label and target label
	this->initialWeight(data);
	int loop = 0;
	this->input = data;
	this->target = t;

	int numerLastLayerNeural = target[0].size();
	int numLastInput = neuralsInLayers[neuralsInLayers.size() - 1];

	// add output layer at last
	Layer *lastLayer = new Layer(numLastInput, numerLastLayerNeural);
	layers.push_back(lastLayer);

	// train and display error
	while (loop <= maxLoops){
		loop++;
		double oneLoopLoss = 0.0;
		for (int i = 0; i < input.size(); ++i){
			feedForward(input[i], target[i]);
			backward();
			oneLoopLoss += L2Loss;
		}
		oneLoopLoss = oneLoopLoss / input.size();
		if (loop % 500 == 0 || loop == 1){
			cout << "Current loop: " << loop << "=======> Loss: " << oneLoopLoss << endl;
		}
		if ((oneLoopLoss < 0 && oneLoopLoss > -lossToleration) || (oneLoopLoss > 0 && oneLoopLoss < lossToleration) ) {
			cout << "Current loop: " << loop << "=======> Loss: " << oneLoopLoss << endl;
			break;
		}
	}
}

// transform weight into string
string NeuralNetwork::toString() const{
	ostringstream outstring;
	for(int i = 0; i < layers.size(); ++i){
		if(i == (layers.size()-1)){
			outstring << "Output Layer: " << endl;
			outstring << layers[i]->weightToString();		
		}else{
			outstring << "Hidden Layer " << (i+1) << " :" << endl;
			outstring << layers[i]->weightToString();
		}
	}
	return outstring.str();
}