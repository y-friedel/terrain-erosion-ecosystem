#ifndef __FORET__H__
#define __FORET__H__
#include "maya.h"
#include "Terrain.h"

enum TreeType
{
	TREETYPE_POMMIER,
	TREETYPE_SAPIN,
};


class Arbre
{
protected:
	double x;
	double y;
	int _age;
	double _taille;
	double _radius;
	MayaGeometry _mgArbre;
	int _treeType;

public:
	Arbre();
	Arbre(double _x, double _y);
	Arbre(double _x, double _y, int age, double taille);

	double getX() const;
	double getY() const;
	int getAge() const;
	double getTaille() const;
	double getRadius() const;
	int getTreeType() const {return _treeType;};

	bool isInRadius(Arbre a);

	void setAge(int age);
	void setTaille(double taille);

	bool lifeProba(double proba);

	bool grow();
};

class Pommier : public Arbre
{
protected:
	static const int treeType = TREETYPE_POMMIER;
public:
	Pommier(double _x, double _y, double taille);
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
	void foretToMGS(Terrain* ter, QVector<MayaGeometrySet>& vec_mgs);
};

#endif
