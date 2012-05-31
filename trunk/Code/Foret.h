#ifndef __FORET__H__
#define __FORET__H__
#include "maya.h"
#include "Terrain.h"


class Arbre
{
private:
	double x;
	double y;
	int _age;
	double _taille;
	double _radius;

public:
	Arbre();
	Arbre(double _x, double _y);
	Arbre(double _x, double _y, int age, double taille);

	double getX() const;
	double getY() const;
	int getAge() const;
	double getTaille() const;
	double getRadius() const;

	bool isInRadius(Arbre a);

	void setAge(int age);
	void setTaille(double taille);

	bool lifeProba(double proba);

	bool grow();
};

class Foret
{
private:
	QVector<Arbre> _arbres;

public:
	Foret();
	void addArbre(Arbre a);
	void killArbre(int i);
	Arbre getArbre(int i);
	void allGrow();
	
	void fillTerrain(Terrain* ter, int nb_arbres, int type);
	MayaGeometrySet foretToMGS(Terrain* ter);
};

#endif
