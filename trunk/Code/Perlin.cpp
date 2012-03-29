#include "Perlin.h"

void Perlin::initBruit2D(int l, int h, int p, int n)
{
    nombre_octaves2D = n;
    if(taille != 0)
	{
        free(valeurs2D);
	}
    longueur = l;
    hauteur = h;
    pas2D = p;
    //longueur_max = (int) ceil(longueur * pow(2., nombre_octaves2D  - 1)  / pas2D);
    //int hauteur_max = (int) ceil(hauteur * pow(2., nombre_octaves2D  - 1)  / pas2D);

	//V1
	//longueur_max = (int) ceil(longueur * nombre_octaves2D*2. / pas2D);
	//int hauteur_max = (int) ceil(hauteur * nombre_octaves2D*2. / pas2D);

		//V2
	longueur_max = longueur;
	int hauteur_max = hauteur;

    valeurs2D = (double*) malloc(sizeof(double) * longueur_max * hauteur_max);

    srand(time(NULL));
    int i;
    for(i = 0; i < longueur_max * hauteur_max; i++)
	{
        valeurs2D[i] = ((double) rand()) / RAND_MAX;
	}
}

void Perlin::destroyBruit2D()
{
    if(longueur != 0)
	{
        free(valeurs2D);
	}
    longueur = 0;
}

double Perlin::bruit2D(int i, int j)
{
    return valeurs2D[i * longueur_max + j];
}

double Perlin::fonction_bruit2D(double x, double y) 
{
   int i = (int) (x / pas2D);
   int j = (int) (y / pas2D);
   return interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / pas2D, 1), fmod(y / pas2D, 1));
}

double Perlin::bruit_coherent2D(double x, double y, double persistance)
{
	double somme = 0;
	double p = 1;
	int f = 1;
	int i;

	for(i = 0 ; i < nombre_octaves2D ; i++)
	{
		somme += p * fonction_bruit2D(x * f, y * f);
		p *= persistance;
		f *= 2;
	}
	return somme * (1 - persistance) / (1 - p);
}