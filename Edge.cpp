#include "Edge.h"

Edge::Edge(string destV, int nomE)
{
	to = destV;
	nom = nomE;
}

Edge::Edge(string fromV, string toV, int nomE)
{
	this->fromV = fromV;
	to = toV;
	nom = nomE;
}

Edge::Edge(string fromV, string toV, int nomE, int endV)
{
	this->fromV = fromV;
	to = toV;
	nom = nomE;
	this->endV = endV;
}

string Edge::getFrom() const
{
	return fromV;
}

string Edge::getTo() const
{
	return to;
}

int Edge::getNom() const
{
	return nom;
}


void Edge::setNom(int n)
{
	nom = n;
}
void Edge::setFrom(string n)
{
	fromV = n;
}

void Edge::setTo(string v)
{
	to = v;
}
int Edge::getEndV() const
{
	return endV;
}
bool Edge::operator<(const Edge& arg) const
{
	return nom < arg.nom;
}
