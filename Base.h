#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Base
{
protected:
	istream &in;
	ostream &out;
	virtual void processInput(const vector<string>& arg) = 0;

public:
	static vector<string> splitLine(const string& Line);
	Base(istream &in, ostream &out);
	virtual ~Base();
	void start();
};

