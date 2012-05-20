#include "Foret.h"
#include "cmath"
#include <time.h>

Arbre::Arbre() : x(0), y(0), _age(0), _taille(0), _radius(0)
{

}

Arbre::Arbre(double _x, double _y) : x(_x), y(_y), _age(0), _taille(0), _radius(0)
{

}

Arbre::Arbre(int age, double taille) : _age(age), _taille(taille), _radius(taille)
{

}
double Arbre::getX() const
{
	return x;
}
double Arbre::getY() const
{
	return y;
}

int Arbre::getAge() const
{
	return _age;
}
double Arbre::getTaille() const
{
	return _taille;
}

double Arbre::getRadius() const
{
	return _radius;
}

bool Arbre::isInRadius(Arbre a)
{
	return( pow((x-a.getX()), 2) + pow((y-a.getY()),2) < a.getRadius() );
}

void Arbre::setAge(int age)
{
	_age = age;
}

void Arbre::setTaille(double taille)
{
	_taille = taille;
}

bool Arbre::lifeProba(double proba)
{

	/* proba entre 0 et 1 */
	srand ( (unsigned int)time(NULL) );
	return (proba > (double)rand()/(double)RAND_MAX);

}

bool Arbre::grow()
{
	if(_age < 100)
	{
		_age ++;
		_taille += 0.1;
		_radius = _taille;
		return true;
	}
	return false;
}

Foret::Foret()
{
	_arbres = QVector<Arbre>();
}

void Foret::addArbre(Arbre a)
{
	_arbres.append(a);
}

void Foret::killArbre(int i)
{
	_arbres.remove(i);
}

Arbre Foret::getArbre(int i)
{
	return _arbres[i];
}