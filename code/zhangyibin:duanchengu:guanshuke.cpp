#include <iostream>
#include "Matrix.h"
#include <vector>
#include "Layer.h"
#include "NeuralNetwork.h"
#include <random>
#include <fstream>
#include "Data.h"
#include <string>

using namespace std;

int main(){

	NeuralNetwork *nn = new NeuralNetwork();
	double learningRate;
	double loss;
	int loops;
	int numberOfLayers;
	bool isFinished = false;

	char trainName[] = "TrainData.csv";
	char testName[] = "TestData.csv";

	Data *train = new Data(trainName);
	Data *test = new Data(testName);

	// get normalized train data set
	vector<vector<double> > trainData = train->getInput();
	vector<vector<double> > trainTarget = train->getTarget();
	// get normalized test data set
	vector<vector<double> > testData = test->getInput();
	vector<vector<double> > testTarget = test->getTarget();

	do{
		// parameters settings
		cout << "Welcome to Silver Prediction Training System\n";
		cout << "Please enter learning rate: ";
		cin >> learningRate;
		nn->setLearningRate(learningRate);
		cout << "Please enter loss toleration: ";
		cin >> loss;
		nn->setLossToleration(loss);
		cout << "Please enter max traninig loop: ";
		cin >> loops;
		nn->setMaxLoops(loops);
		cout << "Please enter the number of hidden layers in NeuralNetwork: ";
		cin >> numberOfLayers;
		vector<int> layerNeurals;
		for(int i = 0; i < numberOfLayers; ++i){
			cout << "Please enter the number of neurons in hidden layer " << (i+1) << " : ";
			int n;
			cin >> n;
			layerNeurals.push_back(n);
		}
		nn->setLayers(layerNeurals);

		// train training data set
		nn->training(trainData, trainTarget);
		cout << "Train data:" << endl;
		nn->score(trainData, trainTarget);

		// finish training, and output weights
		cout << "Finish Training? (y/n)";
		string finish;
		cin >> finish;
		if(finish == "y"){
			isFinished = true;
			cout << nn->toString();

			ofstream outfile;
			outfile.open("FinalWeight.txt");

			outfile << nn->toString() << endl;
			outfile.close();
		}
	}while(!isFinished);
	
	// output test results
	cout << "Test data:" << endl;
	nn->score(testData, testTarget);

	return 0;
}