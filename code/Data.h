#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// define data base structure, and get training and test data set
struct csvdata {
public:
	double cpi;
	double usd;
	double xau;
	double oil;
};

struct csvtarget
{
public:
	double target1;
};

class Data
{
public:
	Data(char[]);
	~Data();
	std::vector<std::vector<double> >getInput();
	std::vector<std::vector<double> >getTarget();
	std::vector<double> normalizeData(std::vector<double>);

private:
	std::vector<std::vector<double> > input;
	std::vector<std::vector<double> > target;
	std::vector<csvdata> incsv;
	std::vector<csvtarget> tcsv;

	double dataAverage(std::vector<double>);
	double dataStd(std::vector<double>);
};