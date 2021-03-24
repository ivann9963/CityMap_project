#pragma once
#include<string>
using namespace std;
struct Edge
{
private:
	string fromV;
	string to;                 /// � �� ������ ���� �� ������� (������� � �������� �� �������� ������� �� �������)
	int nom;                /// � �� �������
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
