#include "Data.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
// get file data
Data::Data(char filename[]){
	csvdata intp;
	csvtarget tgt;
	FILE* fp;
	fp = fopen(filename, "r");
	while (1) {
		fscanf(fp, "%lf,%lf,%lf,%lf,%lf", &tgt.target1, &intp.cpi, &intp.usd, &intp.xau, &intp.oil);
		// cout << intp.cpi << endl;
		incsv.push_back(intp);
		tcsv.push_back(tgt);
		if (feof(fp)) break;
	}
	fclose(fp);
}

// get normalize data
vector<vector<double> > Data::getInput(){
	vector<double> cpiList;
	vector<double> usdList;
	vector<double> xauList;
	vector<double> oilList;

	for (int i = 0; i < incsv.size(); ++i){
		cpiList.push_back(incsv[i].cpi);
		usdList.push_back(incsv[i].usd);
		xauList.push_back(incsv[i].xau);
		oilList.push_back(incsv[i].oil);
	}

	cpiList = normalizeData(cpiList);
	usdList = normalizeData(usdList);
	xauList = normalizeData(xauList);
	oilList = normalizeData(oilList);

	for (int i = 0; i < cpiList.size(); ++i){
		vector<double> singleInput;
		// cout << cpiList[i] << endl;
		singleInput.push_back(cpiList[i]);
		singleInput.push_back(usdList[i]);
		singleInput.push_back(xauList[i]);
		singleInput.push_back(oilList[i]);

		input.push_back(singleInput);
	}

	return input;
}

// get target label
vector<vector<double> > Data::getTarget(){
	vector<double> t1;
	vector<double> t2;

	for (int i = 0; i < tcsv.size(); ++i){
		t1.push_back(tcsv[i].target1);
	}

	for (int i = 0; i < t1.size(); ++i){
		vector<double> singleTarget;
		singleTarget.push_back(t1[i]);
		target.push_back(singleTarget);
	}
	return target;
}

// normalize data
vector<double> Data::normalizeData(vector<double> d){
	double avg = dataAverage(d);
	double std = dataStd(d);
	vector<double> res;
	for (int i = 0; i < d.size(); ++i){
		res.push_back((d[i] - avg) / std);
	}
	return res;
}

// calculate average
double Data::dataAverage(vector<double> d){
	double sum = 0.0;
	int l = d.size();
	for (int i = 0; i < l; ++i){
		sum += d[i];
	}
	return sum / l;
}

// calculate standard deviation
double Data::dataStd(vector<double> d){
	int l = d.size();
	double avg = dataAverage(d);
	double std = 0.0;
	for (int i = 0; i < l; ++i){
		std += pow(d[i] - avg, 2);
	}
	std = sqrt(std / l);
	return std;
}