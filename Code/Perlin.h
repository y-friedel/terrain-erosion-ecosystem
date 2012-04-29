#ifndef __PERLIN__
#define __PERLIN__

#include "Stuff.h"

class Perlin {

public:
	int pas2D;
	int nombre_octaves2D;
	int taille;
	int hauteur;
	int longueur;
	int longueur_max;
	double* valeurs2D;

public:
	Perlin();
	void initBruit2D(int longueur, int hauteur, int pas, int octaves);
	double bruit2D(int i, int j);
	double fonction_bruit2D(double x, double y);
	double bruit_coherent2D(double x, double y, double persistance);
	void destroyBruit2D();

};

#endif