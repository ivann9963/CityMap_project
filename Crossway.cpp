#include "Crossway.h"

Crossway::Crossway(string name)
{
	this->name = name;
}

void Crossway::addCrossways(string name, int num)
{
	linkedCrossways.insert({ name, num }); // linkedCrossways.insert(pair<string, int>(name, num));
}

string Crossway::getName() const
{
	return name;
}

map<string, int> Crossway::getLinkedCrossways() const
{
	return linkedCrossways;
}


ostream & operator<<(ostream & os, const Crossway & arg)
{
	os << arg.name << " ";
	for ( auto it : arg.linkedCrossways)
	{
		os << it.first << " " << it.second << " ";
	}
	return os;
}

bool operator==(const Crossway & lhs, const Crossway & rhs)
{
	return lhs.getName() == rhs.getName();
}
