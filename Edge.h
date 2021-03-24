#pragma once
#include<string>
using namespace std;
struct Edge
{
private:
	string fromV;
	string to;                 /// № на втория край на реброто (първият е индексът на поредния елемент от вектора)
	int nom;                /// № на реброто
	int endV;
public:
	Edge(string destV, int nomE);
	Edge(string fromV, string toV, int nomE);
	Edge(string fromV, string toV, int nomE, int endV);
	bool operator<(const Edge& arg) const;
	void setTo(string v);
	void setFrom(string v);
	void setNom(int n);
	int getEndV() const;
	string getTo() const;
	string getFrom() const;
	int getNom() const;
};
