#pragma once
#include "Base.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <utility>
#include <cassert>
#include "Edge.h"
#include "Crossway.h"
using namespace std;

class System : public Base
{
	// key - име на кръстовището
	// Crossway - самото кръстовище
	//map<string, Crossway> mCrossways;
protected:
	void processInput(const vector<string> &arg);
public:
	map<string, Crossway> mCrossways;
	static System* fromStream(istream& in);

	System(istream &in, ostream& out);
	//virtual ~System();

	void openFromFile(const vector<string> &vsplitLine);
	void printAllCrossways(const vector<string> &vsplitLine);

	bool BFS(const vector<string> &vsplitLine);
	bool DFS(string numCrossways, map<string, bool> &visited, string par);
	void toDFS(const vector<string>& vsplitLine);
	bool isTour(const vector<string>& vsplitLine);
	void blindAlleys(const vector<string>& vsplitLine);
	bool reachAllCrossways(const vector<string> &vsplitLine);

	//list<Edge> bellmanFord(const vector<string>& vsplitLine) const;
	//void Euler(vector<vector<Edge>>& vE, int beg);
	//void dfs(vector<vector<Edge>>& vE, int beg, stack<Edge>& tmp, map<Edge, bool> visited);
};

