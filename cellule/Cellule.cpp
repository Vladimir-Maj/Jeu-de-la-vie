#include "cellule/Cellule.h"

Cellule::Cellule(int index, bool b, int max_x) {
	x = index % max_x;
	y = (index - x) / max_x;
	val = b;
	this->index = index;
}


void Cellule::afficher() const {
	std::cout << x;
	std::cout << y;
	std::cout << val;
}
int Cellule::return_index() const {
	return index;
}

int Cellule::return_x() const
{
	return x;
}

int Cellule::return_y() const
{
	return y;
}

int Cellule::return_state() const
{
	return val;
}

void Cellule::change_state(bool u) 
{
	val = u;
}