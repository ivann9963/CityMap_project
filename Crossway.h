#pragma once
#include <string>
#include <map>
#include <vector>
#include <ostream>
using namespace std;
class Crossway
{
private:
	string name;	
	map<string, int> linkedCrossways;
	// here we save all linked crossways for one crossway 
	// between current crossways to a another crossway there can be only 1 street

public:
	Crossway() = default;

	Crossway(string name);
	Crossway(string name, map<string, int> mCrossways);

	string getName() const;
	map<string, int> getLinkedCrossways() const;

	void addCrossways(string name, int);
	
	friend bool operator==(const Crossway& lhs, const Crossway& rhs);
	
	friend ostream& operator<<(ostream &os, const Crossway& arg);
};

